#define BLYNK_PRINT Serial
#include <SPI.h>
//#include <Ethernet.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include <SoftwareSerial.h>




WidgetLCD lcd (V1);
char auth[] = "BLYNK_AUTH";
char ssid[] = "WIFI_SSID";
char pass[] = "WIFI_PASSWORD";


SoftwareSerial s(D6,D5);
String dataType = "404";
String data = "None";
int Rate=random(70,85);

BLYNK_WRITE(V2)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  // You can also use:
  // String i = param.asStr();
  // double d = param.asDouble();
  Serial.print("V1 Slider value is: ");
  Serial.println(data);
}

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  s.begin(9600);


  Blynk.virtualWrite(V6,Rate);
  lcd.clear();
  lcd.print(0, 0, "Data: ");
  lcd.print(7, 1, data);

}

void loop()
{
  Blynk.run();
    lcd.clear();
  lcd.print(0, 0, "Data: ");
    if(s.available() > 0) {
    String dd = s.readString();
    Serial.println(dd);
    if(dd.charAt(0) == 'W') data = dd.substring(1);
    if(dd.charAt(0) == 'H') Rate = dd.substring(1).toInt();
    Serial.println(data);
      lcd.print(7, 1, data);
    Rate = random(70, 85);
    Blynk.virtualWrite(V6,Rate);
    Blynk.virtualWrite(V3,data);
  }
  // gsender->sender("Doctor@hospital.com", "Patient Exceeded normal Heartrate" + Rate);
}

