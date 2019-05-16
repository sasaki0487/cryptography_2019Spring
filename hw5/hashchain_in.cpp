//Feed the starting nonce as argument 1
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

int main(int argc, char *argv[]){
    SHA256 hash;
    int zeros = 0,flag = 0;
    string msg = "Bitcoin",fname;
    string digest,out,nonse,preimg,prehash,decoded;
    vector<string> v_img,v_hash,v_nonse;
    stringstream ss;
    HexEncoder encoder(new StringSink(out));
    uint64_t i;
    fstream f;

    hash.Update((const byte*)msg.data(), msg.size());
    digest.resize(hash.DigestSize());
    hash.Final((byte*)&digest[0]);
    StringSource(digest, true, new Redirector(encoder));

    prehash = out;
    int start = atoi(argv[1]);
    fname = to_string(start) + ".txt";
    f.open(fname,ios::out);
    out = "";
    flag = 0;
    ss << setw(8) << setfill('0') << uppercase << hex << start;
    nonse = ss.str();
    ss.str("");
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
