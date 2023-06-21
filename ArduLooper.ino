/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/
#define LOOPER   2
#define FLUSH   14
#define STOP  15
#define TOGGLE  16

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LOOPER, OUTPUT);

  pinMode(FLUSH, INPUT_PULLUP);
  pinMode(STOP, INPUT_PULLUP);
  pinMode(TOGGLE, INPUT_PULLUP);

  Serial.begin(9600);

}

// the loop function runs over and over again forever
void loop() {

  if (digitalRead(FLUSH) == LOW) {
    Serial.println("FLUSHING...");
    clear();
    Serial.println("FLUSHED!");

  }

  else if (digitalRead(STOP) == LOW) {
    Serial.println("STOPPING...");
    stop();
    Serial.println("STOPPED!");

  }
  else if (digitalRead(TOGGLE) == LOW) {
    Serial.println("TOGGLING...");
    press(25);
    delay(500);
    Serial.println("TOGGLED!");
  }
}

void press(int time) {
  // corrisponde ad un solo click
  digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
  digitalWrite(LOOPER, HIGH);
  delay(time);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(LOOPER, LOW);
  delay(time);
}

void clear() {
  stop();
  press(1500);
}

void stop() {
  press(25);
  delay(250);

  press(25);
  delay(250);
}
