#include <Arduino.h>
#include "HX711.h"


// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;
const int LED_RED_PIN = 9; // Red pin of the RGB LED
const int LED_GREEN_PIN = 11; // Green pin of the RGB LED
const int LED_BLUE_PIN = 10; // Blue pin of the RGB LED


//HX711 scale;
//bool weightDetected = false;
//unsigned long previousMillis = 0;
//const long intervalBlue = 600000; // 10 minutes in milliseconds
//const long intervalGreen = 300000; // 5 minutes in milliseconds after blue
//const long intervalRed = 120000; // 2 minutes in milliseconds after yellow


HX711 scale;
bool weightDetected = false;
unsigned long previousMillis = 0;
//const long intervalBlue = 30000; // 30 seconds in milliseconds
//const long intervalGreen = 30000; // 30 seconds in milliseconds after blue
//const long intervalRed = 30000; // 30 seconds in milliseconds after green
const long intervalBlue = 0000; // 30 seconds in milliseconds
const long intervalGreen = 5000; // 30 seconds in milliseconds after blue
const long intervalRed = 10000; // 30 seconds in milliseconds after green




void setup() {
 Serial.begin(57600);
 Serial.println("HX711 Demo");
 Serial.println("Initializing the scale");


 scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);


 pinMode(LED_RED_PIN, OUTPUT);
 pinMode(LED_GREEN_PIN, OUTPUT);
 pinMode(LED_BLUE_PIN, OUTPUT);


 scale.set_scale(300);
 scale.tare(); // Reset the scale to 0


 Serial.println("After setting up the scale:");
 Serial.println("Readings:");
}


void loop() {
 long weight = scale.get_units();




 if (weight > 0) {
   if (!weightDetected) {
     previousMillis = millis();
   }
   weightDetected = true;
   unsigned long currentMillis = millis();
   unsigned long millisPassed = currentMillis - previousMillis; // time passed since weight detected
   Serial.println("currentMillis: ");
   Serial.println(currentMillis);
   Serial.println("previousMillis: ");
   Serial.println(previousMillis);


//    if (!digitalRead(LED_BLUE_PIN)) {
//      //digitalWrite(LED_BLUE_PIN, HIGH); // Turn on blue LED if weight detected
//      digitalWrite(LED_GREEN_PIN, HIGH);
//      Serial.println("blue light on");
//    }


   if (millisPassed >= intervalBlue && millisPassed < intervalGreen) {
     digitalWrite(LED_BLUE_PIN, HIGH);
     //digitalWrite(LED_GREEN_PIN, HIGH); // Turn on green LED after 10 minutes
     Serial.println("blue light on");
   }


   if (millisPassed >= intervalGreen && millisPassed < intervalRed) {
     digitalWrite(LED_BLUE_PIN, LOW); // Turn off blue LED
     digitalWrite(LED_GREEN_PIN, HIGH); // Turn off green LED
     Serial.println("green light on");
   }


 //turn on RED LED
   if (millisPassed >= intervalRed) {
     digitalWrite(LED_GREEN_PIN, LOW); // Turn off green LED
     digitalWrite(LED_RED_PIN, HIGH); // Turn on red LED after 2 minutes
     Serial.println("red light on");
   }


 } else {
   if (weightDetected) {
     Serial.println("Weight removed; resetting");
     // Reset timers and LEDs if weight is removed
     weightDetected = false;
     digitalWrite(LED_BLUE_PIN, LOW);
     digitalWrite(LED_GREEN_PIN, LOW);
     digitalWrite(LED_RED_PIN, LOW);
   }
 }


 Serial.println("weight"); // Print the weight to serial monitor
 Serial.println(weight); // Print the weight to serial monitor
 delay(1000); // Adjust delay if needed to control the rate of weight readings
}
