/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2013  <copyright holder> <email>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "TVController.h"
#include "Controller.h"


#define MOVE_DELAY	800
#define KEY_TIMEOUT	400

// initialize all devices

LiquidCrystal lcdDevice(8, 9, 4, 5, 6, 7);
KeyDevice keyDevice(KEY_PIN);
IRDevice irDevice(IR_PIN);
Server server;

// The Controller..

Controller controller;


void setup() 
{
    
	Serial.begin(57600);
    // set up the LCD's number of columns and rows: 
    lcdDevice.begin(LCD_WIDTH, LCD_HEIGHT);
    irDevice.enableIRIn();
	controller.begin();
	
}

void loop()
{
	controller.loop();  
	irDevice.loop();
	keyDevice.loop();
	server.loop();
}
