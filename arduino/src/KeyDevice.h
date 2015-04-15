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



#ifndef KEYDEVICE_H
#define KEYDEVICE_H

#define KEY_DEVICE_NONE		0x7
#define KEY_DEVICE_UP		0x1
#define KEY_DEVICE_DOWN 	0x2
#define KEY_DEVICE_LEFT 	0x3
#define KEY_DEVICE_RIGHT 	0x0
#define KEY_DEVICE_ENTER 	0x5
#define KEY_DEVICE_UNKNOWN	0xf

#define KEY_DEVICE_DEBOUNCE_TIMEOUT 	10

class EventObject;
class Delay;

class KeyDevice : public EventObject
{
	public:
		
		enum EventType {
			KeyDownEvent = 1,
			KeyUpEvent
		};
		
		KeyDevice(uint8_t pin);
		
		uint8_t value();
		void loop();
					
	protected:
	
		uint8_t _peek();

	
		uint8_t 	m_pin;
		uint8_t 	m_key;
		uint8_t		m_lastKey;
		uint8_t		m_value;
		uint32_t	m_lastReadTime;
		
	private:

};

#endif /* KEYDEVICE_H */ 
