 
# TV Controller

import logging, time, struct, datetime, serial, ConfigParser

#define IR_BD_KEY_0					0x30
#define IR_BD_KEY_1					0x31
#define IR_BD_KEY_2					0x32
#define IR_BD_KEY_3					0x33
#define IR_BD_KEY_4					0x34
#define IR_BD_KEY_5					0x35
#define IR_BD_KEY_6					0x36
#define IR_BD_KEY_7					0x37
#define IR_BD_KEY_8					0x38
#define IR_BD_KEY_9					0x39
#define IR_BD_KEY_UP				0x3A
#define IR_BD_KEY_DOWN				0x3B
#define IR_BD_KEY_LEFT				0x3C
#define IR_BD_KEY_RIGHT				0x3D
#define IR_BD_KEY_ENTER				0x3E
#define IR_BD_KEY_MOVE_BEGIN		0x3F
#define IR_BD_KEY_MOVE_END			0x40
#define IR_BD_KEY_FAST_BACK			0x41
#define IR_BD_KEY_FAST_FORWARD		0x42
#define IR_BD_KEY_PLAY				0x43
#define IR_BD_KEY_PAUSE				0x44
#define IR_BD_KEY_STOP				0x45
#define IR_BD_KEY_MENU				0x46
#define IR_BD_KEY_RETURN			0x46
#define IR_BD_KEY_TOOLS				0x47
#define IR_BD_KEY_RED				0x48
#define IR_BD_KEY_GREEN				0x49
#define IR_BD_KEY_YELLOW			0x4A
#define IR_BD_KEY_BLUE				0x4B
#define IR_BD_KEY_TELETEXT			0x4C
#define IR_BD_KEY_HELP				0x4D
#define IR_BD_KEY_POWER				0x4E



class DataPacket:
	
	def __init__(self):
		self._data = None
		self._dataLength = 0
		self._command = 0
		
	def readHeader(self, data):
		self._command = 0
		self._dataLength = 0
		
		items = struct.unpack("=BB", data)
		if items:
			self._command = items[0]
			self._dataLength = items[1]
			
	def readData(self, data):
		self._data = data
		
	def command(self):
		return self._command
	
	def setCommand(self, value):
		self._command = value
		
	def data(self):
		return self._data
		
	def dataLength(self):
		return self._dataLength
		
	def setDateTime(self, datetime):
		self._data = struct.pack('=HBBBBB', datetime.year, datetime.month, datetime.day, datetime.hour, datetime.minute, datetime.second);
		self._dataLength = len(self._data)
		
	def setData(self, data, length = 0):
		self._dataLength = length
		if length == 0:
			self._dataLength = len(data)
		self._data = data[:self._dataLength]
		
		
class TVControllerServer:


	COMMAND_START_CONNECTION = 1
	COMMAND_DEBUG_MESSAGE = 2
	COMMAND_SET_DATE_TIME = 3
	COMMAND_SET_USER = 4
	COMMAND_KEY_PRESS = 5

	def __init__(self):
		self._connection = None

		#self._config = ConfigParser.ConfigParser()
		#self._config.readfp(open('tvcontroller.conf'))
	
		
	def connect(self, device, speed = 9600):
		self._device = device
		self._speed = speed
		self._connection = None
		retryCount = 10
		result = False
		while retryCount > 0:
			try:
				self._connection = serial.Serial(self._device, self._speed, timeout=5)
				result = self._connection.isOpen()
				break;
			except:
				logging.info("Waiting to connect")
				time.sleep(5)
			retryCount -= 1
		return result
	
	def readPacket(self):		
		if self._connection.isOpen() and self._connection.inWaiting():
			packet = DataPacket()
			packet.readHeader(self._connection.read(2))
			if packet.dataLength() > 0:
				packet.readData(self._connection.read(packet.dataLength()))
			return packet
		return None
				
				

	def sendPacket(self, packet):
		if self._connection.isOpen():
			#logging.debug("Sending packet len:%d" % (packet.dataLength()))
			data = struct.pack("=BB", packet.command(), packet.dataLength())
			if packet.dataLength() > 0:
				data += packet.data()
			#for i in range(packet.dataLength() + 3):
				#logging.debug("%d:%d" % ( i, ord(data[i])))
			self._connection.write(data)

	def sendDateTime(self):
		logging.info("Sending DateTime")
		packet = DataPacket()
		packet.setCommand(TVControllerServer.COMMAND_SET_DATE_TIME)
		now = datetime.datetime.now();
		packet.setDateTime(now)
		self.sendPacket(packet)
		
	def sendCommand(self, command):
		logging.info("Sending command %d" % command)
		packet = DataPacket()
		packet.setCommand(command)
		self.sendPacket(packet)
		
	def sendUsers(self):
		logging.info("Sending Users")
		userList = self._config.get('setup', 'users').split(",")
		max_day_minutes = int(self._config.get('setup', 'max_day_minutes'))
		max_week_minutes = int(self._config.get('setup', 'max_week_minutes'))
		index = 0
		for userId in userList:
			userId = userId.strip()
			sectionName = "user %s" % userId
			if self._config.has_section(sectionName):
				name = self._config.get(sectionName, 'name')
				used_day_minutes = int(self._config.get(sectionName, 'used_day_minutes'))
				used_week_minutes = int(self._config.get(sectionName, 'used_week_minutes'))
				password = int(self._config.get(sectionName, 'password'))
				logging.info("Send user %d:'%s'" % (index, name))
				packet = DataPacket()
				packet.setCommand(self.COMMAND_SET_USER)
				packet.setData(struct.pack("=BHHH20s", index, used_day_minutes, used_week_minutes, password, name), 7 + len(name))
				self.sendPacket(packet)
				index += 1
				
	def sendKeyCode(self, value):
		packet = DataPacket()
		packet.setCommand(TVControllerServer.COMMAND_KEY_PRESS)
		packet.setData(struct.pack("=H", value))
		self.sendPacket(packet)
		
