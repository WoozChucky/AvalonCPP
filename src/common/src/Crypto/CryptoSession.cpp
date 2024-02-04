#include <Common/Crypto/CryptoSession.h>
#include <stdexcept>
#include <openssl/x509.h>
#include <openssl/rand.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <iostream>

using namespace Avalon::Crypto;

CryptoSession::CryptoSession() {
    _ownKeyPair = GenerateECDHKeyPair();
}

bool CryptoSession::Initialize(const std::vector<U8> &otherEndPublicKeyBuffer) {

    if (otherEndPublicKeyBuffer.empty()) {
        throw std::invalid_argument("Invalid public key");
    }

    // Parse the byte array to reconstruct the public key
    _otherEndPublicKey = GetOtherEndPublicKey(otherEndPublicKeyBuffer);

    _otherEndPublicKeyBytes = GetPublicKeyBytes(_otherEndPublicKey);

    _sessionKey = CalculateSharedSecret(_ownKeyPair.second, _otherEndPublicKey);

    _ownPublicKey = _ownKeyPair.first;

    _ownPublicKeyBytes = GetPublicKeyBytes(_ownPublicKey);

    return true;
}

std::vector<U8> CryptoSession::GetPublicKeyBytes() {
    return _ownPublicKeyBytes;
}

std::pair<EC_KEY*, EC_KEY*> CryptoSession::GenerateECDHKeyPair() {
    EC_KEY* key = EC_KEY_new_by_curve_name(NID_X9_62_prime256v1);
    if (key == nullptr) {
        throw std::runtime_error("Failed to create new EC key");
    }

    if (EC_KEY_generate_key(key) != 1) {
        EC_KEY_free(key);
        throw std::runtime_error("Failed to generate EC key");
    }

    EC_KEY* publicKey = EC_KEY_new_by_curve_name(NID_X9_62_prime256v1);
    if (publicKey == nullptr) {
        EC_KEY_free(key);
        throw std::runtime_error("Failed to create new EC key for public key");
    }

    const EC_POINT* pubPoint = EC_KEY_get0_public_key(key);
    if (EC_KEY_set_public_key(publicKey, pubPoint) != 1) {
        EC_KEY_free(key);
        EC_KEY_free(publicKey);
        throw std::runtime_error("Failed to set public key");
    }

    return {publicKey, key};
}

EC_KEY *CryptoSession::GetOtherEndPublicKey(const std::vector<U8> &otherEndPublicKeyBuffer) {

    const unsigned char* p = otherEndPublicKeyBuffer.data();
    EC_KEY* publicKey = d2i_EC_PUBKEY(nullptr, &p, otherEndPublicKeyBuffer.size());

    if (publicKey == nullptr) {
        throw std::runtime_error("Invalid public key");
    }

    return publicKey;
}

std::vector<U8> CryptoSession::GetPublicKeyBytes(EC_KEY* publicKey)
{
    unsigned char* der = nullptr;
    int len = i2d_EC_PUBKEY(publicKey, &der);
    if (len < 0) {
        // handle error
        throw std::runtime_error("Failed to convert public key to DER format");
    }

    std::vector<unsigned char> publicKeyBytes(der, der + len);
    OPENSSL_free(der); // free the memory allocated by i2d_PUBKEY

    return publicKeyBytes;
}

std::vector<U8> CryptoSession::CalculateSharedSecret(EC_KEY* ownPrivateKey, EC_KEY* otherPublicKey) {
    const EC_POINT* pubKey = EC_KEY_get0_public_key(otherPublicKey);
    if (pubKey == nullptr) {
        throw std::runtime_error("Failed to get public key from EC_KEY");
    }

    // Create a new BN_CTX for the group operations
    BN_CTX* ctx = BN_CTX_new();
    if (ctx == nullptr) {
        throw std::runtime_error("Failed to create new BN_CTX");
    }

    // Get the group from the private key
    const EC_GROUP* group = EC_KEY_get0_group(ownPrivateKey);

    // Compute the shared secret
    int fieldSize = EC_GROUP_get_degree(group);
    int sharedSecretSize = (fieldSize+7)/8; // size in bytes
    std::vector<unsigned char> sharedSecret(sharedSecretSize);

    // Compute the shared secret
    if (ECDH_compute_key(sharedSecret.data(), sharedSecretSize, pubKey, ownPrivateKey, nullptr) == 0) {
        while (unsigned long errCode = ERR_get_error()) {
            char errMessage[120];
            ERR_error_string_n(errCode, errMessage, sizeof(errMessage));

            std::cerr << "OpenSSL Error: " << errMessage << std::endl;
        }
        BN_CTX_free(ctx);
        throw std::runtime_error("Failed to compute ECDH key");
    }

    // Clean up
    BN_CTX_free(ctx);

    return sharedSecret;
}

std::vector<U8> CryptoSession::Encrypt(const std::vector<U8> &data) {

    EVP_CIPHER_CTX *ctx;
    int len;
    std::vector<unsigned char> ciphertext(data.size()); // + EVP_MAX_BLOCK_LENGTH

    // Create and initialize the context
    if(!(ctx = EVP_CIPHER_CTX_new()))
    {
        throw std::runtime_error("Failed to create new encryption context");
    }

    // Initialize the encryption operation with AES-GCM
    if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_gcm(), nullptr, nullptr, nullptr))
    {
        throw std::runtime_error("Failed to initialize encryption operation");
    }

    auto iv = GenerateIV();

    // Set IV length
    if(1 != EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, iv.size(), nullptr))
    {
        throw std::runtime_error("Failed to set IV length");
    }

    // Initialize key and IV
    if(1 != EVP_EncryptInit_ex(ctx, nullptr, nullptr, _sessionKey.data(), iv.data()))
    {
        throw std::runtime_error("Failed to initialize key and IV");
    }

    // Encrypt plaintext
    if(1 != EVP_EncryptUpdate(ctx, ciphertext.data(), &len, data.data(), data.size()))
    {
        throw std::runtime_error("Failed to encrypt plaintext");
    }

    int ciphertext_len = len;

    // Finalize encryption
    if(1 != EVP_EncryptFinal_ex(ctx, ciphertext.data() + len, &len))
    {
        throw std::runtime_error("Failed to finalize encryption");
    }

    ciphertext_len += len;

    // Get the tag
    std::vector<unsigned char> tag(EVP_GCM_TLS_TAG_LEN);
    if(1 != EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_GET_TAG, EVP_GCM_TLS_TAG_LEN, tag.data()))
    {
        throw std::runtime_error("Failed to get tag");
    }

    // Clean up
    EVP_CIPHER_CTX_free(ctx);

    // Append the tag to ciphertext
    ciphertext.insert(ciphertext.end(), tag.begin(), tag.end());

    // Prepend the IV to the ciphertext
    ciphertext.insert(ciphertext.begin(), iv.begin(), iv.end());

    return ciphertext;

}

std::vector<U8> CryptoSession::Decrypt(std::vector<U8> &data) {
    EVP_CIPHER_CTX *ctx;
    int len;
    std::vector<unsigned char> plaintext(data.size()); // EVP_MAX_BLOCK_LENGTH

    // Create and initialize the context
    if(!(ctx = EVP_CIPHER_CTX_new()))
    {
        throw std::runtime_error("Failed to create new decryption context");
    }

    // Initialize the decryption operation with AES-GCM
    if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_gcm(), nullptr, nullptr, nullptr))
    {
        throw std::runtime_error("Failed to initialize decryption operation");
    }

    // Extract the IV from the first 12 bytes of the ciphertext
    std::vector<U8> iv(data.begin(), data.begin() + IV_KEY_SIZE);

    // Remove the IV from the ciphertext
    data.erase(data.begin(), data.begin() + IV_KEY_SIZE);

    // Set IV length
    if(1 != EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, iv.size(), nullptr))
    {
        throw std::runtime_error("Failed to set IV length");
    }

    // Initialize key and IV
    if(1 != EVP_DecryptInit_ex(ctx, nullptr, nullptr, _sessionKey.data(), iv.data()))
    {
        throw std::runtime_error("Failed to initialize key and IV");
    }

    // Decrypt ciphertext
    if(1 != EVP_DecryptUpdate(ctx, plaintext.data(), &len, data.data(), data.size() - EVP_GCM_TLS_TAG_LEN))
    {
        throw std::runtime_error("Failed to decrypt ciphertext");
    }

    int plaintext_len = len;

    // Set the tag
    if(1 != EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_TAG, EVP_GCM_TLS_TAG_LEN, (void*)(data.data() + data.size() - EVP_GCM_TLS_TAG_LEN)))
    {
        throw std::runtime_error("Failed to set tag");
    }

    // Finalize decryption
    if(1 != EVP_DecryptFinal_ex(ctx, plaintext.data() + len, &len))
    {
        throw std::runtime_error("Failed to finalize decryption");
    }

    plaintext_len += len;

    // Clean up
    EVP_CIPHER_CTX_free(ctx);

    // Resize plaintext to actual size
    plaintext.resize(plaintext_len);

    return plaintext;
}

std::vector<U8> CryptoSession::GenerateIV() {
    std::vector<unsigned char> iv(IV_KEY_SIZE); // 12 bytes = 96 bits

    // Generate random bytes for the IV
    if (RAND_bytes(iv.data(), iv.size()) != 1) {
        throw std::runtime_error("Error generating IV");
    }

    return iv;
}
