/*
  Ziacon3 Badge. 2022
  Dedicated to Lil Baby, Dexter, D, and all of the amazing folks at DCZia. Seriously, thank you for being awesome.
  Code by Lithochasm // April 2022
  Badge designed and code written with sonic help from Ghost, Vision Video, Carpenter Brut, and Charli XCX.
*/

#include <EEPROM.h>

bool lightPattern = 0;  // Are we in normal mode, or are we going crazy?
byte directionLed = 0;  // Breathe in... breathe out
byte ledVal = 0;        // Brightness

void setup(){

byte bootCount = 0;     // Count the times the badge has been powered on

ADCSRA &= ~(1<<ADEN);   // Disable ADC - Saves some power and we are not doing AtoD

//Set Outputs
pinMode(0, OUTPUT);
pinMode(1, OUTPUT);
pinMode(2, OUTPUT);

//Get the float data from the EEPROM at position 'eeAddress'
EEPROM.get(0, bootCount);
if(bootCount == 255) {
      EEPROM.put(0, 0);  // Rolls over boot count so we dont freeze if you somehow reboot this thing that much
    }

    else {
      bootCount = bootCount + 1;  // Add 1 for every boot
      EEPROM.put(0, bootCount);
    }

   //Test light
    if(bootCount % 5 == 0) {      //If its the fifth boot, we get a little crazy
      lightPattern = 1;
    }

}

void loop() {

  if(lightPattern == 0) {

    if(ledVal == 225)  directionLed =1;
    if(ledVal == 0)  directionLed = 0;

    if(directionLed) --ledVal;
    else ++ledVal;

    analogWrite(0, ledVal);  //  analogWrite light from 0 to 225
     delay(3);
    analogWrite(1, ledVal);  //  analogWrite values from 0 to 225
     delay(3);
    analogWrite(2, ledVal);  //  analogWrite values from 0 to 225
     delay(3);
}

else {
  //I'm sorry ziacon I'm afraid i cant show you the normal light pattern right now
  byte err = random(180);  // Get a random value for brightness
  analogWrite(0, err);
   delay(60);
  analogWrite(0, err - err/2);
   delay(20);
  analogWrite(1, err + 3);
   delay(30);
  analogWrite(2, err + 22);
}

// ZiaCTF{imsorrydave}

}
