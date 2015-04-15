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
#include "EditPasswordPage.h"

EditPasswordPage::EditPasswordPage(uint8_t pageId, UserType *user) : Page(pageId)
{
	m_user = user;
}

bool EditPasswordPage::begin()
{
	if ( m_user ) {
		String buffer = m_user->name;
		buffer += ":";
		lcdDevice.print(buffer);
		char startValue[5];
		sprintf(startValue, "%04d", m_user->password);
		controller.setInputForPassword(buffer.length() + 1, startValue);
		controller.setHelpText(getStaticString(SST_CHANGE_PASSWORD_HELP));
		return true;
	}
	return false;
}

void EditPasswordPage::onKeyPress(unsigned char key)
{

	uint8_t value;
	switch (key) {
		case VIRTUAL_KEY_ENTER:
			value = controller.inputAsInt();
			if ( m_user ) {
				m_user->password = value;
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

