#include <windows.h>
#include <wincrypt.h>
#include <iostream>
#include <fstream>
#include <iomanip>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: hashfile.exe <filename>" << std::endl;
        return 1;
    }

    const char* filename = argv[1];

    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Cannot open file: " << filename << std::endl;
        return 1;
    }

    HCRYPTPROV hProv = 0;
    HCRYPTHASH hHash = 0;
    HCRYPTHASH hHashDup = 0;

    if (!CryptAcquireContextA(&hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT)) {
        std::cerr << "CryptAcquireContext failed. Error: " << GetLastError() << std::endl;
        return 1;
    }

    if (!CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash)) {
        std::cerr << "CryptCreateHash failed. Error: " << GetLastError() << std::endl;
        CryptReleaseContext(hProv, 0);
        return 1;
    }

    char buffer[1024];
    while (file.good()) {
        file.read(buffer, sizeof(buffer));
        std::streamsize bytesRead = file.gcount();

        if (bytesRead > 0) {
            if (!CryptHashData(hHash, reinterpret_cast<BYTE*>(buffer), (DWORD)bytesRead, 0)) {
                std::cerr << "CryptHashData failed. Error: " << GetLastError() << std::endl;
                CryptDestroyHash(hHash);
                CryptReleaseContext(hProv, 0);
                return 1;
            }
        }
    }

    if (!CryptDuplicateHash(hHash, NULL, 0, &hHashDup)) {
        std::cerr << "CryptDuplicateHash failed. Error: " << GetLastError() << std::endl;
        CryptDestroyHash(hHash);
        CryptReleaseContext(hProv, 0);
        return 1;
    }

    DWORD hashSize = 0;
    if (!CryptGetHashParam(hHashDup, HP_HASHVAL, NULL, &hashSize, 0)) {
        std::cerr << "CryptGetHashParam(size) failed. Error: " << GetLastError() << std::endl;
        CryptDestroyHash(hHashDup);
        CryptDestroyHash(hHash);
        CryptReleaseContext(hProv, 0);
        return 1;
    }

    BYTE* hash = new BYTE[hashSize];

    if (!CryptGetHashParam(hHashDup, HP_HASHVAL, hash, &hashSize, 0)) {
        std::cerr << "CryptGetHashParam(data) failed. Error: " << GetLastError() << std::endl;
        delete[] hash;
        CryptDestroyHash(hHashDup);
        CryptDestroyHash(hHash);
        CryptReleaseContext(hProv, 0);
        return 1;
    }

    std::cout << "MD5(" << filename << ") = ";
    for (DWORD i = 0; i < hashSize; ++i) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    std::cout << std::endl;

    delete[] hash;
    CryptDestroyHash(hHashDup);
    CryptDestroyHash(hHash);
    CryptReleaseContext(hProv, 0);

    return 0;
}