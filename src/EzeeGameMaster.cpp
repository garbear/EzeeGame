/*
 *        Copyright (C) 2012-2014 Garrett Brown
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

int led = 13;

void EzeeGameMaster::Init()
{
  pinMode(led, OUTPUT);
}

void EzeeGameMaster::Spin()
{
  for (;;)
  {
      digitalWrite(led, HIGH);
      delay(1000);
      digitalWrite(led, LOW);
      delay(1000);
  }
}
