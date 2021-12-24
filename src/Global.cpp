#include "Global.h"

/*********************************************************************************************************************
*****************************************глобальные объекты классов***************************************************
**********************************************************************************************************************/

TickerScheduler ts(MYTEST + 1);
WiFiClient espClient;
#ifdef ASYNC_WEB_SERVER
AsyncWebServer server(80);
#endif

#ifdef STANDARD_WEB_SERVER
#ifdef ESP8266
ESP8266HTTPUpdateServer httpUpdater;
ESP8266WebServer HTTP(80);
#endif
#ifdef ESP32
WebServer HTTP(80);
#endif
#endif

#ifdef STANDARD_WEB_SOCKETS
WebSocketsServer standWebSocket = WebSocketsServer(81);
#endif

/*********************************************************************************************************************
***********************************************глобальные переменные**************************************************
**********************************************************************************************************************/

String settingsFlashJson = "{}";  //переменная в которой хранятся все настройки, находится в оперативной памяти и синхронизированна с flash памятью
String paramsFlashJson = "{}";    //переменная в которой хранятся все параметры, находится в оперативной памяти и синхронизированна с flash памятью
String paramsHeapJson = "{}";     //переменная в которой хранятся все параметры, находится в оперативной памяти только