#include <iostream>
#include <iomanip>

#include "cryptopp/modes.h"
#include "cryptopp/aes.h"
#include "cryptopp/filters.h"
#include "cryptopp/hex.h"

using namespace std;

int main(int argc, char* argv[]) {

    //Key and IV setup
    //AES encryption uses a secret key of a variable length (128-bit, 196-bit or 256-
    //bit). This key is secretly exchanged between two parties before communication
    //begins. DEFAULT_KEYLENGTH= 16 bytes
    CryptoPP::byte key[ CryptoPP::AES::DEFAULT_KEYLENGTH ], iv[ CryptoPP::AES::BLOCKSIZE ];
    memset( key, 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH );
    memset( iv, 0x00, CryptoPP::AES::BLOCKSIZE );

    string keyin = "1234567890123456";
    string ivin = "0000000000000000";
    string dst;
    CryptoPP::StringSource ss1(keyin,true,new CryptoPP::HexEncoder(new CryptoPP::ArraySink(&key[0],16)));
    CryptoPP::StringSource ss2(ivin,true,new CryptoPP::HexEncoder(new CryptoPP::ArraySink(&iv[0],16)));
    key[0]= 0x31;
    key[1]= 0x32;
    key[2]= 0x33;
    key[3]= 0x34;
    key[4]= 0x35;
    key[5]= 0x36;
    key[6]= 0x37;
    key[7]= 0x38;
    key[8]= 0x39;
    key[9]= 0x30;
    key[10]= 0x31;
    key[11]= 0x32;
    key[12]= 0x33;
    key[13]= 0x34;
    key[14]= 0x35;
    key[15]= 0x36;

    iv[0]= 0x30;
    iv[1]= 0x30;
    iv[2]= 0x30;
    iv[3]= 0x30;
    iv[4]= 0x30;
    iv[5]= 0x30;
    iv[6]= 0x30;
    iv[7]= 0x30;
    iv[8]= 0x30;
    iv[9]= 0x30;
    iv[10]= 0x30;
    iv[11]= 0x30;
    iv[12]= 0x30;
    iv[13]= 0x30;
    iv[14]= 0x30;
    iv[15]= 0x30;

    //
    // String and Sink setup
    //
    //string plaintext = "AES is efficient in both software and hardware.";
    string plaintext = "Hello World!";
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
    stfEncryptor1.Put( reinterpret_cast<const unsigned char*>( plaintext.c_str() ), plaintext.length() );
    stfEncryptor1.MessageEnd();

    CryptoPP::StreamTransformationFilter stfEncryptor2(ecbEncryption2, new CryptoPP::StringSink( ciphertext[1] ) ,CryptoPP::StreamTransformationFilter::DEFAULT_PADDING);
    stfEncryptor2.Put( reinterpret_cast<const unsigned char*>( plaintext.c_str() ), plaintext.length() );
    stfEncryptor2.MessageEnd();

    CryptoPP::StreamTransformationFilter stfEncryptor3(cbcEncryption1, new CryptoPP::StringSink( ciphertext[2] ) ,CryptoPP::StreamTransformationFilter::ZEROS_PADDING);
    stfEncryptor3.Put( reinterpret_cast<const unsigned char*>( plaintext.c_str() ), plaintext.length() );
    stfEncryptor3.MessageEnd();

    CryptoPP::StreamTransformationFilter stfEncryptor4(cbcEncryption2, new CryptoPP::StringSink( ciphertext[3] ) ,CryptoPP::StreamTransformationFilter::DEFAULT_PADDING);
    stfEncryptor4.Put( reinterpret_cast<const unsigned char*>( plaintext.c_str() ), plaintext.length() );
    stfEncryptor4.MessageEnd();



        for( int i = 0; i < 4 ; i++ ) {
            for(int j = 0 ; j < ciphertext[i].size(); j++){
                cout << hex << (0xFF & static_cast<CryptoPP::byte>(ciphertext[i][j]));
            }
            cout << endl;
        }

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
