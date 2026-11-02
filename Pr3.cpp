
#include <WiFi.h>
#include <WebServer.h>

// WiFi credentials
const char* ssid = "Your_WiFi_Name";
const char* password = "Your_WiFi_Password";

// LED pins
const int led1 = 12;
const int led2 = 14;

// Create web server on port 80
WebServer server(80);

void handleRoot() {
  String webpage = "<html><body>";
  webpage += "<h1>ESP32 LED Control</h1>";

  webpage += "<h2>LED 1 (GPIO 12)</h2>";
  webpage += "<a href='/12/on'><button>ON</button></a>";
  webpage += "<a href='/12/off'><button>OFF</button></a>";

  webpage += "<h2>LED 2 (GPIO 14)</h2>";
  webpage += "<a href='/14/on'><button>ON</button></a>";
  webpage += "<a href='/14/off'><button>OFF</button></a>";

  webpage += "</body></html>";

  server.send(200, "text/html", webpage);
}

void setup() {
  Serial.begin(115200);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);

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

  server.on("/", handleRoot);

  server.on("/12/on", []() {
    digitalWrite(led1, HIGH);
    Serial.println("LED 1 ON");
    server.sendHeader("Location", "/");
    server.send(303);
  });

  server.on("/12/off", []() {
    digitalWrite(led1, LOW);
    Serial.println("LED 1 OFF");
    server.sendHeader("Location", "/");
    server.send(303);
  });

  server.on("/14/on", []() {
    digitalWrite(led2, HIGH);
    Serial.println("LED 2 ON");
    server.sendHeader("Location", "/");
    server.send(303);
  });

  server.on("/14/off", []() {
    digitalWrite(led2, LOW);
    Serial.println("LED 2 OFF");
    server.sendHeader("Location", "/");
    server.send(303);
  });

  server.begin();
  Serial.println("Web Server Started");
}

void loop() {
  server.handleClient();
}
