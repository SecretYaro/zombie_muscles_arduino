

#include "TimerOne.h"


#define arrSize 32
#define threshold 160
#define LED 3
double sData = 0;
int val[arrSize];
int i = 0;
int emg = 0;
int maxV = 0, minV = 0;

void setup() {
    Serial.begin(115200);

    Timer1.initialize(3000);

    Timer1.attachInterrupt(sendData);
    pinMode(LED, OUTPUT);
    digitalWrite(LED, LOW);

    digitalWrite(LED, HIGH);

    for (int k = 0; k < arrSize; k++) {
        val[k] = 0;
    }
}

void sendData() {


    emg = analogRead(A0);

    val[i] = map(emg, 0, 1023, 0, 255);
    i++;

    if (i == arrSize) {
        i = 0;

        for (int k = 0; k < arrSize; k++) {
            if (val[k] > maxV)
                maxV = val[k];
            if (val[k] < minV)
                minV = val[k];
        }
        sData = maxV - minV;
        maxV = 0;
        minV = 0;
    }
    if (sData > threshold) {
        digitalWrite(LED, HIGH);
        Serial.print(1000);
    } else {
        digitalWrite(LED, LOW);
    }
    Serial.println();
}

void loop() {
}

