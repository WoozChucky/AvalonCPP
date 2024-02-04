#pragma once

#include <boost/asio/ssl/context.hpp>

class SslContext
{
public:
    static bool Initialize(const std::string& certPath, const std::string& password);

    static boost::asio::ssl::context& Instance();
};
