/*************************************************************
 * Created by A Posteriori LLP 
 * For Sample IoT RGB Lamp Project
 * From Blynk tutorial sample code
 * 
 * If you haven't done an IoT project, before, first Setup Blynk:
 * https://blynk.io/en/getting-started
 * 
 * If you don't know much about NeoPixels, get a set wired up to ESP8266, for instance:
 * https://www.instructables.com/id/ESP8266-controlling-Neopixel-LEDs-using-Arduino-ID/
 * 
 * Finally, integrate however you wish.
 * This Arduino code works with a Blynk module (too cheap to share and lose my B$1000 creds at this time) that has:
 * - ZeRGBa wired to V0
 * - On/Off button to V1
 * - Chase Effect On/Off button to V2
 * - Brightness Vertical Slider  to V3
 * 
 * Blynk library is licensed under MIT license
 * This example code is in public domain.
 * 
 */
  
/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Adafruit_NeoPixel.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "INSERT YOUR DEVICE AUTH TOKEN FROM BLYNK HERE";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "INSERT YOUR SSID HERE";
char pass[] = "INSERT YOUR PASWD HERE";

// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN  D8

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 8

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

int onoff = 0;
int chase = 0;
uint32_t color = strip.Color(255, 255, 255);
uint32_t wait = 200;

void chaseoff() {
  chase = 0;
}

void chaseon () {
  chase = 1;
  if (onoff) {
    on();  
  }
}

void off() {
  strip.clear();
  strip.show(); // Update strip with new contents
  onoff = 0;
}

void on() {
  if (chase) {
    strip.clear();
    strip.show();
  }
  for(int c=0; c<strip.numPixels(); c += 1) {
    strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
    if (chase) {
      strip.show(); // Update strip with new contents
      delay(wait);
    }
  }
  strip.show(); // Update strip with new contents
  onoff = 1;
}

// Read args from Blynk and control NEOPixel Ring
BLYNK_WRITE(V0)
{

  int R = param[0].asInt();
  int G = param[1].asInt();
  int B = param[2].asInt();

  color = strip.Color(R,G,B); 

  if (onoff) {
    on();
  }
}

BLYNK_WRITE(V1)
{
  if (param.asInt() == 1) { //on
    on();
  }
  else { //off
    off();
  }
}


BLYNK_WRITE(V2)
{
  if (param.asInt() == 1) { //on
    chaseon();
  }
  else { //off
    chaseoff();
  }
}

BLYNK_WRITE(V3)
{
  strip.setBrightness(param.asFloat()/10 * 250);
  strip.show();
}


void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
}

void loop()
{
  Blynk.run();

  
}
