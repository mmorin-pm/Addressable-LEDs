#pragma once

#include <Arduino.h>
#include <Definitions.h>

enum level {
    Error,
    Info,
    Debug, 
    Trace
};

enum transport {
    SerialPort,
    TelnetPort
};

class Log {
    public:
        static size_t loggingLevel;
        static transport tran;
        static bool telnetConnected;

        static void setLogLevel(size_t level, transport t);

        static void logLoop();

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
        static void LOG(const char msg[], level lvl, const char tag[]);
        static void LOG(const char msg[], level lvl, const char tag[], uint32_t val);
        static void config();
};