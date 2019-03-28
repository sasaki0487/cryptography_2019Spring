#include <iostream>
#include <fstream>
#include <iomanip>

#include "cryptopp/modes.h"
#include "cryptopp/aes.h"
#include "cryptopp/filters.h"
#include "cryptopp/hex.h"

using namespace std;
using namespace CryptoPP;
int main(int argc, char* argv[]) {

    fstream fout;
    byte key[ AES::DEFAULT_KEYLENGTH ], iv[ AES::BLOCKSIZE ];
    memset( key, 0x00, AES::DEFAULT_KEYLENGTH );
    memset( iv, 0x00, AES::BLOCKSIZE );

    string keyin = "1234567890123456";
    string ivin = "0000000000000000";
    string dst;

    for(int i = 0 ; i < AES::DEFAULT_KEYLENGTH ; i++){
        key[i] = (int)keyin[i];
        iv[i] = (int)ivin[i];
    }

    //
    // String and Sink setup
    //

    string plaintext = "AES is efficient in both software and hardware.";
    //string plaintext = "Hello World!";
    string ciphertext[4];
    string decryptedtext;

    //
    // Create Cipher Text
    //
    CryptoPP::AES::Encryption aesEncryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
    CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption1( aesEncryption, iv );
    CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption2( aesEncryption, iv );
    CryptoPP::ECB_Mode_ExternalCipher::Encryption ecbEncryption1( aesEncryption);
    CryptoPP::ECB_Mode_ExternalCipher::Encryption ecbEncryption2( aesEncryption);

    CryptoPP::StreamTransformationFilter stfEncryptor1(ecbEncryption1, new CryptoPP::StringSink( ciphertext[0] ) ,CryptoPP::StreamTransformationFilter::ZEROS_PADDING);
    stfEncryptor1.Put( reinterpret_cast<const unsigned char*>( plaintext.c_str() ), plaintext.length() + 1);
    stfEncryptor1.MessageEnd();

    CryptoPP::StreamTransformationFilter stfEncryptor2(ecbEncryption2, new CryptoPP::StringSink( ciphertext[1] ) ,CryptoPP::StreamTransformationFilter::PKCS_PADDING);
    stfEncryptor2.Put( reinterpret_cast<const unsigned char*>( plaintext.c_str() ), plaintext.length() + 1);
    stfEncryptor2.MessageEnd();

    CryptoPP::StreamTransformationFilter stfEncryptor3(cbcEncryption1, new CryptoPP::StringSink( ciphertext[2] ) ,CryptoPP::StreamTransformationFilter::ZEROS_PADDING);
    stfEncryptor3.Put( reinterpret_cast<const unsigned char*>( plaintext.c_str() ), plaintext.length() + 1);
    stfEncryptor3.MessageEnd();

    CryptoPP::StreamTransformationFilter stfEncryptor4(cbcEncryption2, new CryptoPP::StringSink( ciphertext[3] ) ,CryptoPP::StreamTransformationFilter::PKCS_PADDING);
    stfEncryptor4.Put( reinterpret_cast<const unsigned char*>( plaintext.c_str() ), plaintext.length() + 1);
    stfEncryptor4.MessageEnd();

    fout.open("Out.txt",ios::out);

    for( int i = 0; i < 4 ; i++ ) {
        for(int j = 0 ; j < ciphertext[i].size(); j++){
            cout << hex << (0xFF & static_cast<byte>(ciphertext[i][j]));
            fout << hex << (0xFF & static_cast<byte>(ciphertext[i][j]));
        }
        cout << endl << endl;
        fout << endl << endl;
    }

    fout.close();

    //
    // Decrypt
    //
    /*
    CryptoPP::AES::Decryption aesDecryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
    CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption( aesDecryption, iv );

    CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink( decryptedtext ) );
    stfDecryptor.Put( reinterpret_cast<const unsigned char*>( ciphertext.c_str() ), ciphertext.size() );
    stfDecryptor.MessageEnd();

    std::cout << "Decrypted Text: " << std::endl;
    std::cout << decryptedtext;
    std::cout << std::endl << std::endl;
    */

    return 0;
}
