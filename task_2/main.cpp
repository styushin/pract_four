#include <AES.h>
#include <DES.h>

int main ()
{
    unsigned op, alg;
    string file_in, file_out, key;
    do {
        cout<<"Select operation (0-exit, 1-encrypt, 2-decrypt): ";
            cin >> op;
             if (op != 0) {
            cout << "Cipher ready. Select an algorithm (0-exit, 1-AES, 2-DES): ";
        cin >> alg;
        }
       
        if (op > 2) {
            cerr << "ERROR! Invalid operation" << endl;
        }
        else if (op > 0) {
            cout << "Enter a path to input file: ";
            cin >> file_in;
            cout << "Enter a path to output file: ";
            cin >> file_out;
            cout << "Enter a password: ";
            cin >> key;
            if (alg == 1) {
                AES_CRYP aes(file_in, file_out, key);
                if (op == 1) {
                    if (aes.encrypt())
                        cout << "Encription completed!" << endl;
                    else
                        cout << "Encryption failed!" << endl;
                } else {
                    if (aes.decrypt())
                        cout << "Decription completed!" << endl;
                    else
                        cout << "Decryption failed!" << endl;
                }
            }
            else if (alg == 2) {
                DES_CRYP des(file_in, file_out, key);
                if (op == 1) {
                    if (des.encrypt())
                        cout << "Encription completed!" << endl;
                    else
                        cout << "Encryption failed!" << endl;
                } else {
                    if (des.decrypt())
                        cout << "Decription completed!" << endl;
                    else
                        cout << "Decryption failed!" << endl;
                }
            }
            else {
                cerr << "Algorithm aborted: invalid text" << endl;
            }
        }
    } while (op != 0);
    return 0;
}
