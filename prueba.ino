/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPL2UZ52pyss"
#define BLYNK_TEMPLATE_NAME "Sistema de Riego Automatizado"
#include <LiquidCrystal_I2C.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//Initialize the LCD display
LiquidCrystal_I2C lcd(0x27, 16, 2);

char auth[] = "3sV357aX53GrXMmg4Neh_oUquzLnVoBB";
char ssid[] = "Kristel";
char pass[] = "Piti1006";

BlynkTimer timer;
bool Relay = 0;

//Define component pins
#define sensor A0
#define waterPump D3

void setup() {
  Serial.begin(9600);
  pinMode(waterPump, OUTPUT);
  digitalWrite(waterPump, HIGH);
  lcd.init();
  lcd.backlight();

  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);

  lcd.setCursor(1, 0);
  Serial.print("System Loading");
  for (int a = 0; a <= 15; a++) {
    lcd.setCursor(a, 1);
    Serial.print(".");
    delay(500);
  }
  lcd.clear();

  //Call the function
  timer.setInterval(100L, soilMoistureSensor);
}

//Get the soil moisture values
void soilMoistureSensor() {
  int value = analogRead(sensor);
  value = map(value, 0, 1024, 0, 100);
  value = (value - 100) * -1;

  Blynk.virtualWrite(V0, value);
  lcd.setCursor(0, 0);
  //Serial.print("Moisture :");
  //Serial.print(value);
  //Serial.print(" ");

}

void loop() {
  Blynk.run();//Run the Blynk library
  timer.run();//Run the Blynk timer
}