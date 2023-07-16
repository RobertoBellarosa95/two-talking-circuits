#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Wi-Fi Settings
const char* ssid = "<YOUR_WIFI_NAME>";
const char* password = "<YOUR_WIFI_PASSWORD>";

// API Key
const char* apiKey = "<YOUR_API_KEY>";

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// REPLACE WITH THE MAC Address of your receiver
uint8_t broadcastAddress[] = {0xD2, 0xED, 0x54, 0xC3, 0xD1, 0x12};

String success = "";

//Must match the receiver structure
typedef struct struct_message {
  char message[200];
} struct_message;

struct_message incoming_readings;
struct_message sender_readings;

String text = "";

esp_now_peer_info_t peerInfo;

// Callback when data is sent
void data_sent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
  if (status == 0) {
    success = "Delivery Success :)";
  }
  else {
    success = "Delivery Fail :(";
  }
}

// Callback when data is received
void data_receive(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&incoming_readings, incomingData, sizeof(incoming_readings));
  Serial.print("Bytes received: ");
  Serial.println(len);
  text = String(incoming_readings.message);
}

void setup() {

  Serial.begin(115200);
  WiFi.mode(WIFI_AP_STA);
  Serial.print("Connecting to Wi-Fi ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Established Wi-Fi connection");
  Serial.print("Station IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Wi-Fi Channel: ");
  Serial.println(WiFi.channel());

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_send_cb(data_sent);

  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 11;
  peerInfo.encrypt = false;
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
  // Register for a callback function that will be called when data is received
  esp_now_register_recv_cb(data_receive);
}

void loop() {

  String temp = otherVoice(text);
  temp.toCharArray(sender_readings.message, sizeof(sender_readings.message));

  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &sender_readings, sizeof(sender_readings));

  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  Display();
  delay(10000);
}

void Display() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print(sender_readings.message);
  display.display();

  Serial.println("INCOMING READINGS");
  Serial.println(incoming_readings.message);
  Serial.println("SENDING READINGS");
  Serial.print(sender_readings.message);
  Serial.println();
}

String otherVoice(String text) {
  HTTPClient http;

  // Setup HTTP api request
  http.begin("https://api.openai.com/v1/engines/text-davinci-003/completions");  // API Chat GPT Url
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Authorization", String("Bearer ") + apiKey);

  // Setup payload request
  DynamicJsonDocument doc(200);
  doc["prompt"] = text + ", (The response should be a maximum of 200 characters in size)";
  doc["max_tokens"] = 50;
  doc["temperature"] = 0.7;

  String payload;
  serializeJson(doc, payload);

  int httpCode = http.POST(payload);
  if (httpCode > 0) {
    // Read the API response and print on serial monitor
    String response = http.getString();
    //Parse JSON response with ArduinoJSON library
    const size_t capacity = JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(4) + 250;
    DynamicJsonDocument doc(capacity);
    deserializeJson(doc, response);
    String text = doc["choices"][0]["text"];
    return text;
  } else {
    Serial.println("Error HTTP request");
    Serial.println(httpCode);
  }

  http.end();

  return "Hi how are you? (The response should be a maximum of 200 characters in size)";
}