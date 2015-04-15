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
#include "EditNamePage.h"

EditNamePage::EditNamePage(uint8_t pageId, UserType *user) : Page(pageId)
{
	m_user = user;
}

bool EditNamePage::begin()
{
	if ( m_user ) {
		String buffer = getStaticString(SST_CHANGE_NAME) ;
		buffer += ":";
		lcdDevice.print(buffer);
		controller.setInputForText(buffer.length() + 1, m_user->name, MAX_USER_NAME_LENGTH);
		controller.setHelpText(getStaticString(SST_CHANGE_NAME_HELP));
		return true;
	}
	return false;
}

void EditNamePage::onKeyPress(unsigned char key)
{

	uint8_t value;
	switch (key) {
		case VIRTUAL_KEY_ENTER:
			if ( m_user ) {
				String newName = controller.inputAsString();
				newName.toCharArray(m_user->name, newName.length()  +1);
				raiseEvent(ClosePageWithSuccessEvent);
			}
			else {
				raiseEvent(ClosePageEvent);
			}
			break;
		case VIRTUAL_KEY_ESCAPE:
			raiseEvent(ClosePageEvent);
			break;
	}
	
}

