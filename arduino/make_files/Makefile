UNAME := $(shell uname -s)


# BOARD_TAG = teensy2
BOARD_TAG = leonardo

ifeq ($(UNAME), Linux)
ARDUINO_DIR   = /usr/share/arduino
# ARDMK_DIR     = /usr/local
ARDMK_DIR = /usr/share/arduino/hardware/tools
# AVR_TOOLS_DIR = /usr
AVR_TOOLS_DIR = /usr/share/arduino/hardware/tools/avr

ARDUINO_PORT=/dev/ttyACM0
endif


ifeq ($(UNAME), Darwin)
ARDUINO_SKETCHBOOK = $(HOME)/Documents/Arduino
ARDUINO_DIR   = /Applications/Arduino.app/Contents/Resources/Java
ARDMK_DIR     = /usr/local
ARDUINO_PORT = /dev/cu.usbmodem*
endif

ARDUINO_LIBS = LiquidCrystal IRremote Time EEPROM

# BOARDS_TXT  = $(ARDUINO_DIR)/hardware/teensy/boards.txt
# CPU=16000000L
# MCU=atmega32u4

# USB_TYPE=usb_serial

# usb_serial		- Serial
# usb_hid		- Keyboard + Mouse + Joystick
# usb_serial_hid	- Serial + Keyboard + Mouse + Joystick
# usb_disk		- Disk(Internal) + Keyboard
# usb_disk_sdflash	- Disk(SD Card) + Keyboard
# usb_midi		- MIDI
# usb_rawhid		- Raw HID
# usb_flightsim		- Flight Sim Controls


KEYBOARD_LAYOUT=LAYOUT_US_ENGLISH

# ARDUINO_CORE_PATH = $(ARDUINO_DIR)/hardware/teensy/cores/teensy


RESET_CMD = $(ARDMK_PATH)/ard-reset-leonardo 

	
# include Teensy.mk
include Arduino.mk


