#include "Ultrasonic.h"
#include <Adafruit_SSD1306.h>

// declaration screen
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// declaration variable ultrasonic connected to peripheral
Ultrasonic ultrasonic(12, 13);
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
int buzzerPin = 7;
int pinledred = 4;
int pinledblue = 2;
int pinledyellow = 8;                // choose the pin for the LED
int pininput = 11;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(pinledred, OUTPUT);
  pinMode(pinledblue, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(pinledyellow, OUTPUT);      // declare LED as output
  pinMode(pininput, INPUT);     // declare sensor as input
  digitalWrite(pinledred, LOW);
  digitalWrite(pinledblue, LOW);

  if(!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)){
    Serial.println(F("failed to start SSD1306 OLED"));
    while(1);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
  int distance = ultrasonic.read(CM);
  oled.clearDisplay();
  oled.setTextSize(2);
  oled.setTextColor(WHITE);
  oled.setCursor(1, 2);
  oled.println("Jarak:");
  oled.print(distance);
  oled.println(" cm");
  oled.display();

  val = digitalRead(pininput); 

  // display in led
  if (distance <= 10){
    delay(1000);
    digitalWrite(pinledred, HIGH);
    digitalWrite(pinledblue, LOW);
    tone(buzzerPin, 100, 2000);
    oled.clearDisplay();
    oled.setCursor(1, 2);
    oled.println("Tertabrak");
    oled.display();
  }
  else if (distance <=200){
    delay(1000);
    digitalWrite(pinledblue, HIGH);
    digitalWrite(pinledred, LOW);
    tone(buzzerPin, 100, 500);
    oled.clearDisplay();
    oled.setCursor(1, 2);
    oled.println("Ada Objek");
    oled.display();
  }
  else{
    noTone(buzzerPin);
    digitalWrite(pinledred, LOW);
    digitalWrite(pinledblue, LOW);
  }

  // sensor deteksi gerak
  if (val == HIGH){
    digitalWrite(pinledyellow, HIGH);  
    if (pirState == LOW) {
      Serial.println("Gerakan terdeteksi!");
      pirState = HIGH;
    }
  }
  if (val == LOW){
    digitalWrite(pinledyellow, LOW); 
    if (pirState == HIGH) {
      Serial.println("Gerakan berakhir!");
      pirState = LOW;
    }
  }
}
