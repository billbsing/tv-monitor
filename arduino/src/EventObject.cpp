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
#include "EventObject.h"


EventObject::EventObject() : m_listenerList(LISTENER_LIST_CAPACITY)
{
}

EventObject::~EventObject()
{
	m_listenerList.clear();
}


void EventObject::bind(EventObject *object, uint8_t eventId)
{
	unbind(object, eventId);
	EventListenerItem item;
	item.object = object;
	item.eventId = eventId;
	m_listenerList.add(item);
}

void EventObject::unbind(EventObject *object, uint8_t eventId)
{
	uint16_t i;
	for ( i = 0 ;i < m_listenerList.count(); i ++) {
		EventListenerItem item = m_listenerList.item(i);
		if ( item.object == object && (item.eventId == eventId || eventId == 0) ) {
			m_listenerList.remove(i);
		}
	}	
}


void EventObject::raiseEvent(uint8_t eventId)
{
	uint16_t i;
	for ( i = 0 ;i < m_listenerList.count(); i ++) {
		EventListenerItem item = m_listenerList.item(i);
		if ( (item.eventId == eventId || item.eventId == 0) && item.object ) {
			if ( item.object->onEvent(this, eventId) ) {
				break;
			}
		}
	}
}


bool EventObject::onEvent(EventObject *sender,uint8_t eventId)
{
	return false;
}

/*
void EventObject::bind(const EventDelegate &delegate, uint8_t eventId)
{
	unbind(delegate, eventId);
	EventListenerItem item;
	item.delegate = delegate;
	item.eventId = eventId;
	m_listenerList.add(item);
}

void EventObject::unbind(const EventDelegate &delegate, uint8_t eventId)
{
	uint16_t i;
	for ( i = 0 ;i < m_listenerList.count(); i ++) {
		EventListenerItem item = m_listenerList.item(i);
		if ( item.delegate == delegate && (item.eventId == eventId || eventId == 0) ) {
			m_listenerList.remove(i);
		}
	}
}


void EventObject::raiseEvent(uint8_t eventId)
{
	uint16_t i;
	for ( i = 0 ;i < m_listenerList.count(); i ++) {
		EventListenerItem item = m_listenerList.item(i);
		if ( (item.eventId == eventId || item.eventId == 0) && item.delegate ) {
			if ( item.delegate(eventId) ) {
				break;
			}
		}
	}
}

*/
