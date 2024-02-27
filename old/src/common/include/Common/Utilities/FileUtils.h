#pragma once

#include <Common/Types.h>
#include <fstream>
#include <vector>

namespace File {

    bool Exists(const std::string& path);
    bool ReadStringContent(const std::string& path, std::string& content);
    bool ReadBinaryContent(const std::string& path, std::vector<U8>& content);

}


