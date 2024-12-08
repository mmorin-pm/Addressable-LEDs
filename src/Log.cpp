#include <Log.h>

size_t Log::loggingLevel = level::Info;

void Log::config() {
    static bool isConfigured = false;
    if (isConfigured == false) {
       Serial.begin(SERIAL_SPEED);
    //    while(!Serial); // This makes it so that program doesn't start until serial window is openned...
       delay(1000);
       Serial.print("\nSerial configured at speed: ");
       Serial.print(SERIAL_SPEED);
       Serial.println();
       isConfigured = true;
    }
}

void Log::setLogLevel(size_t level) {
    Log::loggingLevel = level;
    Log::config();
}

void Log::LOG_E(const char msg[]) {
    Log::LOG(msg, level::Error, "ERROR");
}

void Log::LOG_E(const char msg[], uint32_t val) {
    Log::LOG(msg, level::Error, "ERROR", val);
}

void Log::LOG_I(const char msg[]) {
    Log::LOG(msg, level::Info, "INFO");
}

void Log::LOG_I(const char msg[], uint32_t val) {
    Log::LOG(msg, level::Info, "INFO", val);
}

void Log::LOG_D(const char msg[]) {
    Log::LOG(msg, level::Debug, "DEBUG");
}

void Log::LOG_D(const char msg[], uint32_t val) {
    Log::LOG(msg, level::Debug, "DEBUG", val);
}

void Log::LOG_T(const char msg[]) {
    Log::LOG(msg, level::Trace, "TRACE");
}

void Log::LOG_T(const char msg[], uint32_t val) {
    Log::LOG(msg, level::Trace, "TRACE", val);
}

void Log::LOG(const char msg[], level lvl, const char tag[]) {
    Log::config();
    if (loggingLevel >= lvl) {
        Serial.print(tag);
        Serial.print(": ");
        Serial.println(msg);
    }
}

void Log::LOG(const char msg[], level lvl, const char tag[], uint32_t val) {
    Log::config();
    if (loggingLevel >= lvl) {
        Serial.print(tag);
        Serial.print(": ");
        Serial.print(msg);
        Serial.println(val);
    }
}

void Log::FATAL(const char msg[]) {
    Log::config();
    while(1) {
        Serial.println("FATAL_ERROR: ");
        Serial.println(msg);
        delay(3000);
    }
}

void Log::FATAL(const char msg[], uint32_t val) {
    Log::config();
    while(1) {
        Serial.print("FATAL_ERROR: ");
        Serial.print(msg);
        Serial.println(val);
        delay(3000);
    }
}