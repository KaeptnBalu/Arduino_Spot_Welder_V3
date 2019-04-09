These are the pcb files for the Spot welder V3


V3.3
- The mosfet board was updated with following improvements: 
- Much wider traces on the bottom of the pcb for the high current connection to the u-shaped aluminum part
- Mosfet gate resistors directly on the mosfet board, very close to the mosfet gate pins
- All 8 Pins of the female 8 pin header that connects the Arduino and mosfet board are now connected to each other, which eliminates contact problems.
- compatible to all Spot Welder Arduino Boards V3 or later


V3.2
- the Arduino Board was updated so it is now possible to mount a 3.5mm terminal block to the input pads. 
- the voltage measurement now connects directly to the 12V input pad instead of behind the schottky diode in the previous version. This guarantuees a more precise voltage measurement.
- the 8 small SMAJ13A-13-F TVS diodes have been removed from the mosfet board. There is now one of these diodes on the Arduino board that protects all mosfet gates at once.


V3.1

There is a new V3.1 of the mosfet board available. It is fully compatible with the Arduino Board V3, so you only need to upgrade the mosfet board if you already built a V3 Spot Welder. 

Improvements:

    4 TVS diodes instead of only 1

This improvement makes it more capable of higher CCA rated car batteries. In my tests it handled a 800 CCA car battery for a few hundred welds in a row without problems. But using this powerfull batteries operates the welder near its maximum limits so the recommended car battery size is still 400...600 CCA
