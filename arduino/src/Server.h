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


#ifndef SERVER_H
#define SERVER_H


#define SERVER_ENABLE_DEBUG						// Enable server to send debug messages via serial

class EventObject;

// Largest packet size UserType: 22bytes + 3 data bytes = 25 Bytes
#define MAX_DATA_SIZE					64


#define COMMAND_START_CONNECTION 		1
#define COMMAND_DEBUG_MESSAGE			2
#define COMMAND_SET_DATE_TIME			3
#define COMMAND_SET_USER				4
#define COMMAND_TEST_KEY				5
#define COMMAND_GET_USER				6



typedef struct {
	uint8_t		command;
	uint8_t		dataLength;
} HeaderType;

typedef struct {
	uint16_t	year;
	uint8_t 	month;
	uint8_t		day;
	uint8_t		hour;
	uint8_t		minute;
	uint8_t		second;
} DateTimeType;

class Server : public EventObject
{

public:
	enum EventType {
		OnReceiveCommand = 1,
	};
	
    Server();
	void sendCommand(uint8_t command);
	void sendCommand(uint8_t command, uint8_t *data, uint8_t length);
	void sendCommand(uint8_t command, String data);
	void sendCommand(uint8_t command, uint8_t value);
	void sendCommand(uint8_t command, uint16_t value);
	
#ifdef SERVER_ENABLE_DEBUG	
	void sendDebug(String data);
	void sendDebug(uint8_t *data, uint8_t length);
	void sendDebug(char *data, uint8_t length);
#endif
	
	uint8_t command();
	uint8_t *data();
	uint8_t dataLength();
	int asInt();
	DateTimeType *asDateTime();
	
	void loop();
protected:
	void _clearData();
	void _clearHeader();
	void _sendHeader(const HeaderType &header);
	
	HeaderType	m_header;
	uint8_t		m_headerPos;
	uint8_t 	m_dataPos;
	uint8_t		m_data[MAX_DATA_SIZE];
	
};

#endif // SERVER_H
