/*
  ArduLooper

  Controls a cheap Ammoon Loop Station (https://www.ammoon.com/p-i1995.html)

  Three latch buttons are used to create "shortcuts" to play/rec, stop and flush footswitch combinations.
  A pair of wires must be soldered on the two contacts of the original footswitch and connected to the
  collector and emitter of an NPN transistor.


*/
#define LOOPER   2
#define FLUSH   14
#define STOP  15
#define TOGGLE  16
#define RANDOMIZE  17

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LOOPER, OUTPUT);

  pinMode(FLUSH, INPUT_PULLUP);
  pinMode(STOP, INPUT_PULLUP);
  pinMode(TOGGLE, INPUT_PULLUP);
  pinMode(RANDOMIZE, INPUT_PULLUP);

  Serial.begin(9600);

}

// the loop function runs over and over again forever
void loop() {
  if (digitalRead(RANDOMIZE) == LOW) {
    Serial.println("RANDOMIZE...");
    press(25);
    delay(random(2000));
    Serial.println("RANDOMIZE!");
  } else {
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
