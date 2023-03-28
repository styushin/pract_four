#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <cryptopp/cryptlib.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>
#include <cryptopp/aes.h>
#include <cryptopp/des.h>
#include <cryptopp/modes.h>
#include <cryptopp/osrng.h>
#include <cryptopp/sha.h>
#include <cryptopp/pwdbased.h>
#include <cryptopp/filters.h>

using namespace std;
using namespace CryptoPP;

class DES_CRYP
{
private:
  string filein;
  string fileout;
  string psw;
  string salt = "Добрый вечер дамы, добрый вечер господа";
public:
  DES_CRYP() = delete;
  DES_CRYP(const string& input, const string& output, const string& pass): filein(input), fileout(output), psw(pass) {};
  bool encrypt();
  bool decrypt();
};
