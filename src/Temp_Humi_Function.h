#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 5

#define DHTTYPE DHT22

DHT_Unified dht(DHTPIN, DHTTYPE);

enum Types{
    Temperature,
    Humidity
};

void setupDHT22(){
    dht.begin();
}

void getDHT22Info(enum Types type){
    sensor_t sensor;
    if(type == Temperature){
        dht.temperature().getSensor(&sensor);
        Serial.println(F("------------------------------------"));
        Serial.println(F("Temperature Sensor"));
        Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
        Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
        Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
        Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
        Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
        Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
        Serial.println(F("------------------------------------"));
    }else if(type == Humidity){
        dht.humidity().getSensor(&sensor);
        Serial.println(F("Humidity Sensor"));
        Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
        Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
        Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
        Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
        Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
        Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
        Serial.println(F("------------------------------------"));
    }
}

float getTemperature(){
    sensors_event_t event;
    dht.temperature().getEvent(&event);
    return event.temperature;
}

float getHumidity(){
    sensors_event_t event;
    dht.humidity().getEvent(&event);
    return event.relative_humidity;
}