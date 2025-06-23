#include <wiringPi.h>
#include <stdio.h>

#define PIN 7

int main(void) {
    if (wiringPiSetup() == -1) {
        printf("Failed to initialized wiring Library\n");
        return 1;
    }

    pinMode(PIN, OUTPUT);
    digitalWrite(PIN, HIGH);
    delay(500);
    digitalWrite(PIN, LOW);
}