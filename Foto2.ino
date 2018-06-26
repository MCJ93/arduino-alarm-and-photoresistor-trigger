/*
  Analog Input

  Demonstrates analog input by reading an analog sensor on analog pin 0 and
  turning on and off a light emitting diode(LED) connected to digital pin 13.
  The amount of time the LED will be on and off depends on the value obtained
  by analogRead().

  The circuit:
  - potentiometer
    center pin of the potentiometer to the analog input 0
    one side pin (either one) to ground
    the other side pin to +5V
  - LED
    anode (long leg) attached to digital output 13
    cathode (short leg) attached to ground

  - Note: because most Arduinos have a built-in LED attached to pin 13 on the
    board, the LED is optional.

  created by David Cuartielles
  modified 30 Aug 2011
  By Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogInput
*/

const int triggerPin = 12;
const int echoPin = 11;
const int sensorPin = A0;    // select the input pin for the potentiometer
const int ledPin = 8;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor
const int toggleButton = 5;
const int setDistanceButton = 4;
int buttonState = 0;         // current state of the button
int setDistanceButtonState = 0;
int setDistance = 0;
bool enableAlarm = false;



void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);
  pinMode(triggerPin, OUTPUT); //Pin, do którego podłączymy trig jako wyjście
  pinMode(echoPin, INPUT); //a echo, jako wejście
  pinMode(toggleButton, INPUT);
  pinMode(setDistanceButton, INPUT);
  pinMode(A5, OUTPUT);
  Serial.begin(9600); 
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
//  Serial.print(sensorValue);
//  Serial.print('\n');
//  if (sensorValue = 400) {
//    digitalWrite(ledPin, HIGH);
//  } else {
//    digitalWrite(ledPin, LOW);
//  }
  
  buttonState = digitalRead(toggleButton);

  if (buttonState == HIGH) {
    enableAlarm = !enableAlarm;
  }
 
  if (enableAlarm == 1) {
    findDistance();
    analogWrite(ledPin, 128);
  } else {
    digitalWrite(ledPin, LOW);
  }
  tone(A5, 2000); //Wygeneruj sygnał o częstotliwości 4300Hz na pinie A5  
  delay(150);  
  tone(A5, 3500); //Wygeneruj sygnał o częstotliwości 3500Hz na pinie A5  
  delay(150);
}

int findDistance() {
  long time, distance;
  
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
 
  time = pulseIn(echoPin, HIGH);
  distance = time / 58;
  if (distance < 20) {
    
  }

  setDistanceButtonState = digitalRead(setDistanceButton);
  if (setDistanceButtonState == HIGH) {
    Serial.println("SETSET");
    setDistance = distance;
  }
  Serial.println(distance);
  Serial.println("cm1");
  Serial.println(setDistance);
  Serial.println("cm2");
  return distance;
}
