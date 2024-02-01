#include <fmt/core.h>
#include <google/protobuf/stubs/common.h>

int main(int argc, char** argv) {

    GOOGLE_PROTOBUF_VERIFY_VERSION;

    fmt::print("Hello, world!\n");

    if (argc == 2)
    {
        argv[1] = nullptr;
    }

    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}