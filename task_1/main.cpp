#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cryptopp/cryptlib.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>
#include <cryptopp/sha.h>
//подключение библиотек
using namespace std;
int main ()
{
    CryptoPP::SHA1 hash;

    cout << "Имя: " << hash.AlgorithmName() << endl; //ввод
    cout << "Размер хэша: " << hash.DigestSize() << endl;
    cout << "Размер блока: " << hash.BlockSize() << endl;

    string soo = ""; //переменная , куда кладется все из файла
    string stroka;
    ifstream f("/home/student/soo.txt"); //считывает файл в бинарном виде
    while (getline(f, stroka)) {
        soo += stroka;     //кладет в переменную
    }


    cout << "Сообщение: " << soo << endl; //вывод сообщения
    vector<byte> digest(hash.DigestSize()); //

    hash.Update((const byte*)soo.data(), soo.size()); 
    hash.Final(digest.data());

    cout << "Хэш: ";
    CryptoPP::StringSource(digest.data(), digest.size(), true, new CryptoPP::HexEncoder(new CryptoPP::FileSink(cout))); //приводит в адекватный вид
    cout << endl;
    return 0;
}
