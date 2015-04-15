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

#ifndef LCDINPUT_H
#define LCDINPUT_H

#define LCDINPUT_USE_ASCII_KEY_TABLE				// LCDInput can use phone like switching to cyle through each character


class EventObject;

typedef struct {
	unsigned char 	key;
	const char *	text;
} KeyTable;

class LCDInput : public EventObject
{
	public:
	
		enum EventType {
			EndOfInputEvent = 1,
			StartOfInputEvent,
			KeyEnterEvent
		};
	
		LCDInput();
		virtual ~LCDInput();
		void begin(String text, uint8_t col, uint8_t row, uint8_t length, char defaultChar = ' ');
		void close();
		void clear();
		bool show(bool isForce = false);
		void adjustValue(int8_t delta);
		char value();
		void setValue(char value);
		void move(int8_t delta);
		void setInputCharset(String charset);
		void setInputCharset(const char* charset);
		void setInputCharsetP(const char* charset);
		void setInputRange(uint8_t startValue, uint8_t count);
		void processKey(unsigned char key);
		uint8_t length();
		void setLength(uint8_t value);
		void setOpenCloseText(String text);
		char passwordChar();
		void setPasswordChar(char value);
		
		int asInt();
		String asString();
			
	protected:
		
		char _findNextValueInCharSet(char value, String keyCharset);
		void _showText();
		String _getCharset();
		bool _isInCharSet(char value);
		
		uint8_t 	m_col;
		uint8_t 	m_row;
		uint8_t 	m_cursor;
		uint8_t 	m_length;
		char		m_defaultChar;
		String		m_buffer;
		bool		m_needsToShow;
		String		m_charset;
		const char* m_charsetP;
		String 		m_encloseText;
		char		m_passwordChar;
		
	private:
};

#endif /* LCDINPUT_H */ 
