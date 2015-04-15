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


#ifndef _TV_CONTROLLER_DISPLAY_H
#define _TV_CONTROLLER_DISPLAY_H


#include <Arduino.h>
// #include <usb_api.h>
#include <IRremote.h>
#include <LiquidCrystal.h>
#include <Time.h>
// #include <avr/eeprom.h>
#include <EEPROM.h>

#include "EventObject.h"
#include "LCDInput.h"
#include "LCDRotateText.h"
#include "Timer.h"
#include "Page.h"
#include "KeyDevice.h"
#include "IRDevice.h"
#include "Server.h"
#include "StaticStringTable.h"
#include "KeyboardSender.h"


class Controller;

#define KEY_PIN 				A0
#define IR_PIN					A1
#define BACK_LIGHT_PIN			10


#define LCD_WIDTH				16
#define LCD_HEIGHT				2

#define LCD_ROTATE_TEXT_SPEED	400


// #define DEBUG_IR_VALUES

typedef struct {
	uint8_t		hour;
	uint8_t		minute;
} TimeHM;


typedef struct {
	TimeHM		start;
	TimeHM		end;
} AccessTime;

typedef struct {
	uint8_t day;
	uint8_t month;
} DayMonth;

typedef struct {
	uint16_t day;
	uint16_t week;
	uint16_t month;
} UsedMinutesType;

typedef struct {
	atime_t 	startTime;
	atime_t 	endTime;
} LogViewType;


#define MAX_USER_COUNT 			8
#define MAX_USER_NAME_LENGTH	12
#define MAX_LOG_VIEW_COUNT		8

#define USER_INDEX_ADMIN		0
#define USER_INDEX_USER_1		1
#define USER_INDEX_NONE 		0xFF

typedef struct {
	uint8_t 			index;
	UsedMinutesType 	usedMinutes;
	uint16_t 			password;
	char				name[MAX_USER_NAME_LENGTH + 1];
	LogViewType			logViews[MAX_LOG_VIEW_COUNT];
	uint8_t				logViewIndex;
} UserType;

// UserType Memory Footprint
// 1 + 6 + 2 + 13 + ( 8 * 8) + 1 = 87 bytes

#define QUOTA_TYPE_NONE  	0
#define QUOTA_TYPE_DAY 		1
#define QUOTA_TYPE_WEEK  	2
#define QUOTA_TYPE_MONTH  	3

typedef struct {
	uint8_t 	type;
	uint16_t 	maxMinutes;
} QuotaDataType;

// Memory Footprint
// 1 + 2 = 3 bytes


#define EEPROM_HEADER_ID					0x43
#define USER_DEFAULT_MAX_DAY_MINUTES		120


#define VIRTUAL_KEY_UP						250
#define VIRTUAL_KEY_DOWN					251
#define VIRTUAL_KEY_LEFT					252
#define VIRTUAL_KEY_RIGHT					253
#define VIRTUAL_KEY_ENTER					254
#define VIRTUAL_KEY_ESCAPE					255


extern LiquidCrystal lcdDevice;
extern KeyDevice keyDevice;
extern IRDevice irDevice;
extern Controller controller;
extern LCDInput lcdInput;
extern Server server;

#endif
