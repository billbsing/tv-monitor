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


#ifndef STATICSTRINGTABLE_H
#define STATICSTRINGTABLE_H

#define FLASH_RESOURCE_STRING(_name_, _text_)   static const char _name_[] PROGMEM  = _text_


#define SST_STARTING					0
#define SST_TIME_FORMAT					1
#define SST_TIME_DATE_FORMAT 			2
#define SST_USER						3
#define SST_BACK						4
#define SST_LEFT_BACK					5
#define SST_WELCOME						6
#define SST_INPUT_ENCLOSE				7
#define SST_ADMIN_NAME					8
#define SST_USER_1_NAME					9
#define SST_ADMIN_HOME_HELP_TEXT		10
#define SST_SELECT						11
#define SST_ADMIN_USER_HELP_TEXT		12
#define SST_CHANGE_PASSWORD_HELP		13
#define SST_CHANGE_NAME					14
#define SST_CHANGE_NAME_HELP			15
#define SST_INPUT_TEXT_CHARSET			16
#define SST_TV_ON						17
#define SST_TV_OFF						18
#define SST_TV_ON_NO_MONITOR			19



extern const char *getStaticString(uint8_t id);


#endif // STATICSTRINGTABLE_H
