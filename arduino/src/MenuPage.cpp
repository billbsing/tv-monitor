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
#include "Controller.h"
#include "MenuPage.h"

MenuPage::MenuPage(uint8_t pageId, uint8_t helpTextId, uint8_t maxMenuIndex) : Page(pageId)
{
	m_helpTextId = helpTextId;
	m_maxMenuIndex = maxMenuIndex;
}

bool MenuPage::begin()
{
	lcdDevice.print(getStaticString(SST_SELECT));
	controller.setHelpText(getStaticString(m_helpTextId));
	controller.setInputForMenu(6, m_maxMenuIndex);
	return true;
}

void MenuPage::onKeyPress(unsigned char key)
{
    Page::onKeyPress(key);
	uint8_t value;
	uint8_t i;
	switch (key) {
		case VIRTUAL_KEY_ENTER:
			value = controller.inputAsInt();
			raiseEvent(value + 1);
			break;
		case VIRTUAL_KEY_ESCAPE:
			raiseEvent(ClosePageEvent);
			break;
	}
}


