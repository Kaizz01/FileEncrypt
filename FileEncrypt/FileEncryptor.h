#pragma once
#include <string>

class CaesarCipher {
public:
    static std::string encrypt(const std::string& text, int shift);
    static std::string decrypt(const std::string& text, int shift);
};

class XorCipher {
public:
    static std::string encryptDecrypt(const std::string& text, char key);
};

class CombinedCipher {
public:
    static std::string encrypt(const std::string& text, int shift, char key);
    static std::string decrypt(const std::string& text, int shift, char key);
};

class FileEncryptor {
public:
    static void processFile(const std::string& sourceFile, const std::string& destFile, int mode, int shift, char key, bool isEncryption);
};