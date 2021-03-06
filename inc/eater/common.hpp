#ifndef EATER_COMMON_HPP_
#define EATER_COMMON_HPP_

#include <stdint.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>

#define DEBUG
#define COLOR
#define ENABLE_ERROR
#define ENABLE_WARNING
#define ENABLE_MESSAGE

#ifdef DEBUG
#define E_Debug(msg) \
    std::cerr << __FILE__ << ":" << __LINE__ << ": " << msg << std::endl
#else
#define E_Debug(msg)
#endif

#ifdef COLOR
#define E_BLACK(msg) "\033[1;30m" << msg << "\033[0m"
#define E_RED(msg) "\033[1;31m" << msg << "\033[0m"
#define E_GREEN(msg) "\033[1;32m" << msg << "\033[0m"
#define E_YELLOW(msg) "\033[1;33m" << msg << "\033[0m"
#define E_BLUE(msg) "\033[1;34m" << msg << "\033[0m"
#define E_MAGENTA(msg) "\033[1;35m" << msg << "\033[0m"
#define E_CYAN(msg) "\033[1;36m" << msg << "\033[0m"
#define E_WHITE(msg) "\033[1;37m" << msg << "\033[0m"
#else
#define E_RED(msg) msg
#define E_GREEN(msg) msg
#define E_YELLOW(msg) msg
#define E_BLUE(msg) msg
#define E_MAGENTA(msg) msg
#define E_CYAN(msg) msg
#define E_WHITE(msg) msg
#endif

#define LOGG(msg) std::cout << msg
#define LOGG_LN(msg) std::cout << msg << std::endl

#ifdef ENABLE_ERROR
#define LOGG_ERROR(msg) std::cout << E_MAGENTA("ERROR: ") << msg << std::endl
#ifdef ENABLE_WARNING
#define LOGG_WARNING(msg) std::cout << E_RED("WARNING: ") << msg << std::endl
#ifdef ENABLE_MESSAGE
#define LOGG_MESSAGE(msg) std::cout << "MSG: " << msg << std::endl
#endif
#endif
#endif

#define CHECK_RESULT(b);                 \
    if (!b) {                            \
        LOGG_ERROR(__PRETTY_FUNCTION__); \
        return false;                    \
    }

namespace eater
{
typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

typedef int64_t i64;
typedef int32_t i32;
typedef int16_t i16;
typedef int8_t i8;

typedef float f32;
typedef double f64;

typedef i32 id_t;

typedef std::string str;

template<class T> using vec = std::vector<T>;
typedef vec<id_t> id_vec;
typedef vec<str> str_vec;
}

#endif /* EATER_COMMON_HPP_ */
