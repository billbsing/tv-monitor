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
#include "UserStatusPage.h"


bool isDayMonthToday(const DayMonth &date)
{
	return (date.day == day() && date.month == month());
}


UserStatusPage::UserStatusPage(uint8_t pageId, uint8_t userIndex) : Page(pageId)
{
	m_userIndex = userIndex;
	m_isAdmin = (m_userIndex == USER_INDEX_ADMIN);
}


bool UserStatusPage::begin()
{
	UserType *user = controller.getUser(m_userIndex);
	m_minuteCountdown = 60;
	m_usedMinutes = 0;

	if ( user ) {
		if ( controller.isMonitoring() ) {
			_logUserDataStart(user);
		}
		if ( ! m_isAdmin ) {
			lcdDevice.print(user->name);
		}
		if ( controller.isMonitoring() ) {
			controller.setHelpText(getStaticString(SST_TV_ON));
		}
		else {
			controller.setHelpText(getStaticString(SST_TV_ON_NO_MONITOR));
		}
		m_startDelay = 5;
		return true;
	}
	
	return false;
}

void UserStatusPage::onKeyPress(unsigned char key)
{
}

void UserStatusPage::onIRPress(uint8_t key, uint32_t rawValue)
{
	if ( key == IR_TV_KEY_POWER && m_startDelay == 0 ) {
		UserType *user = controller.getUser(m_userIndex);
		if ( user && controller.isMonitoring() ) {
			_logUserDataStop(user);
		}
		m_usedMinutes = 0;
		raiseEvent(ClosePageEvent);
	}
}


void UserStatusPage::onSecondTick()
{	
	m_minuteCountdown --;
	if ( m_minuteCountdown == 0 ) {
		m_usedMinutes ++;
		m_minuteCountdown = 60;
	}
	
	char buffer[20];
	// show the number of hours/minutes left	
	formatMinutes(buffer, m_usedMinutes, false);
	lcdDevice.setCursor(LCD_WIDTH - strlen(buffer), 0);
	lcdDevice.print(buffer);

	if ( m_startDelay > 0 ) {
		m_startDelay --;
		if ( m_startDelay == 0 ) {
			controller.clearHelpText();
		}
	}
	if ( m_startDelay == 0) {
		if ( m_isAdmin ) {
			_showAdminStats();
		}
		else {
			_showUserStats();
		}
	}
}



void UserStatusPage::_logUserDataStart(UserType *user)
{
	controller.logViewStart(user->index);
}

void UserStatusPage::_logUserDataStop(UserType *user)
{
	controller.addUsedMinutes(m_userIndex, m_usedMinutes + 1);
	if ( user ) {
		controller.logViewStop(user->index);
	}
}

void UserStatusPage::_showUserStats()
{
	/*
	uint32_t leftSeconds = (m_user->maxDayMinutes * 60) - m_usedSeconds;
	
	String buffer = "Left:";
	buffer += _formatSeconds(leftSeconds, true, false);
	lcdDevice.setCursor(0, 1);
	lcdDevice.print(buffer);
*/
	
}

void UserStatusPage::_showAdminStats()
{
	UserType *user = controller.getUser(m_userIndex);

	if ( user ) {
		uint32_t daySeconds = user->usedMinutes.day;
		uint32_t weekSeconds = user->usedMinutes.week + daySeconds;
		
		char buffer[20];
		formatMinutes(buffer, daySeconds + m_usedMinutes, false);
		lcdDevice.setCursor(0, 0);
		lcdDevice.print("Td:");
		lcdDevice.print(buffer);

		formatMinutes(buffer, weekSeconds + m_usedMinutes, false);
		lcdDevice.setCursor(0, 1);
		lcdDevice.print("Wk:");
		lcdDevice.print(buffer);
	}
}
