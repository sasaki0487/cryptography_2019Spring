#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <iomanip>
#include <stdint.h>
#include "cryptopp/cryptlib.h"
#include "cryptopp/sha.h"
#include "cryptopp/hex.h"
#include "cryptopp/files.h"

using namespace std;
using namespace CryptoPP;

void Q1(){
    fstream f;
    SHA256 hash;
    string out,digest,msg = "Bitcoin is a cryptocurrency,a form of electronic cash.";
    HexEncoder encoder(new StringSink(out));
    f.open("out.txt",ios::out);
    hash.Update((const byte*)msg.data(), msg.size());
    digest.resize(hash.DigestSize());
    hash.Final((byte*)&digest[0]);
    StringSource(digest, true, new Redirector(encoder));
    f << out << endl;
    f.close();
    return;
}

int main(int argc, char *argv[]){
    SHA256 hash;
    int zeros = 0,flag = 0;
    string msg = "Bitcoin",fname;
    string digest,out,nonse="00000003",preimg,prehash,decoded;
    stringstream ss;
    HexEncoder encoder(new StringSink(out));
    uint64_t i;
    fstream f;

    Q1();
    hash.Update((const byte*)msg.data(), msg.size());
    digest.resize(hash.DigestSize());
    hash.Final((byte*)&digest[0]);
    StringSource(digest, true, new Redirector(encoder));

    prehash = out;

    f.open("out.txt",ios::app);
    out = "";
    preimg = prehash + nonse;
    decoded="";
    StringSource sss (preimg, true,new HexDecoder(new StringSink(decoded)) );
    hash.Update((const byte*)decoded.data(), decoded.size());
    digest.resize(hash.DigestSize());
    hash.Final((byte*)&digest[0]);
    StringSource(digest, true, new Redirector(encoder));
    f << zeros << endl << prehash << endl << nonse << endl << out << endl;
    cout << preimg << endl << out << endl;
    prehash = out;
    zeros++;


    while(1){
        for(i = 0 ; i <= 0xFFFFFFFF ; i++){
            cout << nonse << endl;
            out = "";
            flag = 0;
            ss << setw(8) << setfill('0') << uppercase << hex << i;
            nonse = ss.str();
            ss.str("");
            preimg = prehash + nonse;
            decoded="";
            StringSource sss (preimg, true,new HexDecoder(new StringSink(decoded)) );
            hash.Update((const byte*)decoded.data(), decoded.size());
            digest.resize(hash.DigestSize());
            hash.Final((byte*)&digest[0]);
            StringSource(digest, true, new Redirector(encoder));
            for(int j = 0 ; j < zeros ; j++){
                if(out[j] != '0'){
                    flag = 1;
                    break;
                }
            }
            if(flag == 0){
                f << zeros << endl << prehash << endl << nonse << endl << out << endl;
                cout << preimg << endl << out << endl;
                prehash = out;
                break;
            }
        }

        if(i>0xFFFFFFFF)
            break;
        zeros++;
    }
    f.close();

    return 0;
}
