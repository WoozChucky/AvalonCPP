//
// Created by nunol on 2/1/2024.
//

#include "TLSClient.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <future>

TLSClient::TLSClient(const std::string &serverAddress, int serverPort, TLSReadCallback readCallback)
    : serverAddress_(serverAddress), serverPort_(serverPort),
    ssl_(nullptr, ::SSL_free), sslContext_(nullptr, ::SSL_CTX_free), readCallback_(readCallback) {
    WSAStartup(MAKEWORD(2, 2), &wsaData_);
}

TLSClient::~TLSClient() {
    closesocket(clientSocket_);
    WSACleanup();
}

void TLSClient::ConnectAsync(std::function<void(bool)> callback) {

    // Load certificate
    if (!LoadCertificate()) {
        std::cerr << "Failed to load certificate" << std::endl;
        callback(false);
        return;
    }

    // Create a non-blocking socket
    clientSocket_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket_ == INVALID_SOCKET) {
        std::cerr << "Error creating socket: " << WSAGetLastError() << std::endl;
        callback(false);
        return;
    }

    // Resolve server address
    serverAddr_.sin_family = AF_INET;
    serverAddr_.sin_port = htons(serverPort_);
    serverAddr_.sin_addr.s_addr = inet_addr(serverAddress_.c_str());

    // Connect to server asynchronously
    int result = connect(clientSocket_, reinterpret_cast<struct sockaddr*>(&serverAddr_), sizeof(serverAddr_));
    if (result == SOCKET_ERROR && WSAGetLastError() != WSAEWOULDBLOCK) {
        std::cerr << "Failed to connect to server: " << WSAGetLastError() << std::endl;
        closesocket(clientSocket_);
        callback(false);
        return;
    }

    if (sslContext_ == nullptr) {
        std::cerr << "Error creating SSL context" << std::endl;
        closesocket(clientSocket_);
        callback(false);
        return;
    }

    // Create SSL object
    ssl_.reset(SSL_new(sslContext_.get()));
    if (ssl_ == nullptr) {
        std::cerr << "Error creating SSL object" << std::endl;
        SSL_CTX_free(sslContext_.get());
        closesocket(clientSocket_);
        callback(false);
        return;
    }

    // Attach SSL to the socket
    if (!SSL_set_fd(ssl_.get(), clientSocket_)) {
        std::cerr << "Error attaching SSL to socket" << std::endl;
        SSL_free(ssl_.get());
        SSL_CTX_free(sslContext_.get());
        closesocket(clientSocket_);
        callback(false);
        return;
    }

    // Perform SSL handshake asynchronously
    SSL_set_connect_state(ssl_.get());
    SSL_do_handshake(ssl_.get());

    // Check SSL handshake result
    int sslResult = SSL_get_error(ssl_.get(), result);
    if (sslResult == SSL_ERROR_WANT_READ || sslResult == SSL_ERROR_WANT_WRITE) {
        // Handshake in progress, wait for socket to become writable
        fd_set fdset;
        FD_ZERO(&fdset);
        FD_SET(clientSocket_, &fdset);
        timeval timeout;
        timeout.tv_sec = 10; // 10 seconds timeout
        timeout.tv_usec = 0;

        result = select(clientSocket_ + 1, nullptr, &fdset, nullptr, &timeout);
        if (result <= 0) {
            std::cerr << "SSL handshake timeout or error" << std::endl;
            callback(false);
            return;
        }
    } else if (sslResult != SSL_ERROR_NONE) {
        std::cerr << "SSL handshake failed with error: " << sslResult << std::endl;
        callback(false);
        return;
    }

    std::cout << "Connected to server over TLS" << std::endl;
    callback(true);
}

void TLSClient::DisconnectAsync(std::function<void()> callback) {
    // Shutdown SSL connection asynchronously
    SSL_set_shutdown(ssl_.get(), SSL_RECEIVED_SHUTDOWN);
    SSL_shutdown(ssl_.get());

    // Check if SSL shutdown is complete
    int sslResult = SSL_get_shutdown(ssl_.get());
    if (sslResult == SSL_RECEIVED_SHUTDOWN || sslResult == SSL_SENT_SHUTDOWN) {
        // SSL shutdown complete, close socket and invoke callback
        SSL_free(ssl_.get());
        SSL_CTX_free(sslContext_.get());
        closesocket(clientSocket_);
        callback();
    } else {
        // SSL shutdown in progress, wait for socket to become writable
        fd_set fdset;
        FD_ZERO(&fdset);
        FD_SET(clientSocket_, &fdset);
        timeval timeout;
        timeout.tv_sec = 10; // 10 seconds timeout
        timeout.tv_usec = 0;

        int result = select(clientSocket_ + 1, nullptr, &fdset, nullptr, &timeout);
        if (result <= 0) {
            std::cerr << "SSL shutdown timeout or error" << std::endl;
        } else {
            // Shutdown completed, close socket and invoke callback
            SSL_free(ssl_.get());
            SSL_CTX_free(sslContext_.get());
            closesocket(clientSocket_);
            callback();
        }
    }
}

bool TLSClient::SendData(const std::string &data) {

    if (ssl_ == nullptr) {
        std::cerr << "SSL connection not established" << std::endl;
        return false;
    }

    int bytesSent = SSL_write(ssl_.get(), data.c_str(), data.length());
    if (bytesSent <= 0) {
        int sslError = SSL_get_error(ssl_.get(), bytesSent);
        std::cerr << "Error sending data: " << sslError << std::endl;
        return false;
    }

    std::cout << "Sent " << bytesSent << " bytes of data to the server" << std::endl;
    return true;

}

bool TLSClient::LoadCertificate() {
    // Load certificate from file
    std::ifstream file("cert-public.pem", std::ios::binary);
    if (!file) {
        std::cerr << "Failed to open certificate file: " << "cert-public.pem" << std::endl;
        return false;
    }

    std::vector<char> certData((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    // Initialize OpenSSL
    SSL_library_init();
    SSL_load_error_strings();
    OpenSSL_add_all_algorithms();

    // Create SSL context with TLS 1.2 method
    sslContext_.reset(SSL_CTX_new(TLSv1_2_client_method()));
    if (sslContext_ == nullptr) {
        std::cerr << "Error creating SSL context" << std::endl;
        return false;
    }

    // Disable certificate verification
    SSL_CTX_set_verify(sslContext_.get(), SSL_VERIFY_NONE, nullptr);

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

    if (SSL_CTX_use_certificate(sslContext_.get(), cert) != 1) {
        std::cerr << "Error setting certificate" << std::endl;
        X509_free(cert);
        BIO_free(bio);
        return false;
    }

    X509_free(cert);
    BIO_free(bio);
    return true;
}

bool TLSClient::SendDataAsync(const std::string &data) {

    std::future<bool> result = std::async(std::launch::async, &TLSClient::SendData, this, data);

    // You can get the result of the async operation using result.get()
    // But be aware that get() is a blocking operation, it will wait for the async operation to finish
    // If you don't want to block, you can check if the async operation is ready with result.wait_for(std::chrono::seconds(0)) == std::future_status::ready

    return result.wait_for(std::chrono::seconds(0)) == std::future_status::ready;
}

void TLSClient::RunAsync() {
    std::thread([this]() {
        char buffer[4096];
        while (true) {
            memset(buffer, 0, sizeof(buffer));
            int bytesReceived = SSL_read(ssl_.get(), buffer, sizeof(buffer) - 1);
            if (bytesReceived <= 0) {
                int sslError = SSL_get_error(ssl_.get(), bytesReceived);
                std::cerr << "Error reading data: " << sslError << std::endl;
                break;
            }
            std::vector<char> receivedData(buffer, buffer + bytesReceived);
            readCallback_(receivedData);
            std::cout << "Received " << bytesReceived << " bytes of data from the server. " << std::endl;
        }
    }).detach();
}
