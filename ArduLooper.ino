/*
  ArduLooper

  Controls a cheap Ammoon Loop Station (https://www.ammoon.com/p-i1995.html)

  Three latch buttons are used to create "shortcuts" to play/rec, STOP_FLUSH_PIN and flush footswitch combinations.
  A pair of wires must be soldered on the two contacts of the original footswitch and connected to the
  collector and emitter of an NPN transistor.


*/
#include <EasyButton.h>

#define LOOPER   2
#define STOP_FLUSH_PIN  15
#define TOGGLE_PIN  16
#define RANDOMIZE_PIN  17
#define RANDOM_MIN 100
#define RANDOM_MAX 2000

EasyButton stopFlushButton(STOP_FLUSH_PIN);
EasyButton toggleButton(TOGGLE_PIN);
EasyButton randomizeButton(RANDOMIZE_PIN);

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LOOPER, OUTPUT);


  stopFlushButton.begin();
  //long press -> erase
  stopFlushButton.onPressedFor(1000, flush);
  //short press -> stop
  stopFlushButton.onPressed(stop);

  toggleButton.begin();
  toggleButton.onPressed(onTogglePress);

  randomizeButton.begin();
  Serial.begin(9600);

}

int analogValue;

void onTogglePress() {
  Serial.println("TOGGLING...");
  press(25);
  delay(500);
  Serial.println("TOGGLED!");
}
void flush() {
  Serial.println("FLUSHING...");
  clear();
  Serial.println("FLUSHED!");
}

// the loop function runs over and over again forever
void loop() {
  stopFlushButton.read();
  toggleButton.read();
  randomizeButton.read();

  if (randomizeButton.isPressed()) {
    Serial.println("RANDOMIZE...");
    press(25);
    analogValue = analogRead(A7);
    int value = map(analogValue, 0, 1023, RANDOM_MIN, RANDOM_MAX);
    delay(random(value));
    Serial.println("RANDOMIZE!");
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
  Serial.println("STOPPING...");

  press(25);
  delay(250);

  press(25);
  delay(250);
  Serial.println("STOPPED!");

}
