#include "DES.h"

bool DES_CRYP::encrypt()
{
    SecByteBlock key(DES::DEFAULT_KEYLENGTH);
    PKCS12_PBKDF<SHA1> pbkdf;
    pbkdf.DeriveKey(key.data(), key.size(), 0, (byte*)psw.data(), psw.size(), (byte*)salt.data(), salt.size(), 1024, 0.0f);
    cout << "Key: ";
    StringSource(key.data(), key.size(), true, new HexEncoder( new FileSink(cout) ));

    AutoSeededRandomPool prng;
    byte iv[DES::BLOCKSIZE];
    prng.GenerateBlock(iv, sizeof(iv));
    ofstream f_iv(string(fileout + ".iv").c_str(), ios::out | ios::binary);
    f_iv.write((char*)iv, DES::BLOCKSIZE);
    f_iv.close();
    cout << "\nIV recorded in: " << fileout << ".iv" << endl;

    try {
        CBC_Mode<DES>::Encryption encr;
        encr.SetKeyWithIV(key, key.size(), iv);
        FileSource fs(filein.c_str(), true, new StreamTransformationFilter(encr, new FileSink(fileout.c_str())));
    } catch (const Exception& e) {
        cerr << e.what() << endl;
        return false;
    }

    return true;
}

bool DES_CRYP::decrypt()
{
    SecByteBlock key(DES::DEFAULT_KEYLENGTH);
    PKCS12_PBKDF<SHA1> pbkdf;
    pbkdf.DeriveKey(key.data(), key.size(), 0, (byte*)psw.data(), psw.size(), (byte*)salt.data(), salt.size(), 1024, 0.0f);

    cout << "Key: ";
    StringSource(key.data(), key.size(), true, new HexEncoder( new FileSink(cout) ));
    cout << endl;

    byte iv[DES::BLOCKSIZE];
    ifstream f_iv(string(filein + ".iv").c_str(), ios::in | ios::binary);

    if (f_iv.good()) {
        f_iv.read((char*)&iv, DES::BLOCKSIZE);
        f_iv.close();
    } else if (f_iv.bad()) {
        cerr << "IV file not found" << endl;
        f_iv.close();
        return false;
    } else {
        cerr << "IV file is not correct" << endl;
        f_iv.close();
        return false;
    }

    try {
        CBC_Mode<DES>::Decryption decr;
        decr.SetKeyWithIV(key, key.size(), iv);
        FileSource fs(filein.c_str(), true,
                      new StreamTransformationFilter(decr,
                              new FileSink(fileout.c_str())));
    } catch (const Exception& e) {
        cerr << e.what() << endl;
        return false;
    }

    return true;
}
