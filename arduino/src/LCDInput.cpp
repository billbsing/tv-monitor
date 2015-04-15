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
#include "LCDInput.h"

// try to cut back on flash memory, do not use to reduce the amount of flash available
#ifdef LCDINPUT_USE_ASCII_KEY_TABLE
static char const keyTableSting0[] PROGMEM  = "0!@#$%";
static char const keyTableSting1[] PROGMEM  = "1^&*?+=";
static char const keyTableSting2[] PROGMEM  = "2abcABC";
static char const keyTableSting3[] PROGMEM  = "3defDEF";
static char const keyTableSting4[] PROGMEM  = "4ghiGHI";
static char const keyTableSting5[] PROGMEM  = "5jklJKL";
static char const keyTableSting6[] PROGMEM  = "6mnoMNO";
static char const keyTableSting7[] PROGMEM  = "7pqrsPQRS";
static char const keyTableSting8[] PROGMEM  = "8tuvTUV";
static char const keyTableSting9[] PROGMEM  = "9wxyzWXYZ";



static const KeyTable keyTable[] PROGMEM = {
	'0', 	keyTableSting0,
	'1', 	keyTableSting1,
	'2', 	keyTableSting2,
	'3', 	keyTableSting3,
	'4', 	keyTableSting4,
	'5', 	keyTableSting5,
	'6', 	keyTableSting6,
	'7', 	keyTableSting7,
	'8', 	keyTableSting8,
	'9', 	keyTableSting9,
};

#endif

LCDInput::LCDInput()
{
	clear();
}

LCDInput::~LCDInput()
{
}

void LCDInput::begin(String text, uint8_t col, uint8_t row, uint8_t length, char defaultChar)
{
	m_passwordChar = 0;
	m_col = col;
	m_row = row;
	m_length = length;
	m_cursor = 0;
	
	m_buffer = text;
	
	if ( m_buffer.length() > length ) {
		m_buffer = m_buffer.substring(0, length);
	}

	uint8_t i;
	for (i = 0; i < length; i++ ) {
		if ( m_buffer.length() < length ) {
			m_buffer += defaultChar;
		}
	}
	
	m_needsToShow = true;
	_showText();
	lcdDevice.cursor();
}

void LCDInput::close()
{
	lcdDevice.noCursor();
	lcdDevice.noBlink();
	clear();
}

void LCDInput::clear()
{
	m_col = 0;
	m_row = 0;
	m_cursor = 0;
	m_length = 0;
	m_needsToShow = false;	
	m_encloseText = "";
	m_charsetP = NULL;
	m_charset = "";
	m_passwordChar = 0;	
}




bool LCDInput::show(bool isForce)
{
	bool result = false;
	if ( m_length == 0 ) {
		return false;
	}
	if ( m_needsToShow || isForce ) {
		_showText();
    	m_needsToShow = false;
    	result = true;
    }
    return result;
}


void LCDInput::adjustValue(int8_t delta)
{
	String charset = _getCharset();
	
	int index = charset.indexOf(value());
	if ( index >= 0) {
		index += delta;
		if (index < 0) {
			index = charset.length()  + index;
		}
		if ( index >= charset.length() ) {
			index = index - charset.length();
		}
		setValue(charset[index]);
	}
	else {
		setValue(charset[0]);
	}
}

char LCDInput::value()
{
	return m_buffer[m_cursor];
}

void LCDInput::setValue(char value)
{
	m_buffer.setCharAt(m_cursor, value);
	m_needsToShow = true;
}


void LCDInput::move(int8_t delta)
{
	int8_t cursorPosition = m_cursor + delta;
	if ( cursorPosition < 0 ) {
		cursorPosition = 0;
		raiseEvent(StartOfInputEvent);
	}
	if ( cursorPosition >= m_length ) {
		cursorPosition -= m_length;
		raiseEvent(EndOfInputEvent);
	}
	m_cursor = cursorPosition;
	if ( m_buffer[m_cursor] == 0 ) {
		m_buffer[m_cursor] = m_defaultChar;
	}
	m_needsToShow = true;

}

void LCDInput::setInputCharset(String charset)
{
	m_charset = charset;
	m_charsetP = NULL;
}
void LCDInput::setInputCharset(const char* charset)
{
	setInputCharset(charset);
}

void LCDInput::setInputCharsetP(const char* charset)
{
	m_charsetP = charset;
	m_charset = "";
}


void LCDInput::setInputRange(uint8_t startValue, uint8_t endValue)
{
	uint8_t i;
	m_charset = String();
	for ( i = startValue; i <= endValue ; i++ ) {
		m_charset += i;
	}
	m_charsetP = NULL;
}


uint8_t LCDInput::length()
{
	return length();
}

void LCDInput::setLength(uint8_t value)
{	
	m_length = value;
}

void LCDInput::processKey(unsigned char key )
{
	uint8_t i;

#ifdef LCDINPUT_USE_ASCII_KEY_TABLE
	for ( i = 0; i < sizeof(keyTable) / sizeof(KeyTable); i ++ ) {
		KeyTable item = keyTable[i];
		if ( item.key == key ) {
			char newValue = _findNextValueInCharSet(value(), item.text);
			setValue(newValue);
			move(1);
			break;
		}
	}
#endif

	switch(key) {
		case VIRTUAL_KEY_UP:
			adjustValue(1);
			break;
		case VIRTUAL_KEY_DOWN:
			adjustValue(-1);
			break;
		case VIRTUAL_KEY_LEFT:
			move(-1);
			break;
		case VIRTUAL_KEY_RIGHT:
			move(1);
			break;
		case VIRTUAL_KEY_ENTER:
			raiseEvent(KeyEnterEvent);
			break;
	}

}


int LCDInput::asInt()
{
	char buffer[m_buffer.length() + 2];
	m_buffer.toCharArray(buffer, m_buffer.length() + 1);
	return atoi(buffer);
}

String LCDInput::asString()
{
	return m_buffer;
}

void LCDInput::setOpenCloseText(String text)
{
	m_encloseText = text;
	_showText();
}


char LCDInput::passwordChar()
{
	return m_passwordChar;
}

void LCDInput::setPasswordChar(char value)
{
	m_passwordChar = value;
}

char LCDInput::_findNextValueInCharSet(char value, String keyCharset)
{
	/*
	 * find the value in the keycharset, if found then start looking
	 * at the next char in the keycharset.
	 * keey looking in the keycharset for a valid character which is also
	 * in the main charset. If it' also in the main charset then return 
	 * the new character. If no characters are found in the main charset then
	 * just return the original value.
	 */
	int pos = keyCharset.indexOf(value);
	if ( pos < 0 ) {
		return value;
	}
	uint8_t i = pos + 1;
	String charset = _getCharset();
	while ( true) {
		if ( i >= keyCharset.length() ) {
			i = 0;
		}
		value = keyCharset[i];
		if ( charset.indexOf(value) >=0 ) {
			// the next char found from the keycharset is in the main charset, so we can now return it's value.
			break;
		}
		i++;
		if ( i == pos ) {
			// we have gone around the charset looking for the next key, none found so just return the current key
			break;
		}
	}
	return value;
}

void LCDInput::_showText()
{
	uint8_t offset = 0;
	lcdDevice.setCursor(m_col, m_row);
	if ( m_encloseText.length() > 0 ) {
		lcdDevice.print(m_encloseText[0]);
		offset = 1;
	}
	String buffer = m_buffer;
	if ( m_passwordChar > 0 ) {
		uint8_t i;
		for ( i = 0; i < m_buffer.length(); i ++ ) {
			if ( _isInCharSet(m_buffer[i]) ) {
				buffer[i] = m_passwordChar;
			}
			else {
				buffer[i] = m_buffer[i];
			}
		}
	}
	lcdDevice.print(buffer);
	if ( m_encloseText.length() > 1 ) {
		lcdDevice.print(m_encloseText[1]);
	}
	lcdDevice.setCursor(m_col + offset + m_cursor, m_row);
}

String LCDInput::_getCharset()
{
	String result;
	if ( m_charsetP ) {
		char charsetBuffer[128];
		strcpy_P(charsetBuffer, m_charsetP);
		result = String(charsetBuffer);
	}
	else {
		result = m_charset;
	}
	return result;
}

bool LCDInput::_isInCharSet(char value)
{
	return _getCharset().indexOf(value) >= 0;
}

