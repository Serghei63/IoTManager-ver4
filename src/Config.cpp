#include "Config.h"

void configure(String& path) {
    File file = seekFile(path);

    while (file.available()) {
        String jsonArrayElement = file.readStringUntil('}') + "}";
        String value;
        if (jsonRead(jsonArrayElement, F("subtype"), value)) {
            if (value == F("button-out")) {
                //=============================
            } else if (value == F("pwm-out")) {
                //=============================
            }
        } else {
            SerialPrint(F("E"), F("System"), F("Fatal configuration error, type wrong or missing"));
        }
    }
    file.close();
}