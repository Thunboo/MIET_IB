#include <windows.h>
#include <wincrypt.h>
#include <iostream>
#include <cstring>

int main() {
    HCRYPTPROV hProv = 0;
    HCRYPTHASH hHash = 0;
    HCRYPTKEY hKey = 0;

    // 1. Получаем контекст
    if (!CryptAcquireContextA(&hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT)) {
        std::cerr << "CryptAcquireContext failed: " << GetLastError() << std::endl;
        return 1;
    }

    // 2. Хеш пароля
    if (!CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash)) {
        std::cerr << "CryptCreateHash failed: " << GetLastError() << std::endl;
        return 1;
    }

    const char* password = "mypassword";

    if (!CryptHashData(hHash, (BYTE*)password, strlen(password), 0)) {
        std::cerr << "CryptHashData failed: " << GetLastError() << std::endl;
        return 1;
    }

    // 3. Получаем тот же ключ
    if (!CryptDeriveKey(hProv, CALG_RC4, hHash, 0, &hKey)) {
        std::cerr << "CryptDeriveKey failed: " << GetLastError() << std::endl;
        return 1;
    }

    // ЗАШИФРОВАННЫЕ данные
    BYTE data[] = {
        0x20, 0x49, 0x75, 0x12, 0x17, 0x04, 0x15, 0x1E, 0xC1, 0x77, 0x68, 0x37, 0xE6, 0x5C
    };

    DWORD dataLen = sizeof(data);

    std::cout << "Encrypted: ";
    for (DWORD i = 0; i < dataLen; i++) {
        printf("%02X ", data[i]);
    }
    std::cout << std::endl;

    // 4. Расшифровка
    if (!CryptDecrypt(hKey, 0, TRUE, 0, data, &dataLen)) {
        std::cerr << "CryptDecrypt failed: " << GetLastError() << std::endl;
        return 1;
    }

    std::cout << "Decrypted: " << (char*)data << std::endl;

    // очистка
    CryptDestroyKey(hKey);
    CryptDestroyHash(hHash);
    CryptReleaseContext(hProv, 0);

    return 0;
}