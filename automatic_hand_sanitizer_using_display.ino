#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include <OneWire.h>//
#include <DallasTemperature.h>//

#define ONE_WIRE_BUS 8
#define trigPin 3
#define echoPin 2

OneWire oneWire(ONE_WIRE_BUS);//
DallasTemperature sensors(&oneWire);//

LiquidCrystal_I2C lcd(0x27,16,2);
Servo servo;
int sound = 250;

void setup() {
Serial.begin (9600);
sensors.begin(); //

pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
  lcd.begin(16,2);
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Hand Sanitizer");
  delay(2000);
  lcd.setCursor(0,0);
  lcd.clear();
  
servo.attach(4);
servo.write(0);
}

void loop() {

//temp sensor code
Serial.print("Requesting temperatures...");
sensors.requestTemperatures();
Serial.println("DONE");
float tempC = sensors.getTempCByIndex(0);
if (tempC != DEVICE_DISCONNECTED_C)
  {
    Serial.print("Temperature for the device 1 (index 0) is: ");
    Serial.println(tempC);
    //lcd.setCursor(0, 0);
    //lcd.print("Temperature:");
    lcd.setCursor(0, 1);
    //lcd.print(tempC);
    //lcd.print((char)223);
    lcd.print("BodyTemp: ");
    lcd.print(DallasTemperature::toFahrenheit(tempC));
    lcd.print("F");
  }
  else
  {
    Serial.println("Error: Could not read temp!");
  }

//sanitizer code  
long duration, distance;
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = (duration/2) / 29.1;
if (distance < 7) {
lcd.setCursor(0, 0);
lcd.print(" Dispensing  :D ");
servo.write(90);
delay(1000);
servo.write(0);
}
if (distance > 30 || distance <= 0){
lcd.setCursor(0, 0);  
lcd.print("KeepUrHandsClose ");
Serial.println("KeepUrHandsClose");
}
else {
Serial.println(distance);
lcd.setCursor(0, 0);
lcd.print("Distance: ");
lcd.print(distance);
lcd.print(" cm");
}
delay(500);
}
