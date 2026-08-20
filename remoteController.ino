#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10);

const byte address[6] = "00001";

const int VRx = A1;
const int VRy = A0;

struct JoystickData {
  int x;
  int y;
};

JoystickData data;

void setup() {

  Serial.begin(9600);

  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_250KBPS);
  radio.stopListening();

  Serial.println("Transmitter ready!");
}

void loop() {

  // Read joystick
  data.x = analogRead(VRx);
  data.y = analogRead(VRy);

  // Send joystick data
  bool success = radio.write(&data, sizeof(data));

  // Display joystick position
  Serial.print("X: ");
  Serial.print(data.x);

  Serial.print("   Y: ");
  Serial.print(data.y);

  if (success) {
    Serial.println("   SENT");
  }
  else {
    Serial.println("   FAILED");
  }

  delay(50);
}