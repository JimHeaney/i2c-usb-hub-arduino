/*
	i2cUSB.h - Library for controlling the i2c USB Hub.
	Created by Jim Heaney, May 12 2024.
	Released into the public domain under license CC-BY-NC-SA 4.0.
*/
#ifndef i2cusb_h
#define i2cusb_h

#include "Arduino.h"

class i2cusb
{
	public:
		i2cusb(byte addr = 0x18);
		bool begin();
		void setPort(byte port, bool mode);
		void setLEDs(bool mode);
		void setCurrent(bool mode);
	private:
		byte _addr;
};

#endif