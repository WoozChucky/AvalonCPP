#include <Common/Utilities/FileUtils.h>

bool File::Exists(const std::string& path) {
    std::ifstream file(path);
    return file.good();
}

bool File::ReadStringContent(const std::string& path, std::string& content) {
    std::ifstream file(path);
    if (!file.good()) {
        return false;
    }
    std::string line;
    while (std::getline(file, line)) {
        content += line + "\n";
    }
    return true;
}

bool File::ReadBinaryContent(const std::string& path, std::vector<U8>& content) {
    std::ifstream file(path, std::ios::binary);
    if (!file.good()) {
        return false;
    }
    file.seekg(0, std::ios::end);
    content.resize(file.tellg());
    file.seekg(0, std::ios::beg);
    file.read(reinterpret_cast<char *>(content.data()), content.size());
    file.close();
    return true;
}
