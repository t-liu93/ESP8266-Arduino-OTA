#include "esp8266ota.h"

Esp8266OTA::Esp8266OTA(String hostname, String password)
    : updater()
{
    updater.setHostname(hostname.c_str());
    updater.setPassword(password.c_str());

    updater.onStart([]() {
        Serial.println("Start");
    });
    updater.onEnd([]() {
        Serial.println("\nEnd");
    });

    updater.onProgress([](unsigned int progress, unsigned int total) {
        Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    });

    updater.onError([](ota_error_t error) {
        Serial.printf("Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
        else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
        else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
        else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
        else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });
    updater.begin();
}

Esp8266OTA::Esp8266OTA(String hostname, String password, std::function<void(void)> timerDetatchFunction)
    : updater()
    , m_timerDetatch(timerDetatchFunction)
{
    // std::bind()
    m_timerDetatch = timerDetatchFunction;
    updater.setHostname(hostname.c_str());
    updater.setPassword(password.c_str());

    updater.onStart([&]() {
        m_timerDetatch();
        Serial.println("Start");
    });
    updater.onEnd([]() {
        Serial.println("\nEnd");
    });

    updater.onProgress([](unsigned int progress, unsigned int total) {
        Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    });

    updater.onError([](ota_error_t error) {
        Serial.printf("Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
        else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
        else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
        else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
        else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });
    updater.begin();
}

void Esp8266OTA::handle()
{
    updater.handle();
}