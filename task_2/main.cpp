#include <AES.h>
#include <DES.h>

int main ()
{
    unsigned op, alg; //неопределенные переменные
    string file_in, file_out, key;
    do {
        cout<<"Select operation (0-exit, 1-encrypt, 2-decrypt): "; //выбор операции
            cin >> op;
             if (op != 0) {
            cout << "Cipher ready. Select an algorithm (0-exit, 1-AES, 2-DES): ";         //выводит выбор алгоритма
        cin >> alg;
        }
       
        if (op > 2) {                      //ошибка в случае если выбран некорректная операция с порядковым номером больше двух
            cerr << "ERROR! Invalid operation" << endl;
        }
        else if (op > 0) {
            cout << "Enter a path to input file: "; 
            //тут типа выбор файла
            cin >> file_in;
            cout << "Enter a path to output file: ";
            cin >> file_out;
            cout << "Enter a password: "; 
            cin >> key;                                 //вводим ключ
            if (alg == 1) {
                AES_CRYP aes(file_in, file_out, key); //алгоритм если выбран метод AES
                if (op == 1) {
                    if (aes.encrypt())
                        cout << "Encription completed!" << endl; //если шифрование работает
                    else                                              
                        cout << "Encryption failed!" << endl; //если не работает
                } else {
                    if (aes.decrypt())
                        cout << "Decription completed!" << endl; //если расшифровало 
                    else
                        cout << "Decryption failed!" << endl; //идешь на пересдачу
                }
            }
            else if (alg == 2) { //если выбран алгоритм DES
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
