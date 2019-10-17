EESchema Schematic File Version 5
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 2
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
Comment5 ""
Comment6 ""
Comment7 ""
Comment8 ""
Comment9 ""
$EndDescr
$Comp
L MCU_ST_STM32F0:STM32F030F4Px U2
U 1 1 5D58381A
P 4100 6000
F 0 "U2" H 4100 5900 50  0000 C CNN
F 1 "STM32F030F4Px" H 4000 6000 50  0000 C CNN
F 2 "Package_SO:TSSOP-20_4.4x6.5mm_P0.65mm" H 3700 5300 50  0001 R CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/DM00088500.pdf" H 4100 6000 50  0001 C CNN
	1    4100 6000
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J5
U 1 1 5D5F279C
P 800 1100
F 0 "J5" H 718 1317 50  0000 C CNN
F 1 "Battery" H 718 1226 50  0000 C CNN
F 2 "Connector_Molex:Molex_KK-254_AE-6410-02A_1x02_P2.54mm_Vertical" H 800 1100 50  0001 C CNN
F 3 "~" H 800 1100 50  0001 C CNN
	1    800  1100
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR02
U 1 1 5D5F383F
P 1150 1350
F 0 "#PWR02" H 1150 1100 50  0001 C CNN
F 1 "GND" H 1155 1177 50  0000 C CNN
F 2 "" H 1150 1350 50  0001 C CNN
F 3 "" H 1150 1350 50  0001 C CNN
	1    1150 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	1150 1350 1150 1200
Wire Wire Line
	1150 1200 1000 1200
$Comp
L power:+12V #PWR01
U 1 1 5D5F4014
P 1150 1000
F 0 "#PWR01" H 1150 850 50  0001 C CNN
F 1 "+12V" H 1165 1173 50  0000 C CNN
F 2 "" H 1150 1000 50  0001 C CNN
F 3 "" H 1150 1000 50  0001 C CNN
	1    1150 1000
	1    0    0    -1  
$EndComp
Wire Wire Line
	1150 1000 1150 1100
Wire Wire Line
	1150 1100 1000 1100
$Comp
L Device:D D1
U 1 1 5D5EA175
P 1550 1150
F 0 "D1" V 1504 1229 50  0000 L CNN
F 1 "TVS_SMDJ13A" V 1300 900 50  0000 L CNN
F 2 "Diode_SMD:D_SMC" H 1550 1150 50  0001 C CNN
F 3 "~" H 1550 1150 50  0001 C CNN
	1    1550 1150
	0    1    1    0   
$EndComp
Wire Wire Line
	1550 1000 1550 950 
Wire Wire Line
	1550 950  1250 950 
Wire Wire Line
	1250 950  1250 1100
Wire Wire Line
	1250 1100 1150 1100
Connection ~ 1150 1100
Wire Wire Line
	1550 1300 1550 1350
Wire Wire Line
	1550 1350 1250 1350
Wire Wire Line
	1250 1350 1250 1200
Wire Wire Line
	1250 1200 1150 1200
Connection ~ 1150 1200
$Comp
L Device:D D2
U 1 1 5D5ECDFE
P 2000 950
F 0 "D2" H 2000 1074 50  0000 C CNN
F 1 "SS34" H 2000 1165 50  0000 C CNN
F 2 "Diode_SMD:D_SMA" H 2000 950 50  0001 C CNN
F 3 "~" H 2000 950 50  0001 C CNN
	1    2000 950 
	-1   0    0    1   
$EndComp
Wire Wire Line
	1850 950  1550 950 
Connection ~ 1550 950 
$Comp
L Device:CP C3
U 1 1 5D5F5F67
P 2400 1150
F 0 "C3" H 2500 1200 50  0000 L CNN
F 1 "1u" H 2518 1105 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2438 1000 50  0001 C CNN
F 3 "~" H 2400 1150 50  0001 C CNN
	1    2400 1150
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C4
U 1 1 5D5F6AC6
P 2750 1150
F 0 "C4" H 2950 1200 50  0000 R CNN
F 1 "470u" H 3050 1100 50  0000 R CNN
F 2 "Capacitor_THT:CP_Radial_D10.0mm_P5.00mm" H 2788 1000 50  0001 C CNN
F 3 "~" H 2750 1150 50  0001 C CNN
	1    2750 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 1000 2400 950 
Wire Wire Line
	2400 950  2150 950 
Wire Wire Line
	2750 1000 2750 950 
Wire Wire Line
	2750 950  2400 950 
Connection ~ 2400 950 
$Comp
L power:GND #PWR03
U 1 1 5D5F7B41
P 2400 1400
F 0 "#PWR03" H 2400 1150 50  0001 C CNN
F 1 "GND" H 2405 1227 50  0000 C CNN
F 2 "" H 2400 1400 50  0001 C CNN
F 3 "" H 2400 1400 50  0001 C CNN
	1    2400 1400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR04
U 1 1 5D5F8A9A
P 2750 1400
F 0 "#PWR04" H 2750 1150 50  0001 C CNN
F 1 "GND" H 2755 1227 50  0000 C CNN
F 2 "" H 2750 1400 50  0001 C CNN
F 3 "" H 2750 1400 50  0001 C CNN
	1    2750 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	2750 1400 2750 1300
Wire Wire Line
	2400 1300 2400 1400
Text GLabel 3400 950  2    50   Input ~ 0
12V_VCC
Wire Wire Line
	3400 950  3150 950 
Connection ~ 2750 950 
$Comp
L Device:C C5
U 1 1 5D6028A9
P 3150 1150
F 0 "C5" H 3265 1196 50  0000 L CNN
F 1 "10n" H 3265 1105 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3188 1000 50  0001 C CNN
F 3 "~" H 3150 1150 50  0001 C CNN
	1    3150 1150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR05
U 1 1 5D602F7E
P 3150 1450
F 0 "#PWR05" H 3150 1200 50  0001 C CNN
F 1 "GND" H 3155 1277 50  0000 C CNN
F 2 "" H 3150 1450 50  0001 C CNN
F 3 "" H 3150 1450 50  0001 C CNN
	1    3150 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3150 1450 3150 1300
Wire Wire Line
	3150 1000 3150 950 
Connection ~ 3150 950 
Wire Wire Line
	3150 950  2750 950 
Wire Notes Line
	500  500  3850 500 
Wire Notes Line
	3850 500  3850 1900
Wire Notes Line
	3850 1900 500  1900
Wire Notes Line
	500  1900 500  500 
$Comp
L Regulator_Linear:AMS1117-3.3 U3
U 1 1 5D614B71
P 4850 1050
F 0 "U3" H 4850 1292 50  0000 C CNN
F 1 "AMS1117-3.3" H 4850 1201 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223-3_TabPin2" H 4850 1250 50  0001 C CNN
F 3 "http://www.advanced-monolithic.com/pdf/ds1117.pdf" H 4950 800 50  0001 C CNN
	1    4850 1050
	1    0    0    -1  
$EndComp
$Comp
L Device:C C6
U 1 1 5D61C228
P 4350 1350
F 0 "C6" H 4236 1396 50  0000 R CNN
F 1 "10u" H 4236 1305 50  0000 R CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4388 1200 50  0001 C CNN
F 3 "~" H 4350 1350 50  0001 C CNN
	1    4350 1350
	1    0    0    -1  
$EndComp
$Comp
L Device:C C7
U 1 1 5D61D515
P 5350 1350
F 0 "C7" H 5236 1396 50  0000 R CNN
F 1 "22u" H 5236 1305 50  0000 R CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 5388 1200 50  0001 C CNN
F 3 "~" H 5350 1350 50  0001 C CNN
	1    5350 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 1200 4350 1050
Wire Wire Line
	4350 1050 4550 1050
Wire Wire Line
	5350 1200 5350 1050
Wire Wire Line
	5350 1050 5150 1050
$Comp
L power:GND #PWR06
U 1 1 5D6204D0
P 4350 1650
F 0 "#PWR06" H 4350 1400 50  0001 C CNN
F 1 "GND" H 4355 1477 50  0000 C CNN
F 2 "" H 4350 1650 50  0001 C CNN
F 3 "" H 4350 1650 50  0001 C CNN
	1    4350 1650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR07
U 1 1 5D621691
P 5350 1650
F 0 "#PWR07" H 5350 1400 50  0001 C CNN
F 1 "GND" H 5355 1477 50  0000 C CNN
F 2 "" H 5350 1650 50  0001 C CNN
F 3 "" H 5350 1650 50  0001 C CNN
	1    5350 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 1500 4350 1650
Wire Wire Line
	5350 1650 5350 1600
Text GLabel 4350 950  1    50   Input ~ 0
12V_VCC
Wire Wire Line
	4350 950  4350 1050
Connection ~ 4350 1050
Text GLabel 5350 950  1    50   Input ~ 0
3.3V_MCU
Wire Wire Line
	5350 950  5350 1050
Connection ~ 5350 1050
Wire Notes Line
	3900 500  3900 1900
Wire Notes Line
	3900 1900 5700 1900
Wire Notes Line
	5700 1900 5700 500 
Wire Notes Line
	5700 500  3900 500 
$Comp
L Driver_FET:ZXGD3009E6 U4
U 1 1 5D633BA2
P 6750 1100
F 0 "U4" H 6450 1500 50  0000 C CNN
F 1 "ZXGD3009E6" H 6450 1400 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-6" H 6750 600 50  0001 C CNN
F 3 "https://www.diodes.com/assets/Datasheets/ZXGD3009E6.pdf" H 6400 1350 50  0001 C CNN
	1    6750 1100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR010
U 1 1 5D634D23
P 6750 1550
F 0 "#PWR010" H 6750 1300 50  0001 C CNN
F 1 "GND" H 6755 1377 50  0000 C CNN
F 2 "" H 6750 1550 50  0001 C CNN
F 3 "" H 6750 1550 50  0001 C CNN
	1    6750 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	6750 1400 6750 1550
Text GLabel 6850 650  2    50   Input ~ 0
12V_VCC
Wire Wire Line
	6850 650  6750 650 
Wire Wire Line
	6750 650  6750 800 
Wire Notes Line
	5750 500  5750 1900
Wire Wire Line
	7250 1000 7350 1000
Wire Wire Line
	7350 1000 7350 1100
Wire Wire Line
	7350 1200 7250 1200
Text GLabel 6000 1250 3    50   Input ~ 0
MCU_Gate
Wire Wire Line
	6000 1250 6000 1100
Wire Wire Line
	6000 1100 6250 1100
Wire Notes Line
	7950 500  7950 1900
Wire Notes Line
	5750 1900 7950 1900
Text Notes 600  650  0    50   ~ 0
Input Stage
Text Notes 4650 650  0    50   ~ 0
3.3V Supply
Text Notes 5800 650  0    50   ~ 0
MOSFET Gate Drive
$Comp
L Device:R R3
U 1 1 5D651891
P 8350 850
F 0 "R3" H 8420 896 50  0000 L CNN
F 1 "10k" H 8420 805 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 8280 850 50  0001 C CNN
F 3 "~" H 8350 850 50  0001 C CNN
	1    8350 850 
	1    0    0    -1  
$EndComp
$Comp
L Device:R R4
U 1 1 5D653961
P 8350 1350
F 0 "R4" H 8280 1396 50  0000 R CNN
F 1 "3.3k" H 8280 1305 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 8280 1350 50  0001 C CNN
F 3 "~" H 8350 1350 50  0001 C CNN
	1    8350 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	8350 1000 8350 1100
$Comp
L Device:C C9
U 1 1 5D654A92
P 8750 1350
F 0 "C9" H 9000 1400 50  0000 R CNN
F 1 "10n" H 9050 1300 50  0000 R CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 8788 1200 50  0001 C CNN
F 3 "~" H 8750 1350 50  0001 C CNN
	1    8750 1350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR011
U 1 1 5D657513
P 8350 1650
F 0 "#PWR011" H 8350 1400 50  0001 C CNN
F 1 "GND" H 8355 1477 50  0000 C CNN
F 2 "" H 8350 1650 50  0001 C CNN
F 3 "" H 8350 1650 50  0001 C CNN
	1    8350 1650
	1    0    0    -1  
$EndComp
Text GLabel 8500 600  2    50   Input ~ 0
12V_VCC
Wire Wire Line
	8500 600  8350 600 
Wire Wire Line
	8350 600  8350 700 
Wire Wire Line
	8350 1500 8350 1650
$Comp
L power:GND #PWR013
U 1 1 5D65A044
P 8750 1650
F 0 "#PWR013" H 8750 1400 50  0001 C CNN
F 1 "GND" H 8755 1477 50  0000 C CNN
F 2 "" H 8750 1650 50  0001 C CNN
F 3 "" H 8750 1650 50  0001 C CNN
	1    8750 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	8750 1650 8750 1500
Wire Wire Line
	8750 1200 8750 1100
Wire Wire Line
	8750 1100 8350 1100
Connection ~ 8350 1100
Wire Wire Line
	8350 1100 8350 1200
$Comp
L Diode:BZX84Cxx D3
U 1 1 5D6615FB
P 9150 1350
AR Path="/5D6615FB" Ref="D3"  Part="1" 
AR Path="/5CC51090/5D6615FB" Ref="D?"  Part="1" 
AR Path="/5CC9490C/5D6615FB" Ref="D?"  Part="1" 
AR Path="/5CC41C15/5D6615FB" Ref="D?"  Part="1" 
F 0 "D3" V 9104 1429 50  0000 L CNN
F 1 "BZX84C3V6" V 9195 1429 50  0000 L CNN
F 2 "Diode_SMD:D_SOT-23_ANK" H 9150 1175 50  0001 C CNN
F 3 "https://diotec.com/tl_files/diotec/files/pdf/datasheets/bzx84c2v4.pdf" H 9150 1350 50  0001 C CNN
	1    9150 1350
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR016
U 1 1 5D663F77
P 9150 1650
F 0 "#PWR016" H 9150 1400 50  0001 C CNN
F 1 "GND" H 9155 1477 50  0000 C CNN
F 2 "" H 9150 1650 50  0001 C CNN
F 3 "" H 9150 1650 50  0001 C CNN
	1    9150 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	9150 1650 9150 1500
Wire Wire Line
	9150 1200 9150 1100
Wire Wire Line
	9150 1100 8750 1100
Connection ~ 8750 1100
Text Notes 8650 850  0    60   ~ 0
Input Voltage Measurement
Text GLabel 9400 1100 2    50   Input ~ 0
ADC_VIN
Wire Wire Line
	9400 1100 9150 1100
Connection ~ 9150 1100
Wire Notes Line
	9950 500  9950 1900
Wire Notes Line
	9950 1900 8000 1900
Wire Notes Line
	8000 1900 8000 500 
Wire Notes Line
	8000 500  9950 500 
Wire Notes Line
	7950 500  5750 500 
Connection ~ 8350 2550
Wire Wire Line
	9150 2550 8750 2550
Wire Wire Line
	8750 2650 8750 2550
$Comp
L Device:R R5
U 1 1 5D66CE59
P 8350 2300
F 0 "R5" H 8420 2346 50  0000 L CNN
F 1 "10k" H 8420 2255 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 8280 2300 50  0001 C CNN
F 3 "~" H 8350 2300 50  0001 C CNN
	1    8350 2300
	1    0    0    -1  
$EndComp
Connection ~ 9150 2550
Wire Notes Line
	9950 3350 8000 3350
$Comp
L Device:R R6
U 1 1 5D66CE69
P 8350 2800
F 0 "R6" H 8280 2846 50  0000 R CNN
F 1 "3.3k" H 8280 2755 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 8280 2800 50  0001 C CNN
F 3 "~" H 8350 2800 50  0001 C CNN
	1    8350 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	8750 3100 8750 2950
Text GLabel 8500 2050 2    50   Input ~ 0
OUT-
$Comp
L power:GND #PWR017
U 1 1 5D66CE78
P 9150 3100
F 0 "#PWR017" H 9150 2850 50  0001 C CNN
F 1 "GND" H 9155 2927 50  0000 C CNN
F 2 "" H 9150 3100 50  0001 C CNN
F 3 "" H 9150 3100 50  0001 C CNN
	1    9150 3100
	1    0    0    -1  
$EndComp
Connection ~ 8750 2550
Wire Notes Line
	8000 1950 9950 1950
$Comp
L power:GND #PWR014
U 1 1 5D66CE87
P 8750 3100
F 0 "#PWR014" H 8750 2850 50  0001 C CNN
F 1 "GND" H 8755 2927 50  0000 C CNN
F 2 "" H 8750 3100 50  0001 C CNN
F 3 "" H 8750 3100 50  0001 C CNN
	1    8750 3100
	1    0    0    -1  
$EndComp
Wire Notes Line
	8000 3350 8000 1950
Wire Wire Line
	9150 2650 9150 2550
$Comp
L power:GND #PWR012
U 1 1 5D66CE96
P 8350 3100
F 0 "#PWR012" H 8350 2850 50  0001 C CNN
F 1 "GND" H 8355 2927 50  0000 C CNN
F 2 "" H 8350 3100 50  0001 C CNN
F 3 "" H 8350 3100 50  0001 C CNN
	1    8350 3100
	1    0    0    -1  
$EndComp
$Comp
L Diode:BZX84Cxx D4
U 1 1 5D66CEA4
P 9150 2800
AR Path="/5D66CEA4" Ref="D4"  Part="1" 
AR Path="/5CC51090/5D66CEA4" Ref="D?"  Part="1" 
AR Path="/5CC9490C/5D66CEA4" Ref="D?"  Part="1" 
AR Path="/5CC41C15/5D66CEA4" Ref="D?"  Part="1" 
F 0 "D4" V 9104 2879 50  0000 L CNN
F 1 "BZX84C3V6" V 9195 2879 50  0000 L CNN
F 2 "Diode_SMD:D_SOT-23_ANK" H 9150 2625 50  0001 C CNN
F 3 "https://diotec.com/tl_files/diotec/files/pdf/datasheets/bzx84c2v4.pdf" H 9150 2800 50  0001 C CNN
	1    9150 2800
	0    1    1    0   
$EndComp
Wire Wire Line
	8350 2550 8350 2650
Wire Wire Line
	8500 2050 8350 2050
Wire Notes Line
	9950 1950 9950 3350
Wire Wire Line
	8750 2550 8350 2550
Wire Wire Line
	8350 2450 8350 2550
$Comp
L Device:C C10
U 1 1 5D66CEB7
P 8750 2800
F 0 "C10" H 9000 2850 50  0000 R CNN
F 1 "10n" H 9050 2750 50  0000 R CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 8788 2650 50  0001 C CNN
F 3 "~" H 8750 2800 50  0001 C CNN
	1    8750 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	9150 3100 9150 2950
Wire Wire Line
	8350 2950 8350 3100
Text GLabel 9400 2550 2    50   Input ~ 0
ADC_Pulse
Wire Wire Line
	9400 2550 9150 2550
Text Notes 8650 2300 0    60   ~ 0
Auto Pulse Section
Wire Wire Line
	8350 2050 8350 2150
$Comp
L Connector:Screw_Terminal_01x02 J6
U 1 1 5D67F6D2
P 5950 2650
F 0 "J6" H 5868 2867 50  0000 C CNN
F 1 "Foot_Switch" H 5868 2776 50  0000 C CNN
F 2 "Connector_Molex:Molex_KK-254_AE-6410-02A_1x02_P2.54mm_Vertical" H 5950 2650 50  0001 C CNN
F 3 "~" H 5950 2650 50  0001 C CNN
	1    5950 2650
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 5D68268F
P 6450 2650
F 0 "R1" V 6243 2650 50  0000 C CNN
F 1 "1k" V 6334 2650 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 6380 2650 50  0001 C CNN
F 3 "~" H 6450 2650 50  0001 C CNN
	1    6450 2650
	0    1    1    0   
$EndComp
Wire Wire Line
	6150 2650 6300 2650
$Comp
L Device:R R2
U 1 1 5D68626B
P 6700 2300
F 0 "R2" H 6769 2254 50  0000 L CNN
F 1 "100k" H 6769 2345 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 6630 2300 50  0001 C CNN
F 3 "~" H 6700 2300 50  0001 C CNN
	1    6700 2300
	-1   0    0    1   
$EndComp
Text GLabel 6800 2050 2    50   Input ~ 0
3.3V_MCU
Wire Wire Line
	6800 2050 6700 2050
Wire Wire Line
	6700 2050 6700 2150
$Comp
L Device:C C8
U 1 1 5D690B32
P 6700 2950
F 0 "C8" H 6950 3000 50  0000 R CNN
F 1 "10n" H 7000 2900 50  0000 R CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 6738 2800 50  0001 C CNN
F 3 "~" H 6700 2950 50  0001 C CNN
	1    6700 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	6700 2800 6700 2650
Wire Wire Line
	6700 2650 6600 2650
Wire Wire Line
	6700 2450 6700 2650
Connection ~ 6700 2650
$Comp
L power:GND #PWR08
U 1 1 5D69722C
P 6250 2950
F 0 "#PWR08" H 6250 2700 50  0001 C CNN
F 1 "GND" H 6255 2777 50  0000 C CNN
F 2 "" H 6250 2950 50  0001 C CNN
F 3 "" H 6250 2950 50  0001 C CNN
	1    6250 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	6250 2950 6250 2750
Wire Wire Line
	6250 2750 6150 2750
$Comp
L power:GND #PWR09
U 1 1 5D6A678D
P 6700 3250
F 0 "#PWR09" H 6700 3000 50  0001 C CNN
F 1 "GND" H 6705 3077 50  0000 C CNN
F 2 "" H 6700 3250 50  0001 C CNN
F 3 "" H 6700 3250 50  0001 C CNN
	1    6700 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	6700 3250 6700 3100
Text GLabel 7000 2650 2    50   Input ~ 0
Foot_Switch
Wire Wire Line
	7000 2650 6700 2650
Wire Notes Line
	5750 1950 5750 3500
Wire Notes Line
	5750 3500 7950 3500
Wire Notes Line
	7950 3500 7950 1950
Wire Notes Line
	5750 1950 7950 1950
Text Notes 8800 3650 2    60   ~ 0
Rotary Encoder
Text Notes 7600 2400 2    60   ~ 0
Foot Switch
$Comp
L Device:Rotary_Encoder_Switch SW1
U 1 1 5D6CB9FA
P 9250 5200
F 0 "SW1" V 9204 5430 50  0000 L CNN
F 1 "RE" V 9295 5430 50  0000 L CNN
F 2 "Rotary_Encoder:RotaryEncoder_Alps_EC12E-Switch_Vertical_H20mm_CircularMountingHoles" H 9100 5360 50  0001 C CNN
F 3 "~" H 9250 5460 50  0001 C CNN
	1    9250 5200
	0    1    1    0   
$EndComp
Text GLabel 10000 4650 2    50   Input ~ 0
3.3V_MCU
Text GLabel 8650 4650 0    50   Input ~ 0
3.3V_MCU
$Comp
L Device:R R7
U 1 1 5D6E1836
P 8900 4650
F 0 "R7" V 9107 4650 50  0000 C CNN
F 1 "100k" V 9016 4650 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 8830 4650 50  0001 C CNN
F 3 "~" H 8900 4650 50  0001 C CNN
	1    8900 4650
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R10
U 1 1 5D6E8A49
P 9650 4650
F 0 "R10" V 9857 4650 50  0000 C CNN
F 1 "100k" V 9766 4650 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 9580 4650 50  0001 C CNN
F 3 "~" H 9650 4650 50  0001 C CNN
	1    9650 4650
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9050 4650 9150 4650
Wire Wire Line
	9150 4650 9150 4900
Wire Wire Line
	9500 4650 9350 4650
Wire Wire Line
	9350 4650 9350 4900
Wire Wire Line
	8650 4650 8750 4650
$Comp
L power:GND #PWR019
U 1 1 5D6FA046
P 9250 4800
F 0 "#PWR019" H 9250 4550 50  0001 C CNN
F 1 "GND" H 9255 4627 50  0000 C CNN
F 2 "" H 9250 4800 50  0001 C CNN
F 3 "" H 9250 4800 50  0001 C CNN
	1    9250 4800
	-1   0    0    1   
$EndComp
Wire Wire Line
	9250 4800 9250 4900
$Comp
L power:GND #PWR018
U 1 1 5D6FF4C6
P 9150 5600
F 0 "#PWR018" H 9150 5350 50  0001 C CNN
F 1 "GND" H 9155 5427 50  0000 C CNN
F 2 "" H 9150 5600 50  0001 C CNN
F 3 "" H 9150 5600 50  0001 C CNN
	1    9150 5600
	1    0    0    -1  
$EndComp
Wire Wire Line
	9150 5600 9150 5500
$Comp
L power:GND #PWR021
U 1 1 5D71A4DB
P 9900 6200
F 0 "#PWR021" H 9900 5950 50  0001 C CNN
F 1 "GND" H 9905 6027 50  0000 C CNN
F 2 "" H 9900 6200 50  0001 C CNN
F 3 "" H 9900 6200 50  0001 C CNN
	1    9900 6200
	1    0    0    -1  
$EndComp
Wire Wire Line
	9900 6200 9900 6050
Wire Wire Line
	9900 5750 9900 5600
Wire Wire Line
	9900 5400 9900 5600
Connection ~ 9900 5600
Wire Wire Line
	9350 5600 9500 5600
Text GLabel 10000 5600 2    50   Input ~ 0
Encoder_Switch
$Comp
L Device:C C13
U 1 1 5D71A4F2
P 9900 5900
F 0 "C13" H 10150 5950 50  0000 R CNN
F 1 "10n" H 10200 5850 50  0000 R CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 9938 5750 50  0001 C CNN
F 3 "~" H 9900 5900 50  0001 C CNN
	1    9900 5900
	1    0    0    -1  
$EndComp
$Comp
L Device:R R11
U 1 1 5D71A50E
P 9650 5600
F 0 "R11" V 9443 5600 50  0000 C CNN
F 1 "1k" V 9534 5600 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 9580 5600 50  0001 C CNN
F 3 "~" H 9650 5600 50  0001 C CNN
	1    9650 5600
	0    1    1    0   
$EndComp
Wire Wire Line
	10000 5600 9900 5600
Wire Wire Line
	9900 5600 9800 5600
$Comp
L Device:R R12
U 1 1 5D71A52D
P 9900 5250
F 0 "R12" H 9830 5204 50  0000 R CNN
F 1 "100k" H 9830 5295 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 9830 5250 50  0001 C CNN
F 3 "~" H 9900 5250 50  0001 C CNN
	1    9900 5250
	-1   0    0    1   
$EndComp
Wire Wire Line
	9350 5500 9350 5600
Wire Wire Line
	9800 4650 9900 4650
Wire Wire Line
	9900 4650 9900 5100
Connection ~ 9900 4650
Wire Wire Line
	9900 4650 10000 4650
$Comp
L Device:R R9
U 1 1 5D73541D
P 9350 4300
F 0 "R9" H 9200 4250 50  0000 L CNN
F 1 "1k" H 9200 4350 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 9280 4300 50  0001 C CNN
F 3 "~" H 9350 4300 50  0001 C CNN
	1    9350 4300
	-1   0    0    1   
$EndComp
$Comp
L Device:R R8
U 1 1 5D73A244
P 9150 4300
F 0 "R8" H 9219 4254 50  0000 L CNN
F 1 "1k" H 9219 4345 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 9080 4300 50  0001 C CNN
F 3 "~" H 9150 4300 50  0001 C CNN
	1    9150 4300
	-1   0    0    1   
$EndComp
Wire Wire Line
	9150 4450 9150 4650
Connection ~ 9150 4650
Wire Wire Line
	9350 4450 9350 4650
Connection ~ 9350 4650
$Comp
L Device:C C11
U 1 1 5D748090
P 8950 4050
F 0 "C11" V 9202 4050 50  0000 C CNN
F 1 "10n" V 9111 4050 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 8988 3900 50  0001 C CNN
F 3 "~" H 8950 4050 50  0001 C CNN
	1    8950 4050
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C12
U 1 1 5D73EF2F
P 9550 4050
F 0 "C12" V 9298 4050 50  0000 C CNN
F 1 "10n" V 9389 4050 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 9588 3900 50  0001 C CNN
F 3 "~" H 9550 4050 50  0001 C CNN
	1    9550 4050
	0    1    1    0   
$EndComp
Wire Wire Line
	9100 4050 9150 4050
Wire Wire Line
	9150 4050 9150 4150
Wire Wire Line
	9350 4150 9350 4050
Wire Wire Line
	9350 4050 9400 4050
$Comp
L power:GND #PWR020
U 1 1 5D759345
P 9750 4150
F 0 "#PWR020" H 9750 3900 50  0001 C CNN
F 1 "GND" H 9755 3977 50  0000 C CNN
F 2 "" H 9750 4150 50  0001 C CNN
F 3 "" H 9750 4150 50  0001 C CNN
	1    9750 4150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR015
U 1 1 5D75AB46
P 8750 4150
F 0 "#PWR015" H 8750 3900 50  0001 C CNN
F 1 "GND" H 8755 3977 50  0000 C CNN
F 2 "" H 8750 4150 50  0001 C CNN
F 3 "" H 8750 4150 50  0001 C CNN
	1    8750 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	9700 4050 9750 4050
Wire Wire Line
	9750 4050 9750 4150
Wire Wire Line
	8800 4050 8750 4050
Wire Wire Line
	8750 4050 8750 4150
Text GLabel 9150 3900 1    50   Input ~ 0
Encoder_B
Text GLabel 9350 3900 1    50   Input ~ 0
Encoder_A
Wire Wire Line
	9350 3900 9350 4050
Connection ~ 9350 4050
Wire Wire Line
	9150 3900 9150 4050
Connection ~ 9150 4050
Wire Notes Line
	8000 3400 10800 3400
Wire Notes Line
	10800 3400 10800 6450
Wire Notes Line
	10800 6450 8000 6450
Wire Notes Line
	8000 6450 8000 3400
$Comp
L Connector_Generic:Conn_01x04 J1
U 1 1 5D7821E5
P 5000 2650
F 0 "J1" H 5080 2642 50  0000 L CNN
F 1 "SSD1306" H 5080 2551 50  0000 L CNN
F 2 "Connector_Molex:Molex_KK-254_AE-6410-04A_1x04_P2.54mm_Vertical" H 5000 2650 50  0001 C CNN
F 3 "~" H 5000 2650 50  0001 C CNN
	1    5000 2650
	1    0    0    -1  
$EndComp
Text GLabel 4100 2850 0    50   Input ~ 0
SDA
Wire Wire Line
	4100 2850 4450 2850
Wire Notes Line
	5700 1950 5700 3500
Wire Notes Line
	5700 3500 3900 3500
Wire Notes Line
	3900 3500 3900 1950
Wire Notes Line
	3900 1950 5700 1950
Text GLabel 7600 1300 3    50   Input ~ 0
Gate_Drive
Wire Wire Line
	7600 1300 7600 1100
Wire Wire Line
	7600 1100 7350 1100
Connection ~ 7350 1100
Wire Wire Line
	7350 1100 7350 1200
$Sheet
S 6400 3800 1200 450 
U 5D9E2BB1
F0 "MOSFET_Array" 50
F1 "MOSFET_Array.sch" 50
$EndSheet
$Comp
L power:GND #PWR0105
U 1 1 5D9385C4
P 4850 1700
F 0 "#PWR0105" H 4850 1450 50  0001 C CNN
F 1 "GND" H 4855 1527 50  0000 C CNN
F 2 "" H 4850 1700 50  0001 C CNN
F 3 "" H 4850 1700 50  0001 C CNN
	1    4850 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 1700 4850 1350
$Comp
L Mechanical:MountingHole H3
U 1 1 5D9367B8
P 1200 5550
F 0 "H3" H 1300 5596 50  0000 L CNN
F 1 "MountingHole" H 1300 5505 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.5mm" H 1200 5550 50  0001 C CNN
F 3 "~" H 1200 5550 50  0001 C CNN
	1    1200 5550
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H4
U 1 1 5D937A6C
P 1200 5800
F 0 "H4" H 1300 5846 50  0000 L CNN
F 1 "MountingHole" H 1300 5755 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.5mm" H 1200 5800 50  0001 C CNN
F 3 "~" H 1200 5800 50  0001 C CNN
	1    1200 5800
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H5
U 1 1 5D9397FA
P 1200 6050
F 0 "H5" H 1300 6096 50  0000 L CNN
F 1 "MountingHole" H 1300 6005 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.5mm" H 1200 6050 50  0001 C CNN
F 3 "~" H 1200 6050 50  0001 C CNN
	1    1200 6050
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H6
U 1 1 5D93AEBC
P 1200 6300
F 0 "H6" H 1300 6346 50  0000 L CNN
F 1 "MountingHole" H 1300 6255 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.5mm" H 1200 6300 50  0001 C CNN
F 3 "~" H 1200 6300 50  0001 C CNN
	1    1200 6300
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 5DA83E12
P 5600 1350
F 0 "C1" H 5500 1450 50  0000 R CNN
F 1 "10u" H 5550 1200 50  0000 R CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 5638 1200 50  0001 C CNN
F 3 "~" H 5600 1350 50  0001 C CNN
	1    5600 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 1200 5600 1050
Wire Wire Line
	5600 1050 5350 1050
Wire Wire Line
	5600 1500 5600 1600
Wire Wire Line
	5600 1600 5350 1600
Connection ~ 5350 1600
Wire Wire Line
	5350 1600 5350 1500
Wire Wire Line
	4100 2750 4200 2750
Text GLabel 4100 2750 0    50   Input ~ 0
SCL
Wire Wire Line
	4300 2650 4800 2650
Wire Wire Line
	4300 3150 4300 2650
$Comp
L power:GND #PWR0101
U 1 1 5D78F79B
P 4300 3150
F 0 "#PWR0101" H 4300 2900 50  0001 C CNN
F 1 "GND" H 4305 2977 50  0000 C CNN
F 2 "" H 4300 3150 50  0001 C CNN
F 3 "" H 4300 3150 50  0001 C CNN
	1    4300 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4750 2550 4800 2550
Wire Wire Line
	4750 2200 4750 2550
Wire Wire Line
	4350 2200 4450 2200
Text GLabel 4350 2200 0    50   Input ~ 0
3.3V_MCU
$Comp
L Device:R R21
U 1 1 5DAFE2BC
P 4200 2450
F 0 "R21" H 4130 2496 50  0000 R CNN
F 1 "4.7k" H 4130 2405 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4130 2450 50  0001 C CNN
F 3 "~" H 4200 2450 50  0001 C CNN
	1    4200 2450
	1    0    0    -1  
$EndComp
$Comp
L Device:R R22
U 1 1 5DB04CA4
P 4450 2450
F 0 "R22" H 4600 2500 50  0000 R CNN
F 1 "4.7k" H 4700 2400 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4380 2450 50  0001 C CNN
F 3 "~" H 4450 2450 50  0001 C CNN
	1    4450 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 2600 4200 2750
Connection ~ 4200 2750
Wire Wire Line
	4200 2750 4800 2750
Wire Wire Line
	4450 2600 4450 2850
Connection ~ 4450 2850
Wire Wire Line
	4450 2850 4800 2850
Wire Wire Line
	4450 2300 4200 2300
Wire Wire Line
	4450 2300 4450 2200
Connection ~ 4450 2300
Connection ~ 4450 2200
Wire Wire Line
	4450 2200 4750 2200
Text GLabel 2600 2800 2    50   Input ~ 0
SCL
Text GLabel 2600 2700 2    50   Input ~ 0
SDA
$Comp
L power:GND #PWR0107
U 1 1 5D97C258
P 2050 3250
F 0 "#PWR0107" H 2050 3000 50  0001 C CNN
F 1 "GND" H 2055 3077 50  0000 C CNN
F 2 "" H 2050 3250 50  0001 C CNN
F 3 "" H 2050 3250 50  0001 C CNN
	1    2050 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	2050 3250 2050 3150
Text GLabel 1950 2350 0    50   Input ~ 0
3.3V_MCU
Wire Wire Line
	1950 2350 2050 2350
Wire Wire Line
	2050 2350 2050 2500
Wire Wire Line
	2600 2700 2450 2700
Wire Wire Line
	2600 2800 2450 2800
Wire Wire Line
	2450 2900 2650 2900
Wire Wire Line
	2650 2900 2650 3150
Wire Wire Line
	2650 3150 2050 3150
Connection ~ 2050 3150
Wire Wire Line
	2050 3150 2050 3100
Text Notes 5000 2100 0    50   ~ 0
OLED
Wire Notes Line
	3850 1950 3850 3500
Wire Notes Line
	3850 3500 500  3500
Wire Notes Line
	500  3500 500  1950
Wire Notes Line
	500  1950 3850 1950
Text Notes 2200 2150 0    50   ~ 0
EEPROM
$Comp
L power:GND #PWR0108
U 1 1 5D9A77DD
P 4100 6950
F 0 "#PWR0108" H 4100 6700 50  0001 C CNN
F 1 "GND" H 4105 6777 50  0000 C CNN
F 2 "" H 4100 6950 50  0001 C CNN
F 3 "" H 4100 6950 50  0001 C CNN
	1    4100 6950
	1    0    0    -1  
$EndComp
Wire Wire Line
	4100 6950 4100 6800
$Comp
L Device:C C14
U 1 1 5D9B9BB9
P 3800 4850
F 0 "C14" H 4050 4900 50  0000 R CNN
F 1 "0.1u" H 4100 4800 50  0000 R CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3838 4700 50  0001 C CNN
F 3 "~" H 3800 4850 50  0001 C CNN
	1    3800 4850
	0    1    1    0   
$EndComp
$Comp
L Device:C C15
U 1 1 5D9C4B8A
P 4600 5050
F 0 "C15" H 4850 5100 50  0000 R CNN
F 1 "0.1u" H 4900 5000 50  0000 R CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 4638 4900 50  0001 C CNN
F 3 "~" H 4600 5050 50  0001 C CNN
	1    4600 5050
	0    -1   -1   0   
$EndComp
Text GLabel 4100 4350 1    50   Input ~ 0
3.3V_MCU
Wire Wire Line
	4100 4350 4100 4400
$Comp
L Device:Ferrite_Bead FB1
U 1 1 5D9C376A
P 4350 4600
F 0 "FB1" H 4487 4646 50  0000 L CNN
F 1 "Ferrite_Bead" H 4487 4555 50  0000 L CNN
F 2 "Inductor_SMD:L_0603_1608Metric" V 4280 4600 50  0001 C CNN
F 3 "~" H 4350 4600 50  0001 C CNN
	1    4350 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	3950 4850 4100 4850
Connection ~ 4100 4850
Wire Wire Line
	4100 4850 4100 5300
Wire Wire Line
	4350 4750 4350 5050
Wire Wire Line
	4350 5050 4450 5050
Wire Wire Line
	4200 5300 4200 5050
Wire Wire Line
	4200 5050 4350 5050
Connection ~ 4350 5050
Wire Wire Line
	4350 4450 4350 4400
Wire Wire Line
	4350 4400 4100 4400
Connection ~ 4100 4400
Wire Wire Line
	4100 4400 4100 4850
$Comp
L power:GND #PWR0109
U 1 1 5D9CDA58
P 3400 5050
F 0 "#PWR0109" H 3400 4800 50  0001 C CNN
F 1 "GND" H 3405 4877 50  0000 C CNN
F 2 "" H 3400 5050 50  0001 C CNN
F 3 "" H 3400 5050 50  0001 C CNN
	1    3400 5050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 5050 3400 4850
Wire Wire Line
	3400 4850 3650 4850
$Comp
L power:GND #PWR0110
U 1 1 5D9D1B93
P 4900 5200
F 0 "#PWR0110" H 4900 4950 50  0001 C CNN
F 1 "GND" H 4905 5027 50  0000 C CNN
F 2 "" H 4900 5200 50  0001 C CNN
F 3 "" H 4900 5200 50  0001 C CNN
	1    4900 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 5200 4900 5050
Wire Wire Line
	4900 5050 4750 5050
$Comp
L power:GND #PWR0111
U 1 1 5D9D722B
P 3400 5850
F 0 "#PWR0111" H 3400 5600 50  0001 C CNN
F 1 "GND" H 3405 5677 50  0000 C CNN
F 2 "" H 3400 5850 50  0001 C CNN
F 3 "" H 3400 5850 50  0001 C CNN
	1    3400 5850
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 5850 3400 5700
Wire Wire Line
	3400 5700 3600 5700
$Comp
L Device:C C2
U 1 1 5D9D8D46
P 2900 5700
F 0 "C2" H 3150 5750 50  0000 R CNN
F 1 "1u" H 3200 5650 50  0000 R CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2938 5550 50  0001 C CNN
F 3 "~" H 2900 5700 50  0001 C CNN
	1    2900 5700
	1    0    0    -1  
$EndComp
$Comp
L Device:R R23
U 1 1 5D9DBB04
P 2900 5200
F 0 "R23" H 2969 5154 50  0000 L CNN
F 1 "10k" H 2969 5245 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 2830 5200 50  0001 C CNN
F 3 "~" H 2900 5200 50  0001 C CNN
	1    2900 5200
	-1   0    0    1   
$EndComp
Wire Wire Line
	2900 5350 2900 5500
Wire Wire Line
	3600 5500 2900 5500
Connection ~ 2900 5500
Wire Wire Line
	2900 5500 2900 5550
$Comp
L power:GND #PWR0112
U 1 1 5D9E4275
P 2900 6000
F 0 "#PWR0112" H 2900 5750 50  0001 C CNN
F 1 "GND" H 2905 5827 50  0000 C CNN
F 2 "" H 2900 6000 50  0001 C CNN
F 3 "" H 2900 6000 50  0001 C CNN
	1    2900 6000
	1    0    0    -1  
$EndComp
Wire Wire Line
	2900 6000 2900 5850
Text GLabel 2900 4900 1    50   Input ~ 0
3.3V_MCU
Wire Wire Line
	2900 4900 2900 5050
Text GLabel 4850 6200 2    50   Input ~ 0
Encoder_B
Wire Wire Line
	4850 6000 4600 6000
Wire Wire Line
	4850 6100 4600 6100
Text GLabel 4850 6100 2    50   Input ~ 0
Encoder_A
Wire Wire Line
	4850 6200 4600 6200
Text GLabel 4850 5500 2    50   Input ~ 0
ADC_Pulse
Text GLabel 4850 6000 2    50   Input ~ 0
ADC_VIN
Wire Wire Line
	4850 5500 4600 5500
Wire Wire Line
	4600 5600 4850 5600
Text GLabel 4850 5600 2    50   Input ~ 0
MCU_Gate
Wire Wire Line
	3350 6600 3600 6600
Text GLabel 4850 5900 2    50   Input ~ 0
Foot_Switch
Wire Wire Line
	4850 5800 4600 5800
Text GLabel 4850 6400 2    50   Input ~ 0
SDA
Wire Wire Line
	4850 6400 4600 6400
Text GLabel 4850 6300 2    50   Input ~ 0
SCL
Wire Wire Line
	4850 6300 4600 6300
Text GLabel 4850 6500 2    50   Input ~ 0
SWDIO
Text GLabel 4850 6600 2    50   Input ~ 0
SWCLK
Wire Wire Line
	4850 6500 4600 6500
Wire Wire Line
	4850 6600 4600 6600
$Comp
L Connector_Generic:Conn_01x03 J2
U 1 1 5DA6E6C4
P 1750 4150
F 0 "J2" H 1668 4467 50  0000 C CNN
F 1 "Debug" H 1668 4376 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x03_P2.54mm_Vertical" H 1750 4150 50  0001 C CNN
F 3 "~" H 1750 4150 50  0001 C CNN
	1    1750 4150
	-1   0    0    -1  
$EndComp
Text GLabel 2200 4150 2    50   Input ~ 0
SWCLK
Text GLabel 2200 4050 2    50   Input ~ 0
SWDIO
Wire Wire Line
	2200 4050 1950 4050
Wire Wire Line
	2200 4150 1950 4150
$Comp
L power:GND #PWR0113
U 1 1 5DA7AF9C
P 2100 4400
F 0 "#PWR0113" H 2100 4150 50  0001 C CNN
F 1 "GND" H 2105 4227 50  0000 C CNN
F 2 "" H 2100 4400 50  0001 C CNN
F 3 "" H 2100 4400 50  0001 C CNN
	1    2100 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	1950 4250 2100 4250
Wire Wire Line
	2100 4250 2100 4400
NoConn ~ 3600 6300
NoConn ~ 3600 6400
Text Label 4200 5050 0    50   ~ 0
VDDA
Wire Wire Line
	6800 6150 6800 5850
$Comp
L power:PWR_FLAG #FLG0103
U 1 1 5DAB7ACC
P 6800 6150
F 0 "#FLG0103" H 6800 6225 50  0001 C CNN
F 1 "PWR_FLAG" H 6800 6323 50  0000 C CNN
F 2 "" H 6800 6150 50  0001 C CNN
F 3 "~" H 6800 6150 50  0001 C CNN
	1    6800 6150
	-1   0    0    1   
$EndComp
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 5DA8D4A6
P 7700 6000
F 0 "#FLG0101" H 7700 6075 50  0001 C CNN
F 1 "PWR_FLAG" H 7700 6173 50  0000 C CNN
F 2 "" H 7700 6000 50  0001 C CNN
F 3 "~" H 7700 6000 50  0001 C CNN
	1    7700 6000
	1    0    0    -1  
$EndComp
Wire Wire Line
	6300 5850 6400 5850
$Comp
L power:GND #PWR0114
U 1 1 5DA9B454
P 7700 6150
F 0 "#PWR0114" H 7700 5900 50  0001 C CNN
F 1 "GND" H 7705 5977 50  0000 C CNN
F 2 "" H 7700 6150 50  0001 C CNN
F 3 "" H 7700 6150 50  0001 C CNN
	1    7700 6150
	1    0    0    -1  
$EndComp
Wire Wire Line
	7700 6150 7700 6000
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 5DAA85D7
P 7250 6150
F 0 "#FLG0102" H 7250 6225 50  0001 C CNN
F 1 "PWR_FLAG" H 7250 6323 50  0000 C CNN
F 2 "" H 7250 6150 50  0001 C CNN
F 3 "~" H 7250 6150 50  0001 C CNN
	1    7250 6150
	-1   0    0    1   
$EndComp
Text Label 6400 5850 0    50   ~ 0
VDDA
Text GLabel 6800 5850 2    50   Input ~ 0
12V_VCC
Wire Wire Line
	7250 6150 7250 5900
$Comp
L power:PWR_FLAG #FLG0104
U 1 1 5DABC631
P 6300 6150
F 0 "#FLG0104" H 6300 6225 50  0001 C CNN
F 1 "PWR_FLAG" H 6300 6323 50  0000 C CNN
F 2 "" H 6300 6150 50  0001 C CNN
F 3 "~" H 6300 6150 50  0001 C CNN
	1    6300 6150
	-1   0    0    1   
$EndComp
$Comp
L power:+12V #PWR0115
U 1 1 5DA9FE05
P 7250 5900
F 0 "#PWR0115" H 7250 5750 50  0001 C CNN
F 1 "+12V" H 7265 6073 50  0000 C CNN
F 2 "" H 7250 5900 50  0001 C CNN
F 3 "" H 7250 5900 50  0001 C CNN
	1    7250 5900
	1    0    0    -1  
$EndComp
Wire Wire Line
	6300 6150 6300 5850
Wire Notes Line
	7950 6450 7950 5600
Wire Notes Line
	7950 5600 6000 5600
Wire Notes Line
	6000 5600 6000 6450
Wire Notes Line
	6000 6450 7950 6450
Text Notes 6750 5700 2    60   ~ 0
Power Flags
Text GLabel 3350 6600 0    50   Input ~ 0
Encoder_Switch
Wire Wire Line
	4850 5700 4600 5700
Wire Wire Line
	4850 5900 4600 5900
NoConn ~ 4850 5800
NoConn ~ 4850 5700
$Comp
L Memory_EEPROM:24LC64 U12
U 1 1 5DA8B716
P 2050 2800
F 0 "U12" H 2050 3281 50  0000 C CNN
F 1 "24LC64" H 2050 3190 50  0000 C CNN
F 2 "Package_SO:TSSOP-8_4.4x3mm_P0.65mm" H 2050 2800 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/21189f.pdf" H 2050 2800 50  0001 C CNN
	1    2050 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 2700 1500 2700
Wire Wire Line
	1500 2700 1500 2800
Wire Wire Line
	1500 3150 2050 3150
Wire Wire Line
	1650 2900 1500 2900
Connection ~ 1500 2900
Wire Wire Line
	1500 2900 1500 3150
Wire Wire Line
	1650 2800 1500 2800
Connection ~ 1500 2800
Wire Wire Line
	1500 2800 1500 2900
$EndSCHEMATC
