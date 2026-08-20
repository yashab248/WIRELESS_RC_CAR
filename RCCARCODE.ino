#include <SPI.h>
#include <nRF24L01.h>
NEW SKETCH

#include <RF24.h>
#include <Servo.h>

RF24 radio(9, 10);

const byte address[6] = "00001";

Servo steeringServo;

// Servo
const int servoPin = 5;

// TB6612FNG
const int PWMA = 6;
const int AIN1 = 7;
const int AIN2 = 8;
const int STBY = 4;

// Joystick data
struct JoystickData {
  int x;
  int y;
};

JoystickData data;

// Radio failsafe
unsigned long lastReceiveTime = 0;
const unsigned long signalTimeout = 300;


void setup() {

  // -------------------------
  // SERVO
  // -------------------------

  steeringServo.attach(servoPin);
  steeringServo.write(90);


  // -------------------------
  // MOTOR DRIVER
  // -------------------------

  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(STBY, OUTPUT);

  // Motor OFF
  analogWrite(PWMA, 0);
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);

  // Driver disabled
  digitalWrite(STBY, LOW);


  // -------------------------
  // NRF24
  // -------------------------

  radio.begin();

  radio.openReadingPipe(0, address);

  radio.setPALevel(RF24_PA_LOW);

  radio.setDataRate(RF24_250KBPS);

  radio.startListening();

  // Start timer
  lastReceiveTime = millis();
}


void loop() {

  // -------------------------
  // RECEIVE RADIO DATA
  // -------------------------

  if (radio.available()) {

    radio.read(&data, sizeof(data));

    // We successfully received a packet
    lastReceiveTime = millis();


    // -------------------------
    // STEERING
    // -------------------------

    int servoPosition = map(
      data.x,
      0,
      1023,
      0,
      180
    );

    servoPosition = constrain(
      servoPosition,
      0,
      180
    );

    steeringServo.write(servoPosition);


    // -------------------------
    // MOTOR
    // -------------------------

    int throttle = data.y;


    // STOP
    if (throttle > 480 && throttle < 545) {

      analogWrite(PWMA, 0);

      digitalWrite(AIN1, LOW);
      digitalWrite(AIN2, LOW);

      digitalWrite(STBY, HIGH);
    }


    // FORWARD
    else if (throttle >= 545) {

      int speed = map(
        throttle,
        545,
        1023,
        100,
        255
      );

      speed = constrain(
        speed,
        100,
        255
      );

      digitalWrite(STBY, HIGH);

      digitalWrite(AIN1, LOW);
      digitalWrite(AIN2, HIGH);

      analogWrite(PWMA, speed);
    }


    // REVERSE
    else if (throttle <= 480) {

      int speed = map(
        throttle,
        480,
        0,
        100,
        255
      );

      speed = constrain(
        speed,
        100,
        255
      );

      digitalWrite(STBY, HIGH);

      digitalWrite(AIN1, HIGH);
      digitalWrite(AIN2, LOW);

      analogWrite(PWMA, speed);
    }
  }


  // -------------------------
  // RADIO FAILSAFE
  // -------------------------

  if (millis() - lastReceiveTime > signalTimeout) {

    // STOP MOTOR
    analogWrite(PWMA, 0);

    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);

    // DISABLE TB6612
    digitalWrite(STBY, LOW);

    // CENTER STEERING
    steeringServo.write(90);
    Serial.print("FAILEDDDDDD");
  }
}