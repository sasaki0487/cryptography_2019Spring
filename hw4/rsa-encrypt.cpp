#include "cryptopp/rsa.h"
#include "cryptopp/hex.h"
#include <iostream>
#include <fstream>

using namespace std;
using namespace CryptoPP;

int main(){
    fstream file;
    file.open("out.txt",ios::out);
    Integer e("0x11");
    Integer n1("0xcebe9e0617c706c632e64c3405cda5d1");
    Integer n2("0xaf195de7988cfaa1dbb18c5862e3853f0e79a12bbfa7aa326a52da97caa60c39");

    RSA::PublicKey pubkey;
    pubkey.Initialize(n1,e);
    string msg = "Hello World!";
    Integer cipher1((const byte *)msg.data(), msg.size());
    Integer c = pubkey.ApplyFunction(cipher1);
    cout << "c: " << hex << c << endl;
    file << hex << c << endl;

    pubkey.Initialize(n2,e);
    msg = "RSA is public key.";
    Integer cipher2((const byte *)msg.data(), msg.size());
    c = pubkey.ApplyFunction(cipher2);
    cout << "c: " << c << endl;
    file << hex << c << endl;

    file.close();

    return 0;
}
