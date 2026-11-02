
const int potPin = 34;

int potValue = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);
}

void loop() {
  potValue = analogRead(potPin);

  if (potValue > 2000) {
    Serial.println("warning");
  }

  Serial.println(potValue);

  delay(500);
}
