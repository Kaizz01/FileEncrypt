#include <iostream>
#include <fstream>
#include "FileEncryptor.h"

int main() {
    std::string sourceFile, destFile;
    int mode, shift = 0;
    char key = '\0';
    bool isEncryption;

    std::cout << "Entrez le nom du fichier source : ";
    std::cin >> sourceFile;

    std::ifstream testFile(sourceFile);
    if (!testFile) {
        std::cerr << "Erreur : le fichier source '" << sourceFile << "' ne peut pas etre ouvert. Verifiez le chemin et reessayez." << std::endl;
        return 1;
    }
    testFile.close();

    std::cout << "Voulez-vous chiffrer (1) ou dechiffrer (0) le message ? ";
    std::cin >> isEncryption;

    std::cout << "Entrez le nom du fichier de destination (laisser vide pour modifier le fichier source) : ";
    std::cin.ignore();
    std::getline(std::cin, destFile);

    std::cout << "Choisissez le mode de chiffrement (1: Cesar, 2: XOR, 3: Combine) : ";
    std::cin >> mode;

    if (mode == 1 || mode == 3) {
        std::cout << "Entrez le decalage pour le chiffrement Cesar : ";
        std::cin >> shift;
    }

    if (mode == 2 || mode == 3) {
        std::cout << "Entrez la cle pour le chiffrement XOR : ";
        std::cin >> key;
    }

    FileEncryptor::processFile(sourceFile, destFile, mode, shift, key, isEncryption);

    std::cout << "Operation terminee !" << std::endl;
    return 0;
}
