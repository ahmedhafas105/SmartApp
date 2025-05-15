#include <Arduino.h>

#define BLYNK_TEMPLATE_ID "TMPL64Ucu7v7O"
#define BLYNK_TEMPLATE_NAME "SmartApp"
#define BLYNK_AUTH_TOKEN "jULbQ4nBzAl1ocKw8IAaZ06IdvZVon9g"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <WiFiClient.h>

const char *SSID = "Wokwi-GUEST";
const char *PASSWORD = "";

const int LED_PIN = 2;
const int BUZZER_PIN = 4;
const int IR_SENSOR_PIN = 15;
const int GAS_SENSOR_PIN = 34;

#define V_LED_STATUS V0
#define V_MOTION_LABEL V1
#define V_GAS_GUAGE V2
#define V_BUZZER_STATUS V3

BlynkTimer timer;

void gasData() {
  int gas = analogRead(GAS_SENSOR_PIN);

  Serial.print("Gas Value: ");
  Serial.println(gas);

  Blynk.virtualWrite(V_GAS_GUAGE, gas);
}

void checkMotion() {
  int irSensorValue = digitalRead(IR_SENSOR_PIN);

  if (irSensorValue == 0) {

    Serial.println("Motion Detected");
    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER_PIN, 1500);
    Blynk.virtualWrite(V_LED_STATUS, 1);
    Blynk.virtualWrite(V_BUZZER_STATUS, 1);
    Blynk.virtualWrite(V_MOTION_LABEL, "Motion Detected");
    delay(1500);
  } else {

    Serial.println("No Motion");
    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER_PIN);
    Blynk.virtualWrite(V_LED_STATUS, 0);
    Blynk.virtualWrite(V_BUZZER_STATUS, 0);
    Blynk.virtualWrite(V_MOTION_LABEL, "No Motion");

  }
}

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASSWORD);
  // WiFi.begin("Wokwi-GUEST", "");
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println(WiFi.status());
    Serial.print('.');
    delay(1000);
  }
  Serial.println("Connected");
  Serial.println(WiFi.status());
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(9600);

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(IR_SENSOR_PIN, INPUT);
  pinMode(GAS_SENSOR_PIN, INPUT);

  digitalWrite(LED_PIN, LOW);
  noTone(BUZZER_PIN);

  initWiFi();

  Blynk.begin(BLYNK_AUTH_TOKEN, SSID, PASSWORD);
  Serial.println("Connected to Blynk");

  timer.setInterval(250L, checkMotion);
  timer.setInterval(500L, gasData);

}

void loop() {
  Blynk.run();
  timer.run();
}