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
#include "StaticStringTable.h"


FLASH_RESOURCE_STRING(SST_STARTING_0,				"Starting...");
FLASH_RESOURCE_STRING(SST_TIME_FORMAT_1,			"%02d:%02d");
FLASH_RESOURCE_STRING(SST_TIME_DATE_FORMAT_2,		"%s  %02d %s %04d");
FLASH_RESOURCE_STRING(SST_USER_3,					"User:");
FLASH_RESOURCE_STRING(SST_BACK_4,					"0:Back ");
FLASH_RESOURCE_STRING(SST_LEFT_BACK_5,				"<left>: Back");
FLASH_RESOURCE_STRING(SST_WELCOME_6,				"Welcome ");
FLASH_RESOURCE_STRING(SST_INPUT_ENCLOSE_7,			"[]");
FLASH_RESOURCE_STRING(SST_ADMIN_NAME_8,				"Admin");
FLASH_RESOURCE_STRING(SST_USER_1_NAME_9,			"User1");
FLASH_RESOURCE_STRING(SST_ADMIN_HOME_HELP_TEXT_10,	"0:Back 1:Edit Users 2:Password 3:Quota Amount 4:Quota Type 5:Start Time 6:End Time");
FLASH_RESOURCE_STRING(SST_SELECT_11,				"Select:" );
FLASH_RESOURCE_STRING(SST_ADMIN_USER_HELP_TEXT_12,	"0:Back 1:View 2:Password 3:Name 4:Daily Value 5:Weekly Value 6:Monthly Value 6:Delete");
FLASH_RESOURCE_STRING(SST_CHANGE_PASSWORD_HELP_13,	"<left>: Back. Enter in new password");
FLASH_RESOURCE_STRING(SST_CHANGE_NAME_14,			"New Name:");
FLASH_RESOURCE_STRING(SST_CHANGE_NAME_HELP_15,		"<left>: Back. Change to a new name");
FLASH_RESOURCE_STRING(SST_INPUT_TEXT_CHARSET_16,	"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,-_");
FLASH_RESOURCE_STRING(SST_TV_ON_17,					"TV On");
FLASH_RESOURCE_STRING(SST_TV_OFF_18,				"TV Off");
FLASH_RESOURCE_STRING(SST_TV_ON_NO_MONITOR_19,		"TV On: Free Time");

/*
FLASH_RESOURCE_STRING(SST_HELP_TEXT_14,				"0:Back 1:Daily 2:Weekly 3:Monthly");
FLASH_RESOURCE_STRING(SST_ADMIN_PASSWORD_15,		"Admin Password:" );
FLASH_RESOURCE_STRING(SST_ADMIN_QUOTA_MINS_16,		"Quota Mins:");
FLASH_RESOURCE_STRING(SST_ADMIN_QUOTA_TYPE_17,		"Quota Type:");
FLASH_RESOURCE_STRING(SST_ADMIN_START_TIME_18,		"Start Time:");
FLASH_RESOURCE_STRING(SST_ADMIN_END_TIME_19,		"End Time:");
*/


static const char * const StaticStringTable[] PROGMEM = {
	SST_STARTING_0,
	SST_TIME_FORMAT_1,
	SST_TIME_DATE_FORMAT_2,
	SST_USER_3,
	SST_BACK_4,
	SST_LEFT_BACK_5,
	SST_WELCOME_6,
	SST_INPUT_ENCLOSE_7,
	SST_ADMIN_NAME_8,
	SST_USER_1_NAME_9,
	SST_ADMIN_HOME_HELP_TEXT_10,
	SST_SELECT_11,
	SST_ADMIN_USER_HELP_TEXT_12,
	SST_CHANGE_PASSWORD_HELP_13,
	SST_CHANGE_NAME_14,
	SST_CHANGE_NAME_HELP_15,
	SST_INPUT_TEXT_CHARSET_16,
	SST_TV_ON_17,
	SST_TV_OFF_18,
	SST_TV_ON_NO_MONITOR_19
};


const char *getStaticString(uint8_t id)
{
	static char stringBuffer[120];
	const char *data = (char *)pgm_read_word(&StaticStringTable[id]);
	strcpy_P(stringBuffer, data);
	return stringBuffer;
}
