#include <WiFi.h>
#include <WebServer.h>

// Wi-Fi credentials
const char* ssid = "sarva's";
const char* password = "123123123";

// Sensor & web config
#define SOIL_PIN 34 // ADC pin
WebServer server(80);

// Thresholds (tune based on your sensor!)
#define DRY_THRESHOLD 2800 // above this = dry
#define WET_THRESHOLD 1800 // below this = wet

String getSoilEmoji(int value) {
  if (value < WET_THRESHOLD)
    return "🌿 Moist";
  else if (value > DRY_THRESHOLD)
    return "🟫 Dry";
  else
    return "🌱 Medium";
}

void handleRoot() {
  int soilVal = analogRead(SOIL_PIN);
  String emoji = getSoilEmoji(soilVal);

  String html = "<!DOCTYPE html><html><head><meta charset='utf-8'>";
  html += "<meta http-equiv='refresh' content='5'>";
  html += "<title>Soil Moisture</title>";
  html += "<style>body{font-family:sans-serif;text-align:center;background:#222;color:#fff;}</style>";
  html += "</head><body>";
  html += "<h1>Soil Moisture Monitor</h1>";
  html += "<h2 style='font-size:80px'>" + emoji + "</h2>";
  html += "<p>Analog Reading: <b>" + String(soilVal) + "</b></p>";
  html += "<p>Auto-refreshes every 5 seconds</p>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(SOIL_PIN, INPUT);

  // Connect WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print(".");
  }

  Serial.println("\nConnected! IP: " + WiFi.localIP().toString());

  server.on("/", handleRoot);
  server.begin();
}

void loop() {
  /* Connect WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print(".");
  }

  Serial.println("\nConnected! IP: " + WiFi.localIP().toString());

  server.on("/", handleRoot);
  server.begin();*/
  Serial.println("\nConnected! IP: " + WiFi.localIP().toString());
  server.handleClient();
}
