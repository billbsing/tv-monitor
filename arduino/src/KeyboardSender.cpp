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
#include "KeyboardSender.h"

KeyboardSender::KeyboardSender() : m_items(KEYBOARD_SENDER_ITEMS_CAPACITY)
{
	m_isOpen = false;
	m_state = WaitState;
	Keyboard.begin();
}

KeyboardSender::~KeyboardSender()
{
	m_items.clear();

}
void KeyboardSender::add(unsigned char value)
{
	KeyEventItem item;
	item.keyValue = value;
	m_items.add(item);
}


void KeyboardSender::process()
{
	if ( m_state == WaitState ) {
		if ( m_items.count() > 0 ) {
			KeyEventItem item = m_items.item(0);
			if ( !m_isOpen ) {
//				Keyboard.begin();
				m_isOpen = true;
			}
			m_closeTimeout = millis()  + KEYBOARD_SENDER_CLOSE_TIMEOUT;
			Keyboard.press(item.keyValue);
			m_state = ReleaseKeyState;			
			m_items.remove(0);
			m_timeout = millis() + KEYBOARD_SENDER_KEY_TIMEOUT;
		}
	}
	if ( m_state == ReleaseKeyState && (millis() >= m_timeout) ) {
		Keyboard.releaseAll();
		m_state = WaitState;
	}
	if ( m_isOpen && ( millis() >= m_closeTimeout) ) {
//		Keyboard.end();
		m_isOpen = false;
	}
}


