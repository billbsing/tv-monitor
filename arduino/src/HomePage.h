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


#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include "Page.h"

class HomePage : public Page
{

public:
	
	typedef enum {
		ClosePageEvent = 1,
		RequestUserAccessEvent,
		RequestPowerOnEvent,
	} EventType;
	
    HomePage(uint8_t id);

	virtual bool begin();
	virtual void onSecondTick();
	virtual void onMinuteTick();
	virtual void onKeyPress(unsigned char key);
	virtual void onIRPress(uint8_t key, uint32_t rawValue);



protected:
	
	void _showTime();
	void _showStats();
	
	uint8_t m_startDelay;
	
};

#endif // HOMEPAGE_H
