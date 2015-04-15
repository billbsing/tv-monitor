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


#ifndef LCDROTATETEXT_H
#define LCDROTATETEXT_H

class LCDRotateText
{
	public:
		LCDRotateText();
		void begin(String text, uint8_t col, uint8_t row, uint8_t width, uint16_t speed);
		void begin(const char* text, uint8_t col, uint8_t row, uint8_t width, uint16_t speed);
		void close();
		bool show(bool isForce = false);
		void clear();
		void clearDisplay();

		
	protected:
	
		String _rotateText(String text, uint8_t pos, uint8_t length);
	
		String 			m_text;
		uint8_t 		m_col;
		uint8_t 		m_row;
		uint8_t 		m_width;
		uint8_t			m_position;
		uint16_t 		m_speed;
		uint32_t 		m_nextRoll;
	private:

};

#endif /* LCDROTATETEXT_H */ 
