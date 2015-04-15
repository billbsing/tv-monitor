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
#include "KeyDevice.h"


KeyDevice::KeyDevice(uint8_t pin)
{
	m_pin = pin;	
	m_lastKey = KEY_DEVICE_NONE;
	m_value = KEY_DEVICE_NONE;
	m_lastReadTime = millis();
}

uint8_t KeyDevice::value()
{
	return m_value;
}

void KeyDevice::loop()
{
	uint8_t key;
	if ( millis() < m_lastReadTime ) {
		m_lastReadTime = millis();
	}
	if ( (m_lastReadTime + KEY_DEVICE_DEBOUNCE_TIMEOUT) > millis() ) {
		return;
	}
	m_lastReadTime = millis();
	key = _peek();
	if ( m_lastKey == key ) {
		if ( m_value == KEY_DEVICE_NONE && key != KEY_DEVICE_NONE ) {
			m_value = key;
			raiseEvent(KeyUpEvent);
		}
		if ( m_value != KEY_DEVICE_NONE && key == KEY_DEVICE_NONE ) {
			raiseEvent(KeyDownEvent);
			m_value = key;
		}
	}
	m_lastKey = key;
	
}
uint8_t KeyDevice::_peek()
{
    uint8_t key = analogRead(m_pin) >> 7;
    if ( key == KEY_DEVICE_UP || key == KEY_DEVICE_DOWN || key == KEY_DEVICE_LEFT || key == KEY_DEVICE_RIGHT || key == KEY_DEVICE_ENTER ) {
    	return key;
	}
	return KEY_DEVICE_NONE;
	
}



