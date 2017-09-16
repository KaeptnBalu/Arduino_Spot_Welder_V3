# Arduino_Spot_Welder_V3

This is the latest V3 of the Arduino Spot Welder. The previous V2 can be found here https://github.com/KaeptnBalu/Arduino_Spot_Welder_V2

An Arduino based Spot Welder for battery welding http://www.instructables.com/id/DIY-Arduino-Battery-Spot-Welder/
Introduction Video: https://www.youtube.com/watch?v=CNmvx2JSCvA

Improvements in V3:

- Mosfet PCB now with 2oz copper layer and wider traces which connect the high current carrying mosfet legs to the u-shaped aluminum part
- “AutoPulse” feature, which automatically activates a pulse after a defined delay time when both welding tips touch the nickel strip (thanks to Petr Zverina for the idea)
- 7 segment display replaced by OLED display
- potentiometer replaced by rotary encoder
- Menu system to easy adjust the low battery alarm, AutoPulse delay and short pulse time
- powered directly by car battery, no more need for extra power supply
- TVS diode integrated on the mosfet pcb, no external diodes necessary
- upgraded Mosfets to IRFB7430 (they can handle up to 1000A welding current with no problem)
- Standby feature: after 5 minutes of inactivity the Spot Welder will go to standby and the foot switch and AutoPulse will be deactivated while in standby.
- u-shaped aluminum parts is now riveted to the pcb


This Spot Welder can be used to weld 18650 batteries. It uses a 12V car battery as welding current supply. Typically one 40Ah 440A battery delivers enough current to get good welds with 0.15mm nickel strips and even 0.25mm nickel strips. For thicker nickel strips maybe you will need bigger battery or two in paralell.

The Welder generates a double pulse, where the first one is 12% of the time of the second one by default. Pulse time of the main pulse is adjustable by the rotary encoder and displayed on the screen in mS so you can exactly adjust the time. Its adjustable from 1 … 999 mS.

If you want to download the project click on "clone or download" on this page. Downloading single files sometimes seems to cause some files to be corrupted while downloading.

You can get parts to build your own Spot Welder or prebuilt kits at https://malectrics.eu/
