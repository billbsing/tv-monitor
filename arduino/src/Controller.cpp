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


/* Page Design
 * 
 *
 * 
 * 01234567890123456
 * UserSelectPage:
 * User [0]
 * 0:Back 1:Admin 2:UserA 3:UserB
 * 
 * UserPasswordPage:
 * Password [....]
 * <left>:Back <up>:+ve <down>:-ve <right>:Next
 * 
 * UserStatusPage:
 * Used:02.23
 * 1236h 77m  12h 2m
 * 
 * AdminHomePage:
 * Select [0]
 * 0:Back 1:Edit Users 2:Password 3:Quota Amount 4:Quota Type 5:Start Time 6:End Time
 * 
 * AdminUserSelectPage
 * User [0]
 * 0:Back 1:UserA 2:UserB
 * 
 * AdminUserPage:
 * Select [0]
 * 0:Back 1:View 2:Password 3:Name 4:Daily Value 5:Weekly Value 6:Monthly Value 6:Delete
 * 
 * AdminUserViewPage:
 * Td:08:23 Wk:12 Mn:25
 * <left>:Back
 *
 * AdminUserPasswordPage:
 * User Password: [00000]
 * <left>:Back
 * 
 * AdminUserNamePage:
 * User Name: [........]
 * <left>:Back
 * 
 * AdminUserValuePage:
 * Daily : 0222
 * <left>:Back
 * 
 * AdminUserDeletPage:
 * Delete user xxxxx?
 * <left>:Back <enter>confirm
 * 
 * 
 * AdminPasswordPage:
 * Admin Password [....]
 * <left>:Back
 * 
 * AdminQuotaPage:
 * Quota Mins: [ 1230]
 * <left>:Back
 * 
 * AdminQuotaTypePage:
 * Quota Type: [0]
 * 0:Back 1:Daily 2:Weekly 3:Monthly
 * 
 * AdminStartTimePage:
 * Start Time: [00:00]
 * <left>:Back
 * 
 * AdminEndTimePage:
 * End Time: [00:00]
 * <left>:Back
 * 
 * 
 * 
 * 
 * 
 */


#include "TVController.h"
#include "Controller.h"
#include "Page.h"
#include "HomePage.h"
#include "StartPage.h"
#include "UserStatusPage.h"

/*
#include "UserPasswordPage.h"
#include "UserSelectPage.h"
#include "MenuPage.h"
#include "EditPasswordPage.h"
*/

const static PROGMEM uint8_t KeyDeviceMap[] = { 
						KEY_DEVICE_UP, VIRTUAL_KEY_UP,
						KEY_DEVICE_DOWN, VIRTUAL_KEY_DOWN,
						KEY_DEVICE_LEFT, VIRTUAL_KEY_LEFT,
						KEY_DEVICE_RIGHT, VIRTUAL_KEY_RIGHT,
						KEY_DEVICE_ENTER, VIRTUAL_KEY_ENTER
};

const static PROGMEM uint8_t IRDeviceMap[] = { 
						IR_TV_KEY_UP, VIRTUAL_KEY_UP,
						IR_TV_KEY_DOWN, VIRTUAL_KEY_DOWN,
						IR_TV_KEY_LEFT, VIRTUAL_KEY_LEFT,
						IR_TV_KEY_RIGHT, VIRTUAL_KEY_RIGHT,
						IR_TV_KEY_ENTER, VIRTUAL_KEY_ENTER,
						IR_TV_KEY_0, '0',
						IR_TV_KEY_1, '1',
						IR_TV_KEY_2, '2',
						IR_TV_KEY_3, '3',
						IR_TV_KEY_4, '4',
						IR_TV_KEY_5, '5',
						IR_TV_KEY_6, '6',
						IR_TV_KEY_7, '7',
						IR_TV_KEY_8, '8',
						IR_TV_KEY_9, '9',
						
								};

								
const static PROGMEM uint8_t IRDeviceXBMCMap[] = { 
						IR_BD_KEY_UP, KEY_UP_ARROW ,				// Up arrow
						IR_BD_KEY_DOWN, KEY_DOWN_ARROW ,			// Down arrow
						IR_BD_KEY_LEFT, KEY_LEFT_ARROW ,			// left arrow
						IR_BD_KEY_RIGHT, KEY_RIGHT_ARROW ,			// right arrow
						IR_BD_KEY_ENTER, KEY_RETURN ,				// middle cursor button
						IR_BD_KEY_RETURN, KEY_ESC ,					// 'Return Key'
						IR_BD_KEY_MENU, 'c' ,						// menu button
						
						IR_BD_KEY_PAUSE, ' ' ,						// pause ||
						IR_BD_KEY_PLAY, 'p' ,		    			// play >
						IR_BD_KEY_STOP, 'x' ,						// stop o
						IR_BD_KEY_FAST_FORWARD, 'f',				// fwd    >>
						IR_BD_KEY_FAST_BACK, 'r' ,					// prev   <<
						IR_BD_KEY_MOVE_BEGIN, KEY_PAGE_UP ,			// big forward  >>|
						IR_BD_KEY_MOVE_END, KEY_PAGE_DOWN ,			// big rev |<<
						IR_BD_KEY_RED, 'c' ,						// Red key
						IR_BD_KEY_GREEN, 'w' ,						// Green key
						IR_BD_KEY_YELLOW, 'q' ,						// Yellow key
						IR_BD_KEY_BLUE, KEY_TAB ,					// Blue key
						IR_BD_KEY_POWER, 's' ,						// power off key
						IR_BD_KEY_HELP, 'i' ,						// Info key next to power 
						
						IR_BD_KEY_0, '0' ,							// key 0
						IR_BD_KEY_1, '1' ,							// key 1
						IR_BD_KEY_2, '2' ,							// key 2
						IR_BD_KEY_3, '3' ,							// key 3
						IR_BD_KEY_4, '4' ,							// key 4
						IR_BD_KEY_5, '5' ,							// key 5
						IR_BD_KEY_6, '6' ,							// key 6
						IR_BD_KEY_7, '7' ,							// key 7
						IR_BD_KEY_8, '8' ,							// key 8
						IR_BD_KEY_9, '9' ,							// key 9

					//	{ IR_BD_KEY_UP_TOOLS, 0 },					// tools button
					//	{ 0x0082B474, KEY_ESC },					// internal menu button
					};

	
/*
 * Format of Page Load Sequence...
 * From PageId, 			Page Event Id,		-> Load Page Id
 * 
 * 
 */

const static PROGMEM uint8_t PageLoadSequence[] = {
//		Current PageId sending the event			Event being sent by the page							New page to load
	
		// Home page has requested a user login
		Controller::HomePageId, 					HomePage::RequestUserAccessEvent, 						Controller::UserUserSelectPageId,

		// Home page has requested a power on ir event
		Controller::HomePageId, 					HomePage::RequestPowerOnEvent, 							Controller::UserStatusPageId,

		// User Status page has closed
		Controller::UserStatusPageId,				UserStatusPage::ClosePageEvent,							Controller::HomePageId,

/*
		// User has cancelled user selection page
		Controller::UserUserSelectPageId, 			UserSelectPage::ClosePageEvent, 						Controller::HomePageId,
		// User has been selected to login
		Controller::UserUserSelectPageId,	 		UserSelectPage::ClosePageWithSuccessEvent, 				Controller::UserPasswordPageId,
		// Password cancelled
		Controller::UserPasswordPageId,				UserPasswordPage::ClosePageEvent,						Controller::UserUserSelectPageId,
		// Password successfull for a user
		Controller::UserPasswordPageId,				UserPasswordPage::ClosePageWithUserEvent,				Controller::UserStatusPageId,
		// Password successfull for admin
		Controller::UserPasswordPageId,				UserPasswordPage::ClosePageWithAdminEvent,				Controller::AdminHomePageId,
		
		
		// Admin home page has closed
		Controller::AdminHomePageId,				MenuPage::ClosePageEvent,								Controller::HomePageId,
		// Admin home page closed with menu '1' presesed, Edit Users
		Controller::AdminHomePageId,				MenuPage::ClosePageWithMenu1Event,						Controller::AdminUserSelectPageId,
		
		// Admin Select user page closed
		Controller::AdminUserSelectPageId,			UserSelectPage::ClosePageEvent,							Controller::AdminHomePageId,
		// Admin select user closed with a selected user
		Controller::AdminUserSelectPageId,			UserSelectPage::ClosePageWithSuccessEvent,				Controller::AdminEditUserPageId,
		
		// Admin Edit user closed with menu: View User
		Controller::AdminEditUserPageId,			MenuPage::ClosePageWithMenu1Event,						Controller::AdminEditUserPageId,
		// Admin Edit user closed with menu: Change user password
		Controller::AdminEditUserPageId,			MenuPage::ClosePageWithMenu2Event,						Controller::AdimnEditUserPasswordPageId,
		
		// Change user password success, return back to user edit menu
		Controller::AdimnEditUserPasswordPageId, 	EditPasswordPage::ClosePageWithSuccessEvent,			Controller::AdminEditUserPageId,
		// Change user password cancelled, return back to user edit menu
		Controller::AdimnEditUserPasswordPageId, 	EditPasswordPage::ClosePageEvent,						Controller::AdminEditUserPageId,
		
		// Admin Edit user closed with menu: Change user name
		Controller::AdminEditUserPageId,			MenuPage::ClosePageWithMenu3Event,						Controller::AdminEditUserPageId,
		// Admin Edit user closed with menu: Change user daily amount
		Controller::AdminEditUserPageId,			MenuPage::ClosePageWithMenu4Event,						Controller::AdminEditUserPageId,
		// Admin Edit user closed with menu: Change user weekly amount
		Controller::AdminEditUserPageId,			MenuPage::ClosePageWithMenu5Event,						Controller::AdminEditUserPageId,
		// Admin Edit user closed with menu: Change user monthly amount
		Controller::AdminEditUserPageId,			MenuPage::ClosePageWithMenu6Event,						Controller::AdminEditUserPageId,
		
		
		// Admin home page closed with menu: Change password
		Controller::AdminHomePageId,				MenuPage::ClosePageWithMenu2Event,						Controller::AdimnEditPasswordPageId,
		// Change admin password success, return back to user admin menu
		Controller::AdimnEditPasswordPageId, 		EditPasswordPage::ClosePageWithSuccessEvent,			Controller::AdminHomePageId,
		// Change amin password cancelled, return back to user admin menu
		Controller::AdimnEditPasswordPageId, 		EditPasswordPage::ClosePageEvent,						Controller::AdminHomePageId,



		// Admin home page closed with menu: Set Quota Amount
		Controller::AdminHomePageId,				MenuPage::ClosePageWithMenu3Event,						Controller::AdminHomePageId,
		// Admin home page closed with menu: Set Quota Type
		Controller::AdminHomePageId,				MenuPage::ClosePageWithMenu4Event,						Controller::AdminHomePageId,
		// Admin home page closed with menu: Set Access Start time
		Controller::AdminHomePageId,				MenuPage::ClosePageWithMenu5Event,						Controller::AdminHomePageId,
		// Admin home page closed with menu: Set Access End time
		Controller::AdminHomePageId,				MenuPage::ClosePageWithMenu6Event,						Controller::AdminHomePageId,
*/
};
			
bool isTimeHMValid(const TimeHM &timeHM)
{
	return (timeHM.hour >=0 && timeHM.hour <= 23 && timeHM.minute >=0 && timeHM.minute <=59);
}
bool isAccessTimeValid(const AccessTime &accessTime)
{
	return isTimeHMValid(accessTime.start) && isTimeHMValid(accessTime.end);
}

bool isDayMonthEmpty(const DayMonth &value)
{
	return (value.day == 0) || (value.month == 0);
}

void formatSeconds(char *buffer, uint32_t total_seconds, bool is_hour_visible, bool is_second_visible)
{
	unsigned int hours = total_seconds / 3600;
	unsigned int mins = (total_seconds - (hours * 3600))/ 60;
	unsigned int secs = total_seconds - ((hours * 3600 ) + (mins * 60));

	char text_buffer[12];
	buffer[0] = 0;
	if ( is_hour_visible) {
		sprintf(text_buffer, "%d:", hours);
		strcat(buffer, text_buffer);
	}
	sprintf(text_buffer, "%02d", mins);
	strcat(buffer, text_buffer);
	if ( is_second_visible ) {
		sprintf(text_buffer, ":%02d", secs);
		strcat(buffer, text_buffer);
	}
}

#define MINS_PER_DAY		(60 * 24)
#define MINS_PER_HOUR		60

void formatMinutes(char *buffer, uint32_t total_minutes, bool is_day_visible)
{
	
	unsigned int days = 0;
	if ( is_day_visible ) {
		days = ( total_minutes / MINS_PER_DAY );
	}
	unsigned int hours = floor( (total_minutes - (days * MINS_PER_DAY) ) / MINS_PER_HOUR);
	unsigned int mins = total_minutes - ( (days * MINS_PER_DAY) + (hours * MINS_PER_HOUR));
	

	char text_buffer[20];
	buffer[0] = 0;
	if ( days > 0 ) {
		sprintf(text_buffer, "%dd", days);
		strcat(buffer, text_buffer);
	}
	if ( days >0 || hours > 0 ) {
		sprintf(text_buffer, "%dh", hours);
		strcat(buffer, text_buffer);
	}
	sprintf(text_buffer, "%dm", mins);
	strcat(buffer, text_buffer);
}


Controller::Controller()
{
	keyDevice.bind(this, KeyDevice::KeyDownEvent);
	irDevice.bind(this, IRDevice::IRReadEvent);
	server.bind(this, Server::OnReceiveCommand);

	m_input.bind(this, LCDInput::EndOfInputEvent);
	m_input.bind(this, LCDInput::StartOfInputEvent);
	m_input.bind(this, LCDInput::KeyEnterEvent);

	m_time = 0;
	m_schedulePageId = NoPageId;
	
	memset(&m_data, 0, sizeof(DataType));
	m_userIndex = 0xFF;
	m_page = NULL;
	m_lastTimeUpdateMins = 0;
	m_currentMinute = 0;
	m_saveEPROMTimeout = 0;
	m_isMonitoring = true;
	
	pinMode(BACK_LIGHT_PIN, OUTPUT);
	analogWrite(BACK_LIGHT_PIN, 0x40);
	
}

Controller::~Controller()
{
	keyDevice.unbind(this);
	irDevice.unbind(this);
	server.unbind(this);
	m_input.unbind(this);
	delete m_page;
	
}

void Controller::begin()
{
	_loadPage(StartPageId);
	_loadFromEEPROM();
}

bool Controller::onEvent(EventObject *sender, uint8_t eventId)
{
	if ( sender == &keyDevice && eventId == KeyDevice::KeyDownEvent ) {
		_onKeyCommandPress(((KeyDevice *) sender)->value());
	}
	if ( sender == &irDevice && eventId == IRDevice::IRReadEvent ) {
		_onIRRead(((IRDevice *) sender)->value(), ((IRDevice *) sender)->rawValue());
	}
	if ( sender == &server && eventId == Server::OnReceiveCommand ) {
		if ( server.command() > 0 ) {
			_processServerCommand(server.command());
		}
	}
	
	if ( sender == &m_input && eventId == LCDInput::StartOfInputEvent ) {
		if ( m_page) {
			m_page->onKeyPress(VIRTUAL_KEY_ESCAPE);
		}
		return false;
	}
	if ( sender == &m_input && (eventId == LCDInput::EndOfInputEvent || eventId == LCDInput::KeyEnterEvent) ) {
		if ( m_page) {
			m_page->onKeyPress(VIRTUAL_KEY_ENTER);
		}
		return true;
	}
	
	uint8_t i;
	if ( sender == m_page ) {
		for ( i = 0; i < sizeof(PageLoadSequence); i += 3 ) {
			if ( _pageId() == pgm_read_byte(&PageLoadSequence[i]) && eventId == pgm_read_byte(&PageLoadSequence[i + 1]) ) {
				if ( m_page ) {
					_onPageClose(_pageId(), eventId);
				}
				_scheduleLoadPage((PageIdType) pgm_read_byte(&PageLoadSequence[i + 2]));
			}
		}
	}
	
	// allow other objects to receive these events
	return false;
}


void Controller::loop()
{
	if ( m_time != now() ) {
		m_time = now();
		_secondTick();
	}
	if ( m_currentMinute != minute() ) {
		m_currentMinute = minute();
		_minuteTick();
	}
	
	if ( m_schedulePageId != NoPageId ) {
		PageIdType lastPageId  = _pageId();
		if ( !_loadPage(m_schedulePageId) ) {
			// if failed to load the page then revert back to the prev page.
			_loadPage(lastPageId);
		}
		m_schedulePageId = NoPageId;
	}
	bool forceShow = m_helpText.show();
	m_input.show(forceShow);
	m_keyboardSender.process();
}


void Controller::setHelpText(String buffer)
{
	m_helpText.begin(buffer, 0, 1, LCD_WIDTH, LCD_ROTATE_TEXT_SPEED);
}

void Controller::clearHelpText()
{
	m_helpText.clearDisplay();
	m_helpText.clear();
}

void Controller::setInputForMenu(uint8_t col, String charset)
{
	m_input.begin("0", col, 0, 1);
	m_input.setOpenCloseText(getStaticString(SST_INPUT_ENCLOSE));
	m_input.setInputCharset(charset);
}

void Controller::setInputForMenu(uint8_t col, uint8_t maxIndex)
{
	m_input.begin("0", col, 0, 1);
	m_input.setOpenCloseText(getStaticString(SST_INPUT_ENCLOSE));
	m_input.setInputRange(0, maxIndex);
}


void Controller::setInputForPassword(uint8_t col,char *startValue)
{
	m_input.begin(startValue, col, 0, 4, ' ');
	m_input.setOpenCloseText(getStaticString(SST_INPUT_ENCLOSE));
	m_input.setInputRange(0, 9);
//	m_input.setPasswordChar('*');
}

void Controller::setInputForText(uint8_t col, char* startValue, uint8_t length)
{
	m_input.begin(startValue, col, 0, length, ' ');
	m_input.setOpenCloseText(getStaticString(SST_INPUT_ENCLOSE));
	m_input.setInputCharset(getStaticString(SST_INPUT_TEXT_CHARSET));
}

int Controller::inputAsInt()
{
	return m_input.asInt();
}
String Controller::inputAsString()
{
	return m_input.asString();
}

UserType* Controller::getUser(uint8_t index)
{
	if ( index == USER_INDEX_NONE ) {
		index = m_userIndex;
	}
	if ( index >=0 && index <= MAX_USER_COUNT ) {
		return &m_data.users[index];
	}
	return NULL;
}

void Controller::addUsedMinutes(uint8_t userId, uint16_t usedMinutes)
{
	UserType *user = getUser(userId);
	if ( user ) {
		user->usedMinutes.day += usedMinutes;
		m_saveEPROMTimeout = 4;
	}
}
void Controller::logViewStart(uint8_t userId)
{
	uint8_t index;
	UserType *user = getUser(userId);
	if ( user ) {
		index = user->logViewIndex;
		user->logViews[index].startTime = now();
		user->logViews[index].endTime = now();
		m_saveEPROMTimeout = 4;
	}
	
}
void Controller::logViewStop(uint8_t userId)
{
	uint8_t index;
	UserType *user = getUser(userId);
	if ( user ) {
		index = user->logViewIndex;
		user->logViews[index].endTime = now();
		index ++;
		if ( index >= MAX_LOG_VIEW_COUNT ) {
			index = 0;
		}
		user->logViewIndex = index;
		m_saveEPROMTimeout = 4;
	}
}


DayMonth Controller::getLastDate()
{
	return m_data.lastDate;
}

uint8_t Controller::getLastTimeUpdateMins()
{
	return m_lastTimeUpdateMins;
}

bool Controller::isMonitoring()
{
	return m_isMonitoring;
}

void Controller::setMonitoring(bool value)
{
	m_isMonitoring = value;
}


bool Controller::_loadPage(Controller::PageIdType pageId)
{
	bool result = false;
	
	if ( m_page ) {
		m_page->unbind(this);
		m_helpText.clear();
		m_input.clear();
		delete m_page;
		m_page = NULL;
	}

	switch(pageId) {
		case StartPageId:
			m_page = new StartPage(StartPageId);
			break;
		case HomePageId:
			m_page = new HomePage(HomePageId);			
			break;
		case UserStatusPageId:
			m_page = new UserStatusPage(UserStatusPageId, m_userIndex);			
			break;
/*
 		case UserUserSelectPageId:
			m_page = new UserSelectPage(UserUserSelectPageId, true);
			break;
		case UserPasswordPageId:
			m_page = new UserPasswordPage(UserPasswordPageId, getUser());
			break;
		case AdminHomePageId:
			m_page = new MenuPage(AdminHomePageId, SST_ADMIN_HOME_HELP_TEXT, 6);
			break;
		case AdminUserSelectPageId:
			m_page = new UserSelectPage(AdminUserSelectPageId, false);
			break;
		case AdminEditUserPageId:
			m_page = new MenuPage(AdminEditUserPageId, SST_ADMIN_USER_HELP_TEXT, 6);
			break;
		case AdimnEditUserPasswordPageId:
			m_page = new EditPasswordPage(AdimnEditUserPasswordPageId, m_adminUser);
			break;
		case AdimnEditPasswordPageId:
			m_page = new EditPasswordPage(AdimnEditUserPasswordPageId, getUser());
			break;
*/
	}

	if ( m_page ) {
		m_page->bind(this);
		lcdDevice.clear();
		result = m_page->begin();
	}

	return result;
}

void Controller::_onPageClose(Controller::PageIdType pageId, uint8_t eventId)
{

	switch (pageId) {
/*	
		case UserUserSelectPageId:
			m_userIndex = ((UserSelectPage *) m_page)->userIndex();
		break;
		case AdminUserSelectPageId:
			m_adminUser = getUser(((UserSelectPage *) m_page)->userIndex());
		break;
*/
		case HomePageId:
			if ( eventId == HomePage::RequestPowerOnEvent ) {
				m_userIndex = USER_INDEX_ADMIN;
			}
		break;
	}
}


void Controller::_processServerCommand(uint8_t command)
{
	DateTimeType *dateTimeValue = NULL;
	uint8_t key;
	UserType *user;
	
	switch( command ) {
		case COMMAND_SET_DATE_TIME:
			dateTimeValue = server.asDateTime();
			if ( dateTimeValue ) {
				setTime( (int) dateTimeValue->hour, (int) dateTimeValue->minute, (int) dateTimeValue->second, (int) dateTimeValue->day, (int) dateTimeValue->month, (int) dateTimeValue->year);
				if ( isDayMonthEmpty(m_data.lastDate) ) {
					m_data.lastDate.day = day();
					m_data.lastDate.month = month();
					_saveToEEPROM();
				}
				m_lastTimeUpdateMins = 0;
				m_currentMinute = minute();
			}
			if ( _pageId() == StartPageId ) {
				_scheduleLoadPage(HomePageId);
			}
			break;
		case COMMAND_SET_USER:
			user = (UserType *) server.data();
			if ( user->index >=0 && user->index <= MAX_USER_COUNT ) {
				memcpy(&m_data.users[user->index], user, sizeof(UserType));
			}
			break;
		case COMMAND_TEST_KEY:
			key = (uint8_t) *server.data();
			_onIRRead(key , 0);
			break;
		case COMMAND_GET_USER:
			uint8_t userId = (uint8_t) *server.data();
			user = getUser(userId);
			server.sendCommand(COMMAND_SET_USER, (uint8_t *) user, sizeof(UserType));
			break;
	}
}

void Controller::_secondTick()
{
	if ( m_page ) {
		m_page->onSecondTick();
	}
	if ( m_saveEPROMTimeout > 0 ) {
		m_saveEPROMTimeout --;
		if ( m_saveEPROMTimeout == 0 ) {
			_saveToEEPROM();
		}
	}
}

void Controller::_minuteTick()
{
	m_lastTimeUpdateMins ++;
	if ( _pageId() != StartPageId ) {
		_processUserTime();
	}
	if ( m_page ) {
		m_page->onMinuteTick();
	}
}

void Controller::_onKeyCommandPress(uint8_t key)
{
	unsigned char value = _findKeyMapValue(KeyDeviceMap, sizeof(KeyDeviceMap), key);
	if ( value > 0 && m_page) {
		m_input.processKey(value);
		m_page->onKeyPress(value);
	}
}


void Controller::_onIRRead(uint8_t key, uint32_t rawValue)
{
	if ( m_page ) {
		unsigned char value;
		value = _findKeyMapValue(IRDeviceMap, sizeof(IRDeviceMap), key);
		if ( value > 0 ) {
			m_input.processKey(value);		
			m_page->onKeyPress(value);
		}
		else {
			value = _findKeyMapValue(IRDeviceXBMCMap, sizeof(IRDeviceXBMCMap), key);
			if ( value > 0 ) {
				m_keyboardSender.add(value);
			}
		}
		
		m_page->onIRPress(key, rawValue);
	}
#ifdef DEBUG_IR_VALUES
	_debugIRValue(key, rawValue);
#endif
}

#ifdef DEBUG_IR_VALUES

void Controller::_debugIRValue(uint8_t key, uint32_t rawValue, bool isDebug)
{
	char text[12];
	sprintf(text, "%02d - %08lX", key, rawValue);
	server.sendDebug(text);
	
	if ( isDebug ) {
		decode_results *results = irDevice.results();
		uint8_t buffer[(results->rawlen  + 4) * 2];
		uint16_t i;
		uint8_t *ptr = buffer;
		ptr[0] = results->decode_type >> 8;
		ptr[1] = results->decode_type & 0xFF;
		ptr += 2;
		ptr[0] = results->bits >> 8;
		ptr[1] = results->bits & 0xFF;
		ptr += 2;
		for ( i = 0; i < results->rawlen; i ++ ) {
			ptr[0] = (results->rawbuf[i] >> 8) & 0xFF;
			ptr[1] = results->rawbuf[i] & 0xFF;
			ptr += 2;
		}
		server.sendDebug(buffer, results->rawlen * 2);
	}
}
#endif

unsigned char Controller::_findKeyMapValue(const PROGMEM uint8_t *map, uint16_t length, uint8_t key)
{
	uint16_t i;
	for ( i = 0; i < length; i += 2 ) {
		uint16_t value = pgm_read_word(&map[i]);
		if ( (value & 0xFF ) == key ) {
			return (value >>8) & 0xFF;
		}
	}
	return 0;
}

void Controller::_scheduleLoadPage(Controller::PageIdType value)
{
	m_schedulePageId = value;
}

Controller::PageIdType Controller::_pageId()
{
	if ( m_page ) {
		return (PageIdType) m_page->id();
	}
	return NoPageId;
}


void Controller::_loadFromEEPROM()
{
	int i;

	m_data.header = EEPROM.read(0);
	if ( m_data.header == EEPROM_HEADER_ID ) {
		unsigned char *ptr = (unsigned char *) &m_data;
		for ( i = 0; i < sizeof(DataType); i ++ ) {
			*ptr = EEPROM.read(i);
			ptr ++;
		}
	}
	else {
		memset(&m_data, 0, sizeof(DataType));
		strcpy(m_data.users[USER_INDEX_ADMIN].name, getStaticString(SST_ADMIN_NAME));
		strcpy(m_data.users[USER_INDEX_USER_1].name, getStaticString(SST_USER_1_NAME));
		m_data.quota.type = QUOTA_TYPE_NONE;
		m_data.quota.maxMinutes = 0;
		m_data.header = EEPROM_HEADER_ID;
	}
	for ( i = 0; i < MAX_USER_COUNT; i ++ ) {
		m_data.users[i].index = i;
	}
	
//	lcdDevice.print(m_data.users[0].usedMinutes.day);
}
void Controller::_saveToEEPROM()
{
	int i;
	lcdDevice.setCursor(LCD_WIDTH - 6, 0);
	lcdDevice.print('*');
	m_data.header = EEPROM_HEADER_ID;
	unsigned char *ptr = (unsigned char *) &m_data;
	for ( i = 0; i < sizeof(DataType); i ++ ) {
		EEPROM.write(i, *ptr);
		ptr ++;
	}
	lcdDevice.setCursor(LCD_WIDTH - 6, 0);
	lcdDevice.print(' ');	
}


void Controller::_processUserTime()
{
	uint8_t i;
	UserType *userData;
	// check for day change , week change and month change
	

	if ( m_data.lastDate.day != day() ) {
		for ( i = 0; i < MAX_USER_COUNT; i ++ ) {
			UserType *userData = getUser(i);
			userData->usedMinutes.week += userData->usedMinutes.day;
			userData->usedMinutes.day = 0;
			// test for new week if day is a Monday
			if ( weekday() == 1 ) {
				userData->usedMinutes.month += userData->usedMinutes.week;
				userData->usedMinutes.week = 0;
			}
			if ( m_data.lastDate.month != month() ) {
				userData->usedMinutes.month = 0;
			}
		}
		m_data.lastDate.day = day();
		m_data.lastDate.month = month();
		_saveToEEPROM();
	}
}



