#define BLYNK_TEMPLATE_ID "TMPL6NwgEPQxv"
#define BLYNK_TEMPLATE_NAME "ESP32"
#define BLYNK_AUTH_TOKEN "LYPzRZC2yJuJC6yHWtOHBeCB-OzRR-Un"
#define BLYNK_PRINT Serial

// declaration screen
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// library digunakan untuk menghubungkan ke blynk
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "Ultrasonic.h"
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

// declaration variable ultrasonic connected to peripheral
Ultrasonic ultrasonic(2, 4);
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
int buzzerPin = 33;

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Wokwi-GUEST";  // nama hotspot yang digunakan
char pass[] = "";             // password hotspot yang digunakan

int pinledred = 13;
int pinledgreen = 12;

void setup(){
  // put your setup code here, to run once:
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);

  if(!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)){
    Serial.println(F("failed to start SSD1306 OLED"));
    while(1);
  }
  pinMode(pinledred, OUTPUT);
  pinMode(pinledgreen, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  delay(1000);
  oled.clearDisplay();

  oled.setTextSize(1);
  oled.setTextColor(WHITE);
  oled.setCursor(0,2);
  oled.println("Hello");
  oled.display();
}


void loop(){
  Blynk.run();

  // put your main code here, to run repeatedly:
  delay(1000);
  int distance = ultrasonic.read(CM);
  Blynk.virtualWrite(V0, distance);
  oled.clearDisplay();
  oled.setTextSize(2);
  oled.setTextColor(WHITE);
  oled.setCursor(1, 2);
  Serial.print("Jarak : ");
  Serial.print(distance);
  Serial.println(" cm");
  oled.display();

  // display in led
  if (distance <= 100){
    delay(1000);
    digitalWrite(pinledred, HIGH);
    digitalWrite(pinledgreen, LOW);
    tone(buzzerPin, 100, 1000);
    oled.clearDisplay();
    oled.setCursor(1, 2);
    oled.setTextColor(WHITE);
    oled.println("Alert");
    oled.display();
  }
  else{
    delay(1000);
    digitalWrite(pinledgreen, HIGH);
    digitalWrite(pinledred, LOW);
    noTone(buzzerPin);
    oled.clearDisplay();
    oled.setCursor(1, 2);
    oled.setTextColor(WHITE);
    oled.println("Safe");
    oled.display();
  }
}

// tambahkan library blynk
