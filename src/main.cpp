#include <WiFi.h>
#include <WebServer.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

// LCD Pin definitions
#define TFT_CS   14
#define TFT_RST  19
#define TFT_DC   15
#define TFT_MOSI 23
#define TFT_SCLK 18

// LED Pins
const int builtInLedPin = 2; // Built-in LED
const int ledPin = 4;
const int ledPin2 = 21;

// Wi-Fi credentials
const char* ssid = "TELUS2405-2.4G";
const char* password = "7aet6s54w6";

// LCD display object
Adafruit_ST7789 display = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

// Web server
WebServer server(80);

bool isConnected = false;

void testdrawtext(const char *text, uint16_t color) {
  display.fillScreen(ST77XX_BLACK); // clear screen
  display.setCursor(0, 0);
  display.setTextSize(2);
  display.setTextColor(color);
  display.setTextWrap(true);
  display.print(text);
}

// Add a new function that doesn't clear the screen
void drawtext(const char *text, uint16_t color, int ypos) {
  display.setCursor(0, ypos);
  display.setTextSize(2);
  display.setTextColor(color);
  display.setTextWrap(true);
  display.print(text);
}

// Handle System ON
void handleOn() {
  digitalWrite(ledPin, HIGH);
  digitalWrite(ledPin2, !digitalRead(ledPin));
  server.send(200, "text/plain", "System is ON");
  
  // Clear the screen once
  display.fillScreen(ST77XX_BLACK);
  
  // Display WiFi and IP info at the top
  String message = "WiFi Connected\nIP: " + WiFi.localIP().toString();
  drawtext(message.c_str(), ST77XX_CYAN, 0);
  
  // Display System status below the IP (adjust 60 as needed for your display)
  drawtext("System is ON", ST77XX_GREEN, 60);
  
  // Display address and water consumption
  drawtext("0xeBd1...306f", ST77XX_WHITE, 100);
  drawtext("Water Consumption:", ST77XX_WHITE, 140);
  drawtext("12/h", ST77XX_BLUE, 180);
}

// Handle LED OFF
void handleOff() {
  digitalWrite(ledPin, LOW);
  digitalWrite(ledPin2, !digitalRead(ledPin));
  server.send(200, "text/plain", "System is OFF");
  
  // Clear the screen once
  display.fillScreen(ST77XX_BLACK);
  
  // Display WiFi and IP info at the top
  String message = "WiFi Connected\nIP: " + WiFi.localIP().toString();
  drawtext(message.c_str(), ST77XX_CYAN, 0);
  
  // Display System status below the IP
  drawtext("System is OFF", ST77XX_RED, 60);
  
  // Display address and water consumption
  drawtext("0xeBd1...306f", ST77XX_WHITE, 100);
  drawtext("Water Consumption:", ST77XX_WHITE, 140);
  drawtext("12/h", ST77XX_BLUE, 180);
}

void setup() {
  Serial.begin(921600);

  // Pin modes
  pinMode(ledPin, OUTPUT);
  pinMode(builtInLedPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  // LCD setup
  display.init(240, 320, SPI_MODE3); // Or change to (135, 240) if using 1.14" model
  display.setRotation(2);
  testdrawtext("Connecting...", ST77XX_YELLOW);

  // Wi-Fi
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi...");

  // Web server routes
  server.on("/on", handleOn);
  server.on("/off", handleOff);
  server.begin();
}

void loop() {
  server.handleClient();

  if (WiFi.status() == WL_CONNECTED && !isConnected) {
    digitalWrite(builtInLedPin, HIGH);
    Serial.print("Connected to WiFi: ");
    Serial.println(WiFi.localIP());

    handleOff();  // ✅ Turn system off by default after connection
    isConnected = true;
  }

  if (WiFi.status() != WL_CONNECTED) {
    digitalWrite(builtInLedPin, !digitalRead(builtInLedPin));
    delay(500);

    if (isConnected) {
      testdrawtext("WiFi Lost!", ST77XX_ORANGE);
      isConnected = false;
    }
  }
}
