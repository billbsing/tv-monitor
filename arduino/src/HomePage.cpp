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
#include "HomePage.h"

HomePage::HomePage(uint8_t id) : Page(id)
{
}

bool HomePage::begin()
{
	_showTime();
	_showStats();
	lcdDevice.noCursor();
	m_startDelay = 4;

	return true;
}

void HomePage::onSecondTick()
{
	_showTime();
	
	if ( m_startDelay > 0 ) {
		m_startDelay --;
	}
}

void HomePage::onMinuteTick()
{
	_showStats();
}


void HomePage::onKeyPress(unsigned char key)
{
/*	
	if ( key == VIRTUAL_KEY_ENTER ) {
		raiseEvent(RequestUserAccessEvent);
	}
*/
}

void HomePage::onIRPress(uint8_t key, uint32_t rawValue)
{
	if ( m_startDelay == 0 ) {
		if ( key == IR_TV_KEY_POWER) {
			controller.setMonitoring(true);
			raiseEvent(RequestPowerOnEvent);		
		}
		if ( key >= IR_TV_KEY_0 && key < IR_TV_KEY_9) {
			controller.setMonitoring(true);
			raiseEvent(RequestPowerOnEvent);		
		}
		if ( key == IR_TV_KEY_9 || key == IR_BD_KEY_9) {
			controller.setMonitoring(false);
			raiseEvent(RequestPowerOnEvent);		
		}
	}
}


void HomePage::_showTime()
{
	char buffer[20];
	
//	char monthText[dt_MAX_STRING_LEN];
//	char dayText[dt_MAX_STRING_LEN];

	sprintf(buffer, getStaticString(SST_TIME_FORMAT), hour(), minute());
	lcdDevice.setCursor(LCD_WIDTH - strlen(buffer), 0);
	lcdDevice.print(buffer);
/*
	strcpy(monthText,monthShortStr(month()));
	strcpy(dayText, dayShortStr(weekday()));
	sprintf(buffer, getStaticString(SST_TIME_DATE_FORMAT), dayText , day(), monthText, year());
	lcdDevice.setCursor(0, 1);
	lcdDevice.print(buffer);
	lcdDevice.setCursor(0, 1);
*/
}


void HomePage::_showStats()
{

	UserType *user = controller.getUser(USER_INDEX_ADMIN);
		
	uint16_t dayMins = user->usedMinutes.day;
	uint16_t weekMins = user->usedMinutes.week;

	char buffer[20];
	formatMinutes(buffer, dayMins, false);
	lcdDevice.setCursor(0, 0);
	lcdDevice.print("Td:      ");
	lcdDevice.setCursor(3, 0);
	lcdDevice.print(buffer);

	formatMinutes(buffer, weekMins, false);
	lcdDevice.setCursor(0, 1);
	lcdDevice.print("Wk:      ");
	lcdDevice.setCursor(3, 1);
	lcdDevice.print(buffer);

//	sprintf(buffer, "%4d",  user->usedMinutes.day);

//	lcdDevice.setCursor(LCD_WIDTH - strlen(buffer), 1);
//	lcdDevice.print(buffer);
}


