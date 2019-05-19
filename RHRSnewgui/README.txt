To compile and run the gui open a terminal window and cd to the
directory containing the gui folder. If Qt has not been set up on the pi see READMEQT.txt.

Run "qmake", if qmake fails
target the .pro file with qmake. 
ex: qmake LHRSnewgui.pro

then run "make clean"

And finally "make". 



qmake  or qmake xxx.pro
make clean
make



To open the gui from the gui directory run

chmod +x rungui 

chmod +x cam.sh ./rungui

./rungui

In the terminal from the gui.



TRANSDUCERS:

The transducers need to be terminated in the following AIN() terminals on the labjack. 

AIN(0) Input Voltage
AIN(1) Main X-axis
AIN(2) Main Y-axis
AIN(3) A_T x1-axis 
AIN(4) A_T y1-axis
AIN(5) A_T x2-axis
AIN(6) A_T y2-axis

It is important that the Main X and Y axis transducers have a range of 54 cm, this can be read on the side of the transducers. The A_T transducers need to have a range of 10.2 cm. The distance read outs will not give accurate feedback if this is not the case. The transducers can only give accurate readings for distances less than there listed ranges. Although the string will extend further, the voltage reading stops after the range is meet, followed by a small "dead zone", than staring over. So distances beyond 54 and 10.2 cm, respectively, cannot be measured.

The transducers should all be ran in parallel, with one wire from the input going to AIN(0), which should read 10 V. All of the grounds should be ran together and inserted into SGND with a 100 ohm resistor ran in series. There should be several resistors included in the packaging. This is recommended to prevent any excess current from damaging the labjack. All the ground terminals on the lab jack are connected so technically any GND terminals will work, SGND is not absolutely necessary. 

Input voltage goes to cw, ground goes to ccw, and S/NU goes to the AIN() terminals.

Please see Labjacktransducerdiagram.png for correct AIN() slot placements, and see Transducerdiagram.png for proper wiring. 

The code connecting the labjack and gui can be found in the script.py files and under the object readLabJack() in the main window.cpp file. 


MOTORS:

When hooking up the motors, all of the A_T detector motors need to be ran on the same master controller. While the main motors and the rotary motor need to be ran on there own master. The order in which the master controllers are plugged into the pi, via USB, is important. They will be assigned a /dev/USBTTY port either 0 or 1. The main axis master controller needs to have the /dev port ending in 1 while the A_T master controller needs to have the port ending in 0. This can be checked by plugging one in and running
 
dmesg | grep tty

In the terminal this will show which port it was assigned. 
The A_T detector motors are my main concern if anything is to go wrong, I was unable to fully test with all four A_T detectors hooked up at once, it is possible that the motors may not be assigned the correct axis, the only way to find out is to test as soon as possible.

For the A_T detectors they should have the following order

Motor 1  first A_T detector x-axis 
Motor 2  first A_T detector y-axis

Motor 3  second A_T detector x-axis
Motor 4  second A_T detector y-axis

The code for the velmex motors can be found in the VXM_interface_bare.cpp file.
See the vxm_user_man.pdf for more information on wiring or coding for the welmex motors.

All files cited in the Read me file can be found in the GUI folder.
