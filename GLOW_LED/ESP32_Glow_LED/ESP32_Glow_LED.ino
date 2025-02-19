#define LED 5

void setup() {
  pinMode(LED, OUTPUT);
}

void loop() {
  int delta = 0;

  for(delta == 0; delta <= 255; delta = delta + 25){
    analogWrite(LED, delta);
    delay(1000);
  }

  for(delta == 256; delta>=0; delta = delta - 25){
    analogWrite(LED, delta);
    delay(1000);
  }
}
