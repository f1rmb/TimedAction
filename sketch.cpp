/*
  Copyright (C) 2013 F1RMB, Daniel Caujolle-Bert <f1rmb.daniel@gmail.com>

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include <Arduino.h>

#include <TimedAction.h>

#warning (I) *** You are using mutex

// Function prototype
void blink(void *data);

//this initializes a TimedAction class that will change the state of an LED every half second.
TimedAction timedAction(500, blink, NULL, false);

//pin / state variables
const byte  ledPin = 13;
boolean     ledState;
int         counter;

void blink(void *data)
{
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
}

void setup()
{
    counter  = 0;
    ledState = false;

    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, ledState);

    timedAction.enable();
}

void loop()
{
#if 1
    if (timedAction.check() == true)
    {
        counter++;

        if (counter == 10)
        {
            timedAction.setInterval(timedAction.getInterval() == 500 ? 250 : 500);
            counter = 0;
        }
    }
#else
    blink(NULL);
    delay(1000);
#endif
}

