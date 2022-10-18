// src :
// https://create.arduino.cc/projecthub/Raushancpr/arduino-with-ir-sensor-1579b6
// src :
// https://create.arduino.cc/projecthub/electropeak/use-an-ir-remote-transmitter-and-receiver-with-arduino-1e6bc8
// src : https://github.com/Arduino-IRremote/Arduino-IRremote

// All librairies : https://github.com/arduino-libraries
// TOOL manage librairies -> to install libraries

// tone melodies : https://www.arduino.cc/en/Tutorial/BuiltInExamples/toneMelody
// builtin-examples : https://docs.arduino.cc/built-in-examples/



/*
Calling the package dependencies of the code
*/
#include "pitches.h"
#include <IRremote.hpp>


/*
Defining the pin adresses location of each device which would be remoted -> You should look to your arduino board to define them.
*/
const int IRSensor = 11; // connect ir sensor to arduino pin 11
const int Speaker = 8;   // conect Speaker to arduino pin 8


/*
Defining the touchs' remote adresses after testing each touch with the serial Monitor furnished with the Arduino Code Editor software
*/
// Remote Touches
// const int DEAD = 0;
// const int BUTTONHOLD = -1;
const int ONOFF = 69;
const int VOLUP = 70;
const int VOLDOWN = 21;
const int FUNCSTOP = 71;
const int FORWARD = 67;
const int BACKWARD = 68;
const int PLAYSTOP = 64;
const int UP = 9;
const int DOWN = 7;
const int EQ = 25;
const int STREPT = 13;
const int ZERO = 22;
const int ONE = 12;
const int TWO = 24;
const int THREE = 94;
const int FOUR = 8;
const int FIVE = 28;
const int SIX = 90;
const int SEVEN = 66;
const int EIGHT = 82;
const int NINE = 74;
/*
Defining a melody with two tables: 
                                 - melody[] : this table contain each notes which will be played in the melody
                                 - noteDurations[] : this table contain each duration time associated to the notes which will be played in the melody
*/
// notes in the melody:
int melody[] = {
    NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
    4, 8, 8, 4, 4, 4, 4, 4
};

/*
Defining another melody called star wars with two tables: 
                                 - StartwarsMelody[] : this table contain each notes which will be played in the melody
                                 - StartwarsNoteDurations[] : this table contain each duration time associated to the notes which will be played in the melody
*/
// https://www.musicnotes.com/sheetmusic/mtd.asp?ppn=MN0127456
int StartwarsMelody[] = {
    NOTE_D3, NOTE_D3, NOTE_D3, NOTE_G3, NOTE_D4, NOTE_C4, NOTE_B3, NOTE_A3,
    NOTE_G4, NOTE_D4, NOTE_C4, NOTE_B3, NOTE_A3, NOTE_G4, NOTE_D4, NOTE_C4,
    NOTE_B3, NOTE_C4, NOTE_A3, NOTE_D3, NOTE_D3, NOTE_G3, NOTE_D4, NOTE_C4,
    NOTE_B3, NOTE_A3, NOTE_G4, NOTE_D4, NOTE_C4, NOTE_B3, NOTE_A3, NOTE_G4,
    NOTE_D4, NOTE_C4, NOTE_B3, NOTE_C4, NOTE_A3, NOTE_D3, NOTE_D3, NOTE_E3,
    NOTE_E3, NOTE_C4, NOTE_B3, NOTE_A3, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_B3,
    NOTE_A3, NOTE_E3, NOTE_F3, NOTE_D3, NOTE_D3};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int StartwarsNoteDurations[] = {6, 6, 6, 2, 2, 6, 6, 6, 2, 4, 6, 6, 6, 2,
                                4, 6, 6, 6, 2, 4, 4, 2, 2, 6, 6, 6, 4, 2,
                                6, 6, 6, 2, 4, 6, 6, 6, 2, 4, 4, 4, 4, 6,
                                6, 6, 6, 6, 6, 6, 4, 4, 4, 4, 4};

// Defining constant variable for the single notes which are played on the others touches on the remote from 0 to 9
const int noteDuration_ = 1000 / 4;
const int pauseBetweenNotes_ = noteDuration_ * 1.30;

// Defining action in the one lap programm which runs at the IO of the Arduino 
void setup() {
  // Initializing the serial connection
  Serial.begin(9600);
    
  // Initializing the IR receiver connection
  IrReceiver.begin(IRSensor, ENABLE_LED_FEEDBACK);
}

// Defining action in the infinit lap programm which runs after the IO of the Arduino and thus after the setup() programm.
void loop() {
  
    // If the IR receiver decode 'something = bus data from the IRremote' ->  from the bus data, slice it and give it only the adress command (adress of the touch pressed)  if (IrReceiver.decode()) {
    // print the value of the decoded touch adress
    // Stop the reception of the IR receiver  (close the eye) -> It is mandatory else the IR receiver will still wait another data and still decode but data.
    Serial.println("AFFICHE VALEUR");
    int value = IrReceiver.decodedIRData.command;
    Serial.println(value);
    IrReceiver.stop(); // Receive the next value
      
      
    //Defining a switch case in order to define action linked to the adress of each touch
    Serial.println("DEBUT DU CASE SWITCH");
    switch (value) {
    // Backward key is used for left key operation
    case BUTTONHOLD:
      Serial.print("BUTTONHOLD\n");
      break;
    case ONOFF:
      Serial.print("ONOFF\n");
      for (int thisNote = 0; thisNote < 8; thisNote++) {
        int noteDuration = 1000 / noteDurations[thisNote];
        tone(Speaker, melody[thisNote], noteDuration);

        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
      }
      break;
    case VOLUP:
      Serial.print("VOLUP\n");
      break;
    case VOLDOWN:
      Serial.print("VOLDOWN\n");
      break;
    case FUNCSTOP:
      Serial.print("FUNCSTOP\n");
      break;
    case FORWARD:
      Serial.print("FORWARD\n");
      break;
    case BACKWARD:
      Serial.print("BACKWARD\n");
      break;
    case PLAYSTOP:
      Serial.print("PLAYSTOP\n");
      for (int thisNote = 0; thisNote < 37; thisNote++) {
        // for (int thisNote = 0; thisNote < sizeof(StartwarsMelody);
        // thisNote++){
        int noteDuration = 1000 / StartwarsNoteDurations[thisNote];
        tone(Speaker, StartwarsMelody[thisNote], noteDuration);

        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
      }
      break;
    case UP:
      Serial.print("UP\n");
      break;
    case DOWN:
      Serial.print("DOWN\n");
      break;
    // --------------------------------------------------------------------//
    case ZERO:
      Serial.print("ZERO\n");
      tone(Speaker, NOTE_C3, noteDuration_);
      break;
    case EQ:
      Serial.print("EQ\n");
      tone(Speaker, NOTE_CS3, noteDuration_);
      break;
    case STREPT:
      Serial.print("STREPT\n");
      tone(Speaker, NOTE_D3, noteDuration_);
      break;
    case ONE:
      Serial.print("ONE\n");
      tone(Speaker, NOTE_DS3, noteDuration_);
      break;
    case TWO:
      Serial.print("TWO\n");
      tone(Speaker, NOTE_E3, noteDuration_);
      break;
    case THREE:
      Serial.print("THREE\n");
      tone(Speaker, NOTE_F3, noteDuration_);
      break;
    case FOUR:
      Serial.print("FOUR\n");
      tone(Speaker, NOTE_FS3, noteDuration_);
      break;
    case FIVE:
      Serial.print("FIVE\n");
      tone(Speaker, NOTE_G3, noteDuration_);
      break;
    case SIX:
      Serial.print("SIX\n");
      tone(Speaker, NOTE_GS3, noteDuration_);
      break;
    case SEVEN:
      Serial.print("SEVEN\n");
      tone(Speaker, NOTE_A3, noteDuration_);
      break;
    case EIGHT:
      Serial.print("EIGHT\n");
      tone(Speaker, NOTE_AS3, noteDuration_);
      break;
    case NINE:
      Serial.print("NINE\n");
      tone(Speaker, NOTE_B3, noteDuration_);
      break;
    }
    delay(pauseBetweenNotes_);
    IrReceiver.start(pauseBetweenNotes_*1000); // Restarts in ms
    Serial.print("FIN DU CASE SWITCH\n");
    noTone(Speaker);
    IrReceiver.resume(); // Receive the next value
  }
}
