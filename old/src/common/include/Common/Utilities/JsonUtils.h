#include <Common/Types.h>
#include <Common/Utilities/Optional.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace Avalon::Utilities::Json
{
    template<class T>
    Optional<T> Deserialize(const String& jsonStr) {
        json j = json::parse(jsonStr);
        auto obj =  j.template get<T>();
        return obj;
    }

    template<class T>
    std::string Serialize(const T& obj) {
        json j = obj;
        return  j.dump(4);
    }

}

