#include <windows.h>
#include <wincrypt.h>
#include <iostream>
#include <fstream>
#include <iomanip>

bool hashFile(HCRYPTPROV hProv, const char* filename, HCRYPTHASH& hHash) {
    if (!CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash)) {
        std::cerr << "CryptCreateHash failed: " << GetLastError() << std::endl;
        return false;
    }

    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Cannot open file: " << filename << std::endl;
        CryptDestroyHash(hHash);
        hHash = 0;
        return false;
    }

    char buffer[1024];
    while (file.good()) {
        file.read(buffer, sizeof(buffer));
        std::streamsize bytesRead = file.gcount();

        if (bytesRead > 0) {
            if (!CryptHashData(hHash, reinterpret_cast<BYTE*>(buffer), (DWORD)bytesRead, 0)) {
                std::cerr << "CryptHashData failed: " << GetLastError() << std::endl;
                CryptDestroyHash(hHash);
                hHash = 0;
                return false;
            }
        }
    }

    return true;
}

void printHex(const BYTE* data, DWORD len, const char* title) {
    std::cout << title;
    for (DWORD i = 0; i < len; ++i) {
        std::cout << std::hex << std::setw(2) << std::setfill('0')
                  << (int)data[i] << " ";
    }
    std::cout << std::dec << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: sign_verify.exe <filename>" << std::endl;
        return 1;
    }

    const char* filename = argv[1];
    const char* containerName = "MyKeyContainer";

    HCRYPTPROV hProv = 0;
    HCRYPTHASH hHashSign = 0;
    HCRYPTHASH hHashVerify = 0;
    HCRYPTKEY hPublicKey = 0;

    BYTE* signature = NULL;
    DWORD sigLen = 0;

    if (!CryptAcquireContextA(&hProv, containerName, NULL, PROV_RSA_FULL, 0)) {
        std::cerr << "CryptAcquireContext failed: " << GetLastError() << std::endl;
        return 1;
    }

    std::cout << "Container opened." << std::endl;

    // 1. Хеш файла для подписи
    if (!hashFile(hProv, filename, hHashSign)) {
        CryptReleaseContext(hProv, 0);
        return 1;
    }

    std::cout << "Hash for signing created." << std::endl;

    // 2. Узнаём размер подписи
    if (!CryptSignHashA(hHashSign, AT_SIGNATURE, NULL, 0, NULL, &sigLen)) {
        std::cerr << "CryptSignHash(size) failed: " << GetLastError() << std::endl;
        CryptDestroyHash(hHashSign);
        CryptReleaseContext(hProv, 0);
        return 1;
    }

    signature = new BYTE[sigLen];

    // 3. Формируем подпись
    if (!CryptSignHashA(hHashSign, AT_SIGNATURE, NULL, 0, signature, &sigLen)) {
        std::cerr << "CryptSignHash(data) failed: " << GetLastError() << std::endl;
        delete[] signature;
        CryptDestroyHash(hHashSign);
        CryptReleaseContext(hProv, 0);
        return 1;
    }

    std::cout << "Signature created." << std::endl;
    printHex(signature, sigLen, "Signature: ");

    // 4. Новый хеш для проверки
    if (!hashFile(hProv, filename, hHashVerify)) {
        delete[] signature;
        CryptDestroyHash(hHashSign);
        CryptReleaseContext(hProv, 0);
        return 1;
    }

    std::cout << "Hash for verification created." << std::endl;

    // 5. Получаем открытый ключ подписи
    if (!CryptGetUserKey(hProv, AT_SIGNATURE, &hPublicKey)) {
        std::cerr << "CryptGetUserKey failed: " << GetLastError() << std::endl;
        delete[] signature;
        CryptDestroyHash(hHashVerify);
        CryptDestroyHash(hHashSign);
        CryptReleaseContext(hProv, 0);
        return 1;
    }

    std::cout << "Public key for signature retrieved." << std::endl;

    // 6. Проверяем подпись
    BOOL result = CryptVerifySignatureA(hHashVerify, signature, sigLen, hPublicKey, NULL, 0);

    if (!result) {
        std::cerr << "CryptVerifySignature failed: " << GetLastError() << std::endl;
    } else {
        std::cout << "Signature verification: VERIFIED" << std::endl;
    }

    delete[] signature;
    CryptDestroyKey(hPublicKey);
    CryptDestroyHash(hHashVerify);
    CryptDestroyHash(hHashSign);
    CryptReleaseContext(hProv, 0);

    return result ? 0 : 1;
}