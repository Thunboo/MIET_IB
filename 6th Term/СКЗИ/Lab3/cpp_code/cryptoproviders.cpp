#include <windows.h>
#include <wincrypt.h>
#include <iostream>

int main() {
    DWORD index;
    DWORD type;
    DWORD nameSize;

    std::cout << "=== PROVIDERS ===" << std::endl;

    index = 0;
    while (true) {
        nameSize = 0;

        if (!CryptEnumProvidersA(index, NULL, 0, &type, NULL, &nameSize)) {
            break;
        }

        char* name = new char[nameSize];

        if (CryptEnumProvidersA(index, NULL, 0, &type, name, &nameSize)) {
            std::cout << "Index: " << index << std::endl;
            std::cout << "Provider name: " << name << std::endl;
            std::cout << "Provider type: " << type << std::endl;
            std::cout << "------------------------------" << std::endl;
        } else {
            std::cerr << "CryptEnumProvidersA failed at index " << index
                      << ", error: " << GetLastError() << std::endl;
            delete[] name;
            return 1;
        }

        delete[] name;
        index++;
    }

    std::cout << std::endl;
    std::cout << "=== PROVIDER TYPES ===" << std::endl;

    index = 0;
    while (true) {
        nameSize = 0;

        if (!CryptEnumProviderTypesA(index, NULL, 0, &type, NULL, &nameSize)) {
            break;
        }

        char* name = new char[nameSize];

        if (CryptEnumProviderTypesA(index, NULL, 0, &type, name, &nameSize)) {
            std::cout << "Index: " << index << std::endl;
            std::cout << "Type name: " << name << std::endl;
            std::cout << "Type ID: " << type << std::endl;
            std::cout << "------------------------------" << std::endl;
        } else {
            std::cerr << "CryptEnumProviderTypesA failed at index " << index
                      << ", error: " << GetLastError() << std::endl;
            delete[] name;
            return 1;
        }

        delete[] name;
        index++;
    }

    return 0;
}