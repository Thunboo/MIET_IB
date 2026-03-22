#include <windows.h>
#include <wincrypt.h>
#include <iostream>

int main() {
    HCRYPTPROV hProv = 0;
    HCRYPTKEY hKeyExchange = 0;
    HCRYPTKEY hSignature = 0;

    const char* containerName = "MyKeyContainer";

    if (!CryptAcquireContextA(
            &hProv,
            containerName,
            NULL,
            PROV_RSA_FULL,
            CRYPT_NEWKEYSET)) {

        DWORD err = GetLastError();

        if (err == NTE_EXISTS) {
            std::cout << "Container already exists. Opening existing container..." << std::endl;

            if (!CryptAcquireContextA(
                    &hProv,
                    containerName,
                    NULL,
                    PROV_RSA_FULL,
                    0)) {
                std::cerr << "Cannot open existing container. Error: " << GetLastError() << std::endl;
                return 1;
            }
        } else {
            std::cerr << "CryptAcquireContextA failed. Error: " << err << std::endl;
            return 1;
        }
    } else {
        std::cout << "New key container created: " << containerName << std::endl;
    }

    if (!CryptGenKey(hProv, AT_KEYEXCHANGE, CRYPT_EXPORTABLE, &hKeyExchange)) {
        std::cerr << "CryptGenKey (AT_KEYEXCHANGE) failed. Error: " << GetLastError() << std::endl;
        CryptReleaseContext(hProv, 0);
        return 1;
    }
    std::cout << "Key exchange key pair generated." << std::endl;

    if (!CryptGenKey(hProv, AT_SIGNATURE, CRYPT_EXPORTABLE, &hSignature)) {
        std::cerr << "CryptGenKey (AT_SIGNATURE) failed. Error: " << GetLastError() << std::endl;
        CryptDestroyKey(hKeyExchange);
        CryptReleaseContext(hProv, 0);
        return 1;
    }
    std::cout << "Signature key pair generated." << std::endl;

    CryptDestroyKey(hKeyExchange);
    CryptDestroyKey(hSignature);
    CryptReleaseContext(hProv, 0);

    std::cout << "Done." << std::endl;
    return 0;
}