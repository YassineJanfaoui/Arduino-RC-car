#include <RH_ASK.h>
#include <SPI.h>  // Not actually used but needed to compile

RH_ASK driver;
#define A 2
#define B 3
#define C 4
#define D 5
#define E 6
#define F 7
#define Joy_BT 8
#define Joy_X A0
#define Joy_Y A1
int buttons[] = { A, B, C, D, E, F, Joy_BT };
int turned = 0;

void setup() {
  Serial.begin(115200);  // Debugging only
  if (!driver.init()) {
    Serial.println("init failed");
  }
  for (int i = 0; i < 7; i++) pinMode(buttons[i], INPUT);

}

void loop() {
  int X = analogRead(Joy_X);
  int Y = analogRead(Joy_Y);

  // Define the threshold values
  const int thresholdHigh = 512;
  const int thresholdLow = 250;

  if (Y > thresholdHigh) {
    const char *msg = "1";  // Forward
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
  } else if (Y < thresholdLow) {
    const char *msg = "2";  // Backward
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
  } else if (X > thresholdHigh) {
    const char *msg = "6";  // Turn right
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
  } else if (X < thresholdLow) {
    const char *msg = "4";  // Turn left
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
  } else {
    const char *msg = "0";  // Stop
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
  }

  if(digitalRead(B)==0)
  {
    const char *msg = "b";  // Stop
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
  }


  delay(200);  // Delay to avoid flooding
}