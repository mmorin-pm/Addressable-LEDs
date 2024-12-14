#include <Log.h>
#include <ESPTelnet.h>

size_t Log::loggingLevel = level::Info;

transport Log::tran = transport::SerialPort;

static ESPTelnet telnet;

void onTelnetConnect(String ip) {
  Serial.print("- Telnet: ");
  Serial.print(ip);
  Serial.println(" connected");
  
  telnet.println("\nWelcome " + telnet.getIP());
  telnet.println("(Use ^] + q  to disconnect.)");
}

void onTelnetDisconnect(String ip) {
  Serial.print("- Telnet: ");
  Serial.print(ip);
  Serial.println(" disconnected");
}

void onTelnetReconnect(String ip) {
  Serial.print("- Telnet: ");
  Serial.print(ip);
  Serial.println(" reconnected");
}

void onTelnetConnectionAttempt(String ip) {
  Serial.print("- Telnet: ");
  Serial.print(ip);
  Serial.println(" tried to connected");
}

void setupTelnet() {  
  // passing on functions for various telnet events
  telnet.onConnect(onTelnetConnect);
  telnet.onConnectionAttempt(onTelnetConnectionAttempt);
  telnet.onReconnect(onTelnetReconnect);
  telnet.onDisconnect(onTelnetDisconnect);

  Serial.print("- Telnet: ");
  if (telnet.begin(TELNET_PORT)) {
    Serial.println("running");
  } else {
    Serial.println("error.");
  }
}

void Log::logLoop() {
    if (tran == transport::TelnetPort) {
        telnet.loop();
    }
}

void Log::config() {
    static bool isConfigured = false;
    if (isConfigured == false) {
       Serial.begin(SERIAL_SPEED);
    //    while(!Serial); // This makes it so that program doesn't start until serial window is openned... (will block OTA updates!)
       delay(1000);
       Serial.print("\nSerial configured at speed: ");
       Serial.print(SERIAL_SPEED);
       Serial.println();
       isConfigured = true;
       if (tran == transport::TelnetPort) {
        setupTelnet();
       }
    }
}

void Log::setLogLevel(size_t level, transport t) {
    Log::loggingLevel = level;
    Log::tran = t;
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
        switch(tran){
            case transport::TelnetPort:
                telnet.print(tag);
                telnet.print(": ");
                telnet.println(msg);
                break;
            case transport::SerialPort:
            default:
                Serial.print(tag);
                Serial.print(": ");
                Serial.println(msg);
                break;
        }
    }
}

void Log::LOG(const char msg[], level lvl, const char tag[], uint32_t val) {
    Log::config();
    if (loggingLevel >= lvl) {
        switch(tran){
            case transport::TelnetPort:
                telnet.print(tag);
                telnet.print(": ");
                telnet.print(msg);
                telnet.println(val);
                break;
            case transport::SerialPort:
            default:
                Serial.print(tag);
                Serial.print(": ");
                Serial.print(msg);
                Serial.println(val);
                break;
        }
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