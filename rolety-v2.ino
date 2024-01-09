#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define STEP_PIN D1
#define DIR_PIN D2
#define ENABLE_PIN D3

int delayTimeMicros = 1000;
const unsigned long inactiveTimeout = 3000; // 3 sekundy
unsigned long lastClientRequestTime = millis();

ESP8266WebServer server(80);

bool motorMoving = false;
int stepsRemaining = 0;

void moveMotor(String direction) {
  int steps = 18432000; // 9 otáček motoru

  if (direction == "up") {
    digitalWrite(DIR_PIN, HIGH);
    steps = 9 * steps; // 9 otáček motoru
  } else if (direction == "down") {
    digitalWrite(DIR_PIN, LOW);
  }

  digitalWrite(ENABLE_PIN, LOW);

  for (int i = 0; i < steps; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(delayTimeMicros);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(delayTimeMicros);
  }

  digitalWrite(ENABLE_PIN, HIGH); // Uspání motoru
}

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
  server.on("/open-blinds", HTTP_GET, handleOpenBlinds);
  server.on("/close-blinds", HTTP_GET, handleCloseBlinds);
  server.begin();
}

void loop() {
  server.handleClient();

  unsigned long currentMillis = millis();
  if ((currentMillis - lastClientRequestTime) > inactiveTimeout && !motorMoving) {
    digitalWrite(ENABLE_PIN, HIGH); // Uspání motoru
  }

  if (motorMoving) {
    if (stepsRemaining > 0) {
      digitalWrite(STEP_PIN, HIGH);
      delayMicroseconds(delayTimeMicros);
      digitalWrite(STEP_PIN, LOW);
      delayMicroseconds(delayTimeMicros);
      stepsRemaining--;
    } else {
      digitalWrite(ENABLE_PIN, HIGH); // Uspání motoru
      motorMoving = false;
    }
  }
}

void handleRoot() {
  lastClientRequestTime = millis();

  String page = "<!DOCTYPE html>";
  page += "<html lang='en'>";
  page += "<head>";
  page += "<meta charset='UTF-8'>";
  page += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  page += "<title>Krokový motor ovládání</title>";
  page += "<script>";
  page += "function sendDirection(direction) {";
  page += "  fetch('/move?direction=' + direction)";
  page += "    .then(response => {";
  page += "      console.log('Command sent');";
  page += "    });";
  page += "}";
  page += "function openBlinds() {";
  page += "  fetch('/open-blinds')";
  page += "    .then(response => {";
  page += "      console.log('Blinds fully open');";
  page += "    });";
  page += "}";
  page += "function closeBlinds() {";
  page += "  fetch('/close-blinds')";
  page += "    .then(response => {";
  page += "      console.log('Blinds fully closed');";
  page += "    });";
  page += "}";
  page += "</script>";
  page += "</head>";
  page += "<body style='text-align: center;'>";
  page += "<h1>Krokový motor ovládání</h1>";
  page += "<button style='margin: 10px; padding: 8px 16px; font-size: 16px;' onclick='sendDirection(\"up\")'>Nahoru</button>";
  page += "<button style='margin: 10px; padding: 8px 16px; font-size: 16px;' onclick='sendDirection(\"down\")'>Dolů</button>";
  page += "<button style='margin: 10px; padding: 8px 16px; font-size: 16px;' onclick='openBlinds()'>Úplně Otevřít</button>";
  page += "<button style='margin: 10px; padding: 8px 16px; font-size: 16px;' onclick='closeBlinds()'>Úplně Zavřít</button>";
  page += "</body></html>";

  server.send(200, "text/html", page);
}

void handleMove() {
  digitalWrite(ENABLE_PIN, LOW);
  lastClientRequestTime = millis();

  if (server.arg("direction") == "up") {
    moveMotor("up");
  } else if (server.arg("direction") == "down") {
    moveMotor("down");
  }
  server.send(204); // Úspěšná odpověď, ale bez obsahu pro neobnovení stránky
}

void handleOpenBlinds() {
  if (!motorMoving) {
    motorMoving = true;
    stepsRemaining = 9 * 2048000; // 9 otáček motoru pro plné otevření
    digitalWrite(DIR_PIN, HIGH);
    digitalWrite(ENABLE_PIN, LOW);
  }
  server.send(204); // Úspěšná odpověď
}

void handleCloseBlinds() {
  if (!motorMoving) {
    motorMoving = true;
    stepsRemaining = 9 * 2048000; // 9 otáček motoru pro plné uzavření
    digitalWrite(DIR_PIN, LOW);
    digitalWrite(ENABLE_PIN, LOW);
  }
  server.send(204); // Úspěšná odpověď
}
