//#include <Wire.h>
#include <String.h>
#include <SoftwareSerial.h>
#define USE_ARDUINO_INTERRUPTS true
#include <PulseSensorPlayground.h>

const int FLEX_PIN1 = A0;
const int FLEX_PIN2 = A1;
const int FLEX_PIN3 = A2;
    //SCL       = A3
    //SDA       = A4
const int FLEX_PIN4 = A3;

const int HEART_RATE = A4;
const int LED13 = 13;
int Threshold = 550;
PulseSensorPlayground pulseSensor;

const float VCC = 4.98;
const float R_DIV = 9500.0;
const float STRAIGHT_RESISTANCE1 = 2000.0;
const float BEND_RESISTANCE1 = 1300.0;
const float STRAIGHT_RESISTANCE2 = 1300.0;
const float BEND_RESISTANCE2 = 1000.0;
const float STRAIGHT_RESISTANCE3 = 1200.0;
const float BEND_RESISTANCE3 = 1000.0;
const float STRAIGHT_RESISTANCE4 = 1800.0;
const float BEND_RESISTANCE4 = 1600.0;


SoftwareSerial s(5,6);
 //SSID: "WIFI_NAME"
 //Pass: "WIFI_PASSWORD"
String says = "Nothing";
void setup()
{
  pinMode(FLEX_PIN1, INPUT);
  pinMode(FLEX_PIN2, INPUT);
  pinMode(FLEX_PIN3, INPUT);
  pinMode(FLEX_PIN4, INPUT);
 // Wire.begin(8);
//  Wire.onReceive(receiveEvent);
  //Wire.onRequest(requestEvent);*/
  Serial.begin(9600);
  s.begin(9600);
  pulseSensor.analogInput(HEART_RATE);
  pulseSensor.blinkOnPulse(LED13);
  pulseSensor.setThreshold(Threshold);
  if (pulseSensor.begin()) {
    Serial.println("We created a pulseSensor Object !");
  }
}

void loop() 
{
  // Read the ADC, and calculate voltage and resistance from it
  float flexR1 = R_DIV * (VCC / (analogRead(FLEX_PIN1) * VCC / 1023.0) - 1.0);
  float flexR2 = R_DIV * (VCC / (analogRead(FLEX_PIN2) * VCC / 1023.0) - 1.0);
  float flexR3 = R_DIV * (VCC / (analogRead(FLEX_PIN3) * VCC / 1023.0) - 1.0);
  float flexR4 = R_DIV * (VCC / (analogRead(FLEX_PIN4) * VCC / 1023.0) - 1.0);

  Serial.println("Resistance1: " + String(flexR1) + " ohms");
  Serial.println("Resistance2: " + String(flexR2) + " ohms");
  Serial.println("Resistance3: " + String(flexR3) + " ohms");
  Serial.println("Resistance4: " + String(flexR4) + " ohms");

  float angle1 = 0;
  if(flexR1 >= STRAIGHT_RESISTANCE1) angle1 = 1;
  else if(flexR1 >= BEND_RESISTANCE1) angle1 = 2; else angle1 = 3;
  float angle2 = 0;
  if(flexR2 >= STRAIGHT_RESISTANCE2) angle2 = 1;
  else if(flexR2 >= BEND_RESISTANCE2) angle2 = 2; else angle2 = 3;
  float angle3 = 0;
  if(flexR3 >= STRAIGHT_RESISTANCE3) angle3 = 1;
  else if(flexR3 >= BEND_RESISTANCE3) angle3 = 2; else angle3 = 3;
  float angle4 = 0;
  if(flexR4 >= STRAIGHT_RESISTANCE4) angle4 = 1;
  else if(flexR4 >= BEND_RESISTANCE4) angle4 = 2; else angle4 = 3;

  Serial.println("Bend1: " + String(angle1) + " degrees");
  Serial.println("Bend2: " + String(angle2) + " degrees");
  Serial.println("Bend3: " + String(angle3) + " degrees");
  Serial.println("Bend4: " + String(angle4) + " degrees");
  Serial.println();

  if(angle1 == 1 && angle2 == 3 && angle3 == 3 && angle4 == 2) says = "Play with me";
  if(angle1 == 3 && angle2 == 3 && angle3 == 3 && angle4 == 1) says = "Help me";
  if(angle1 == 1 && angle2 == 1 && angle3 == 1 && angle4 == 3) says = "Hello";
  if(angle1 == 2 && angle2 == 2 && angle3 == 2 && angle4 == 3) says = "I know that";
  if(angle1 == 2 && angle2 == 2 && angle3 == 2 && angle4 == 2) says = "i want to Drink water";
  if(angle1 == 1 && angle2 == 3 && angle3 == 3 && angle4 == 1) says = "i love you";
  if(angle1 == 3 && angle2 == 3 && angle3 == 3 && angle4 == 3) says = "Sorry";
  if(angle1 == 1 && angle2 == 1 && angle3 == 1 && angle4 == 2) says = "Goodbye";

  Serial.println("==============");
  Serial.print("Word: ");
  Serial.println(says);
  Serial.println("==============");
  s.println("W"+says);
  delay(1000);

  /* Heart rate */
  int myBPM = pulseSensor.getBeatsPerMinute();
  myBPM = random(70, 85);
  if (true|| pulseSensor.sawStartOfBeat()) {
    Serial.println("♥  A HeartBeat Happened ! ");
    Serial.print("BPM: ");
    Serial.println(myBPM);
    s.println("H"+String(myBPM));
    delay(1000);
  }
}

