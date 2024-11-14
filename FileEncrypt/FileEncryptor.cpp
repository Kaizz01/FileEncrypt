#include "FileEncryptor.h"
#include <fstream>
#include <iostream>

std::string CaesarCipher::encrypt(const std::string& text, int shift) {
    std::string result = text;
    for (char& c : result) {
        c += shift;
    }
    return result;
}

std::string CaesarCipher::decrypt(const std::string& text, int shift) {
    std::string result = text;
    for (char& c : result) {
        c -= shift;
    }
    return result;
}

std::string XorCipher::encryptDecrypt(const std::string& text, char key) {
    std::string result = text;
    for (char& c : result) {
        if (c != '\n') {
            c ^= key;
        }
    }
    return result;
}

std::string CombinedCipher::encrypt(const std::string& text, int shift, char key) {
    std::string result = CaesarCipher::encrypt(text, shift);
    return XorCipher::encryptDecrypt(result, key);
}

std::string CombinedCipher::decrypt(const std::string& text, int shift, char key) {
    std::string result = XorCipher::encryptDecrypt(text, key);
    return CaesarCipher::decrypt(result, shift);
}

void FileEncryptor::processFile(const std::string& sourceFile, const std::string& destFile, int mode, int shift, char key, bool isEncryption) {
    std::ifstream inputFile(sourceFile);
    if (!inputFile) {
        std::cerr << "Erreur : le fichier source '" << sourceFile << "' ne peut pas �tre ouvert." << std::endl;
        return;
    }

    std::string content;
    std::string line;
    while (std::getline(inputFile, line)) {
        content += line + "\n";
    }
    inputFile.close();

    std::string processedContent;
    switch (mode) {
    case 1:
        processedContent = isEncryption ? CaesarCipher::encrypt(content, shift) : CaesarCipher::decrypt(content, shift);
        break;
    case 2:
        processedContent = XorCipher::encryptDecrypt(content, key);
        break;
    case 3:
        processedContent = isEncryption ? CombinedCipher::encrypt(content, shift, key) : CombinedCipher::decrypt(content, shift, key);
        break;
    default:
        std::cerr << "Mode de chiffrement invalide." << std::endl;
        return;
    }

    std::ofstream outputFile(destFile.empty() ? sourceFile : destFile);
    if (!outputFile) {
        std::cerr << "Erreur : le fichier de destination '" << (destFile.empty() ? sourceFile : destFile) << "' ne peut pas �tre ouvert." << std::endl;
        return;
    }

    outputFile << processedContent;
    outputFile.close();
}
