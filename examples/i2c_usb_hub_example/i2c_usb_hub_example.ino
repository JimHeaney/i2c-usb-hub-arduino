/*
  i2c USB Hub Example Sketch
  Written by: Jim Heaney, May 12 2024
  Licensed under CC-By-NC-SA 4.0

  This sketch shows how to use the libary's main functions;
  * begin(a) - Used to initialize the device. 
  * setPort(a, b) - Used to set port a to mode b. A is a byte from 1-4, other numbers simply ignored. b is a bool, 1 turns on port a, 0 turns it off.
  * setLEDs(a) - Used to turn on or off the status LEDs on the ports. a is a bool, set to 1 for LEDs on, 0 for off. LEDs will show if a specific port is on or off. 
  * setCurrent(a) - Used to set the current limit on the USB ports and hub. a is a bool, set to 1 for high-power mode, 0 for low-power. In high-power, the entire hub is limited to 1000mA, and each port to 240mA. In low-power, the entire hub is limited to 500mA, and each port to 100mA. 
*/

#include "i2cusb.h"

i2cusb Hub;  //creates a "hub" class, can have multiples if you want to control multiple different USB hubs in the same sketch. Optionally accepts a new i2c address (set by jumpers on the back of the board)
//Example: if you have a second hub and close the last jumper on the back of the board,  write "i2cusb Hub2(0x19);".

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);

  if (Hub.begin()) {
    //If the hub initializes, it should return 1.
    Serial.println(F("USB Hub Initialized"));
  } else {
    //begin returned 0, probably couldn't find an i2c device at that address
    Serial.println(F("Could not find the device, bad wiring or wrong i2c address? Please reset and try again!"));
    while (1)
      ;
  }

  Hub.setLEDs(1);     //Turn on the LEDs;
  Hub.setCurrent(1);  //Set to high current limit mode
}

void loop() {
  // put your main code here, to run repeatedly:

  //Cycle though all the ports, turning them on and off one at a time;
  Hub.setPort(1, 1);
  delay(1000);
  Hub.setPort(1, 0);
  Hub.setPort(2, 1);
  delay(1000);
  Hub.setPort(2, 0);
  Hub.setPort(3, 1);
  delay(1000);
  Hub.setPort(3, 0);
  Hub.setPort(4, 1);
  delay(1000);
  Hub.setPort(4, 0);
  delay(1000);

  //Now turn on all the ports at once
  Hub.setPort(1, 1);
  Hub.setPort(2, 1);
  Hub.setPort(3, 1);
  Hub.setPort(4, 1);
  delay(1000);

  //Now turn off all the LEDs, but leave the ports on. If you have USB devices connected, you should still see them as normal on the computer.
  Hub.setLEDs(0);
  delay(1000);
  Hub.setLEDs(1);
  delay(1000);

  //Now turn them all off at once
  Hub.setPort(1, 0);
  Hub.setPort(2, 0);
  Hub.setPort(3, 0);
  Hub.setPort(4, 0);
  delay(1000);
}
