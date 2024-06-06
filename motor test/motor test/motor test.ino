#include <RH_ASK.h>
#include <SPI.h>

// Motor driver pins
int enA = 3;
int IN1 = 8;
int IN2 = 4;

int enB = 6;
int IN3 = 5;
int IN4 = 7;
int beep = 10;
uint8_t buf[1];
uint8_t buflen = sizeof(buf);
char receivedChar;

RH_ASK driver;

void setup() {
  Serial.begin(115200);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(beep,OUTPUT);
  analogWrite(enA, 100);
  analogWrite(enB, 100);
  
  if (!driver.init()) {
    Serial.println("init failed");
  }
}

void loop() {
  // Check if we have received any data from the RF module
  if (driver.recv(buf, &buflen)) {  // Non-blocking
    receivedChar = (char)buf[0];
    Serial.print(receivedChar);
    // Control the motors based on the received character
    handleMotorControl(receivedChar);

  } 
  receivedChar = Serial.read();
  handleMotorControl(receivedChar);
}

void handleMotorControl(char command) {
  switch (command) {
    case '1':  // Forward command
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      Serial.print("forward");
      break;
    case '0':  // Stop command
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      Serial.print("stop");
      break;
    case '6':  // Turn right command
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      Serial.print("right");
      break;
    case '4':  // Turn left command
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      Serial.print("left");
      break;
    case '2':
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      Serial.print("back");
      break;
    case 'b':
      tone(beep,512);
      delay(1000);
      noTone(beep);
      break;
  }
}