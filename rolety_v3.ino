#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define STEP_PIN D1
#define DIR_PIN D2
#define ENABLE_PIN D3

int delayTimeMicros = 1000;
const unsigned long inactiveTimeout = 3000; // 3 sekundy
unsigned long lastClientRequestTime = millis();

ESP8266WebServer server(80);

int stepsToOpen = 2048; // Počet kroků pro otevření

bool motorMoving = false;
String currentDirection = "";
int stepsRemaining = 0;

void moveMotor(String direction, int steps);

void setup() {
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(ENABLE_PIN, OUTPUT);

  digitalWrite(ENABLE_PIN, LOW);

  WiFi.begin("Radim_5G", "SoNy6255");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Připojování k WiFi...");
  }
  Serial.println("Připojeno k WiFi");

  server.on("/", HTTP_GET, handleRoot);
  server.on("/move", HTTP_GET, handleMove);
  server.on("/open", HTTP_GET, handleOpen);
  server.begin();
}

void loop() {
  server.handleClient();

  unsigned long currentMillis = millis();
  if ((currentMillis - lastClientRequestTime) > inactiveTimeout && !motorMoving) {
    digitalWrite(ENABLE_PIN, HIGH); // Uspání motoru
  }

  if (motorMoving && stepsRemaining > 0) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(delayTimeMicros);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(delayTimeMicros);
    stepsRemaining--;
  } else {
    motorMoving = false;
  }
}

void handleRoot() {
  lastClientRequestTime = millis();

  String page = "<!DOCTYPE html>";
  page += "<html lang='en'>";
  page += "<head>";
  page += "<meta charset='UTF-8'>";
  page += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  page += "<title>Rolety</title>";
  page += "</head>";
  page += "<body style='text-align: center;'>";
  page += "<h1>Ovládaní Rolet</h1>";
  page += "<form action='/move' method='GET'>";
  page += "<button style='margin: 10px; padding: 8px 16px; font-size: 16px;' name='direction' value='up'>Otevřít</button>";
  page += "<button style='margin: 10px; padding: 8px 16px; font-size: 16px;' name='direction' value='down'>Zavřít</button>";
  page += "</form>";
  page += "<form action='/open' method='GET'>";
  page += "<button style='margin: 10px; padding: 8px 16px; font-size: 16px;'>Posuň</button>";
  page += "</form>";
  page += "</body></html>";

  server.send(200, "text/html", page);
}

void handleMove() {
  digitalWrite(ENABLE_PIN, LOW);
  lastClientRequestTime = millis();

  if (server.arg("direction") == "up") {
    moveMotor("up", 9 * 2048);
  } else if (server.arg("direction") == "down") {
    moveMotor("down", 9 * 2048);
  }
  server.sendHeader("Location", "http://192.168.0.202/"); // Přesměrování na základní stránku
  server.send(303); // Kód pro přesměrování
}

void handleOpen() {
  digitalWrite(ENABLE_PIN, LOW);
  lastClientRequestTime = millis();
  stepsRemaining = stepsToOpen;
  motorMoving = true;
  currentDirection = "up";
  server.sendHeader("Location", "http://192.168.0.202/"); // Přesměrování na základní stránku
  server.send(303); // Kód pro přesměrování
}

void moveMotor(String direction, int steps) {
  if (steps <= 0) return;

  if (direction == "up") {
    digitalWrite(DIR_PIN, HIGH);
  } else if (direction == "down") {
    digitalWrite(DIR_PIN, LOW);
  }

  stepsRemaining = steps;
  motorMoving = true;
  currentDirection = direction;
}
