// Include WiFi and MQTT communcation functionalities
#include "WiFi_MQTT.h"
#include "Temp_Humi_Function.h"
#include "Lightning_Control.h"
#include "Buzzer.h"

// Replace the next variables with your SSID/Password combination
const char* ssid = "jianing 1505-2.4Ghz";
const char* password = "jianing1505";

const char* mqtt_server = "192.168.100.54";


void setup() {

  // Setup serial monitor for trobleshooting
  Serial.begin(9600);

  // // Eduroam connection
  // setup_wifi("eduroam", "ecysh1", "bDagef.19z");

  WiFi.begin(ssid,password);

  while(!connectToWiFi()){
    connectToWiFi();
  }
  connectToMQTT(mqtt_server, "esp-32");

  setupDHT22();
  getDHT22Info(Temperature);
  getDHT22Info(Humidity);

  setupLightSensor();
  setupLED();
  setupBuzzer();


}

void loop() {
  client.loop();
  String msg;
  
  msg = String(getTemperature());
  client.publish("Temperature_Level", msg.c_str());

  msg = String(getHumidity());
  client.publish("Humidity_Level", msg.c_str());

  msg = String(isIntensityAbove());
  client.publish("Light_Control", msg.c_str());

  if(msg == "1"){
    singleBeep();
  }

  delay(2000);
}