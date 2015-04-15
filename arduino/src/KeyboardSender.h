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


#ifndef KEYBOARDSENDER_H
#define KEYBOARDSENDER_H

#include "List.h"
#define KEYBOARD_SENDER_ITEMS_CAPACITY	4

#define KEYBOARD_SENDER_KEY_TIMEOUT		10
#define KEYBOARD_SENDER_CLOSE_TIMEOUT	1000

typedef struct KeyEventStruct {
	unsigned char keyValue;
} KeyEventItem;


class KeyboardSender
{

public:
	
	typedef enum {
		NoneState = 0,
		WaitState,
		ReleaseKeyState,
		
		
		
	} KeyboardSenderStateEnum;
	
    KeyboardSender();
    virtual ~KeyboardSender();
	
	void add(unsigned char value);
	void process();
	
protected:
	
	bool 					m_isOpen;
	KeyboardSenderStateEnum m_state;
	unsigned long			m_timeout;
	unsigned long			m_closeTimeout;
	List<KeyEventItem> 		m_items;
	

};

#endif // KEYBOARDSENDER_H
