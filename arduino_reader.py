# For use with the EMG Arduino spiker unit. 
# Opens a serial channel to the Arduino and listens for an ASCII control
# character and sends a Windows IO event (in this case, the space bar). 

# change to True to enable acceletrometer 
ACC_ENABLE = False

import pynput, serial, time
import serial.tools.list_ports

# Automatically find Arduino COM port 
port = 'NOT FOUND'
ports = list(serial.tools.list_ports.comports())
for i in ports:
	if i.description.find('Arduino') == 0:
		port = i.device
		break


# Attempt to connect to the port. If the search above failed,
# it will try to connect to an invalid port. 
try:
	ser = serial.Serial(port, 9600, timeout = 0)
except Exception as e:
	print("""Could not connect to Arduino!\nMake sure it's connected before running this script 
and that nothing else is using the Arduino already, such as the Arduino IDE.""")
	print("\nDebug Info: \nPort: " + str(port))
	print(e)
	input("\n\nPress Enter to continue...")
	quit()
	
kb  = pynput.keyboard.Controller()
if ACC_ENABLE:  
	mouse = pynput.mouse.Controller()
key = pynput.keyboard.Key.space

print("Ready!")  
print("Remember to use the tan button to change sensitivity.")

if ACC_ENABLE:
	print("ACC ENABLED")
	while True:
		i = ser.readline().decode('UTF-8')
		if i != '':
			if i == 'T':
				print("Trigger")
				kb.press(key)
				time.sleep(0.2)
				kb.release(key)
			else:
				t = tuple(i[1:-1].split(','))
				if(len(t) != 3):
					continue
				try:
					mouse.move(int(t[1]) * 2, int(t[2]) * 2)
				except:
					continue
		ser.flushInput()
else:
	print("NO ACC")
	while True:
		i = ser.readline().decode('UTF-8').strip('\n')
		if i == 'T':
			kb.press(key)
			kb.release(key)
		#ser.flushInput()