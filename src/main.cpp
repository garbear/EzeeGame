/*
 *        Copyright (C) 2112 Garrett Brown <gbruin@ucla.edu>
 *
 *  This Program is free software; you can redistribute it and/or modify it
 *  under the terms of the Modified BSD License.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *     1. Redistributions of source code must retain the above copyright
 *        notice, this list of conditions and the following disclaimer.
 *     2. Redistributions in binary form must reproduce the above copyright
 *        notice, this list of conditions and the following disclaimer in the
 *        documentation and/or other materials provided with the distribution.
 *     3. Neither the name of the organization nor the
 *        names of its contributors may be used to endorse or promote products
 *        derived from this software without specific prior written permission.
 *
 *  This Program is distributed AS IS in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

#include "EzeeGameMaster.h"

#include <Arduino.h>
#include <Servo.h> // temp: if this isn't here arduino-cmake can't find the Servo library

#include <digitalWriteFast.h>

/**
 * We need to declare master as a global variable. When it was declared locally
 * right before master.Spin() below, the Arduino would glitch out hardcore and
 * turn random LEDs on and off.
 */
EzeeGameMaster master;

/**
 * Called by Arduino's main() function before loop().
 */
void setup()
{
	// Set up our serial communications
	master.Init();
}

/**
 * master.Spin() uses an infinite loop to bypass Arduino's main loop. The
 * advantages here are twofold: we avoid the overhead of a function call, and
 * we skip Arduino's call to "if (serialEventRun) serialEventRun();" betwixt
 * every call to loop(). This is desirable because we are using master to
 * process serial data instead of the serialEvent() callback provided by
 * Arduino.
 */
void loop()
{
	master.Spin();
}

