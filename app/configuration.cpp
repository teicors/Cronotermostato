#include <Libraries/Default/configuration.h>
#include <SmingCore/Data/Stream/JsonObjectStream.h>
#include <SmingCore.h>

LampConfig ActiveConfig;

#define SENSORDATA_JSON_SIZE (JSON_OBJECT_SIZE(8))

extern	String NetworkSSID;
extern	String NetworkPassword;
extern  CronoTempConfig CronoTempCfg;


void loadConfig()
{
    DynamicJsonBuffer jsonBuffer;
    LampConfig cfg;
    if (fileExist(CRONOTEMP_CONFIG_FILE))
    {
        int size = fileGetSize(CRONOTEMP_CONFIG_FILE);
        char* jsonString = new char[size + 1];
        fileGetContent(LAMP_CONFIG_FILE, jsonString, size + 1);
        JsonObject& root = jsonBuffer.parseObject(jsonString);
        
        CronoTempCfg.temperature = root["temperature"];
        CronoTempCfg.noicetemp = root["noicetemp"];
        CronoTempCfg.welltemp = root["welltemp"];
        
        CronoTempCfg.stringtime[1] = String((const char*)root["stringtime1"]);
        CronoTempCfg.stringtime[2] = String((const char*)root["stringtime2"]);
        CronoTempCfg.stringtime[3] = String((const char*)root["stringtime3"]);
        CronoTempCfg.stringtime[4] = String((const char*)root["stringtime4"]);
        CronoTempCfg.stringtime[5] = String((const char*)root["stringtime5"]);
        CronoTempCfg.stringtime[6] = String((const char*)root["stringtime6"]);
        CronoTempCfg.stringtime[7] = String((const char*)root["stringtime7"]);
        
        delete[] jsonString;
    }
    else
    {
        debugf("Il file non esiste");
        CronoTempCfg.NetworkSSID = WIFI_SSID;
        CronoTempCfg.NetworkPassword = WIFI_PWD;
    }

//    String s;
//    s += CronoTempCfg.stringtime[1];
//    s += CronoTempCfg.stringtime[2];
//    s += CronoTempCfg.stringtime[3];
//    s += CronoTempCfg.stringtime[4];
//    s += CronoTempCfg.stringtime[5];
//    s += CronoTempCfg.stringtime[6];
//    s += CronoTempCfg.stringtime[7];
    
//        {"1":[0,1,2,3,4,5,45,46,47],"2":[0,1,2,3,4,5,34,35,36,37,38,39,40,41,45,46,47], ... }
////    for (int i=0; i<49; i++) {
////        if (CronoTempCfg.stringtime1.substring(i,1) = "1") {
//            String Result=to_string(i);
//            s=s+Result+",";
////        }
////    }
//    Serial.println(s);
//    s=s.substring(0,s.length()-1);
}

void saveConfig()
{
    DynamicJsonBuffer jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();

    root["stringtime1"] = CronoTempCfg.stringtime[1];
    root["stringtime2"] = CronoTempCfg.stringtime[2];
    root["stringtime3"] = CronoTempCfg.stringtime[3];
    root["stringtime4"] = CronoTempCfg.stringtime[4];
    root["stringtime5"] = CronoTempCfg.stringtime[5];
    root["stringtime6"] = CronoTempCfg.stringtime[6];
    root["stringtime7"] = CronoTempCfg.stringtime[7];

    root["temperature"] = CronoTempCfg.temperature;
    root["noicetemp"] = CronoTempCfg.noicetemp;
    root["welltemp"] = CronoTempCfg.welltemp;

    
    char buf[3096];
    root.prettyPrintTo(buf, sizeof(buf));
    fileSetContent(LAMP_CONFIG_FILE, buf);
    root.printTo(Serial);
}


