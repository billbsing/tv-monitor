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
#include "LCDRotateText.h"


LCDRotateText::LCDRotateText()
{
	clear();	
}

void LCDRotateText::begin(String text, uint8_t col, uint8_t row, uint8_t width, uint16_t speed)
{
	m_text = text;
	m_col = col;
	m_row = row;
	m_width = width;
	m_speed = speed;
	m_nextRoll = millis() + speed;
	
}

void LCDRotateText::begin(const char* text, uint8_t col, uint8_t row, uint8_t width, uint16_t speed)
{
	begin(String(text), col, row, width, speed);	
}

void LCDRotateText::close()
{
	clear();
}

void LCDRotateText::clear()
{
	m_text = "";
	m_col = 0;
	m_row = 0;
	m_width = 0;
	m_speed = 0;
}


void LCDRotateText::clearDisplay()
{
	uint8_t i;
	for ( i = m_col; i < LCD_WIDTH; i ++ ) {
		lcdDevice.setCursor(i, m_row);
		lcdDevice.print(' ');		
	}	
}
bool LCDRotateText::show(bool isForce)
{
	bool result = false;
	if ( m_speed == 0 ) {
		return false;
	}
	if ( m_nextRoll <= millis() || isForce ) {
		m_nextRoll = millis() + m_speed;
		lcdDevice.setCursor(m_col, m_row);
		if ( m_text.length() > m_width ) {
			String buffer = _rotateText(m_text, m_position, m_width);
			lcdDevice.print(buffer);
			m_position ++;
			if ( m_position >= m_text.length() ) {
				m_position = 0;
			}
		}
		else {
			lcdDevice.print(m_text);
			m_nextRoll += ( m_speed * 10);
		}
		lcdDevice.setCursor(m_col, m_row);
		result = true;
	}
	return result;
}



String LCDRotateText::_rotateText(String text, uint8_t pos, uint8_t length)
{
	String result;
    uint8_t copyLength = text.length() - pos;
    if ( copyLength > length ) {
		copyLength = length;
    }

    result = text.substring(pos, pos + copyLength + 1);
    if ( copyLength < length ) {
		result += " ";
		copyLength ++;
    }
    if ( copyLength < length ) {
		result += text.substring(0, length - copyLength);
    }
    return result;
}
