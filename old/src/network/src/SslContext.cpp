#include <Network/SslContext.h>
#include <Common/Logging/Log.h>
#include <fstream>

bool SslContext::Initialize(const std::string& certPath, const std::string& password)
{
    boost::system::error_code err;

    // Load certificate from file
    std::ifstream file("cert-public.pem", std::ios::binary);
    if (!file) {
        LOG_ERROR("network", "Failed to open certificate file: {}", "cert-public.pem");
        return false;
    }

    std::vector<char> certData((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    SSL_CTX* nativeContext = Instance().native_handle();

    // Disable certificate verification
    SSL_CTX_set_verify(nativeContext, SSL_VERIFY_NONE, nullptr);

    // Load certificate into SSL context
    BIO* bio = BIO_new_mem_buf(certData.data(), static_cast<int>(certData.size()));
    if (bio == nullptr) {
        LOG_ERROR("network.ssl", "Error creating BIO");
        return false;
    }

    X509* cert = PEM_read_bio_X509(bio, nullptr, 0, nullptr);
    if (cert == nullptr) {
        LOG_ERROR("network.ssl", "Error loading certificate");
        BIO_free(bio);
        return false;
    }

    if (SSL_CTX_use_certificate(nativeContext, cert) != 1) {
        LOG_ERROR("network.ssl", "Error setting certificate");
        X509_free(cert);
        BIO_free(bio);
        return false;
    }

    X509_free(cert);
    BIO_free(bio);

    return true;
}

boost::asio::ssl::context& SslContext::Instance()
{
    static boost::asio::ssl::context context(boost::asio::ssl::context::tls);
    return context;
}
