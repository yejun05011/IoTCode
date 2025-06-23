#include <wiringPi.h>
#include <stdio.h>

#define PIN 2
#define CONTROL_PIN 7

void edge_rise(void);
void edge_fall(void);

int main(void){
    if(wiringPiSetup() == -1) return 1;
    pinMode(PIN, INPUT);

    wiringPiISR(PIN, INT_EDGE_RISING, edge_rise);

    delay(10000);
}

void edge_rise(void){
    pinMode(CONTROL_PIN, OUTPUT);
    digitalWrite(CONTROL_PIN, HIGH);
    wiringPiISR(PIN, INT_EDGE_FALLING, edge_fall);
    printf("Edge_Rised.\n");
}

void edge_fall(void){
    pinMode(CONTROL_PIN, OUTPUT);
    digitalWrite(CONTROL_PIN, LOW);
    wiringPiISR(PIN, INT_EDGE_RISING, edge_rise);
    printf("Edge_Falled.\n");
}
