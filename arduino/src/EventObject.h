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

#ifndef EventObject_h
#define EventObject_h

#include "List.h"

#define LISTENER_LIST_CAPACITY 4

/*
using namespace fastdelegate;
#include "FastDelegate.h"
#include "FastDelegateBind.h"

typedef FastDelegate1<uint8_t, bool> EventDelegate;
*/

class EventObject;
/*
typedef struct EventListenerItemStruct {
	EventDelegate delegate;
	uint8_t eventId;
} EventListenerItem;
*/

typedef struct EventListenerItemStruct {
	EventObject *object;
	uint8_t eventId;
} EventListenerItem;

class EventObject
{
public:
	EventObject();
	virtual ~EventObject();
	void clearListenerList();
	void createListenerList(int size);

/*
 *	void bind(const EventDelegate &delegate, uint8_t eventId = 0);
	void unbind(const EventDelegate &delegate, uint8_t eventId = 0);
*/
	void bind(EventObject *object, uint8_t eventId = 0);
	void unbind(EventObject *object, uint8_t eventId = 0);

	void raiseEvent(uint8_t eventId = 0);

	virtual bool onEvent(EventObject *sender, uint8_t eventId);

protected:

	List<EventListenerItem> m_listenerList;
};

#endif
