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

    // 2. Создаём хеш (из пароля)
    if (!CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash)) {
        std::cerr << "CryptCreateHash failed: " << GetLastError() << std::endl;
        return 1;
    }

    const char* password = "mypassword";

    if (!CryptHashData(hHash, (BYTE*)password, strlen(password), 0)) {
        std::cerr << "CryptHashData failed: " << GetLastError() << std::endl;
        return 1;
    }

    // 3. Получаем ключ из хеша
    if (!CryptDeriveKey(hProv, CALG_RC4, hHash, 0, &hKey)) {
        std::cerr << "CryptDeriveKey failed: " << GetLastError() << std::endl;
        return 1;
    }

    // 4. Данные для шифрования
    char data[128] = "Secret message";
    DWORD dataLen = strlen(data);

    std::cout << "Original: " << data << std::endl;

    // 5. Шифрование
    if (!CryptEncrypt(hKey, 0, TRUE, 0, (BYTE*)data, &dataLen, sizeof(data))) {
        std::cerr << "CryptEncrypt failed: " << GetLastError() << std::endl;
        return 1;
    }

    std::cout << "Encrypted: ";
    for (DWORD i = 0; i < dataLen; i++) {
        printf("%02X ", (unsigned char)data[i]);
    }
    std::cout << std::endl;

    // Oчистка
    CryptDestroyKey(hKey);
    CryptDestroyHash(hHash);
    CryptReleaseContext(hProv, 0);

    return 0;
}