#include <windows.h>
#include <wincrypt.h>
#include <iostream>

int main() {
    HCRYPTPROV hProv = 0;
    HCRYPTKEY hKeyExchange = 0;
    HCRYPTKEY hSignature = 0;

    const char* containerName = "MyKeyContainer";

    // 1. Открываем существующий контейнер
    if (!CryptAcquireContextA(
            &hProv,
            containerName,
            NULL,
            PROV_RSA_FULL,
            0)) {
        std::cerr << "Cannot open container. Error: " << GetLastError() << std::endl;
        return 1;
    }

    std::cout << "Container opened." << std::endl;

    // 2. Получаем ключ обмена
    if (!CryptGetUserKey(hProv, AT_KEYEXCHANGE, &hKeyExchange)) {
        std::cerr << "Failed to get key exchange key. Error: " << GetLastError() << std::endl;
    } else {
        std::cout << "Key exchange key retrieved." << std::endl;
    }

    // 3. Получаем ключ подписи
    if (!CryptGetUserKey(hProv, AT_SIGNATURE, &hSignature)) {
        std::cerr << "Failed to get signature key. Error: " << GetLastError() << std::endl;
    } else {
        std::cout << "Signature key retrieved." << std::endl;
    }

    // 4. Удаляем ключи из памяти программы
    if (hKeyExchange) {
        CryptDestroyKey(hKeyExchange);
        std::cout << "Key exchange handle destroyed." << std::endl;
    }

    if (hSignature) {
        CryptDestroyKey(hSignature);
        std::cout << "Signature handle destroyed." << std::endl;
    }

    // 5. Закрываем контекст
    CryptReleaseContext(hProv, 0);

    // 6. УДАЛЯЕМ контейнер
    if (!CryptAcquireContextA(
            &hProv,
            containerName,
            NULL,
            PROV_RSA_FULL,
            CRYPT_DELETEKEYSET)) {

        std::cerr << "Failed to delete container. Error: " << GetLastError() << std::endl;
        return 1;
    }

    std::cout << "Container deleted." << std::endl;

    return 0;
}