#include "cryptopp/rsa.h"
#include "cryptopp/hex.h"
#include "cryptopp/osrng.h"
#include <iostream>
#include <fstream>

using namespace std;
using namespace CryptoPP;

int main(){
    AutoSeededRandomPool prng;
    fstream file;
    Integer e("0x11");
    Integer d("0x974f3eaa763ad0979644dbfaac47867bd87b4c5c8b7fcd72943d0dde4303639");
    Integer n("0xa0c432951d9e7da10fa929ba570bfee52db56fc477e60b742581a35d1723ad6f");
    Integer cipher("0x404ea0a1c26fc6562ff17a61849520e0fdf70654c6460b0954918e8447d6cdba");
    string plain_str;
    RSA::PublicKey pubkey;
    RSA::PrivateKey privkey;

    file.open("out.txt",ios::app);
    privkey.Initialize(n,e,d);
    Integer plain_int = privkey.CalculateInverse(prng,cipher);

    size_t size = plain_int.MinEncodedSize();
    plain_str.resize(size);
    plain_int.Encode((byte *) &plain_str[0], plain_str.size());
    cout << "plaintext: " << plain_str << endl;
    file << plain_str << endl;

    file.close();

    return 0;
}
