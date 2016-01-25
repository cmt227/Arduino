#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

#define DEBOUNCE_MILLIS 3
#define chan 1
#define nbtns 4
#define nleds 3

int btnPins[] = {2, 3, 4, 5};
int prevBtnVal[] = {HIGH, HIGH, HIGH, HIGH};
int ledPins[] = {9, 10, 11};
//int vals[] = {0, 0, 0, 0};
//int ledStates[] = {LOW, LOW, LOW, LOW};

int btnPin;
int btnVal;
//int ledPin;

void setup()
{
    for(int i = 0; i < nbtns; i++) {
      pinMode(btnPins[i], INPUT_PULLUP);
      //pinMode(ledPins[i], OUTPUT);
      //digitalWrite(ledPins[i], LOW);
    }
    for(int i = 0; i < nleds; i++) {
      pinMode(ledPins[i], OUTPUT);
    }

    // a pretty light show
    digitalWrite(ledPins[0], HIGH);
    delay(300);
    digitalWrite(ledPins[0], LOW);
    digitalWrite(ledPins[1], HIGH);
    delay(300);
    digitalWrite(ledPins[1], LOW);
    digitalWrite(ledPins[2], HIGH);
    delay(300);
    digitalWrite(ledPins[2], LOW);
    
    MIDI.begin(chan);   // Launch MIDI and listen to channel chan
}

void loop()
{
  for(int i = 0; i < nbtns; i = i + 1)
  {
    delay(DEBOUNCE_MILLIS);
    
    btnPin = btnPins[i];
    //ledPin = ledPins[i];
    
    btnVal = digitalRead(btnPin);

    //btn was pushed or released
    if(btnVal != prevBtnVal[i])
    {
      // btn pushed
      if(btnVal == LOW)
      {
        MIDI.sendControlChange(i, 127, 1);
      }
      // btn released
      else { }
    }

    prevBtnVal[i] = btnVal;
    
  } // for
}
