#include <TimerOne.h>

// define all the pins
#define Button1 2
#define Button2 3

#define greenPin 11
#define redPin 12

#define trigPin 10
#define echoPin 9

#define LM35 A1
#define PHR A0

// Define variables
long duration; // for the duration of sound wave travel
int distance; // for the distance measurement
int temp; // for the temperature measurment
int lumination; // for the illumination measurment
float avgDist; // for average distance
float avgTemp; // for average temperature
float avgLumi; // for average illumination

void setup() {
  //Set all the pins to what they are, input or output
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  pinMode(LM35, INPUT);
  pinMode(PHR, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(Button1, INPUT_PULLUP);
  pinMode(Button2, INPUT_PULLUP);
  Serial.begin(9600); // Serial Communication is starting with 9600 of baudrate speed
}

void Distance(){
  // Clears the condition for trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin to active for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  //distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Calculating the average distance of 10 calculations
  for(int i=0; i<10; i++){
    distance = duration * 0.034 / 2;
    avgDist += distance;
  }
  
  // Displays the average distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(avgDist/10);
  Serial.println(" cm");

  // Set the average distance to 0 again
  avgDist = 0;
}

void Temperature(){
  // Calculating the average temperature of 10 calculations
  for(int i=0; i<10; i++){
    temp = analogRead(LM35)*500.0/1023;
    avgTemp += temp;
  }
  // Displays the average temeprature on the Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(avgTemp/10);
  Serial.println("C");

  // Check if average temperature is above 30, the red is turned on and if below, the green is turned on
  if(avgTemp > 30){
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
  } else if (avgTemp < 30){
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
  }

  // Set the average temperature to 0 again
  avgTemp = 0;
}

void Lumination(){
  // Calculating the average illumination of 10 calculations
  for(int i=0; i<10; i++){
    lumination = analogRead(PHR);
    avgLumi += lumination;
  }
  //int illumination = analogRead(PHR); 
  // Displays the average illumination on the Serial Monitor
  Serial.print("Illumination: ");
  Serial.print(avgLumi/10);
  Serial.println(" lux");

  // Set the average illumination to 0 again
  avgLumi = 0;
}

void loop() {
  // Read the buttons
  byte buttonState1 = digitalRead(Button1);
  byte buttonState2 = digitalRead(Button2);

  // Print everything on the Serial Monitor in order
  Serial.println("********************");
  Distance();
  Temperature();
  Lumination();
  Serial.println("********************");

  // Delay the printing 5 seconds
  delay(5000);
  
}
