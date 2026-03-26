#include <windows.h>
#include <wincrypt.h>
#include <iostream>
#include <iomanip>
#include <cstring>

void printHex(const BYTE* data, DWORD len, const char* title) {
    std::cout << title;
    for (DWORD i = 0; i < len; ++i) {
        std::cout << std::hex << std::setw(2) << std::setfill('0')
                  << (int)data[i] << " ";
    }
    std::cout << std::dec << std::endl;
}

int main() {
    HCRYPTPROV hProv = 0;
    HCRYPTKEY hPublicKey = 0;
    HCRYPTKEY hSessionKey = 0;

    const char* containerName = "MyKeyContainer";

    // 1. Открываем контейнер
    if (!CryptAcquireContextA(&hProv, containerName, NULL, PROV_RSA_FULL, 0)) {
        std::cerr << "CryptAcquireContext failed: " << GetLastError() << std::endl;
        return 1;
    }

    std::cout << "Container opened." << std::endl;

    // 2. Получаем открытый ключ обмена
    if (!CryptGetUserKey(hProv, AT_KEYEXCHANGE, &hPublicKey)) {
        std::cerr << "CryptGetUserKey failed: " << GetLastError() << std::endl;
        CryptReleaseContext(hProv, 0);
        return 1;
    }

    std::cout << "Public key for key exchange retrieved." << std::endl;

    // 3. Генерируем сеансовый симметричный ключ
    if (!CryptGenKey(hProv, CALG_RC4, CRYPT_EXPORTABLE, &hSessionKey)) {
        std::cerr << "CryptGenKey failed: " << GetLastError() << std::endl;
        CryptDestroyKey(hPublicKey);
        CryptReleaseContext(hProv, 0);
        return 1;
    }

    std::cout << "Session key generated." << std::endl;

    // 4. Шифруем данные
    BYTE data[128] = "Secret hybrid message";
    DWORD dataLen = (DWORD)strlen((char*)data);

    std::cout << "Original: " << data << std::endl;

    if (!CryptEncrypt(hSessionKey, 0, TRUE, 0, data, &dataLen, sizeof(data))) {
        std::cerr << "CryptEncrypt failed: " << GetLastError() << std::endl;
        CryptDestroyKey(hSessionKey);
        CryptDestroyKey(hPublicKey);
        CryptReleaseContext(hProv, 0);
        return 1;
    }

    printHex(data, dataLen, "Encrypted data: ");

    // 5. Экспортируем (т.е. шифруем) сеансовый ключ открытым RSA-ключом
    DWORD blobLen = 0;
    if (!CryptExportKey(hSessionKey, hPublicKey, SIMPLEBLOB, 0, NULL, &blobLen)) {
        std::cerr << "CryptExportKey(size) failed: " << GetLastError() << std::endl;
        CryptDestroyKey(hSessionKey);
        CryptDestroyKey(hPublicKey);
        CryptReleaseContext(hProv, 0);
        return 1;
    }

    BYTE* blob = new BYTE[blobLen];

    if (!CryptExportKey(hSessionKey, hPublicKey, SIMPLEBLOB, 0, blob, &blobLen)) {
        std::cerr << "CryptExportKey(data) failed: " << GetLastError() << std::endl;
        delete[] blob;
        CryptDestroyKey(hSessionKey);
        CryptDestroyKey(hPublicKey);
        CryptReleaseContext(hProv, 0);
        return 1;
    }

    printHex(blob, blobLen, "Exported session key (SIMPLEBLOB): ");

    delete[] blob;
    CryptDestroyKey(hSessionKey);
    CryptDestroyKey(hPublicKey);
    CryptReleaseContext(hProv, 0);

    std::cout << "Done." << std::endl;
    return 0;
}