#include "UpgradeFirm.h"

#include "Class/NotAsinc.h"
#include "ESP8266.h"
#include "Global.h"

void upgradeInit() {
    myNotAsincActions->add(
        do_UPGRADE, [&](void*) {
            upgrade_firmware(3);
        },
        nullptr);

    myNotAsincActions->add(
        do_GETLASTVERSION, [&](void*) {
            getLastVersion();
        },
        nullptr);

    if (isNetworkActive()) {
        getLastVersion();
        if (lastVersion > 0) {
            SerialPrint("I", "Update", "available version: " + lastVersion);
        }
    };
}

void getLastVersion() {
    if ((WiFi.status() == WL_CONNECTED)) {
        String tmp = getURL(F("http://95.128.182.133/projects/iotmanager/esp8266/esp8266ver/esp8266ver.txt"));
        if (tmp == "error") {
            lastVersion = -1;
        } else {
            lastVersion = tmp.toInt();
        }
    } else {
        lastVersion = -2;
    }
    jsonWriteInt(configSetupJson, "last_version", lastVersion);
}

void upgrade_firmware(int type) {
    if (type == 1) {  //only build
        if (upgradeBuild()) restartEsp();
    } else if (type == 2) {  //only spiffs
        if (upgradeFS()) restartEsp();
    } else if (type == 3) {  //spiffs and build
        if (upgradeFS()) {
            if (upgradeBuild()) {
                restartEsp();
            }
        }
    }
}

bool upgradeFS() {
    WiFiClient wifiClient;
    bool ret = false;
    Serial.println("Start upgrade LittleFS, please wait...");
    ESPhttpUpdate.rebootOnUpdate(false);
    t_httpUpdate_return retFS = ESPhttpUpdate.updateSpiffs(wifiClient, F("http://95.128.182.133/projects/iotmanager/esp8266/littlefs/littlefs.bin"));
    if (retFS == HTTP_UPDATE_OK) {  //если FS обновилась успешно
        SerialPrint("I", "Update", "LittleFS upgrade done!");
        ret = true;
    }
    return ret;
}

bool upgradeBuild() {
    WiFiClient wifiClient;
    bool ret = false;
    Serial.println("Start upgrade BUILD, please wait...");
    ESPhttpUpdate.rebootOnUpdate(false);
    t_httpUpdate_return retBuild = ESPhttpUpdate.update(wifiClient, F("http://95.128.182.133/projects/iotmanager/esp8266/firmware/firmware.bin"));
    if (retBuild == HTTP_UPDATE_OK) {  //если BUILD обновился успешно
        SerialPrint("I", "Update", "BUILD upgrade done!");
        ret = true;
    }
    return ret;
}

void restartEsp() {
    Serial.println("Restart ESP....");
    delay(1000);
    ESP.restart();
}