/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPL2UZ52pyss"
#define BLYNK_TEMPLATE_NAME "Sistema de Riego Automatizado"
#define BLYNK_AUTH_TOKEN            "3sV357aX53GrXMmg4Neh_oUquzLnVoBB"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
#define sensor A0



#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Colibri2";
char pass[] = "cLaEXg54!460";

WiFiClient client;


BlynkTimer timer;

// This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V0)
{
  // Set incoming value from pin V0 to a variable
  int value = param.asInt();

  // Update state
  Blynk.virtualWrite(V1, value);
}

// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

// This function sends Arduino's uptime every second to Virtual Pin 2.
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V2, millis() / 1000);
}

void setup()
{
  // Debug console
  Serial.begin(9600); // Inicia la comunicación serial a 9600 baudios

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);


  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);

  //connectToWiFi();

}

void loop()
{
  Blynk.run();
  timer.run();
  int value = analogRead(sensor); // Lee el valor del sensor
  value = map(value, 0, 1024, 0, 100); // Mapea el valor a un rango de 0 a 100
  value = (value - 100) * -1; // Invierte el valor

  Serial.print("Humedad del suelo: "); // Imprime un mensaje en el monitor serial
  Serial.print(value); // Imprime el valor
  Serial.println("%"); // Imprime un símbolo de porcentaje y un salto de línea

  delay(1000); // Espera un segundo antes de la siguiente lectura

}
