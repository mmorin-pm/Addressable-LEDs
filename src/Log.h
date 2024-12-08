#pragma once

#include <Arduino.h>

#define SERIAL_SPEED 9600
#define ERROR 0
#define INFO 1
#define DEBUG 2
#define TRACE 3

class Log {
    public:
        static size_t loggingLevel;

        static void setLogLevel(size_t level);

        static void LOG_E(const char msg[]);
        static void LOG_E(const char msg[], uint32_t val);

        static void LOG_I(const char msg[]);
        static void LOG_I(const char msg[], uint32_t val);

        static void LOG_D(const char str[]);
        static void LOG_D(const char msg[], uint32_t val);

        static void LOG_T(const char msg[]);
        static void LOG_T(const char msg[], uint32_t val);

        static void FATAL(const char msg[]);
        static void FATAL(const char msg[], uint32_t val);

    private:
        static void LOG(const char msg[], size_t lvl, const char tag[]);
        static void LOG(const char msg[], size_t lvl, const char tag[], uint32_t val);
        static void config();
};