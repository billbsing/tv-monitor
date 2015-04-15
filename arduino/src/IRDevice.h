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


#ifndef IRDEVICE_H
#define IRDEVICE_H

#define IR_TV_KEY_0					0x01
#define IR_TV_KEY_1					0x02
#define IR_TV_KEY_2					0x03
#define IR_TV_KEY_3					0x04
#define IR_TV_KEY_4					0x05
#define IR_TV_KEY_5					0x06
#define IR_TV_KEY_6					0x07
#define IR_TV_KEY_7					0x08
#define IR_TV_KEY_8					0x09
#define IR_TV_KEY_9					0x0A
#define IR_TV_KEY_UP				0x0B
#define IR_TV_KEY_DOWN				0x0C
#define IR_TV_KEY_LEFT				0x0D
#define IR_TV_KEY_RIGHT				0x0E
#define IR_TV_KEY_ENTER				0x0F
#define IR_TV_KEY_VOLUME_UP			0x10
#define IR_TV_KEY_VOLUME_DOWN		0x11
#define IR_TV_KEY_PROGRAM_UP		0x12
#define IR_TV_KEY_PROGRAM_DOWN		0x13
#define IR_TV_KEY_MOVE_BEGIN		0x14
#define IR_TV_KEY_MOVE_END			0x15
#define IR_TV_KEY_SKIP_BACK			0x16
#define IR_TV_KEY_SKIP_FORWARD		0x17
#define IR_TV_KEY_FAST_BACK			0x18
#define IR_TV_KEY_FAST_FORWARD		0x19
#define IR_TV_KEY_PLAY				0x1A
#define IR_TV_KEY_RECORD			0x1B
#define IR_TV_KEY_PAUSE				0x1C
#define IR_TV_KEY_STOP				0x1D
#define IR_TV_KEY_MUTE				0x1E
#define IR_TV_KEY_MENU				0x1F
#define IR_TV_KEY_RETURN			0x20
#define IR_TV_KEY_TOOLS				0x21
#define IR_TV_KEY_PICTURE			0x22
#define IR_TV_KEY_SOURCE			0x23
#define IR_TV_KEY_RED				0x24
#define IR_TV_KEY_GREEN				0x25
#define IR_TV_KEY_YELLOW			0x26
#define IR_TV_KEY_BLUE				0x27
#define IR_TV_KEY_POWER				0x28



#define IR_BD_KEY_0					0x30
#define IR_BD_KEY_1					0x31
#define IR_BD_KEY_2					0x32
#define IR_BD_KEY_3					0x33
#define IR_BD_KEY_4					0x34
#define IR_BD_KEY_5					0x35
#define IR_BD_KEY_6					0x36
#define IR_BD_KEY_7					0x37
#define IR_BD_KEY_8					0x38
#define IR_BD_KEY_9					0x39
#define IR_BD_KEY_UP				0x3A
#define IR_BD_KEY_DOWN				0x3B
#define IR_BD_KEY_LEFT				0x3C
#define IR_BD_KEY_RIGHT				0x3D
#define IR_BD_KEY_ENTER				0x3E
#define IR_BD_KEY_MOVE_BEGIN		0x3F
#define IR_BD_KEY_MOVE_END			0x40
#define IR_BD_KEY_FAST_BACK			0x41
#define IR_BD_KEY_FAST_FORWARD		0x42
#define IR_BD_KEY_PLAY				0x43
#define IR_BD_KEY_PAUSE				0x44
#define IR_BD_KEY_STOP				0x45
#define IR_BD_KEY_MENU				0x46
#define IR_BD_KEY_RETURN			0x46
#define IR_BD_KEY_TOOLS				0x47
#define IR_BD_KEY_RED				0x48
#define IR_BD_KEY_GREEN				0x49
#define IR_BD_KEY_YELLOW			0x4A
#define IR_BD_KEY_BLUE				0x4B
#define IR_BD_KEY_TELETEXT			0x4C
#define IR_BD_KEY_HELP				0x4D
#define IR_BD_KEY_POWER				0x4E





class EventObject;

class IRDevice : public IRrecv, public EventObject
{

public:
	
	enum EventType {
		IRReadEvent = 1
	};
    IRDevice(uint8_t pin);
	uint32_t read();
	uint8_t value();
	uint32_t rawValue();
	void loop();
	decode_results *results();
	
protected:
	uint8_t _translateToKeyCode(uint32_t value);
	void _sendValue(uint32_t value);
	
	decode_results 	m_results;
	uint8_t 		m_value;
	uint32_t 		m_rawValue;
	uint32_t		m_receiveTimout;
	uint8_t			m_sendCount;
	uint32_t		m_lastValue;
	
};

#endif // IRDEVICE_H
