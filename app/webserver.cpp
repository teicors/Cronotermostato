// #include <user_config.h>
#include <SmingCore.h>
//#include <JsonObjectStream5.h>A
#include <SmingCore/Data/Stream/JsonObjectStream.h>
#include "configuration.h"
#include <CronLibrary/Cron.h>

HttpServer server;

bool serverStarted = false;
extern String alarmtime, sleeptime;
extern int sleepenabled,alarmenabled, buzzerenabled;
//extern void setpwn(int led0);
extern void sendData();
extern Cron cron;
extern CronoTempConfig CronoTempCfg;
extern LampMessage LampMsg;
extern float temperature;
extern float humidity ;

// If you want, you can define WiFi settings globally in Eclipse Environment Variables
#ifndef WIFI_SSID
	#define WIFI_SSID "PleaseEnterSSID" // Put you SSID and Password here
	#define WIFI_PWD "PleaseEnterPass"
#endif


void onIndex(HttpRequest &request, HttpResponse &response)
{
    TemplateFileStream *tmpl = new TemplateFileStream("index.html");
    auto &vars = tmpl->variables();
    vars["temperature"] = CronoTempCfg.temperature;
    vars["noicetemp"] = CronoTempCfg.noicetemp;
    vars["welltemp"] = CronoTempCfg.welltemp;
    vars["stringtime1"] = CronoTempCfg.stringtime1;
    vars["stringtime2"] = CronoTempCfg.stringtime2;
    vars["stringtime3"] = CronoTempCfg.stringtime3;
    vars["stringtime4"] = CronoTempCfg.stringtime4;
    vars["stringtime5"] = CronoTempCfg.stringtime5;
    vars["stringtime6"] = CronoTempCfg.stringtime6;
    vars["stringtime5"] = CronoTempCfg.stringtime7;
    vars["temp"] = temperature;
    vars["date"] = SystemClock.now();
    debugf("Send Home Page");
    response.sendTemplate(tmpl);
}

void onConfiguration(HttpRequest &request, HttpResponse &response)
{
//    LampConfig cfg = loadConfig();
    loadConfig();
    if (request.method == HTTP_POST)
    {
            debugf("Update config");
            // Update config
            if (request.getPostParameter("SSID").length() > 0) // Network
            {
                    CronoTempCfg.NetworkSSID = request.getPostParameter("SSID");
                    CronoTempCfg.NetworkPassword = request.getPostParameter("Password");
            }
            saveConfig();
//            startWebClock(); // Apply time zone settings
            response.headers[HTTP_HEADER_LOCATION] = "/";

//            response.redirect("/");
    }

    debugf("Send template");
    TemplateFileStream *tmpl = new TemplateFileStream("config.html");
    auto &vars = tmpl->variables();
    vars["SSID"] = CronoTempCfg.NetworkSSID;
    response.sendTemplate(tmpl);
}
/*
void onFile(HttpRequest &request, HttpResponse &response)
{
    String file = request.getPath();
    if (file[0] == '/')
            file = file.substring(1);

    if (file[0] == '.')
            response.forbidden();
    else
    {JSON.stringify($('#test1').scheduler('val'))
            response.setCache(86400, true); // It's important to use cache for better performance.
            response.sendFile(file);
    }
}
*/
void onFile(HttpRequest& request, HttpResponse& response)
{
        String file = request.uri.getRelativePath();

        if(file[0] == '.')
                response.code = HTTP_STATUS_FORBIDDEN;
        else {
                response.setCache(86400, true); // It's important to use cache for better performance.
                response.sendFile(file);
        }
}

/// API ///
//char FromNumberToBit (JsonObject& valore)
//{
//  char result="000000000000000000000000000000000000000000000000";
//  for(int i = 0; i < valore.size(); i++) {
//      result[valore[i]]="1";
//      result.substr(0, valore[i]-1) + "1" + result.substr(valore[i]+1);
//      int indice=valore[i];
//      result[indice]="1";
 //     result.replace(valore[i], 1, "1");
//    }  
//  return result*;
//}


void onApiTime(HttpRequest &request, HttpResponse &response)
{
    
    String timefromweb=(String)request.getPostParameter("time");
    Serial.printf("timefromweb %s\n",timefromweb.c_str());
    
    DynamicJsonBuffer jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(timefromweb);

//    String s1=root["1"];
//    String s2=root["2"];
//    String s3=root["3"];
//    String s4=root["4"];
//    String s5=root["5"];
//    String s6=root["6"];
//    String s7=root["7"];
      
      String  s="000000000000000000000000000000000000000000000000";
      String s1="000000000000000000000000000000000000000000000000";
      String s2="000000000000000000000000000000000000000000000000";
      String s3="000000000000000000000000000000000000000000000000";
      String s4="000000000000000000000000000000000000000000000000";
      String s5="000000000000000000000000000000000000000000000000";
      String s6="000000000000000000000000000000000000000000000000";
      String s7="000000000000000000000000000000000000000000000000";
     
    
//    Serial.printf("s1 %s\n",s1.c_str());
//    Serial.printf("s2 %s\n",s2.c_str());
//    Serial.printf("s3 %s\n",s3.c_str());
//    Serial.printf("s4 %s\n",s4.c_str());
//    Serial.printf("s5 %s\n",s5.c_str());
//    Serial.printf("s6 %s\n",s6.c_str());
//    Serial.printf("s7 %s\n",s7.c_str());
    int arraySize0 =  root.size();
    int arraySize1 =  root["1"].size();
    int arraySize2 =  root["2"].size();
    int arraySize3 =  root["3"].size();
    int arraySize4 =  root["4"].size();
    int arraySize5 =  root["5"].size();
    int arraySize6 =  root["6"].size();
    int arraySize7 =  root["7"].size();
//    Serial.printf("arraySize0 %d\n",arraySize0);
//    Serial.printf("arraySize1 %d\n",arraySize1);
//    Serial.printf("arraySize2 %d\n",arraySize2);
//    Serial.printf("arraySize3 %d\n",arraySize3);
//    Serial.printf("arraySize4 %d\n",arraySize4);
//    Serial.printf("arraySize5 %d\n",arraySize5);
//    Serial.printf("arraySize6 %d\n",arraySize6);
//    Serial.printf("arraySize7 %d\n",arraySize7);
    
    JsonArray& a1 = root["1"];
    JsonArray& a2 = root["2"];
    JsonArray& a3 = root["3"];
    JsonArray& a4 = root["4"];
    JsonArray& a5 = root["5"];
    JsonArray& a6 = root["6"];
    JsonArray& a7 = root["7"];
    
    for (int i=0; i< a1.size(); i++) {
        s=s.substring(0,(int)a1[i])+"1"+s.substring((int)a1[i]+1);
        Serial.printf("Ciclo S1 %s\n",s.c_str());
    }
    CronoTempCfg.stringtime1=s;
    
        s="000000000000000000000000000000000000000000000000";
    for (int i=0; i< a2.size(); i++) {
        s=s.substring(0,(int)a2[i])+"1"+s.substring((int)a2[i]+1);
        Serial.printf("Ciclo S2 %s\n",s.c_str());
    }
    CronoTempCfg.stringtime2=s;
    
        s="000000000000000000000000000000000000000000000000";
    for (int i=0; i< a3.size(); i++) {
        s=s.substring(0,(int)a3[i])+"1"+s.substring((int)a3[i]+1);
        Serial.printf("Ciclo S3 %s\n",s.c_str());
    }
    CronoTempCfg.stringtime3=s;
    
        s="000000000000000000000000000000000000000000000000";
    for (int i=0; i< a4.size(); i++) {
        s=s.substring(0,(int)a4[i])+"1"+s.substring((int)a4[i]+1);
        Serial.printf("Ciclo S4 %s\n",s.c_str());
    }
    CronoTempCfg.stringtime4=s;
    
        s="000000000000000000000000000000000000000000000000";
    for (int i=0; i< a5.size(); i++) {
        s=s.substring(0,(int)a5[i])+"1"+s.substring((int)a5[i]+1);
        Serial.printf("Ciclo S5 %s\n",s.c_str());
    }
    CronoTempCfg.stringtime5=s;
    
        s="000000000000000000000000000000000000000000000000";
    for (int i=0; i< a6.size(); i++) {
        s=s.substring(0,(int)a6[i])+"1"+s.substring((int)a6[i]+1);
        Serial.printf("Ciclo S6 %s\n",s.c_str());
    }
    CronoTempCfg.stringtime6=s;
    
        s="000000000000000000000000000000000000000000000000";
    for (int i=0; i< a7.size(); i++) {
        s=s.substring(0,(int)a7[i])+"1"+s.substring((int)a7[i]+1);
        Serial.printf("Ciclo S7 %s\n",s.c_str());
    }
    CronoTempCfg.stringtime7=s;
    
    Serial.printf("s1 %s\n",s1.c_str());
    
    for (int i=0; i< a2.size(); i++) {
        Serial.printf("a2[i] %d\n",(int)a2[i]);
    }
    for (int i=0; i< a3.size(); i++) {
        Serial.printf("a3[i] %d\n",(int)a3[i]);
    }
    for (int i=0; i< a4.size(); i++) {
        Serial.printf("a4[i] %d\n",(int)a4[i]);
    }
    for (int i=0; i< a5.size(); i++) {
        Serial.printf("a5[i] %d\n",(int)a5[i]);
    }
    for (int i=0; i< a6.size(); i++) {
        Serial.printf("a6[i] %d\n",(int)a6[i]);
    }
    for (int i=0; i< a7.size(); i++) {
        Serial.printf("a7[i] %d\n",(int)a7[i]);
    }
    
    int what=request.getPostParameter("state").toInt();
    switch (what) {
        case 1: CronoTempCfg.stringtime1=s1; break;
        case 2: CronoTempCfg.stringtime2=s2; break;
        case 3: CronoTempCfg.stringtime3=s3; break;
        case 4: CronoTempCfg.stringtime4=s4; break;
        case 5: CronoTempCfg.stringtime5=s5; break;
        case 6: CronoTempCfg.stringtime6=s6; break;
        case 7: CronoTempCfg.stringtime7=s7; break;
    }
//    LampCfg.buzzerenabled = request.getPostParameter("state").toInt();
    LampMsg.evento = TIME;
    LampMsg.pulsante = what;
    LampMsg.stato = 1;
    LampMsg.valore = 60*timefromweb.substring(0,2).toInt()+timefromweb.substring(3,5).toInt();   
    cron.UpdateCommand(what,1,"00."+timefromweb.substring(3,5)+"."+timefromweb.substring(0,2)+".*.*.*");
    saveConfig();
    sendData();
//    debugf("Update onApiBuzzer");
}


void onApiDoc(HttpRequest &request, HttpResponse &response)
{
        TemplateFileStream *tmpl = new TemplateFileStream("api.html");
        auto &vars = tmpl->variables();
        vars["IP"] = (WifiStation.isConnected() ? WifiStation.getIP() : WifiAccessPoint.getIP()).toString();
        response.sendTemplate(tmpl);
}

void onApiStatus(HttpRequest &request, HttpResponse &response)
{
    JsonObjectStream* stream = new JsonObjectStream();
    JsonObject& json = stream->getRoot();
    json["status"] = (bool)true;
    JsonObject& sensors = json.createNestedObject("sensors");
    sensors["temp"] = CronoTempCfg.temperature;
    sensors["noicetemp"] = CronoTempCfg.noicetemp;
    sensors["welltemp"] = CronoTempCfg.welltemp;
    sensors["stringtime1"] = CronoTempCfg.stringtime1;
    sensors["stringtime2"] = CronoTempCfg.stringtime2;
    sensors["stringtime3"] = CronoTempCfg.stringtime3;
    sensors["stringtime4"] = CronoTempCfg.stringtime4;
    sensors["stringtime5"] = CronoTempCfg.stringtime5;
    sensors["stringtime6"] = CronoTempCfg.stringtime6;
    sensors["stringtime5"] = CronoTempCfg.stringtime7;
//    response.sendJsonObject(stream);
    response.sendDataStream(stream, MIME_JSON);
}

void OnApiShowInfo(HttpRequest &request, HttpResponse &response) {
    Serial.printf("\r\nSDK: v%s\r\n", system_get_sdk_version());
    Serial.printf("Free Heap: %d\r\n", system_get_free_heap_size());
    Serial.printf("CPU Frequency: %d MHz\r\n", system_get_cpu_freq());
    Serial.printf("System Chip ID: %x\r\n", system_get_chip_id());
    Serial.printf("SPI Flash ID: %x\r\n", spi_flash_get_id());
    Serial.printf("SPI Flash Size: %d\r\n", (1 << ((spi_flash_get_id() >> 16) & 0xff)));
}


void OnAjaxDate(HttpRequest& request, HttpResponse& response) {
    JsonObjectStream* stream = new JsonObjectStream();
    JsonObject& json = stream->getRoot();
    json["status"] = (bool)true;
    json["value"] = SystemClock.now();
    response.sendDataStream(stream, MIME_JSON);
}

void OnAjaxTemp(HttpRequest& request, HttpResponse& response) {
    JsonObjectStream* stream = new JsonObjectStream();
    JsonObject& json = stream->getRoot();
    json["status"] = (bool)true;
    json["value"] = temperature;
    response.sendDataStream(stream, MIME_JSON);
}

void onReboot(HttpRequest &request, HttpResponse &response)
{
    System.restart();
}


void startWebServer()
{
    if (serverStarted) return;

    server.listen(80);
    server.paths.set("/", onIndex);
    server.paths.set("/api", onApiDoc);
    server.paths.set("/api/status", onApiStatus);
    server.paths.set("/api/time", onApiTime);
    server.paths.set("/api/info", OnApiShowInfo);    
    server.paths.set("/api/date", OnAjaxDate);    
    server.paths.set("/api/temp", OnAjaxTemp);    
    server.paths.set("/config", onConfiguration);
    server.paths.set("/reboot", onReboot);
    server.paths.setDefault(onFile);
//    server.setDefaultHandler(onFile);
    serverStarted = true;

    if (WifiStation.isEnabled())
            debugf("STA: %s", WifiStation.getIP().toString().c_str());
    if (WifiAccessPoint.isEnabled())
        debugf("AP: %s", WifiAccessPoint.getIP().toString().c_str());
}

/// FileSystem Initialization ///
/*
HttpClient downloadClient;
int dowfid = 0;
void downloadContentFiles()
{
	debugf("DownloadContentFiles");

	downloadClient.downloadFile("http://simple.anakod.ru/templates/MeteoControl/MeteoControl.html", "index.html");
	downloadClient.downloadFile("http://simple.anakod.ru/templates/MeteoControl/MeteoConfig.html", "config.html");
	downloadClient.downloadFile("http://simple.anakod.ru/templates/MeteoControl/MeteoAPI.html", "api.html");
	downloadClient.downloadFile("http://simple.anakod.ru/templates/bootstrap.css.gz");
	downloadClient.downloadFile("http://simple.anakod.ru/templates/jquery.js.gz",
								(RequestCompletedDelegate)([](HttpConnection& connection, bool success) -> int {
									if(success) {
										startWebServer();
									}
                                                                        return true;
								}));
}
*/
