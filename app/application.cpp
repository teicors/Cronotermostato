//#include <user_config.h>
#include <SmingCore.h>
#include <Libraries/ArduinoJson/ArduinoJson.h>

///////////////////////////////////////////////////////////////////
// Set your SSID & Pass for initial configuration
#include "configuration.h" // application configuration
///////////////////////////////////////////////////////////////////
// wget "http://192.168.1.220/api/output?status=1&led=2" -o pippo
///////////////////////////////////////////////////////////////////
#include "special_chars.h"
#include "webserver.h"
//#include <Libraries/CronLibrary/TimedCommand.h>
//#include <Libraries/CronLibrary/Cron.h>
#include "NtpClientDemo.h"
#include <Libraries/Timezone/include/Timezone.h>
#include <Libraries/SolarCalculator/include/SolarCalculator.h>
#include <Libraries/OneWire/OneWire.h>
#include <Libraries/DS18S20/ds18s20.h>
#include <Libraries/Adafruit_ILI9341_NEW/Adafruit_ILI9341_NEW.h>
#include <c_types.h>
#include <Libraries/Adafruit_GFX_Library_master/Adafruit_GFX.h>
#include <Libraries/XPT2046/XPT2046.h>
#include "BPMDraw.h"
#include "FreeSansBold9pt7b.h"
#include "DSEG7ClassicRegular18pt7b.h"

/*
Pinout:
MISO GPIO12 D6
MOSI GPIO13 D7
CLK GPIO14  D5
CS GPIO15
DC GPIO5
RST GPIO4
*/

XPT2046 touch(/*cs=*/ D0, /*irq=*/ D3);

// # include <Libraries/Adafruit_ST7735/Adafruit_ST7735.h>
// # include <Libraries/Adafruit_GFX/Adafruit_GFX.h>
// # include <Adafruit-GFX-Library/Adafruit_GFX.h>
// # include <Adafruit_GFX_AS/Font7s.h>

//#define TFT_CLK        14 /* D5 */
//#define TFT_MOSI        13 /* D7 */
//#define TFT_RST         0 /* D0 */
//#define TFT_DC          15 /* D8 */ 
//#define TFT_CS          4  /* D2 */

// in this demo, the same ports for HW and SW SPI are used
Adafruit_ILI9341_NEW tft; // = Adafruit_ILI9341_NEW(TFT_CS, TFT_DC, TFT_RST);

#define LCD 1
// 0 BN
// 1 COLOR
#define TYPEOFBOARD 00

//uint8_t pins[1] = {15}; // List of pins that you want to connect to pwm
//HardwarePWM HW_pwm(pins, 1);
void onNtpReceive(NtpClient& client, time_t timestamp);
// Callback example using defined class ntpClientDemo
NtpClientDemo* demo;

#define MAX_READ 101

#define JSON_HOST "10.10.20.1"
#define JSON_PORT 8111

Timer Timer0;
Timer CronTimer;
Timer TempTimer;

boolean commasec;
int inter0;
int verso;
int data_to_send;
int32_t read0, last0, led0;
String StrTime;
DateTime ShowMyTime;
int32_t ColoreOrario;
boolean OldStatoRelais=false; 
boolean StatoRelais=false;
uint16_t x, y, xold, yold;

float humidity = 0;
float temperature = 0;
float temp=0;
float Old_temp=0;
uint32_t startTime;

CronoTempConfig CronoTempCfg;
CronoTempMessage CronoTempMsg;


DS18S20 ReadTemp;
FtpServer ftp;

void onNtpReceive(NtpClient& client, time_t timestamp);
void DisplayTimeClock(uint8_t hour, uint8_t minutes, uint8_t seconds);
void DisplayDateClock(uint8_t day, uint8_t month, uint16_t year);

#if LCD == 0
// Do not need the board's setup 
#else

//Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
//Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);


//Adafruit_ST7735_AS tft = Adafruit_ST7735_AS(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
//Adafruit_ST7735_AS tft = Adafruit_ST7735_AS(TFT_CS, TFT_DC, TFT_RST);
//Adafruit_ST7735 tft1 = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
#endif

    uint8_t Old_Hour = 25;
    uint8_t Old_Minute = 61;
    uint8_t Old_Second = 61;
//    uint16_t Old_Milliseconds;
    uint8_t Old_Day = 40;
    uint8_t Old_DayofWeek = 8; // Sunday is day 0
    uint8_t Old_Month =  13; // Jan is month 0
    uint16_t Old_Year = 100;  // Full Year numer

//Central European Time (Frankfurt, Paris)
TimeChangeRule *tcr;        //pointer to the time change rule, use to get the TZ abbrev
TimeChangeRule CEST = {"CEST", Last, Sun, Mar, 2, 120};     //Central European Summer Time
TimeChangeRule CET = {"CET ", Last, Sun, Oct, 3, 60};       //Central European Standard Time
Timezone CE(CEST, CET);


//
// TimedCommand 1 : PowerOff
// TimedCommand 2 : Alarm
// TimedCommand 3 : Buzzer
//

// Abilitato, CrontSring, Cosa, PIN
//TimedCommand command01("0","00.*.*.*.*.*","ONN","13");

// create an array of timed commands
//TimedCommand *tCommands[] = {
//    &command01,
//}
//;
        
// create a cron object and pass it the array of timed commands
// and the count of timed commands
//Cron cron(tCommands,1);


// Forward declarations
void onMessageReceived(String topic, String message);
//void publishMessage(int evento, int linea, int tempo);
void sendData();
//void setpwn(int led0);


void JsonOnComplete(TcpClient& client, bool successful)
{
    // debug msg
    debugf("JsonOnComplete");
    debugf("successful: %d", successful);
    client.close();
}

void JsonOnReadyToSend(TcpClient& client, TcpConnectionEvent sourceEvent)
{
    // debug msg
    debugf("JsonOnReadyToSend");
    debugf("sourceEvent: %d", sourceEvent);

    // The connection is made at the time of shipment
    if(sourceEvent == eTCE_Connected)
    {
        DynamicJsonBuffer jsonBuffer;
        JsonObject& MsgToSend = jsonBuffer.createObject();

        MsgToSend["basetta"] = WifiStation.getIP().toString();
        MsgToSend["evento"]  = CronoTempMsg.evento;
        MsgToSend["stato"]   = CronoTempMsg.stato;

        client.sendString("POST /json HTTP/1.1\r\n");
        client.sendString("Accept: */*\r\n");
        client.sendString("Content-Type: application/json;charset=utf-8\r\n");
        client.sendString("Content-Length: "+String(MsgToSend.measureLength()+1)+"\r\n");
        client.sendString("\r\n");
        char buf[MsgToSend.measureLength()];
        MsgToSend.printTo(buf, sizeof(buf)+1);
        client.sendString(buf);
        MsgToSend.printTo(Serial);
        client.sendString("\r\n");
    }
}

bool JsonOnReceive(TcpClient& client, char *buf, int size)
{
    // debug msg
    debugf("JsonOnReceive");
    debugf("%s", buf);
    client.close();
    return true;
}

// Create an object of class JsonMon TcpClient
TcpClient JsonMon(JsonOnComplete, JsonOnReadyToSend, JsonOnReceive);



// This function will be called by timer
void sendData()
{
    // We read the sensor data
    // connect to the server narodmon
    JsonMon.connect(JSON_HOST, JSON_PORT);
}


// Callback for messages, arrived from MQTT server
void onMessageReceived(String topic, String message)
{
    Serial.print(topic);
    Serial.print(":\r\n\t"); // Pretify alignment for printing
    Serial.println(message);
}

/*
void check_button0() {
//  read0 = micros();
//  if (cron.setAlarm==false and digitalRead(PIN_BUTTON)==1 ) {
        if (inter0==true) {   
//            if (last0 < read0-40000) 
//            {
//                last0=read0;
                LampCfg.lamp=LampCfg.lamp+2*verso;
                if (LampCfg.lamp<0) {LampCfg.lamp=0;}
                if (LampCfg.lamp>MAX_READ-1) {LampCfg.lamp=MAX_READ-1; }
                setpwn(LampCfg.lamp);
                Serial.printf("Lamp %d\n",LampCfg.lamp);
//            }
        }
     if (data_to_send==1) {
        LampMsg.evento = LIGHT;
        LampMsg.stato=Lampada_radiocontrollata;
        LampMsg.valore=LampCfg.lamp;
        LampMsg.pulsante=0;
        saveConfig();
        sendData();
        data_to_send=0;    
    }
  
//    }
}

void IRAM_ATTR interruptHandler01();

void IRAM_ATTR interruptHandler00()
{
    inter0=true;
//    debugf("Key pressed Value %d",cfg.lamp);
//    debugf("Pressed : interrupt1 %d interrupt2 %d delta %d\n",interrupt1,interrupt2, interrupt1-interrupt2);
//    interrupt2=interrupt1;
//    interrupt1=micros();
    detachInterrupt(INT_PIN0);
    attachInterrupt(INT_PIN0, interruptHandler01, RISING);
}

void IRAM_ATTR interruptHandler01()
{
    inter0=false;
    cron.setAlarm=false;
    cron.setPower=false;
    cron.setBuzzer=false;
//    debugf("Key released Value %d",cfg.lamp);
    verso=verso*-1;
//    debugf("Key released : direction %d, Led %d\n",verso,cfg.lamp);
    detachInterrupt(INT_PIN0);
    attachInterrupt(INT_PIN0, interruptHandler00, FALLING);
}        
*/

////// WEB Clock //////
Timer clockRefresher;
HttpClient clockWebClient;
uint32_t lastClockUpdate = 0;
DateTime clockValue;
const int clockUpdateIntervalMs = 10 * 60 * 1000; // Update web clock every 10 minutes

/*
void onClockUpdating(HttpClient& client, bool successful)
{
    if (!successful)
    {
            debugf("CLOCK UPDATE FAILED %d (code: %d)", successful, client.getResponseCode());
            lastClockUpdate = 0;
            return;
    }

    // Extract date header from response
    clockValue = client.getServerDate();
    if (clockValue.isNull()) clockValue = client.getLastModifiedDate();
}

void refreshClockTime()
{
    uint32_t nowClock = millis();
    if (nowClock < lastClockUpdate) lastClockUpdate = 0; // Prevent overflow, restart
    if ((lastClockUpdate == 0 || nowClock - lastClockUpdate > clockUpdateIntervalMs) && !clockWebClient.isProcessing())
    {
            clockWebClient.downloadString("google.com", onClockUpdating);
            lastClockUpdate = nowClock;
    }
    else if (!clockValue.isNull())
            clockValue.addMilliseconds(clockRefresher.getIntervalMs());

    if (!clockValue.isNull())
    {
            StrTime = clockValue.toShortDateString() + " " + clockValue.toShortTimeString(false);

            if ((millis() % 2000) > 1000)
                    StrTime.setCharAt(13, ' ');
            else
                    StrTime.setCharAt(13, ':');
    }
}
 
void startWebClock()
{
    lastClockUpdate = 0;
    clockRefresher.stop();
    clockRefresher.initializeMs(500, refreshClockTime).start();
}

void setpwn(int led0)
{
    HW_pwm.analogWrite(INT_PIN15, led0*10);
}

*/
void startFTP()
{
        if (!fileExist("index.html"))
                fileSetContent("index.html", "<h3>Please connect to FTP and upload files from folder 'web/build' (details in code)</h3>");

        // Start FTP server
        ftp.listen(21);
        ftp.addUser("me", "123"); // FTP account
}


void draw_clock(void) {
    uint8_t Hour;
    uint8_t Minute;
    uint8_t Second;
//    uint16_t Milliseconds;
    uint8_t Day;
    uint8_t DayofWeek; // Sunday is day 0
    uint8_t Month; // Jan is month 0
    uint16_t Year;  // Full Year numer
    ShowMyTime.fromUnixTime(SystemClock.now(),&Second,&Minute,&Hour,&Day,&DayofWeek,&Month,&Year);
#if LCD == 0
//    debugf("DrawClock");
    DisplayTimeClock(Hour, Minute, Second);
    DisplayDateClock(Day, Month, Year);
#else    
//    tft.fillScreen(ST7735_BLACK);
    tft.setFont(&DSEG7ClassicRegular18pt7b);
    tft.setTextSize(1);
    if ((Old_Hour!=Hour) || (OldStatoRelais!=StatoRelais)) {
    tft.setTextColor(ILI9341_BLACK);    
    tft.setCursor(10,40);
        if (Old_Hour<10) {
            tft.print("0");
        }
        tft.print(Old_Hour);
        tft.setTextColor(ColoreOrario); // ILI9341_WHITE
        tft.setCursor(10,40);
        if (Hour<10) {
            tft.print("0");
        }
        tft.print(Hour);        
    }
    if ((Old_Minute!=Minute) || (OldStatoRelais!=StatoRelais)) {
    tft.setTextColor(ILI9341_BLACK);    
    tft.setCursor(80,40);
        if (Old_Minute<10) {
            tft.print("0");
        }
        tft.print(Old_Minute);
        tft.setTextColor(ColoreOrario); // ILI9341_WHITE
        tft.setCursor(80,40);
        if (Minute<10) {
            tft.print("0");
        }
        tft.print(Minute);        
    }
    tft.setTextColor(ColoreOrario); // ILI9341_WHITE
/* Rimuovo i secondi   
    if (Old_Second!=Second) {
    tft.setTextColor(ILI9341_BLACK);    
    tft.setCursor(150,40);
        if (Old_Second<10) {
            tft.print("0");
        }
        tft.print(Old_Second);
        tft.setTextColor(ILI9341_WHITE);
        tft.setCursor(150,40);
        if (Second<10) {
            tft.print("0");
        }
        tft.print(Second);        
    }
*/
/*    
    tft.setCursor(70,40);    
    tft.print(":");
    tft.setCursor(80,40);
    if (Old_Minute<10) {
        tft.print("0");
    }
    tft.print(Old_Minute);
    tft.setCursor(140,40);
    tft.print(":");
    tft.setCursor(150,40);
    if (Old_Second<10) {
        tft.print("0");
    }
    tft.print(Old_Second);
*/
    tft.setCursor(70,40);
    if (commasec) {
      tft.setTextColor(ColoreOrario); 
      tft.print(":");
    }
    else {
      tft.setTextColor(ILI9341_BLACK); 
      tft.print(":");
    }
    commasec=!commasec;
/*
    tft.setCursor(80,40);
    if (Minute<10) {
        tft.print("0");
    }
    tft.print(Minute);
*/
/* Rimuovo i : per i secondi
    tft.setCursor(140,40);
    tft.print(":");
*/
/*
    tft.setCursor(150,40);
    if (Second<10) {
        tft.print("0");
    }
    tft.print(Second);
*/    
    tft.setFont(&FreeSansBold9pt7b);
    tft.setCursor(10,160);
    tft.setTextSize(2);
    if (Old_DayofWeek!=DayofWeek) {
        tft.setCursor(10,190);    
        tft.setTextColor(ILI9341_BLACK);
        tft.print("Lunedi ");
        tft.print(Old_DayofWeek);
        tft.setCursor(10,70);
        tft.setTextColor(ILI9341_RED);
        tft.print("Lunedi ");
        tft.print(DayofWeek);        
    }

    tft.setCursor(10,110);
    if (Old_Day+Old_Month+Old_Year!=Day+Month+Year) {
        tft.setTextColor(ILI9341_BLACK);
        tft.print(Old_Day);
        tft.print(Old_Month);
        tft.print(Old_Year);
        tft.setCursor(10,110);
        tft.setTextColor(ILI9341_GREEN);
        tft.print(Day);
        tft.print(Month);
        tft.print(Year);        
    }
#endif    
    Old_Hour=Hour;
    Old_Minute=Minute;
    Old_Second=Second;
    Old_DayofWeek=DayofWeek;
    Old_Day=Day;
    Old_Month=Month;
    Old_Year=Year;
        
}



void CronLoop()
{
//    debugf("CronLoop");
    uint8_t Hour;
    uint8_t Minute;
    uint8_t Second;
//    uint16_t Milliseconds;
    uint8_t Day;
    uint8_t DayofWeek; // Sunday is day 0
    uint8_t Month; // Jan is month 0
    uint16_t Year;  // Full Year numer
    ShowMyTime.fromUnixTime(SystemClock.now(),&Second,&Minute,&Hour,&Day,&DayofWeek,&Month,&Year);
    int i=0;
    if (Minute>30) { i=1 ;}
    int HalfNumHour=Hour*2+i;
    i=0;
    if (Minute>15) { i=1 ;}
    if (Minute>30) { i=2 ;}
    if (Minute>45) { i=3 ;}
    int QuarterNumHour=Hour*4+i;
    if (CronoTempCfg.stringtime[DayofWeek+1].substring(HalfNumHour,HalfNumHour+1)=="0") {
        digitalWrite(PIN_RELAIS,LOW);
        ColoreOrario = ILI9341_GREEN;
        StatoRelais = false;
    }
    else {
        digitalWrite(PIN_RELAIS,HIGH);
        ColoreOrario = ILI9341_RED;
        StatoRelais = true;
    }     
    draw_clock();
    OldStatoRelais=StatoRelais;
    if (touch.isTouching()) {
//      uint16_t x, y;
      touch.getPosition(x, y);
      if ((x!=65535) and (y!=65535)) {          
        tft.setCursor(10,200);
        tft.setTextColor(ILI9341_BLACK);
        tft.print(xold);
        tft.setCursor(100,200);
        tft.setTextColor(ILI9341_BLACK);
        tft.print(yold);
        tft.setCursor(10,200);
        tft.setTextColor(ILI9341_PURPLE);
        tft.print(x);
        tft.setCursor(100,200);
        tft.setTextColor(ILI9341_YELLOW);
        tft.print(y);
//        tft.print(DayofWeek);  
        Serial.println(x);
        Serial.println(y);
        xold=x;
        yold=y;
      }
    }

}


void TempLoop()
{
    float temp0;
    if(!ReadTemp.MeasureStatus()) // the last measurement completed
    {
        if(ReadTemp.GetSensorsCount()) // is minimum 1 sensor detected ?
                Serial.println("******************************************");
        Serial.println(" Reding temperature DEMO");
        for(uint8_t a = 0; a < ReadTemp.GetSensorsCount(); a++) // prints for all sensors
        {
            Serial.print(" T");
            Serial.print(a + 1);
            Serial.print(" = ");
            if(ReadTemp.IsValidTemperature(a)) // temperature read correctly ?
            {
                temp0=ReadTemp.GetCelsius(a);
                Serial.print(temp0);
                Serial.print(" Celsius, (");
                Serial.print(ReadTemp.GetFahrenheit(a));
                Serial.println(" Fahrenheit)");
            } else
                Serial.println("Temperature not valid");

            Serial.print(" <Sensor id.");

            uint64_t info = ReadTemp.GetSensorID(a) >> 32;
            temperature = ReadTemp.GetCelsius(a);
            Serial.print((uint32_t)info, 16);
            Serial.print((uint32_t)ReadTemp.GetSensorID(a), 16);
            Serial.println(">");
        }
        Serial.println("******************************************");
        ReadTemp.StartMeasure(); // next measure, result after 1.2 seconds * number of sensors
        tft.setFont(&FreeSansBold9pt7b);
        tft.setCursor(200,70);
        tft.setTextSize(3);
        if (Old_temp!=temp0) {
            tft.setCursor(170,70);    
            tft.setTextColor(ILI9341_BLACK);
            tft.print(Old_temp);
            tft.setCursor(170,70);
            tft.setTextColor(ILI9341_BLUE);
            switch ((uint)temp0)
            {        
                case 16:
                     tft.setTextColor(ILI9341_DARKCYAN);
                     break;
                case 17:
                     tft.setTextColor(ILI9341_NAVY);
                     break;
                case 18:
                     tft.setTextColor(ILI9341_GREEN);
                     break;
                case 19:
                     tft.setTextColor(ILI9341_WHITE);
                     break;
                case 20:
                     tft.setTextColor(ILI9341_YELLOW);
                     break;
                case 21:
                     tft.setTextColor(ILI9341_ORANGE);
                     break;
                case 22:
                     tft.setTextColor(ILI9341_RED);
                     break;
            }
            if ((uint)temp0<16) {tft.setTextColor(ILI9341_DARKCYAN);}
            if ((uint)temp0>22) {tft.setTextColor(ILI9341_RED);}
            tft.print(temp0);        
        Old_temp=temp0;
        }
    } else
            Serial.println("No valid Measure so far! wait please");
}
    

void drawButtons()
{
// Draw the upper row of buttons
  for (x=0; x<5; x++)
  {
//    tft.setColor(0, 0, 255);
    tft.fillRoundRect (10+(x*60), 10, 60+(x*60), 60,10,255);
//    tft.setColor(255, 255, 255);
    tft.drawRoundRect (10+(x*60), 10, 60+(x*60), 60,10,255*255);
//    tft.printNumI(x+1, 27+(x*60), 27);
  }
// Draw the center row of buttons
  for (x=0; x<5; x++)
  {
//    tft.setColor(0, 0, 255);
    tft.fillRoundRect (10+(x*60), 70, 60+(x*60), 120,10, 255);
//    tft.setColor(255, 255, 255);
    tft.drawRoundRect (10+(x*60), 70, 60+(x*60), 120,10,255*255);
//    if (x<4)
//      myGLCD.printNumI(x+6, 27+(x*60), 87);
  }
//  tft.print("0", 267, 87);
// Draw the lower row of buttons
//  tft.setColor(0, 0, 255);
  tft.fillRoundRect (10, 130, 150, 180,10,tft.Color565(0, 0, 255));
//  tft.setColor(255, 255, 255);
  tft.drawRoundRect (10, 130, 150, 180, 10, tft.Color565(255, 255, 255));
  tft.setCursor(40, 147);
  tft.print("Clear");
//  tft.setColor(0, 0, 255);
  tft.fillRoundRect (160, 130, 300, 180, 10, tft.Color565(0, 0, 255));
//  tft.setColor(255, 255, 255);
  tft.drawRoundRect (160, 130, 300, 180, 10, tft.Color565(255, 255, 255));
  tft.setCursor(190, 147);
  tft.print("Enter" );
//  tft.setBackColor (0, 0, 0);
}



void SendPresence()
{
    CronoTempMsg.evento=SEND_PRESENCE;
    CronoTempMsg.stato=Cronotermostato;
    sendData();
}

void onPrintSystemTime() {
    Serial.print("Local Time    : ");
    Serial.println(SystemClock.getSystemTimeString());
    Serial.print("UTC Time: ");
    Serial.println(SystemClock.getSystemTimeString(eTZ_UTC));
}


// Called when time has been received by NtpClient (option 1 or 2)
// Either after manual requestTime() or when
// and automatic request has been made.
void onNtpReceive(NtpClient& client, time_t timestamp) {
    SystemClock.setTime(timestamp);

    Serial.println("Time synchronized: ");
    Serial.println(SystemClock.getSystemTimeString());
    draw_clock();
}

// Will be called when WiFi station was connected to AP
// void connectOk(const String& SSID, MacAddress bssid, uint8_t channel)
void connectOk(String ssid, uint8_t ssid_len, uint8_t bssid[6], uint8_t channel)
{
    debugf("I'm CONNECTED");
    WifiAccessPoint.enable(false);
}

void gotIP(IPAddress ip, IPAddress netmask, IPAddress gateway)
{

    Serial.println(WifiStation.getIP().toString());
//    Timer0.initializeMs(50, check_button0).start();

    debugf("connected");

    // At first run we will download web server content
    //if (!fileExist("index.html") || !fileExist("config.html") || !fileExist("bootstrap.css.gz") || !fileExist("jquery.js.gz"))
    //    downloadContentFiles();
    //else
    startWebServer();
    startFTP();
    tft.fillScreen(ILI9341_BLACK);
    CronTimer.initializeMs(500, CronLoop).start();
    TempTimer.initializeMs(15000, TempLoop).start();
    SendPresence();
    demo = new NtpClientDemo();
}

// Will be called when WiFi station timeout was reached
//void connectFail(const String& ssid, MacAddress bssid, WifiDisconnectReason reason)
void connectFail(String ssid, uint8_t ssid_len, uint8_t bssid[6], uint8_t reason)
{
        debugf("I'm NOT CONNECTED!");
	WifiAccessPoint.config("LampConfig", "", AUTH_OPEN);
	WifiAccessPoint.enable(true);

//	startWebServer();

        WifiStation.disconnect();
        WifiStation.connect();
}

void testdrawtext(const char text[], uint16_t color)
{
        tft.setCursor(0, 0);
        tft.setTextColor(color);
        tft.setTextWrap(true);
        tft.print(text);
}


void init()
{
    Serial.systemDebugOutput(true); // Allow debug output to serial
    debugf("Init!");

    spiffs_mount(); // Mount file system, in order to work with files
    Serial.begin(SERIAL_BAUD_RATE); // 115200 or 9600 by default
    delay(3000);
    
    inter0=false;
    verso=1;
    loadConfig();
    commasec=false;

#if LCD == 0
    LcdInitialise();
    LcdClear();
#else
    Serial.println("Display start");
    startTime = millis();
    SystemClock.setTimeZone(0); 
    // text display tests
    //tft.begin();
    tft.begin();
    //tft.init(4000000);        // optionally init with specific SPI speed (HWSPI)
    Serial.println("Init done");
    debugf("-clearscreen\n");
    tft.fillScreen(ILI9341_BLACK);
    debugf("-Initialized in %d ms\n", millis() - startTime);
    
    tft.setRotation(3);
    debugf("-setrotation(2) done");
    tft.setTextSize(2);
    debugf("-seTextSize(2) done");
    tft.setTextColor(ILI9341_GREEN);
    tft.setCursor(0, 0);
    tft.setCursor(60, 60);
    tft.println("Sming  Framework");
    tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK); // text

    tft.setTextColor(ILI9341_CYAN);
    tft.setCursor(60, 90);
    tft.println("ili9340-40C-41 ");
    tft.setCursor(60, 125);
    tft.println("have fun with Sming");
    Serial.println("Dopo init");

//    drawButtons();
    
    touch.begin(320, 240);  // Must be done before setting rotation
    touch.setRotation(touch.ROT270);
    
#endif    
    Serial.println("Dopo init 2");
    ReadTemp.Init(PIN_DHT);                // select PIN It's required for one-wire initialization!
    ReadTemp.StartMeasure(); // first measure start,result after 1.2 seconds * number of sensors

    WifiStation.enable(true);
    WifiAccessPoint.enable(false);
    WifiStation.config(CronoTempCfg.NetworkSSID, CronoTempCfg.NetworkPassword);
    
    WifiEvents.onStationConnect(connectOk);
    WifiEvents.onStationDisconnect(connectFail);
    WifiEvents.onStationGotIP(gotIP);
}
