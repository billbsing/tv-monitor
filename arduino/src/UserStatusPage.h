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


#ifndef USERSTATUSPAGE_H
#define USERSTATUSPAGE_H

class Page;

class UserStatusPage : public Page
{

public:
	
	typedef enum {
		ClosePageEvent = 1
	} EventType;
	
    UserStatusPage(uint8_t pageId, uint8_t userIndex);
	
	virtual bool begin();
	virtual void onSecondTick();

	virtual void onKeyPress(unsigned char key);
	virtual void onIRPress(uint8_t key, uint32_t rawValue);
	
	
protected:
	
	void _logUserDataStart(UserType *user);
	void _logUserDataStop(UserType *user);
	void _showUserStats();
	void _showAdminStats();

	
	
	uint32_t		m_minuteCountdown;
	uint32_t		m_usedMinutes;
	int8_t			m_startDelay;
	uint8_t			m_userIndex;
	bool			m_isAdmin;
};

#endif // USERSTATUSPAGE_H
