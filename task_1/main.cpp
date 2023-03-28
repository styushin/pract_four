#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cryptopp/cryptlib.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>
#include <cryptopp/sha.h>
using namespace std;
int main ()
{
    CryptoPP::SHA1 hash;

    cout << "Имя: " << hash.AlgorithmName() << endl;
    cout << "Размер хэша: " << hash.DigestSize() << endl;
    cout << "Размер блока: " << hash.BlockSize() << endl;

    string soo = "";
    string stroka;
    ifstream f("/home/student/soo.txt");
    while (getline(f, stroka)) {
        soo += stroka;
    }


    cout << "Сообщение: " << soo << endl;
    vector<byte> digest(hash.DigestSize());

    hash.Update((const byte*)soo.data(), soo.size());
    hash.Final(digest.data());

    cout << "Хэш: ";
    CryptoPP::StringSource(digest.data(), digest.size(), true, new CryptoPP::HexEncoder(new CryptoPP::FileSink(cout)));
    cout << endl;
    return 0;
}
