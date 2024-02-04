#pragma once

#include <Common/Types.h>
#include <memory>
#include <vector>
#include <openssl/types.h>


namespace Avalon::Crypto
{
    class CryptoSession
    {
        public:
            CryptoSession();

            bool Initialize(const std::vector<U8>& otherEndPublicKeyBuffer);
            std::vector<U8> GetPublicKeyBytes();

            std::vector<U8> Encrypt(const std::vector<U8>& data);
            std::vector<U8> Decrypt(std::vector<U8>& data);

        private:
            std::pair<EC_KEY*, EC_KEY*> _ownKeyPair;
            EC_KEY * _otherEndPublicKey;
            std::vector<U8> _otherEndPublicKeyBytes;
            EC_KEY * _ownPublicKey;
            std::vector<U8> _ownPublicKeyBytes;

            std::vector<U8> _sessionKey;

            // Public key, private key
            std::pair<EC_KEY*, EC_KEY*> GenerateECDHKeyPair();

            EC_KEY* GetOtherEndPublicKey(std::vector<U8> const& otherEndPublicKeyBuffer);
            std::vector<U8> GetPublicKeyBytes(EC_KEY* publicKey);
            std::vector<U8> CalculateSharedSecret(EC_KEY* ownPrivateKey, EC_KEY* otherPublicKey);

            std::vector<U8> GenerateIV();
    };
}

