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
#include "IRDevice.h"



static const uint32_t PROGMEM irDeviceCodeTable[] = {
	 0x00910, IR_TV_KEY_0 ,
	 0x00010, IR_TV_KEY_1 ,
	 0x00810, IR_TV_KEY_2 ,
	 0x00410, IR_TV_KEY_3 ,
	 0x00C10, IR_TV_KEY_4 ,
	 0x00210, IR_TV_KEY_5 ,
	 0x00A10, IR_TV_KEY_6 ,
	 0x00610, IR_TV_KEY_7 ,
	 0x00E10, IR_TV_KEY_8 ,
	 0x00110, IR_TV_KEY_9 ,
	 0x002F0, IR_TV_KEY_UP ,
	 0x00AF0, IR_TV_KEY_DOWN ,
	 0x002D0, IR_TV_KEY_LEFT ,
	 0x00CD0, IR_TV_KEY_RIGHT ,
	 0x00A70, IR_TV_KEY_ENTER,
	 0x00490, IR_TV_KEY_VOLUME_UP,
	 0x00C90, IR_TV_KEY_VOLUME_DOWN,
	 0x00090, IR_TV_KEY_PROGRAM_UP,
	 0x00890, IR_TV_KEY_PROGRAM_DOWN,
	 0x01EE9, IR_TV_KEY_MOVE_BEGIN,
	 0x05EE9, IR_TV_KEY_MOVE_END,
	 0x04FE9, IR_TV_KEY_SKIP_BACK,
	 0x00FE9, IR_TV_KEY_SKIP_FORWARD,
	 0x06CE9, IR_TV_KEY_FAST_BACK,
	 0x01CE9, IR_TV_KEY_FAST_FORWARD,
	 0x02CE9, IR_TV_KEY_PLAY,
	 0x003EE, IR_TV_KEY_RECORD,
	 0x04CE9, IR_TV_KEY_PAUSE,
	 0x00CE9, IR_TV_KEY_STOP,
	 0x00290, IR_TV_KEY_MUTE,
	 0x00070, IR_TV_KEY_MENU,
	 0x062E9, IR_TV_KEY_RETURN,
	 0x036E9, IR_TV_KEY_TOOLS,
	 0x06D25, IR_TV_KEY_PICTURE,
	 0x00A50, IR_TV_KEY_SOURCE,
	 0x00338, IR_TV_KEY_RED,
	 0x00B38, IR_TV_KEY_GREEN,
	 0x00738, IR_TV_KEY_YELLOW,
	 0x00F38, IR_TV_KEY_BLUE,
	 0x00A90, IR_TV_KEY_POWER,
	 
	 0x90B47, IR_BD_KEY_0 ,
	 0x00B47, IR_BD_KEY_1 ,
	 0x80B47, IR_BD_KEY_2 ,
	 0x40B47, IR_BD_KEY_3 ,
	 0xC0B47, IR_BD_KEY_4 ,
	 0x20B47, IR_BD_KEY_5 ,
	 0xA0B47, IR_BD_KEY_6 ,
	 0x60B47, IR_BD_KEY_7 ,
	 0xE0B47, IR_BD_KEY_8 ,
	 0x10B47, IR_BD_KEY_9 ,
	 0x9CB47, IR_BD_KEY_UP ,
	 0x5CB47, IR_BD_KEY_DOWN ,
	 0xDCB47, IR_BD_KEY_LEFT ,
	 0x3CB47, IR_BD_KEY_RIGHT ,
	 0xBCB47, IR_BD_KEY_ENTER,
	 0xEAB47, IR_BD_KEY_MOVE_BEGIN,
	 0x6AB47, IR_BD_KEY_MOVE_END,
	 0xD8B47, IR_BD_KEY_FAST_BACK,
	 0x38B47, IR_BD_KEY_FAST_FORWARD,
	 0x58B47, IR_BD_KEY_PLAY,
	 0x98B47, IR_BD_KEY_PAUSE,
	 0x18B47, IR_BD_KEY_STOP,
	 0x42B47, IR_BD_KEY_MENU,
	 0xC2B47, IR_BD_KEY_RETURN,
	 0xFCB47, IR_BD_KEY_TOOLS,
	 0xE6B47, IR_BD_KEY_RED,
	 0x16B47, IR_BD_KEY_GREEN,
	 0x96B47, IR_BD_KEY_YELLOW,
	 0x66B47, IR_BD_KEY_BLUE,
	 0xF0B47, IR_BD_KEY_TELETEXT,
	 0x82B47, IR_BD_KEY_HELP,
	 0xA8B47, IR_BD_KEY_POWER,

};



IRDevice::IRDevice(uint8_t pin) : IRrecv(pin)
{
	m_value = 0;
	m_rawValue = 0;
	m_lastValue = 0;
	m_sendCount = 0;
}

uint32_t IRDevice::read()
{
	uint32_t value = 0;
	if ( decode(&m_results) ) {
		value = m_results.value;
		resume();
	}
	return value;
}

uint8_t IRDevice::value()
{
	return m_value;
}

uint32_t IRDevice::rawValue()
{
	return m_rawValue;
}

decode_results* IRDevice::results()
{
	return &m_results;
}

void IRDevice::loop()
{
	uint32_t value = read();
	if ( value > 0 ) {
		if (m_lastValue == value && m_sendCount > 0 ) {
			m_sendCount --;
		}
		else {
			_sendValue(value);
			m_sendCount = 4;
			m_lastValue = value;
		}
	}
	
/*	
	if ( value > 0) {
		if ( m_lastValue == 0 ) {
			m_lastValue = value;
			m_receiveTimout = millis() + 400;
			m_sendCount = 0;
		}
		else {
			if ( value == m_lastValue ) {
				m_sendCount ++;
				m_receiveTimout = millis() + 400;
			}
		}
		if ( m_sendCount == 3) {
			_sendValue(value);
		}
	}
	if ( millis() > m_receiveTimout && m_lastValue > 0 ) {
		_sendValue(m_lastValue);
	}
*/
}

void IRDevice::_sendValue(uint32_t value)
{
	m_rawValue = value;
	m_value = _translateToKeyCode(value);
	
/*
	lcdDevice.clear();
	lcdDevice.setCursor(0, 0);
	lcdDevice.print(value, HEX);
	lcdDevice.setCursor(8, 0);
	lcdDevice.print(m_value, HEX);
*/

	raiseEvent(IRReadEvent);
	m_lastValue = 0;
	m_sendCount = 0;

}


uint8_t IRDevice::_translateToKeyCode(uint32_t value)
{
	uint16_t i, result = 0;
	
	for ( i = 0; i < sizeof(irDeviceCodeTable); i += 2 ) {
		uint32_t irCode = pgm_read_dword(&irDeviceCodeTable[i]);
		if ( irCode == value ) {
			result = pgm_read_dword(&irDeviceCodeTable[i + 1]);
		}
	}
	return result;
}



