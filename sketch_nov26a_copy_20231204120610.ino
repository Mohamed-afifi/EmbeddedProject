#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define echoPin1 2               // CHANGE PIN NUMBER HERE IF YOU WANT TO USE A DIFFERENT PIN
#define trigPin1 4               // CHANGE PIN NUMBER HERE IF YOU WANT TO USE A DIFFERENT PIN
#define echoPin2 18               // CHANGE PIN NUMBER HERE IF YOU WANT TO USE A DIFFERENT PIN
#define trigPin2 19  
#define LED_PIN 23
#define motor_pin 26
long duration, distance, duration2, distance2;
int lcdColumns = 16;
int lcdRows = 2;
int counter = 0; // Counter variable
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  

void setup() {
  Serial.begin(9600);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  pinMode(LED_PIN, OUTPUT);
  pinMode(motor_pin, OUTPUT); 

  lcd.init();
  lcd.noBacklight();
  lcd.backlight();
  lcd.print("Hi Dr Sedky");
  delay(1000);
}

void loop() {
  // Trigger sensor 1
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration = pulseIn(echoPin1, HIGH);
  distance = 0.017 * duration;

  // Trigger sensor 2
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = 0.017 * duration2;

  // Print distances for debugging
  Serial.print("distance: ");
  Serial.print(distance);
  Serial.print(" cm, distance2: ");
  Serial.println(distance2);

  delay(60);

  // Trigger sensor 1 again
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration = pulseIn(echoPin1, HIGH);
  distance = 0.017 * duration;
  Serial.print("new_distance : ");
  Serial.print(distance);
  Serial.println(" cm");

  // Trigger sensor 2 again
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = 0.017 * duration2;
  delay(60);
  Serial.print("new_distance2 : ");
  Serial.print(distance2);
  Serial.println(" cm");

  if (distance2 < (distance - 10)) {
    // Someone is entering
    counter++;
    Serial.print("entered! counter : ");
    Serial.println(counter);
  } else if (distance < (distance2 - 10)) {
    // Someone is exiting
    counter--;
    Serial.print("exited! counter : ");
    Serial.println(counter);
  }

  if (counter <= 0) {   
    digitalWrite(LED_PIN, LOW);
    digitalWrite(motor_pin, LOW);
    counter=0;
  } else {
    digitalWrite(LED_PIN, HIGH); 
    digitalWrite(motor_pin, HIGH);
  }

  lcd.setCursor(0, 1);
  lcd.print("Counter : ");
  lcd.print(counter);
  delay(500);
  lcd.clear();
}
