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


#ifndef CONTROLLER_H
#define CONTROLLER_H


class EventObject;
class LCDInput;
class LCDRotateText;
class Timer;
class Page;
class KeyboardSender;




void formatSeconds(char *buffer, uint32_t total_seconds, bool is_hour_visible, bool is_second_visible);
void formatMinutes(char *buffer, uint32_t total_minutes, bool is_day_visible);


typedef struct {
	uint8_t 		header;
	UserType 		users[MAX_USER_COUNT];
	QuotaDataType 	quota;
	DayMonth		lastDate;
} DataType;

/*
 * 
 * EPROM size
 * 
 * header			 			1 byte
 * UserType[MAX_USER_COUNT]		87 * 8 bytes
 * QuotaDataType				3 bytes
 * DayMonth						2 bytes
 * 
 * Total						702 bytes
 * 
 */




class Controller : public EventObject
{
	public:	
		
		
		typedef enum {
			NoPageId = 0,					// No page shown
			StartPageId,					// Start page
			HomePageId,						// Home page 
			UserUserSelectPageId,			// Select a user to login
			UserPasswordPageId,				// Enter the users password
			UserStatusPageId,				// Show the user status when watching
			AdminHomePageId,				// Admin home menu page
			AdminUserSelectPageId,			// Admin select the user to edit
			AdminEditUserPageId,			// Admin show user edit menu
			AdimnEditUserPasswordPageId,	// Admin Edit user password
			AdimnEditPasswordPageId,		// Admin Edit password
		} PageIdType;
		
		Controller();
		virtual ~Controller();
		
		
		void begin();
		bool onEvent(EventObject *sender, uint8_t eventId);
		void loop();
		
		void setHelpText(String buffer);
		void clearHelpText();
		void setInputForMenu(uint8_t col, String charset);
		void setInputForMenu(uint8_t col, uint8_t maxIndex);
		void setInputForPassword(uint8_t col, char *startValue = NULL);
		void setInputForText(uint8_t col, char *startValue = NULL, uint8_t length = 0);
		int inputAsInt();
		String inputAsString();
		void addUsedMinutes(uint8_t userId, uint16_t usedMinutes);
		void logViewStart(uint8_t userId);
		void logViewStop(uint8_t userId);
		DayMonth getLastDate();
		uint8_t getLastTimeUpdateMins();
		
		UserType* getUser(uint8_t index = USER_INDEX_NONE);
		bool isMonitoring();
		void setMonitoring(bool value);
 		
	protected:
		bool _loadPage(PageIdType pageId);
		void _onPageClose(PageIdType pageId, uint8_t eventId);
		void _processServerCommand(uint8_t command);
		void _secondTick();
		void _minuteTick();
		void _onKeyCommandPress(uint8_t key);
		void _onIRRead(uint8_t key, uint32_t rawValue);
#ifdef DEBUG_IR_VALUES		
		void _debugIRValue(uint8_t key, uint32_t rawValue, bool isDebug = false);
#endif
		unsigned char _findKeyMapValue(const PROGMEM uint8_t *map, uint16_t length, uint8_t key);
		void _scheduleLoadPage(PageIdType value);
		PageIdType _pageId();
		void _loadFromEEPROM();
		void _saveToEEPROM();
		void _processUserTime();

		
		atime_t			m_time;
		Page*			m_page;
		PageIdType		m_schedulePageId;
		uint8_t			m_userIndex;
		UserType*		m_adminUser;
		LCDRotateText	m_helpText;
		LCDInput		m_input;
		DataType		m_data;
		KeyboardSender	m_keyboardSender;
		uint8_t 		m_lastTimeUpdateMins;
		uint8_t 		m_currentMinute;
		uint8_t 		m_saveEPROMTimeout;
		bool			m_isMonitoring;
		
	private:
	
};

#endif /* CONTROLLER_H */ 
