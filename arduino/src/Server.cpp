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
#include "Server.h"

Server::Server()
{
	_clearHeader();
	_clearData();
}

void Server::sendCommand(uint8_t command)
{
	HeaderType header;
	header.command = command;
	header.dataLength = 0;
	_sendHeader(header);

}

void Server::sendCommand(uint8_t command, uint8_t *data, uint8_t length)
{
	HeaderType header;
	header.command = command;
	header.dataLength = length;
	_sendHeader(header);
	if ( length > 0 ) {
		Serial.write(data, length);
		Serial.flush();
	}
}

void Server::sendCommand(uint8_t command, String data)
{
	uint8_t buffer[data.length() + 1];
	data.getBytes(buffer, data.length() + 1);
	sendCommand(command, buffer, data.length() + 1);
}

void Server::sendCommand(uint8_t command, uint8_t value)
{
	uint8_t buffer[1];
	buffer[0] = value;
	sendCommand(command, buffer, 1);
}
void Server::sendCommand(uint8_t command, uint16_t value)
{
	uint8_t buffer[sizeof(uint16_t)];
	*((uint16_t *)&buffer) = value;
	sendCommand(command, buffer, sizeof(uint16_t));
}

#ifdef SERVER_ENABLE_DEBUG

void Server::sendDebug(String data)
{
	sendCommand(COMMAND_DEBUG_MESSAGE, data);
}

void Server::sendDebug(uint8_t* data, uint8_t length)
{
	sendCommand(COMMAND_DEBUG_MESSAGE, data, length);
}

void Server::sendDebug(char* data, uint8_t length)
{
	sendCommand(COMMAND_DEBUG_MESSAGE, (uint8_t *) data, length);
}

#endif

uint8_t Server::command()
{
	return m_header.command;
}

uint8_t * Server::data()
{
	return m_data;
}

uint8_t Server::dataLength()
{
	return m_header.dataLength;
}

int Server::asInt()
{
	if ( dataLength() != sizeof(int)) {
		return NULL;
	}
	int value = *(int *) &m_data;
	return value;
}

DateTimeType *Server::asDateTime()
{
	if ( dataLength()  != sizeof(DateTimeType) ) {
		return NULL;
	}
	return (DateTimeType *) &m_data;
}


void Server::loop()
{
	while ( Serial.available() ) {
		uint8_t value = Serial.read();
		if ( m_headerPos == 0 ) {
			m_header.command = value;
			m_headerPos ++;
			_clearData();
			return;
		}
		if ( m_headerPos > 0 && m_headerPos < sizeof(HeaderType)) {
			((uint8_t *) &m_header)[m_headerPos] = value;
			m_headerPos ++;
			if ( m_headerPos >= sizeof(HeaderType) && m_header.dataLength == 0) {
				raiseEvent(OnReceiveCommand);
				_clearData();
				_clearHeader();
			}
			return;
		}
		if ( m_headerPos >= sizeof(HeaderType) ) {
			m_data[m_dataPos] = value;
			m_dataPos ++;
			if ( m_dataPos >= m_header.dataLength ) {
				m_data[m_dataPos] = 0;
				raiseEvent(OnReceiveCommand);
				_clearData();
				_clearHeader();
			}
			if ( m_dataPos >= MAX_DATA_SIZE ) {
				_clearData();
				_clearHeader();
			}
		}
	}

}

void Server::_clearData()
{
	m_dataPos = 0;
	memset(m_data, 0, MAX_DATA_SIZE);
	
}

void Server::_clearHeader()
{
	memset(&m_header, 0, sizeof(HeaderType));
	m_headerPos = 0;
}

void Server::_sendHeader(const HeaderType& header)
{
	uint8_t i;
	uint8_t *ptr = (uint8_t *) &header;
	for ( i = 0; i < sizeof(HeaderType); i ++ ) {
		Serial.write(ptr[i]);
	}
	Serial.flush();

}



