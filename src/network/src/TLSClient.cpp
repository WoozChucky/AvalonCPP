#include <Network/TLSClient.h>
#include "Common/Logging/Log.h"
#include <iostream>
#include <utility>
#include <vector>
#include <fstream>
#include <future>

TLSClient::TLSClient(std::string serverAddress, int serverPort, TLSReadCallback readCallback)
    : serverAddress_(std::move(serverAddress)), serverPort_(serverPort),
    _socket(nullptr), _ssl(nullptr), _sslContext(nullptr), readCallback_(std::move(readCallback)) {
    _socket = new Socket();
}

TLSClient::~TLSClient() {
    if (shutdownRequested_ && connected_)
    {
        Shutdown();
    }
}

void TLSClient::ConnectAsync(const std::function<void(bool)>& callback) {
    std::thread([this, callback]() {
        try {
            callback(Connect());
        } catch (const std::exception& e) {
            LOG_ERROR("network", "Failed to connect: {}", e.what());
            callback(false);
        }
    }).detach();
}

void TLSClient::SendDataAsync(const std::string &data, const std::function<void(bool)>& callback) {
    std::thread([this, data, callback]() {
        bool result = false;

        try {
            result = SendData(data);
        } catch (const std::exception& e) {
            result = false;
            LOG_WARN("network", "Failed to send data: {}", e.what());
        }

        if (callback) {
            callback(result);
        }
    }).detach();
}

void TLSClient::Shutdown() {
    // Shutdown SSL connection asynchronously
    SSL_set_shutdown(_ssl, SSL_RECEIVED_SHUTDOWN);
    SSL_shutdown(_ssl);

    // Check if SSL shutdown is complete
    int sslResult = SSL_get_shutdown(_ssl);
    if (sslResult == SSL_RECEIVED_SHUTDOWN || sslResult == SSL_SENT_SHUTDOWN) {
        // SSL shutdown complete, close socket and invoke callback
        SSL_free(_ssl);
        SSL_CTX_free(_sslContext);
        _socket->Close();
    } else {
        // SSL shutdown in progress, wait for socket to become writable
        fd_set fdset;
        FD_ZERO(&fdset);
        FD_SET(_socket->operator int(), &fdset);
        timeval timeout;
        timeout.tv_sec = 10; // 10 seconds timeout
        timeout.tv_usec = 0;

        int result = select(_socket->operator int() + 1, nullptr, &fdset, nullptr, &timeout);
        if (result <= 0) {
            LOG_ERROR("network", "SSL shutdown timeout or error");
        } else {
            // Shutdown completed, close socket and invoke callback
            SSL_free(_ssl);
            SSL_CTX_free(_sslContext);
            _socket->Close();
        }
    }
}

bool TLSClient::SendData(const std::string &data) {

    if (_ssl == nullptr) {
        LOG_ERROR("network", "SSL connection not established");
        return false;
    }

    int bytesSent = SSL_write(_ssl, data.c_str(), data.length());
    if (bytesSent <= 0) {
        int sslError = SSL_get_error(_ssl, bytesSent);
        LOG_ERROR("network", "Error sending data: {}", sslError);
        return false;
    }

    LOG_DEBUG("network", "Sent {} bytes of data to the server", bytesSent);
    return true;

}

bool TLSClient::LoadCertificate() {
    // Load certificate from file
    std::ifstream file("cert-public.pem", std::ios::binary);
    if (!file) {
        LOG_ERROR("network", "Failed to open certificate file: {}", "cert-public.pem");
        return false;
    }

    std::vector<char> certData((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    // Create SSL context with TLS 1.2 method
    _sslContext = SSL_CTX_new(TLSv1_2_client_method());
    if (_sslContext == nullptr) {
        std::cerr << "Error creating SSL context" << std::endl;
        return false;
    }

    // Disable certificate verification
    SSL_CTX_set_verify(_sslContext, SSL_VERIFY_NONE, nullptr);

    // Load certificate into SSL context
    BIO* bio = BIO_new_mem_buf(certData.data(), static_cast<int>(certData.size()));
    if (bio == nullptr) {
        std::cerr << "Error creating BIO" << std::endl;
        return false;
    }

    /**
    SSL_CTX_set_info_callback(sslContext_.get(), [](const SSL* ssl, int where, int ret) {

        const char *str;
        int w;

        w=where& ~SSL_ST_MASK;

        if (w & SSL_ST_CONNECT)
            str="SSL_connect";
        else if (w & SSL_ST_ACCEPT)
            str="SSL_accept";
        else
            str="undefined";

        if (where & SSL_CB_LOOP)
        {
            fprintf(stderr,"%s:%s\n",str,SSL_state_string_long(ssl));
            //BIO_printf(bio_,"%s:%s\n",str,SSL_state_string_long(ssl));
        }
        else if (where & SSL_CB_ALERT)
        {
            str=(where & SSL_CB_READ)?"read":"write";
            fprintf(stderr,
                "SSL3 alert %s:%s:%s\n",
                    str,
                    SSL_alert_type_string_long(ret),
                    SSL_alert_desc_string_long(ret)
            );
            //BIO_printf(bio_,"SSL3 alert %s:%s:%s\n",
            //        str,
            //        SSL_alert_type_string_long(ret),
            //        SSL_alert_desc_string_long(ret));
        }
        else if (where & SSL_CB_EXIT)
        {
            if (ret == 0) {
                fprintf(stderr,"%s:failed in %s\n", str,SSL_state_string_long(ssl));
                //BIO_printf(bio_,"%s:failed in %s\n", str,SSL_state_string_long(ssl));
            }
            else if (ret < 0)
            {
                fprintf(stderr,"%s:error in %s\n",str,SSL_state_string_long(ssl));
                //BIO_printf(bio_,"%s:error in %s\n",str,SSL_state_string_long(ssl));
            }
        }
    });
    */

    X509* cert = PEM_read_bio_X509(bio, nullptr, 0, nullptr);
    if (cert == nullptr) {
        std::cerr << "Error loading certificate" << std::endl;
        BIO_free(bio);
        return false;
    }

    if (SSL_CTX_use_certificate(_sslContext, cert) != 1) {
        std::cerr << "Error setting certificate" << std::endl;
        X509_free(cert);
        BIO_free(bio);
        return false;
    }

    X509_free(cert);
    BIO_free(bio);
    return true;
}

void TLSClient::RunAsync() {
    std::thread([this]() {
        char buffer[4096];
        while (!shutdownRequested_) {
            memset(buffer, 0, sizeof(buffer));
            int bytesReceived = SSL_read(_ssl, buffer, sizeof(buffer) - 1);
            if (bytesReceived <= 0) {
                int sslError = SSL_get_error(_ssl, bytesReceived);
                std::cerr << "Error reading data: " << sslError << std::endl;
                break;
            }
            std::vector<char> receivedData(buffer, buffer + bytesReceived);
            LOG_DEBUG("network", "Received {} bytes from the server", bytesReceived);
            readCallback_(receivedData);
        }
    }).detach();
}

void TLSClient::SignalShutdown() {
    shutdownRequested_ = true;
}

bool TLSClient::Connect() {
    // Load certificate
    if (!LoadCertificate()) {
        std::cerr << "Failed to load certificate" << std::endl;
        return false;
    }

    // Connect to server asynchronously
    if (!_socket->Connect(serverAddress_.c_str(), serverPort_)) {
        LOG_ERROR("network", "Failed to connect to server");
        return false;
    }

    if (_sslContext == nullptr) {
        std::cerr << "Error creating SSL context" << std::endl;
        _socket->Close();
        return false;
    }

    // Create SSL object
    _ssl = SSL_new(_sslContext);
    if (_ssl == nullptr) {
        std::cerr << "Error creating SSL object" << std::endl;
        SSL_CTX_free(_sslContext);
        _socket->Close();
        return false;
    }

    // Attach SSL to the socket
    if (!SSL_set_fd(_ssl, _socket->operator int())) {
        std::cerr << "Error attaching SSL to socket" << std::endl;
        SSL_free(_ssl);
        SSL_CTX_free(_sslContext);
        _socket->Close();
        return false;
    }

    // Perform SSL handshake asynchronously
    SSL_set_connect_state(_ssl);
    SSL_do_handshake(_ssl);
    auto result = SSL_get_error(_ssl, 0);

    // Check SSL handshake result
    int sslResult = SSL_get_error(_ssl, result);
    if (sslResult == SSL_ERROR_WANT_READ || sslResult == SSL_ERROR_WANT_WRITE) {
        // Handshake in progress, wait for socket to become writable
        fd_set fdset;
        FD_ZERO(&fdset);
        FD_SET(_socket->operator int(), &fdset);
        timeval timeout;
        timeout.tv_sec = 10; // 10 seconds timeout
        timeout.tv_usec = 0;

        result = select(_socket->operator int() + 1, nullptr, &fdset, nullptr, &timeout);
        if (result <= 0) {
            LOG_ERROR("network", "SSL handshake timeout or error");
            return false;
        }
    } else if (sslResult != SSL_ERROR_NONE) {
        LOG_ERROR("network", "SSL handshake failed with error: {}", sslResult);
        connected_ = true;
        return true;
    }

    LOG_DEBUG("network", "Connected to server over TLS");
    connected_ = true;
    return true;
}
