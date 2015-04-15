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

#ifndef TIMER_H_
#define TIMER_H_

#define TIMER_LIST_CAPACITY 4

class EventObject;

typedef struct TimerItemStruct {
	uint16_t value;
	uint16_t restartValue;
	uint8_t eventId;
} TimerItem;


class Timer : public EventObject
{
public:
	Timer();
	~Timer();
	void clear();
	void add(uint16_t value, uint8_t eventId, bool isRepeat = false);
	bool isEventId(uint8_t eventId);
	uint16_t value(uint8_t eventId);
	void remove(uint8_t eventId);
	void tick();


protected:
	List<TimerItem> m_itemList;

};

#endif /* TIMER_H_ */
