// Include WiFi and MQTT communcation functionalities
#include "WiFi_MQTT.h"
#include "Temp_Humi_Function.h"
#include "Lightning_Control.h"
#include "Buzzer.h"
#include "LoRa_Function.h"

// Replace the next variables with your SSID/Password combination
const char* ssid = "Infinix NOTE 30 Pro";
const char* password = "1234567890";

const char* mqtt_server = "192.168.86.36";

void setup() {

  // Setup serial monitor for trobleshooting
  Serial.begin(9600);

  // Eduroam connection
  // setupWiFi("eduroam", "ecysh1@nottingham.edu.my", "bDagef.19z");

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,password);

  while(!connectToWiFi()){
    Serial.print(".");
    delay(50);
  }
  Serial.println();

  setupMQTT(mqtt_server, "esp-32");

  while(!connectToMQTT()){
    Serial.print(".");
    delay(50);
  }
  Serial.println();

  setupDHT22();
  // getDHT22Info(Temperature);
  // getDHT22Info(Humidity);

  setupLightSensor();
  setupLED();
  setupBuzzer();

  client.subscribe("Light_Control_PC");
}

unsigned long timer = millis();

void loop() {
  client.loop();
  String msg;

  sensors_event_t event;
  
  msg = String(getTemperature(event));
  client.publish("Temperature_Level", msg.c_str());

  msg = String(getHumidity(event));
  client.publish("Humidity_Level", msg.c_str());

  msg = String(isIntensityAbove());
  client.publish("Light_Control", msg.c_str());

  if(msg == "1"){
    singleBeep();
  }
  
  if(millis() - timer >= 2500){
    msg = String(getTemperature());
    client.publish("Temperature_Level", msg.c_str());

  delay(2000);
}
