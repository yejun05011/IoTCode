#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>

#define SPI_CH     0
#define ADC_CH     5
#define ADC_CS     29
#define SPI_SPEED  500000

int main(void){
    int value = 0, i;
    unsigned char buf[3];

    if(wiringPiSetup() == -1) return 1;
    if(wiringPiSPISetup(SPI_CH, SPI_SPEED) == -1) return -1;

    pinMode(ADC_CS, OUTPUT);

    for(i = 0; i < 20; i++){
        buf[0] = 0x06 | ((ADC_CH & 0x04) >> 2);
        buf[1] = ((ADC_CH & 0x03) << 6);
        buf[2] = 0x00;

        digitalWrite(ADC_CS, 0);
        wiringPiSPIDataRW(SPI_CH, buf, 3);
        digitalWrite(ADC_CS, 1);

        buf[1] = 0x0F & buf[1];
        value = (buf[1] << 8) | buf[2];

        printf("%d\n", value);
        delay(100);
    }
}
