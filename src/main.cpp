#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

class conexionWeb{
  private:

  public:
    conexionWeb(const char *_SSID, const char* _PASSWORD ){
      WiFi.begin(_SSID, _PASSWORD);
      while(WiFi.status()!= WL_CONNECTED){
          delay(500);
          Serial.print("...");
      }
    }

}; 

class DateTime
{
private:
  int defaultTime;
  struct tm timeinfo;
  const char *ntpServer = "pool.ntp.org";
  const long gmtOffset_sec = 0;
  const int daylightOffset_sec = 0;

public:
  char timeStringBuff[20];
  DateTime()
  {
    defaultTime = 0;
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    getTime();
  }

  void getTime()
  {   
    setLocalTime();
  }

  void setLocalTime()
  {
    
    if (!getLocalTime(&timeinfo))
    {
    }
    strftime(timeStringBuff, sizeof(timeStringBuff), "%Y-%m-%dT%H:%M:%SZ", &timeinfo);
  }
};
conexionWeb *coneccionHD;
DateTime *tiempo;
StaticJsonDocument<512> horaReal;


const char *ssid="INFINITUM1272_5";
const char *passwrd="E2a4F3PvSm";


void setup() {
  Serial.begin(115200);
  coneccionHD= new conexionWeb(ssid,passwrd);
  tiempo=new DateTime();
  
}
int sumatotal=0;
void loop() {
  sumatotal++;
  horaReal.clear();
  tiempo->getTime();
  horaReal["hora"]=tiempo->timeStringBuff;
  horaReal["Sumatoria"]=sumatotal;
  serializeJson(horaReal,Serial);
  Serial.println("");
  delay(1000);
}

