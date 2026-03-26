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
    HCRYPTKEY hKeyExchange = 0;
    HCRYPTKEY hSessionKey = 0;
    HCRYPTKEY hImportedSessionKey = 0;

    const char* containerName = "MyKeyContainer";

    if (!CryptAcquireContextA(&hProv, containerName, NULL, PROV_RSA_FULL, 0)) {
        std::cerr << "CryptAcquireContext failed: " << GetLastError() << std::endl;
        return 1;
    }

    std::cout << "Container opened." << std::endl;

    if (!CryptGetUserKey(hProv, AT_KEYEXCHANGE, &hKeyExchange)) {
        std::cerr << "CryptGetUserKey failed: " << GetLastError() << std::endl;
        CryptReleaseContext(hProv, 0);
        return 1;
    }

    std::cout << "Key exchange key retrieved." << std::endl;

    if (!CryptGenKey(hProv, CALG_RC4, CRYPT_EXPORTABLE, &hSessionKey)) {
        std::cerr << "CryptGenKey failed: " << GetLastError() << std::endl;
        CryptDestroyKey(hKeyExchange);
        CryptReleaseContext(hProv, 0);
        return 1;
    }

    std::cout << "Session key generated." << std::endl;

    BYTE data[128] = "Secret hybrid message";
    DWORD dataLen = (DWORD)strlen((char*)data);

    std::cout << "Original text: " << data << std::endl;

    if (!CryptEncrypt(hSessionKey, 0, TRUE, 0, data, &dataLen, sizeof(data))) {
        std::cerr << "CryptEncrypt failed: " << GetLastError() << std::endl;
        CryptDestroyKey(hSessionKey);
        CryptDestroyKey(hKeyExchange);
        CryptReleaseContext(hProv, 0);
        return 1;
    }

    printHex(data, dataLen, "Encrypted data: ");

    DWORD blobLen = 0;
    if (!CryptExportKey(hSessionKey, hKeyExchange, SIMPLEBLOB, 0, NULL, &blobLen)) {
        std::cerr << "CryptExportKey(size) failed: " << GetLastError() << std::endl;
        CryptDestroyKey(hSessionKey);
        CryptDestroyKey(hKeyExchange);
        CryptReleaseContext(hProv, 0);
        return 1;
    }

    BYTE* keyBlob = new BYTE[blobLen];

    if (!CryptExportKey(hSessionKey, hKeyExchange, SIMPLEBLOB, 0, keyBlob, &blobLen)) {
        std::cerr << "CryptExportKey(data) failed: " << GetLastError() << std::endl;
        delete[] keyBlob;
        CryptDestroyKey(hSessionKey);
        CryptDestroyKey(hKeyExchange);
        CryptReleaseContext(hProv, 0);
        return 1;
    }

    printHex(keyBlob, blobLen, "Exported session key (SIMPLEBLOB): ");

    if (!CryptImportKey(hProv, keyBlob, blobLen, hKeyExchange, 0, &hImportedSessionKey)) {
        std::cerr << "CryptImportKey failed: " << GetLastError() << std::endl;
        delete[] keyBlob;
        CryptDestroyKey(hSessionKey);
        CryptDestroyKey(hKeyExchange);
        CryptReleaseContext(hProv, 0);
        return 1;
    }

    std::cout << "Session key imported back." << std::endl;

    if (!CryptDecrypt(hImportedSessionKey, 0, TRUE, 0, data, &dataLen)) {
        std::cerr << "CryptDecrypt failed: " << GetLastError() << std::endl;
        delete[] keyBlob;
        CryptDestroyKey(hImportedSessionKey);
        CryptDestroyKey(hSessionKey);
        CryptDestroyKey(hKeyExchange);
        CryptReleaseContext(hProv, 0);
        return 1;
    }

    std::cout << "Decrypted text: " << data << std::endl;

    delete[] keyBlob;
    CryptDestroyKey(hImportedSessionKey);
    CryptDestroyKey(hSessionKey);
    CryptDestroyKey(hKeyExchange);
    CryptReleaseContext(hProv, 0);

    std::cout << "Done." << std::endl;
    return 0;
}