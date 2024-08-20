#include <Arduino.h>

#define BuzzerPIN 33

void setupBuzzer(){
    pinMode(BuzzerPIN, OUTPUT);
    digitalWrite(BuzzerPIN,HIGH);
}

void singleBeep(){
    digitalWrite(BuzzerPIN,LOW);
    delay(500);
    digitalWrite(BuzzerPIN,HIGH);
}