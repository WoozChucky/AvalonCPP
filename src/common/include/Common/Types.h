#pragma once

#include <cstdint>
#include <string>
#include <string_view>
#include <memory>

#include <Common/Utilities/advstd.h>

#ifdef AV_DEBUG
#if defined(AV_PLATFORM_WIN)
		#define AV_DEBUGBREAK() __debugbreak()
	#elif defined(AV_PLATFORM_UNIX)
		#include <csignal>
		#define AV_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
		#define AV_ENABLE_ASSERTS
#else
#define AV_DEBUGBREAK()
#endif

#define AV_EXPAND_MACRO(x) x
#define AV_STRINGIFY_MACRO(x) #x

#define BIT(x) (1 << x)

#define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

using S8 = int8_t;
using S16 = int16_t;
using S32 = int32_t;
using S64 = int64_t;

using U8 = uint8_t;
using U16 = uint16_t;
using U32 = uint32_t;
using U64 = uint64_t;

using F32 = float;

using String = std::string;
using StringView = std::string_view;

template<typename T>
using Scope = std::unique_ptr<T>;
template<typename T, typename ... Args>
constexpr Scope<T> CreateScope(Args&& ... args)
{
    return std::make_unique<T>(std::forward<Args>(args)...);
}

template<typename T>
using Ref = std::shared_ptr<T>;
template<typename T, typename ... Args>
constexpr Ref<T> CreateRef(Args&& ... args)
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}

namespace Avalon {
    // end "iterator" tag for find_type_if
    struct find_type_end;

    template<template<typename...> typename Check, typename... Ts>
    struct find_type_if;

    template<template<typename...> typename Check>
    struct find_type_if<Check>
    {
        using type = find_type_end;
    };

    template<template<typename...> typename Check, typename T1, typename... Ts>
    struct find_type_if<Check, T1, Ts...> : std::conditional_t<Check<T1>::value, advstd::type_identity<T1>, find_type_if<Check, Ts...>>
    {
    };

    template<template<typename...> typename Check, typename... Ts>
    using find_type_if_t = typename find_type_if<Check, Ts...>::type;

    template <typename T>
    struct dependant_false { static constexpr bool value = false; };

    template <typename T>
    constexpr bool dependant_false_v = dependant_false<T>::value;
}

constexpr auto MINUTE = 60;
constexpr auto HOUR = MINUTE * 60;
constexpr auto DAY = HOUR * 24;
constexpr auto WEEK = DAY * 7;
constexpr auto MONTH = DAY * 30;
constexpr auto YEAR = MONTH * 12;
constexpr auto IN_MILLISECONDS = 1000;

enum AccountTypes
{
    SEC_PLAYER         = 0,
    SEC_MODERATOR      = 1,
    SEC_GAMEMASTER     = 2,
    SEC_ADMINISTRATOR  = 3,
    SEC_CONSOLE        = 4                                  // must be always last in list, accounts must have less security level always also
};

enum LocaleConstant
{
    LOCALE_enUS = 0,
    LOCALE_koKR = 1,
    LOCALE_frFR = 2,
    LOCALE_deDE = 3,
    LOCALE_zhCN = 4,
    LOCALE_zhTW = 5,
    LOCALE_esES = 6,
    LOCALE_esMX = 7,
    LOCALE_ruRU = 8,

    TOTAL_LOCALES
};

#define DEFAULT_LOCALE LOCALE_enUS

#define MAX_LOCALES 8

#if AV_PLATFORM_WIN
    #define ATTR_PRINTF(F, V)
#elif AV_PLATFORM_UNIX
    #define ATTR_PRINTF(F, V) __attribute__ ((format (printf, F, V)))
#endif

#define UI64LIT(N) UINT64_C(N)
#define SI64LIT(N) INT64_C(N)
