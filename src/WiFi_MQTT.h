#include <SPI.h>
#include <WiFi.h>
#include <PubSubClient.h>

WiFiClient espClient;
PubSubClient client(espClient);

// WiFi
// setup WiFi connection
void setupWiFi(String ssid, String identity, String password){

  // set ESP as station to connect to access point
  WiFi.mode(WIFI_STA);

  // start the connection to "ssid" with "identity" and "password"
  WiFi.begin(ssid, WPA2_AUTH_PEAP, identity, identity, password);
}

// connect to set WiFi
bool connectToWiFi(){

  // check if the WiFi is connected
  if(WiFi.status() == WL_CONNECTED){

    //print out the IP address of the ESP
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    //return true if connected
    return true;
  }else{
    // if fail to connect after 5 trials, then return false
    return false;
  }
}

String messageBuffer = "";
bool isMQTTMessageIn = false;

void callback(char* topic, byte* message, byte length) {
  messageBuffer = "";
  isMQTTMessageIn = true;
  String outputMessage = "Message arrived [" + String(topic) + "]: ";
  Serial.print(outputMessage);
  for (byte i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageBuffer += (char)message[i];
  }
  Serial.println();
}

// MQTT
// connect to MQTT with specified client ID
void setupMQTT(String serverAddress, String clientID) {
    client.setServer(serverAddress.c_str(), 1883);
    client.connect(clientID.c_str());
    
}

bool connectToMQTT(){
  if(client.connected()){
    client.setCallback(callback);
    return true;
  }else{
    return false;
  }
}