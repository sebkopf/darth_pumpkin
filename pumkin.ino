/*
 * Created on: October 30, 2016
 * Author: Sebastian Kopf <seb.kopf@gmail.com>
 * Darth Pumpkin script for Particle Photon
 * (should work with any arduino as well with a little modification)
 */

#include "application.h"
#include "pitches.h"

// range finder
#define TRIGGER_PIN D1
#define ECHO_PIN D0
#define READ_INTERVAL 50 // how often to query sensor [ms] (limited by speed of reading)
#define ALARM_DISTANCE 400 // distance for activation [cm]
#define TRIGGER_TIME 500 // debounce [ms]
bool is_active = false;
long last_read_time = millis();
long last_active_time = millis();

// song and LEDs
#define BUZZER_PIN A5
#define SONG_MIN_INTERVAL 1000*30 // minimum wait for activating the song [ms]
long last_song_time = millis();

// beginning of imperial march (modified for easier extension)
// original transcription thanks to instructables user eserra
// http://www.instructables.com/id/How-to-easily-play-music-with-buzzer-on-arduino-Th/
const int n_notes = 71;
const double notes[] =
  {NA3, NA3,  NA3, NF3, NC4,  NA3, NF3,  NC4, NA3, NE4, NE4,  NE4,  NF4,  NC4,  NAb3, NF3, NC4, NA3,
   NA4, NA3,  NA3, NA4, NAb4, NG4, NGb4, NE4, NF4, NP,  NBb3, NEb4, ND4,  NDb4, NC4,  NB3, NC4, NP,
   NF3, NAb3, NF3, NA3, NC4,  NA3, NC4,  NE4, NA4, NA3, NA3,  NA4,  NAb4, NG4,  NGb4, NE4, NF4, NP,
   NBb3,NEb4, ND4, NDb4,NC4,  NB3, NC4,  NP,  NF3, NAb3,NF3,  NC4,  NA3,  NF3,  NC4,  NA3, NP};
const double beats[] =
  {Q,   Q,    Q,   E+S, S,    Q,   E+S,  S,   H,   Q,   Q,    Q,    E+S,  S,    Q,    E+S, S,   H,
   Q,   E+S,  S,   Q,   E+S,  S,   S,    S,   E,   E,   E,    Q,    E+S,  S,    S,    S,   E,   E,
   E,   Q,    E+S, S,   Q,    E+S, S,    H,   Q,   E+S, S,    Q,    E+S,  S,    S,    S,   E,   E,
   E,   Q,    E+S, S,   S,    S,   E,    E,   E,   Q,   E+S,  S,    Q,    E+S,  S,    H,   H};

// lightin settings
#define LED0 D2 // background lighting
#define LED1 D3 // red
#define LED2 D4 // red
#define LED3 D5 // green
#define LED4 D6 // blue
#define LED5 D7 // PAUSE - usually don't connect to any external LED

const int lights[] =
  {LED1,LED1, LED1,LED2,LED3, LED1,LED2, LED3,LED4,LED1,LED1,LED1,  LED2, LED3, LED1, LED2,LED3,LED4,
   LED1,LED2, LED3,LED1,LED2, LED3,LED1, LED3,LED4,LED5,LED4,LED1,  LED2, LED3, LED1, LED3,LED4,LED5,
   LED4,LED1, LED2,LED3,LED1, LED2,LED3, LED4,LED1,LED2,LED3,LED1,  LED2, LED3, LED1, LED3,LED4,LED5,
   LED4,LED1, LED2,LED3,LED1, LED3,LED4, LED5,LED4,LED1,LED2,LED3,  LED1, LED2, LED3, LED4,LED5};


// setup
void setup() {
  Serial.begin(9600); // for info messages

  pinMode(TRIGGER_PIN, OUTPUT);
  digitalWriteFast(TRIGGER_PIN, LOW);
  pinMode(ECHO_PIN, INPUT);

  pinMode(BUZZER_PIN,  OUTPUT);
  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);

  digitalWrite(LED0, HIGH);
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  digitalWrite(LED4, HIGH);
  digitalWrite(LED5, HIGH);

  // few s delay to check all LEDs are active (for troubleshooting)
  delay(1000*3);
  turn_on_LED(LED0); // only background on
}

void turn_on_LED (int pin) {
  // turn all off
  digitalWrite(LED0, LOW);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, LOW);
  // turn specified on
  digitalWrite(pin, HIGH);
}

// loop
void loop() {

  if (millis() - last_read_time > READ_INTERVAL &&
      millis() - last_song_time > SONG_MIN_INTERVAL ) {
    last_read_time = millis();
    double d_cm = read_distance();
    if (d_cm < ALARM_DISTANCE) {
      // distance sensor activated
      if (!is_active) {
        is_active = true;
        last_active_time = millis();
        Serial.print(millis());
        Serial.printf("ms ACTIVATED %.1f cm", d_cm);
        Serial.println();
      }
      // see if min active trigger time has passed (i.e. debounce it)
      if (millis() - last_active_time > TRIGGER_TIME) {
        Serial.print(millis());
        Serial.println("ms PLAYING SONG");
        play_song();
        last_song_time = millis();
        is_active = false;
      }
    }
    else if (is_active == true) {
      Serial.print(millis());
      Serial.printf("ms DEACTIVATED %.1f cm", d_cm);
      Serial.println();
      // no activity
      is_active = false;
    }
  }

}

double read_distance () {
    digitalWriteFast(TRIGGER_PIN, HIGH);
    delayMicroseconds(10);
    digitalWriteFast(TRIGGER_PIN, LOW);
    unsigned long duration = pulseIn(ECHO_PIN, HIGH); // in mico seconds
    double cm = duration * 340 * 0.0001 * 0.5; // speed of sound 340 m/s, convert to cm/us, factor 2 for there and back
    return(cm);
}

void play_song() {
  int i = 0;
  for (; i < n_notes; i++) {
    turn_on_LED(lights[i]);
    if (notes[i] == NP) {
      noTone(BUZZER_PIN);
      delay(beats[i]);
    } else {
      tone(BUZZER_PIN, notes[i], beats[i]);
      delay(beats[i]); // wait for tone to finish
    }
    digitalWrite(lights[i], LOW);
    delay(GAP); // brief pause between notes
  }

  digitalWrite(LED0, HIGH); // background LED back on
  Serial.println("song done");
}
