These programs allow the DIYEMG to communicate with a desktop computer. By default, the program output the spacebar signal to the computer's operating system.

These programs require:
	1x Arduino Uno 
	1x DIYEMG build
	1x USB cable to connect the Arduino to the computer
	3x Conductive EMG pads
	1x Computer with the following installed:
* Python3.x with the pynput and pyserial modules installed. (These libraries can be installed using pip3 in the python install directory).
* The Arduino IDE

Setup:
1. First try opening the 'arduino_reader' application. It is a compiled python script that should run without installing the python environment. It should open with the message "Could not connect to Arduino!" If this message appears, you can skip to step 2. If the program does not run, you will need to install the python environment and libraries.
	a. Open the 'installer_python' folder.
	b. Run python-3.8.5
	c. When prompted, install with the 'Add to PATH' option selected.
	d. After install, run the 'install_libs' batch file in the 'installer_python' folder.
2. Open the folder 'installer_arduino'
3. Install arduino-1.8.13-windows and install normally.


Getting started:
1. Connect the Arduino to the computer and open the diyemg_control.ino file in the Arduino IDE. Ensure that the target parameters are correct under “Tools”, specifically the COM port used by the computer. 
2. Upload the diyemg_control.ino program to the Arduino.
3. While keeping the Arduino plugged into the computer, open (double click) on the arduino_reader file (the application if you didn't need to install python in the above steps). The python script should open a command prompt window and output "Ready" when it has connected to the Arduino and is receiving data. 
4. Attach the pads to a muscle group on your arm, attach them to the alligator clips, and attach the leads to the appropriate resistor inputs.
6. When the Arduino is triggered, it will output a spacebar press to the computer.
7. Turn the potentiometer to adjust the sensitivity of the DIYEMG.  

Modifying the program:
	The Arduino and Python programs can be modified in several ways. The primary things that can be modified are the EMG sensitivity values and the "trigger" values. 

Trigger: 
The trigger values are used to "debounce" the signal received by the Spiker unit. Muscles, when flexed, tend to give unstable electrical signals which may cause the DIYEMG to false-trigger. In the Arduino code, there are two main trigger preprocessor values defined as TRIGGER_LOW and TRIGGER_HIGH. These values introduce a "blind spot" in the signal detection so that any value between the high and low values are ignored. These values can be adjusted to balance sensitivity and stability of the output signal. The actual trigger functionality can be seen in the function "update_output". 

The second portion of the “debouncing” code is the TRIGGER_WAIT_TIME_MS. This value delays processing between triggers. Lowering this value will increase responsiveness at the cost of being less accurate with triggers overall. 

The diyemg_control program has been optimized for high-performance processing, so it may be difficult to follow if you’re not used to C programming. As a result of this, the DIYEMG is only usable on analog port A0 on the Arduino Nano and Arduino Uno. 
