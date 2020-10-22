#ifndef INCLUDE_CONFIGURATION_H_
#define INCLUDE_CONFIGURATION_H_

//#include <SmingCore.h>
/*
adc0   - a0     d0 - gpio16
--     - g      d1 - gpio5
--     - vu     d2 - gpio4
gpio10 - s3     d3 - gpio0
gpio9  - s2     d4 - gpio2
mosi   - s1     3v - 3v
cs     - sc     g  - gnd
miso   - s0     d5 - gpio14 hsclk
sclk   - sk     d6 - gpio12 hmiso
gnd    - g      d7 - gpio13 hmosi
3v     - 3v     d8 - gpio15 hcs
en     - en     rx - gpio3
rst    - rst    tx - gpio1
gnd    - g      g  - gnd
vin    - vin    3v - 3v
*/

/*
 * Hardware SPI mode:
 * GND      (GND)         GND
 * VCC      (VCC)         3.3v
 * D0       (CLK)         GPIO14
 * D1       (MOSI)        GPIO13
 * RES      (RESET)       GPIO16
 * DC       (DC)          GPIO0
 * CS       (CS)          GPIO2
 */

#define TFT_SCLK 14 // D5
#define TFT_MOSI 13 // D7
#define TFT_RST 16  // D0
#define TFT_DC 0    // D3
#define TFT_CS 2    // D4


// If you want, you can define WiFi settings globally in Eclipse Environment Variables
#ifndef WIFI_SSID
//#define WIFI_SSID "FRITZ!Box 7530 LV" // Put you SSID and Password here
//#define WIFI_PWD "72032560351074684900"
//#define WIFI_SSID "angelo-thinkpad-x1-carbon-4th" // Put you SSID and Password here
//#define WIFI_PWD "qwerty123456"
#define WIFI_SSID "iot" // Put you SSID and Password here
#define WIFI_PWD "lamiapassword"
#endif

#define KEYPOWER    0xFD9A65
#define SUBTITLE    0xFD1AE5
#define LANGUAGE    0xFD18E7
#define OPENCLOSE   0xFD9867
#define ANGLEUP     0xFDB24D
#define TITLE       0xFD708F
#define VOLUMEUP    0xFDB04F
#define ANGLEDOWN   0xFD8A75
#define MENU        0xFD48B7
#define VOLUMEDOWN  0xFD8877
#define PROG        0xFDA25D
#define UP          0xFD609F
#define PLAYPAUSE   0xFDA05F
#define LEFT        0xFD5AA5
#define ENTER       0xFD58A7
#define RIGHT       0xFDD827
#define LR          0xFDAA55
#define DOWN        0xFD6897
#define STOP        0xFDA857
#define KEY1        0xFD4AB5
#define KEY2        0xFD0AF5
#define KEY3        0xFD08F7
#define GOTO        0xFDC837
#define KEY4        0xFD6A95
#define KEY5        0xFD2AD5
#define KEY6        0xFD28D7 
#define KEY10       0xFDE817
#define KEY7        0xFD728D 
#define KEY8        0xFD32CD
#define KEY9        0xFD30CF
#define KEY0        0xFDF00F
#define REV         0xFD52AD
#define FWD         0xFD12ED
#define PREV        0xFD10EF
#define NEXT        0xFDD02F
#define PCB         0xFD629D
#define DISPLAY     0xFD22DD
#define ZOOM        0xFD20DF
#define SLOW        0xFDE01F
#define MUTE        0xFD42BD
#define AB          0xFD020xFD
#define REPEAT      0xFD00FF
#define VIDEOMODE   0xFDC03F


#define JSON_HOST "10.10.20.1"
#define JSON_PORT 8111

enum TriggerType { eTT_None = 0, eTT_Temperature, eTT_Humidity };

#define LAMP_CONFIG_FILE ".lamp.conf"
#define SWITCH_CONFIG_FILE ".switch.conf"
#define CRONOTEMP_CONFIG_FILE ".cronotemp.conf"
#define METER_CONFIG_FILE ".meter.conf"
#define METEO_CONFIG_FILE ".meteo.conf"
#define DIMMER_CONFIG_FILE ".dimmer.conf"
#define STANDARD_CONFIG_FILE ".standard.conf"
#define SOIL_CONFIG_FILE ".soil.conf"
#define STEREO_CONFIG_FILE ".stereo.conf"

#define LED_PIN 4 // GPIO2
#define CONTROL_PIN 4 // GPIO 2

#define INT_PIN0 0   // GPIO0 d3
#define INT_PIN2 2   // GPIO2 d4
#define INT_PIN4 4   // GPIO4 d2
#define INT_PIN5 5   // GPIO5 d1
#define INT_PIN14 14 // GPIO14 d5
#define INT_PIN12 12 // GPIO12 d6
#define INT_PIN13 13 // GPIO13 d7
#define INT_PIN15 15 // GPIO15 d8
#define INT_PIN16  0 // GPIO16 d0

#define D0 16  // GPIO16 d0
#define D3 0   // GPIO0  d3
#define D4 2   // GPIO2  d4
#define D2 4   // GPIO4  d2
#define D1 5   // GPIO5  d1
#define D5 14 // GPIO14  d5
#define D6 12 // GPIO12  d6
#define D7 13 // GPIO13  d7
#define D8 15 // GPIO15  d8

#define say(a) ( Serial.print(a) )

#define LIGHT 1
#define ALARM 2
#define POWER 3
#define BUZZER 4
#define SLEEP 5
#define TEMPERATURE 6
#define SWITCH 7
#define PIR 8
#define AMPERE 9
#define TIME 10
#define PULSE 11

#define Lampada_radiocontrollata 1
#define Pulsantiera_4_posti 2
#define Cronotermostato 3
#define Rivelatore_temperatura 4
#define Rivelatore_movimento 5
#define Rivelatore_luce 6
#define Rivelatore_gas 7
#define Rivelatore_pressione 8
#define Rivelatore_acqua 9
#define Termometro 10
#define Amperometro 11
#define Dimmer 12
#define ContaScatti 13
#define MeteoControl 14
#define SwitchTriac 15
#define SoilMoisture 16
#define Stereo 17


#define SEND_PRESENCE 9999
#define CONFIGURATION 9998

#define Button_1 1
#define Button_2 2
#define Button_3 3
#define Button_4 4

#define Switch_1 10
#define Switch_2 11

//#define LCD 1
// 0 BN
// 1 COLOR

#define LCD_C     LOW
#define LCD_D     HIGH

struct LampConfig
{
	LampConfig()
	{
            lamp=50;
            alarmtime="09:30";
            sleeptime="23:30";
            sleepenabled=0;
            alarmenabled=0;
            buzzerenabled=0;
            powered=1;
            NetworkSSID="";
            NetworkPassword="";
	}

	String NetworkSSID;
	String NetworkPassword;
 
        String alarmtime, sleeptime;
        int lamp, sleepenabled,alarmenabled, buzzerenabled, powered;
        
};


struct CronoTempConfig
{
	CronoTempConfig()
	{
            stringtime[1]="000000000000000000000000000000000000000000000000";
            stringtime[2]="000000000000000000000000000000000000000000000000";
            stringtime[3]="000000000000000000000000000000000000000000000000";
            stringtime[4]="000000000000000000000000000000000000000000000000";
            stringtime[5]="000000000000000000000000000000000000000000000000";
            stringtime[6]="000000000000000000000000000000000000000000000000";
            stringtime[7]="000000000000000000000000000000000000000000000000";

            temperature=0;
            noicetemp=4;
            welltemp=18;
            NetworkSSID="";
            NetworkPassword="";
	}

	String NetworkSSID;
	String NetworkPassword;
        String stringtime[7];
//                , stringtime[2];
//        String stringtime[3], stringtime[4];
//        String stringtime[5], stringtime[6];
//        String stringtime[7];
 
        int temperature, noicetemp, welltemp;
        
};

struct SwitchConfig
{
	SwitchConfig()
	{
            Led0=0;
            Led2=0;
            Led4=0;
            Led5=0;
            powered=0;
            NetworkSSID="";
            NetworkPassword="";
	}

	String NetworkSSID;
	String NetworkPassword;
 
        int Led0, Led2, Led4, Led5, powered;
        
};

struct MeteoConfig
{
        MeteoConfig()
        {
            NetworkSSID="";
            NetworkPassword="";
            last_clock = 0;
            Label0="Da assegnare";
            Label1="Da assegnare";
            Enabled0=-1;
            Enabled1=-1;
            AddT=0;
            AddRH=0;
            AddTZ=0;
            Trigger=eTT_Temperature;;
            RangeMin=0.0;
            RangeMax=0.0;
        }

        String NetworkSSID;
        String NetworkPassword;

        time_t last_clock;
        String Label0, Label1,Label2, Label3;
        int Enabled0, Enabled1, Enabled2, Enabled3;
        TriggerType Trigger; // Sensor trigger type
        float AddT, AddRH, AddTZ, RangeMin, RangeMax;
};


struct MeterConfig
{
	MeterConfig()
	{
            NetworkSSID="";
            NetworkPassword="";
            last_clock = 0;
            Label0="Da assegnare";
            Label1="Da assegnare";
            Label2="Da assegnare";
            Label3="Da assegnare";
            Enabled0=1;
            Enabled1=1;
            Enabled2=1;
            Enabled3=1;
	}

	String NetworkSSID;
	String NetworkPassword;
 
        time_t last_clock;
        String Label0, Label1,Label2, Label3;
        int Enabled0, Enabled1, Enabled2, Enabled3;
};

struct SoilConfig
{
	SoilConfig()
	{
            NetworkSSID="";
            NetworkPassword="";
	    dry=630;
	    flood=220;
	}

	String NetworkSSID;
	String NetworkPassword;
	int dry,flood;
 
};
struct StereoConfig
{
	StereoConfig()
	{
            NetworkSSID="";
            NetworkPassword="";
	    dry=630;
	    flood=220;
	}

	String NetworkSSID;
	String NetworkPassword;
	int dry,flood;
 
};

struct StandardConfig
{
	StandardConfig()
	{
            NetworkSSID="";
            NetworkPassword="";
	}

	String NetworkSSID;
	String NetworkPassword;
};


struct LampMessage
{
    LampMessage()
    {
        evento=0;
        stato=0;
    }
    int evento, stato, unixtime;
};

struct SoilMessage
{
    SoilMessage()
    {
        evento=0;
        stato=0;
    }
    int evento, stato, unixtime;
};

struct MeterMessage
{
    MeterMessage()
    {
        unixtime=0;
        evento=0;
        stato=0;
    }
    int evento, stato, unixtime;
};

struct MeteoMessage
{
    MeteoMessage()
    {
        unixtime=0;
        evento=0;
        stato=0;
    }
    int evento, stato, unixtime;
};

struct StereoMessage
{
    StereoMessage()
    {
        unixtime=0;
        evento=0;
        stato=0;
    }
    int evento, stato, unixtime;
};


struct CronoTempMessage
{
    CronoTempMessage()
    {
        unixtime=0;
        evento=0;
        stato=0;
    }
    int evento, stato, unixtime;
};



extern void loadConfig();
extern void saveConfig();
extern void startWebClock();
extern void flashleds();
//extern MeterConfig MeterCfg;
extern void publishMessage(int evento, int linea, int tempo);
extern void DisplayTime(uint8_t hour, uint8_t minutes, uint8_t seconds);
extern void LcdInitialise(void);
extern void LcdClear();
extern void LcdWrite(uint8_t dc, uint8_t data);


//#define TFT_SCLK 	14 /* D5 */
//#define TFT_MOSI 	13 /* D7 */
//#define TFT_RST  	16 /* D0 */
//#define TFT_DC   	15 /* D8 */ // 15 8  
//#define TFT_CS   	4  /* D2 */ //  4 2

#define PIN_BUTTON      5  /* D1 */ //  5 1
#define PIN_PWM         2  /* D4 */ //  2 4
#define PIN_DHT         2  /* D4 */ //  2 4
#define PIN_BUZZER      0  /* D3 */ //  0 3
#define PIN_RELAIS      0  /* D3 */ //  0 3

#endif /* INCLUDE_CONFIGURATION_H_ */
