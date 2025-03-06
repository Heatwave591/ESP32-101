const int trigger = 22;
const int echo = 23;

long duration;
int distance;

void setup() {
  pinMode(trigger, OUTPUT); 
  pinMode(echo, INPUT); 
  Serial.begin(9600); 
  
}
void loop() {
  // This par tof the code is to reset the sensor
  // We do this after every read to measure distance from 0 each cycle.

  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  // Measures the duration fron the triger HIGH
  // until the echo reads a signal setting it to HIGH

  duration = pulseIn(echo, HIGH);

  // this piece of code calculates the net distance
  // Origin of this equation is as follows
  // Distance = speed * time
  // speed = 340 m/s = 0.034 cm/ms
  // The /2 is present here because the distance is the total distance
  // from the trigger of the sensor to the echo of the sensor...
  // This is essentially the distance back and forth, but we need only
  // one way of the distance. So we divide by 2.
  // to print the distance in m, replace 0.034 with 340.
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);
}
Code language: Arduino (arduino)