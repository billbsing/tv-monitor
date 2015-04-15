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


#ifndef MENUPAGE_H
#define MENUPAGE_H

class Page;

class MenuPage : public Page
{

public:
	typedef enum {
		ClosePageEvent = 1,
		ClosePageWithMenu1Event,
		ClosePageWithMenu2Event,
		ClosePageWithMenu3Event,
		ClosePageWithMenu4Event,
		ClosePageWithMenu5Event,
		ClosePageWithMenu6Event,
		ClosePageWithMenu7Event,
		ClosePageWithMenu8Event,
		ClosePageWithMenu9Event,
	} EventType;
		
    MenuPage(uint8_t id, uint8_t helpTextId = 0, uint8_t maxMenuIndex = 0);
	virtual bool begin();
	virtual void onKeyPress(unsigned char key);
protected:
	uint8_t 	m_helpTextId;
	uint8_t		m_maxMenuIndex;
};

#endif // MENUPAGE_H
