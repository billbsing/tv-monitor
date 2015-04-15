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
#include "UserSelectPage.h"

UserSelectPage::UserSelectPage(uint8_t pageId, bool isAdminVisible) : Page(pageId)
{
	m_isAdminVisible = isAdminVisible;
}

bool UserSelectPage::begin()
{
	uint8_t i;
	lcdDevice.print(getStaticString(SST_USER));
	String buffer = getStaticString(SST_BACK);
	String charset = "0";
	for ( i = 0; i < MAX_USER_COUNT; i ++ ) {
		if ( m_isAdminVisible == false && i == USER_INDEX_ADMIN ) {
			continue;
		}
		if ( strlen(controller.getUser(i)->name )  > 0 ) {
			buffer += " ";
			buffer += (i + 1);
			buffer += ":";
			buffer += controller.getUser(i)->name;
			charset += (i + 1);
		}
	}
	controller.setInputForMenu(6, charset);
	controller.setHelpText(buffer);	
	m_userIndex = USER_INDEX_NONE;
	return true;
}

void UserSelectPage::onKeyPress(unsigned char key)
{
    Page::onKeyPress(key);
	uint8_t value;
	switch (key) {
		case VIRTUAL_KEY_ENTER:
			value = controller.inputAsInt();
			if ( value == 0 ) {
				raiseEvent(ClosePageEvent);
			}
			m_userIndex = value - 1;
			raiseEvent(ClosePageWithSuccessEvent);
			break;
		case VIRTUAL_KEY_ESCAPE:
			raiseEvent(ClosePageEvent);
			break;
	}
}

uint8_t UserSelectPage::userIndex()
{
	return m_userIndex;
}



