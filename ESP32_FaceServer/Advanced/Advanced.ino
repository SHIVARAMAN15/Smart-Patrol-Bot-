#include <WiFi.h>
#include "esp_camera.h"
#include "camera_pins.h"
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include "base64.h"  // Use this library: https://github.com/Densaugeo/base64_arduino

#define PIR_PIN 13

const char* ssid = "your_wifi_name";
const char* password = "your_wifi_password";

const char* serverUrl = "http://192.168.135.145:5000/upload";  // Update with your Flask server IP
const char* telegramChatID = "your_chat_id";
const char* telegramToken = "your_bot_token";

bool motionDetected = false;

void setup() {
  Serial.begin(115200);
  pinMode(PIR_PIN, INPUT);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");

  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  config.frame_size = FRAMESIZE_QVGA;
  config.jpeg_quality = 12;
  config.fb_count = 1;

  if (esp_camera_init(&config) != ESP_OK) {
    Serial.println("Camera init failed");
    return;
  }

  Serial.println("Camera ready");
}

void loop() {
  if (digitalRead(PIR_PIN) == HIGH && !motionDetected) {
    motionDetected = true;
    Serial.println("Motion detected! Capturing image...");
    captureAndSendImage();
  } else if (digitalRead(PIR_PIN) == LOW) {
    motionDetected = false;
  }

  delay(500);
}

void captureAndSendImage() {
  camera_fb_t* fb = esp_camera_fb_get();
  if (!fb) {
    Serial.println("Camera capture failed");
    return;
  }

  String imageBase64 = base64::encode(fb->buf, fb->len);
  String timestamp = String(__DATE__) + " " + String(__TIME__);

  DynamicJsonDocument doc(2048);
  doc["image"] = imageBase64;
  doc["timestamp"] = timestamp;
  doc["chat_id"] = telegramChatID;
  doc["token"] = telegramToken;

  String jsonStr;
  serializeJson(doc, jsonStr);

  HTTPClient http;
  http.begin(serverUrl);
  http.addHeader("Content-Type", "application/json");

  int httpResponseCode = http.POST(jsonStr);
  Serial.printf("Server response: %d\n", httpResponseCode);

  http.end();
  esp_camera_fb_return(fb);
}
