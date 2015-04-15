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
#include "Timer.h"

Timer::Timer() : m_itemList(TIMER_LIST_CAPACITY)
{

}
Timer::~Timer()
{
	m_itemList.clear();
}

void Timer::clear()
{
	m_itemList.clear();
}

void Timer::add(uint16_t value, uint8_t eventId, bool isRepeat)
{
	TimerItemStruct item;
	memset(&item, 0, sizeof(TimerItemStruct));
	item.value = value;
	if ( isRepeat) {
		item.restartValue = value;
	}
	item.eventId = eventId;
	m_itemList.add(item);
}

bool Timer::isEventId(uint8_t eventId)
{
	uint16_t i;
	for ( i = 0 ;i < m_itemList.count(); i ++) {
		TimerItemStruct item = m_itemList.item(i);
		if ( item.eventId == eventId) {
			return true;
		}
	}
	return false;
}

uint16_t Timer::value(uint8_t eventId)
{
	uint16_t i;
	for ( i = 0 ;i < m_itemList.count(); i ++) {
		TimerItemStruct item = m_itemList.item(i);
		if ( item.eventId == eventId) {
			return item.value;
		}
	}
	return 0;
}
void Timer::remove(uint8_t eventId)
{
	uint16_t i;
	for ( i = 0 ;i < m_itemList.count(); i ++) {
		TimerItemStruct item = m_itemList.item(i);
		if ( item.eventId == eventId) {
			m_itemList.remove(i);
		}
	}
}

void Timer::tick()
{
	uint16_t i;
	for ( i = 0 ;i < m_itemList.count(); i ++) {
		TimerItemStruct item = m_itemList.item(i);
		if ( item.value <= 1) {
			raiseEvent(item.eventId);
			if ( item.restartValue == 0) {
				m_itemList.remove(i);
			}
			else {
				m_itemList.item(i).value = item.restartValue;
			}
		}
		else {
			m_itemList.item(i).value --;
		}
	}
}

