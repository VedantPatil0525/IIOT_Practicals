
#include <WiFi.h>
#include <WebServer.h>

// WiFi credentials
const char* ssid = "Your_WiFi_Name";
const char* password = "Your_WiFi_Password";

// Potentiometer pin
const int potPin = 34;

int potValue = 0;

// Create web server on port 80
WebServer server(80);

// Function to display sensor value
void handleRoot() {
  potValue = analogRead(potPin);

  String webpage = "<html><body>";
  webpage += "<h1>ESP32 Sensor Monitoring</h1>";
  webpage += "<h2>Potentiometer Value: ";
  webpage += String(potValue);
  webpage += "</h2>";
  webpage += "</body></html>";

  server.send(200, "text/html", webpage);
}

void setup() {
  Serial.begin(115200);

  pinMode(potPin, INPUT);

  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected!");

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, handleRoot);

  server.begin();

  Serial.println("Web Server Started");
}

void loop() {
  potValue = analogRead(potPin);

  server.handleClient();

  delay(100);
}
