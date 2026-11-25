/*
 * ESP32 WiFi LED Controller
 * -------------------------
 * Turns an ESP32 into a tiny web server on your home WiFi.
 * Open the printed IP address in any browser (phone or PC)
 * to switch the built-in LED on and off.
 *
 * Board:  any ESP32 dev board (built-in LED is usually GPIO 2)
 * IDE:    Arduino IDE with the ESP32 board package installed
 * Libs:   none extra - WiFi and WebServer ship with the ESP32 core
 */

#include <WiFi.h>
#include <WebServer.h>

// ---- Change these to your own network ----
const char* WIFI_SSID     = "YOUR_WIFI_NAME";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";
// ------------------------------------------

const int LED_PIN = 2;  // built-in LED on most ESP32 dev boards

WebServer server(80);
bool ledOn = false;

String pageHtml() {
  String state = ledOn ? "ON" : "OFF";
  String html =
    "<!DOCTYPE html><html><head>"
    "<meta name='viewport' content='width=device-width, initial-scale=1'>"
    "<title>ESP32 LED</title>"
    "<style>"
    "body{font-family:sans-serif;text-align:center;background:#0b1120;color:#e2e8f0;padding-top:60px}"
    "h1{font-weight:700}.state{font-size:3rem;margin:20px}"
    "a{display:inline-block;margin:10px;padding:16px 40px;border-radius:12px;"
    "font-size:1.3rem;text-decoration:none;color:#0b1120}"
    ".on{background:#22c55e}.off{background:#ef4444;color:#fff}"
    "</style></head><body>"
    "<h1>ESP32 LED Controller</h1>"
    "<div class='state'>LED is " + state + "</div>"
    "<a class='on' href='/led/on'>Turn ON</a>"
    "<a class='off' href='/led/off'>Turn OFF</a>"
    "</body></html>";
  return html;
}

void handleRoot()   { server.send(200, "text/html", pageHtml()); }
void handleLedOn()  { ledOn = true;  digitalWrite(LED_PIN, HIGH); server.sendHeader("Location", "/"); server.send(303); }
void handleLedOff() { ledOn = false; digitalWrite(LED_PIN, LOW);  server.sendHeader("Location", "/"); server.send(303); }

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.begin(115200);
  Serial.println();
  Serial.print("Connecting to WiFi");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(400);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected! Open this in your browser: http://");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/led/on", handleLedOn);
  server.on("/led/off", handleLedOff);
  server.begin();
  Serial.println("Web server started.");
}

void loop() {
  server.handleClient();
}
