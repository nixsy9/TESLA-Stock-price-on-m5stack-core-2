#include <LovyanGFX.hpp>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <lgfx/v1_autodetect/LGFX_AutoDetect_ESP32_all.hpp>

#define LGFX_AUTODETECT
static LGFX lcd;

// WiFi credentials
const char* ssid = "PUT YOUR WIFI SSID IN HERE";
const char* password = "AND ITS PASSWORD HERE";

// Finnhub API endpoint for Tesla quote data //REPLACE API-KEY-HERE with your free api from https://finnhub.io/
const String stockAPI = "https://finnhub.io/api/v1/quote?symbol=TSLA&token=API-KEY-HERE";

void setup() {
  Serial.begin(9600);

  // Initialize the display
  lcd.init();
  lcd.setRotation(1);
  lcd.setBrightness(128);
  lcd.fillScreen(TFT_BLACK);
  lcd.setTextSize(2);
  lcd.setTextColor(TFT_WHITE);
  lcd.setCursor(10, 10);
  lcd.println("Initializing...");

  // Connect to WiFi
  lcd.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
    lcd.print(".");
  }
  lcd.println("\nConnected to WiFi");
  Serial.println("Connected to WiFi");
}

void loop() {
  HTTPClient http;
  http.begin(stockAPI);
  int httpCode = http.GET();

  if (httpCode == HTTP_CODE_OK) {
    String payload = http.getString();
    Serial.println(payload);

    // Parse the JSON response
    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, payload);

    if (!error) {
      float currentPrice = doc["c"];
      float previousClose = doc["pc"];
      float priceChange = currentPrice - previousClose;
      String changeSymbol = (priceChange >= 0) ? "+" : "-";

      // Display stock data
      lcd.fillScreen(TFT_BLACK);
      lcd.setCursor(10, 10);
      lcd.println("Preious to New Price:");
      lcd.println("Tesla Stock Data:");
      lcd.printf("Current: $%.2f\n", currentPrice);
      lcd.printf("Prev:    $%.2f\n", previousClose);
      lcd.printf("Change:  %s$%.2f\n", changeSymbol.c_str(), abs(priceChange));
    } else {
      Serial.println("JSON Parsing Error");
      lcd.fillScreen(TFT_BLACK);
      lcd.setCursor(10, 10);
      lcd.println("JSON Parsing Error");
    }
  } else {
    Serial.println("Error on HTTP request");
    lcd.fillScreen(TFT_BLACK);
    lcd.setCursor(10, 10);
    lcd.println("HTTP Request Failed");
  }

  http.end();
  delay(1800000);  // 30-minute delay
}
