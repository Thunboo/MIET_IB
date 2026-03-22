HCRYPTPROV hProv;
HCRYPTKEY hKey;

CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT);
CryptGenKey(hProv, CALG_RC4, CRYPT_EXPORTABLE, &hKey);

char data[] = "Secret";
DWORD len = strlen(data);

CryptEncrypt(hKey, 0, TRUE, 0, (BYTE*)data, &len, sizeof(data));

std::cout << "Encrypted: " << data << std::endl;

CryptDecrypt(hKey, 0, TRUE, 0, (BYTE*)data, &len);

std::cout << "Decrypted: " << data << std::endl;

CryptDestroyKey(hKey);
CryptReleaseContext(hProv, 0);