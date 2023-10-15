#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const byte address[5][6] = {"00001", "00002", "00003", "00004", "00005"};

int amt_transmitters = 5;
RF24 radios[5] = {};


void setup() {
  Serial.begin(9600);
  for (int i = 0; i < amt_transmitters; i++) {
    RF24 radio(7, 8);
    radios[i] = radio;
    radios[i].begin();

    radio.openReadingPipe(0, address[i]);
    radio.setPALevel(RF24_PA_MIN);
    radio.startListening();
  }
}

void loop() {
  for (int i = 0; i < amt_transmitters; i++) {
    if (radios[i].available()) {
      char text[32] = "";
      radios[i].read(&text, sizeof(text));
      Serial.println(text);
    }
  }
}