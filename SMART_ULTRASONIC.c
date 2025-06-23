#include <stdio.h>
#include <wiringPi.h>

#define TRIG 28
#define OUT 29

int main(void) {
    int dis = 0, i;
    long start, travel;

    if (wiringPiSetup() == -1) return 1;
    pinMode(TRIG, OUTPUT);
    pinMode(OUT, INPUT);

    for (i = 0; i < 20; i++) {
        // TRIG pin must start LOW
        digitalWrite(TRIG, 0);
        // Wait for sensor to settle
        usleep(2);

        // Send trig pulse
        digitalWrite(TRIG, 1);
        usleep(20);
        digitalWrite(TRIG, 0);

        // Wait for echo start
        while (digitalRead(OUT) == 0);

        start = micros();

        // Wait for echo end
        while (digitalRead(OUT) == 1);

        travel = micros() - start;

        // 거리 계산: 소리 속도 340m/s ≈ 29us/cm
        // 왕복 시간 기준이므로 2로 나눔, 결국 58로 나누면 cm 거리
        dis = travel / 58;
        printf("%d\n", dis);

        delay(100);
    }
}
