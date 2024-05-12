/*
	i2cUSB.cpp - Library for controlling the i2c USB Hub.
	Created by Jim Heaney, May 12 2024.
	Released into the public domain under license CC-BY-NC-SA 4.0.
*/

#include "Arduino.h"
#include "i2cusb.h"
#include "Wire.h"

i2cusb::i2cusb(byte addr = 0x18)
{
	_addr = addr;
}

bool i2cusb::begin()
{
	//Called to initialize the IC, optionally accepts address
	Wire.begin();
	Wire.beginTransmission(_addr);
	Wire.write(0b00000011); //Configuration register address
	Wire.write(0b00000000); //Sets all pins as outputs 
	bool error = Wire.endTransmission();
	Wire.beginTransmission(_addr);
	Wire.write(0b00000010); //Polarity Inversion Register
	Wire.write(0b00000000); //Disable inversion on all pins (Why is this a feature?!)
	Wire.endTransmission();
	Wire.beginTransmission(_addr);
	Wire.write(0b00000001); //Output Control Register
	Wire.write(0b10000000); //Set current limit output to high for lower limit, all other inputs low
	Wire.endTransmission();
	setPort(4, 0); //For some reason the 4th port defaults to on, turn it off
	setLEDs(0); //Default the LEDs off
	return !error;
}

void i2cusb::setPort(byte port, bool mode)
{
 //Turns port X (1, 2, 3, 4) on (1) or off (0)
  if((port > 4) || (port == 0)){
    //Invalid port numbers
    return; 
	}	
	Wire.beginTransmission(_addr);
	Wire.write(0b00000001); //Output port register
	Wire.endTransmission();
	Wire.requestFrom(_addr, 1);
	byte oldstate = Wire.read(); //The current state of the registers, just flip the one needed bit  
	bitWrite(oldstate, (port+3), mode);  
	Wire.beginTransmission(_addr);
	Wire.write(0b00000001);
	Wire.write(oldstate);
	Wire.endTransmission();
}

void i2cusb::setLEDs(bool mode)
{
	//Turns on (1) or off (0) the LEDs
	Wire.beginTransmission(_addr);
	Wire.write(0b00000001); //Output port register
	Wire.endTransmission();
	Wire.requestFrom(_addr, 1);
	byte oldstate = Wire.read();
	bitWrite(oldstate, 3, mode);
	Wire.beginTransmission(_addr);
	Wire.write(0b00000001);
	Wire.write(oldstate);
	Wire.endTransmission();
}

void i2cusb::setCurrent(bool mode)
{
	//Sets the current limit of the USB ports. 1 for high-power mode, 0 for low-power mode. 
	Wire.beginTransmission(_addr);
	Wire.write(0b00000001); //Output port register
	Wire.endTransmission();
	Wire.requestFrom(_addr, 1);
	byte oldstate = Wire.read();
	bitWrite(oldstate, 0, !mode);
	Wire.beginTransmission(_addr);
	Wire.write(0b00000001);
	Wire.write(oldstate);
	Wire.endTransmission();
}	