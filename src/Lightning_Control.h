#include <Arduino.h>

#define LightSensorPIN 27

#define WhiteLED 18

void setupLED(){
    pinMode(WhiteLED,OUTPUT);
}

void setupLightSensor(){
    pinMode(LightSensorPIN,INPUT);
}

bool isIntensityAbove(){
    if(digitalRead(LightSensorPIN)){
        digitalWrite(WhiteLED,HIGH);
        return true;
    }else{
        digitalWrite(WhiteLED,LOW);
        return false;
    }
}