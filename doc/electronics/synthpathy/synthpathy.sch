EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Synthpathy schematics"
Date "2022-02-25"
Rev "1.0"
Comp ""
Comment1 "Author : B. Croix"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_RaspberryPi_and_Boards:Pico U1
U 1 1 6216ABB0
P 5850 4700
F 0 "U1" H 5850 5915 50  0000 C CNN
F 1 "Raspberry Pico" H 5850 5824 50  0000 C CNN
F 2 "RPi_Pico:RPi_Pico_SMD_TH" V 5850 4700 50  0001 C CNN
F 3 "" H 5850 4700 50  0001 C CNN
	1    5850 4700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR03
U 1 1 6218C59F
P 5150 3950
F 0 "#PWR03" H 5150 3700 50  0001 C CNN
F 1 "GND" V 5150 3850 50  0000 R CNN
F 2 "" H 5150 3950 50  0001 C CNN
F 3 "" H 5150 3950 50  0001 C CNN
	1    5150 3950
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR04
U 1 1 6218D0F7
P 7250 4000
F 0 "#PWR04" H 7250 3750 50  0001 C CNN
F 1 "GND" H 7400 3950 50  0000 C CNN
F 2 "" H 7250 4000 50  0001 C CNN
F 3 "" H 7250 4000 50  0001 C CNN
	1    7250 4000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR05
U 1 1 6218E7E5
P 5150 4450
F 0 "#PWR05" H 5150 4200 50  0001 C CNN
F 1 "GND" V 5150 4350 50  0000 R CNN
F 2 "" H 5150 4450 50  0001 C CNN
F 3 "" H 5150 4450 50  0001 C CNN
	1    5150 4450
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR07
U 1 1 6218EB56
P 5150 4950
F 0 "#PWR07" H 5150 4700 50  0001 C CNN
F 1 "GND" V 5155 4822 50  0000 R CNN
F 2 "" H 5150 4950 50  0001 C CNN
F 3 "" H 5150 4950 50  0001 C CNN
	1    5150 4950
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR09
U 1 1 6218EE49
P 5150 5450
F 0 "#PWR09" H 5150 5200 50  0001 C CNN
F 1 "GND" V 5155 5322 50  0000 R CNN
F 2 "" H 5150 5450 50  0001 C CNN
F 3 "" H 5150 5450 50  0001 C CNN
	1    5150 5450
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR010
U 1 1 6218F0D1
P 6550 5450
F 0 "#PWR010" H 6550 5200 50  0001 C CNN
F 1 "GND" V 6555 5322 50  0000 R CNN
F 2 "" H 6550 5450 50  0001 C CNN
F 3 "" H 6550 5450 50  0001 C CNN
	1    6550 5450
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR08
U 1 1 6218FDCB
P 6550 4950
F 0 "#PWR08" H 6550 4700 50  0001 C CNN
F 1 "GND" V 6555 4822 50  0000 R CNN
F 2 "" H 6550 4950 50  0001 C CNN
F 3 "" H 6550 4950 50  0001 C CNN
	1    6550 4950
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR06
U 1 1 6219289F
P 6550 4450
F 0 "#PWR06" H 6550 4200 50  0001 C CNN
F 1 "GND" V 6555 4322 50  0000 R CNN
F 2 "" H 6550 4450 50  0001 C CNN
F 3 "" H 6550 4450 50  0001 C CNN
	1    6550 4450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5150 4050 5050 4050
Wire Wire Line
	5150 4150 5050 4150
Wire Wire Line
	5150 4350 5050 4350
Wire Wire Line
	5150 4250 5050 4250
Text Label 5050 4050 2    50   ~ 0
audio_pwm_L
Text Label 5050 4150 2    50   ~ 0
audio_pwm_H
Text Label 5050 4350 2    50   ~ 0
midi_in
Text Label 5050 4250 2    50   ~ 0
midi_out
Wire Wire Line
	4650 5150 5150 5150
Wire Wire Line
	4700 5250 5150 5250
Wire Wire Line
	5150 5350 4750 5350
Wire Wire Line
	4800 5550 5150 5550
Wire Wire Line
	5150 5650 4850 5650
Wire Wire Line
	4650 5150 4650 6000
Wire Wire Line
	4700 5250 4700 6050
Wire Wire Line
	4750 5350 4750 6100
Wire Wire Line
	4800 5550 4800 6150
Wire Wire Line
	4850 5650 4850 6200
Wire Wire Line
	5150 3750 5050 3750
Wire Wire Line
	5050 3850 5150 3850
Text Notes 5000 3750 2    50   ~ 0
reserved
Text Notes 5000 3850 2    50   ~ 0
reserved
Wire Wire Line
	6550 5650 6650 5650
Wire Wire Line
	6650 5550 6550 5550
Wire Wire Line
	6650 5350 6550 5350
Wire Wire Line
	6650 5250 6550 5250
Text Notes 6700 5650 0    50   ~ 0
reserved
Text Notes 6700 5550 0    50   ~ 0
reserved
Text Notes 6700 5350 0    50   ~ 0
reserved
Text Notes 6700 5250 0    50   ~ 0
reserved
$Comp
L Device:LED D3
U 1 1 6233D7E9
P 8000 5450
F 0 "D3" H 7993 5195 50  0000 C CNN
F 1 "LED0" H 7993 5286 50  0000 C CNN
F 2 "" H 8000 5450 50  0001 C CNN
F 3 "~" H 8000 5450 50  0001 C CNN
	1    8000 5450
	-1   0    0    1   
$EndComp
$Comp
L Device:R R3
U 1 1 6233DDBF
P 7650 5450
F 0 "R3" V 7443 5450 50  0000 C CNN
F 1 "100k" V 7534 5450 50  0000 C CNN
F 2 "" V 7580 5450 50  0001 C CNN
F 3 "~" H 7650 5450 50  0001 C CNN
	1    7650 5450
	0    1    1    0   
$EndComp
Wire Wire Line
	7800 5450 7850 5450
$Comp
L power:GND #PWR011
U 1 1 62352B09
P 8200 5500
F 0 "#PWR011" H 8200 5250 50  0001 C CNN
F 1 "GND" H 8205 5327 50  0000 C CNN
F 2 "" H 8200 5500 50  0001 C CNN
F 3 "" H 8200 5500 50  0001 C CNN
	1    8200 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	8150 5450 8200 5450
Wire Wire Line
	8200 5450 8200 5500
$Comp
L Device:LED D2
U 1 1 6235A950
P 8000 5050
F 0 "D2" H 7993 4795 50  0000 C CNN
F 1 "LED1" H 7993 4886 50  0000 C CNN
F 2 "" H 8000 5050 50  0001 C CNN
F 3 "~" H 8000 5050 50  0001 C CNN
	1    8000 5050
	-1   0    0    1   
$EndComp
$Comp
L Device:LED D1
U 1 1 62361C7E
P 8000 4650
F 0 "D1" H 7993 4395 50  0000 C CNN
F 1 "LED2" H 7993 4486 50  0000 C CNN
F 2 "" H 8000 4650 50  0001 C CNN
F 3 "~" H 8000 4650 50  0001 C CNN
	1    8000 4650
	-1   0    0    1   
$EndComp
Wire Wire Line
	8150 4650 8200 4650
Wire Wire Line
	8200 4650 8200 5050
Connection ~ 8200 5450
Wire Wire Line
	8150 5050 8200 5050
Connection ~ 8200 5050
Wire Wire Line
	8200 5050 8200 5450
Wire Wire Line
	7500 5050 6550 5050
Wire Wire Line
	7800 4650 7850 4650
Wire Wire Line
	7800 5050 7850 5050
$Comp
L Device:R R2
U 1 1 62380B0B
P 7650 5050
F 0 "R2" V 7443 5050 50  0000 C CNN
F 1 "100k" V 7534 5050 50  0000 C CNN
F 2 "" V 7580 5050 50  0001 C CNN
F 3 "~" H 7650 5050 50  0001 C CNN
	1    7650 5050
	0    1    1    0   
$EndComp
$Comp
L Device:R R1
U 1 1 62380F3D
P 7650 4650
F 0 "R1" V 7443 4650 50  0000 C CNN
F 1 "100k" V 7534 4650 50  0000 C CNN
F 2 "" V 7580 4650 50  0001 C CNN
F 3 "~" H 7650 4650 50  0001 C CNN
	1    7650 4650
	0    1    1    0   
$EndComp
Wire Wire Line
	7450 5150 7450 5450
Wire Wire Line
	7450 5450 7500 5450
Wire Wire Line
	6550 5150 7450 5150
Wire Wire Line
	7450 4650 7450 4850
Wire Wire Line
	7450 4650 7500 4650
Wire Wire Line
	6550 4850 7450 4850
NoConn ~ 6650 5650
NoConn ~ 6650 5550
NoConn ~ 6650 5350
NoConn ~ 6650 5250
NoConn ~ 5050 3850
NoConn ~ 5050 3750
Wire Wire Line
	6550 4750 6650 4750
NoConn ~ 6650 4750
Wire Wire Line
	5750 5850 5750 5950
Wire Wire Line
	5850 5850 5850 5950
Wire Wire Line
	5950 5850 5950 5950
NoConn ~ 5950 5950
NoConn ~ 5850 5950
NoConn ~ 5750 5950
Wire Wire Line
	6550 4050 6650 4050
NoConn ~ 6650 4050
Wire Wire Line
	6550 3850 6650 3850
Wire Wire Line
	6550 3750 6650 3750
Wire Wire Line
	6950 3750 6950 3700
Connection ~ 6650 3750
Wire Wire Line
	6550 4250 6650 4250
NoConn ~ 6650 4250
Wire Wire Line
	6650 3850 6650 3750
$Comp
L power:+3.3V #PWR02
U 1 1 624217A0
P 7550 3700
F 0 "#PWR02" H 7550 3550 50  0001 C CNN
F 1 "+3.3V" H 7565 3873 50  0000 C CNN
F 2 "" H 7550 3700 50  0001 C CNN
F 3 "" H 7550 3700 50  0001 C CNN
	1    7550 3700
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR01
U 1 1 62421EDB
P 6950 3700
F 0 "#PWR01" H 6950 3550 50  0001 C CNN
F 1 "+5V" H 6965 3873 50  0000 C CNN
F 2 "" H 6950 3700 50  0001 C CNN
F 3 "" H 6950 3700 50  0001 C CNN
	1    6950 3700
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG01
U 1 1 6249888C
P 6650 3700
F 0 "#FLG01" H 6650 3775 50  0001 C CNN
F 1 "PWR_FLAG" H 6650 3900 50  0000 C CNN
F 2 "" H 6650 3700 50  0001 C CNN
F 3 "~" H 6650 3700 50  0001 C CNN
	1    6650 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	7550 4150 7550 3700
Wire Wire Line
	6650 3700 6650 3750
$Comp
L power:PWR_FLAG #FLG02
U 1 1 624FA4C2
P 7250 3700
F 0 "#FLG02" H 7250 3775 50  0001 C CNN
F 1 "PWR_FLAG" H 7250 3900 50  0000 C CNN
F 2 "" H 7250 3700 50  0001 C CNN
F 3 "~" H 7250 3700 50  0001 C CNN
	1    7250 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	7250 3950 7250 4000
Wire Wire Line
	6550 3950 7250 3950
Wire Wire Line
	7250 3950 7250 3700
Connection ~ 7250 3950
Wire Wire Line
	6950 3750 6650 3750
Wire Wire Line
	7550 4150 6550 4150
Wire Wire Line
	6550 4350 6650 4350
Wire Wire Line
	6550 4550 6650 4550
Wire Wire Line
	6550 4650 6650 4650
Text Label 6650 4650 0    50   ~ 0
pot0
Text Label 6650 4550 0    50   ~ 0
pot1
Text Label 6650 4350 0    50   ~ 0
pot2
$Comp
L Device:R_POT RV1
U 1 1 62549A19
P 8850 3850
F 0 "RV1" H 8780 3804 50  0000 R CNN
F 1 "500k" H 8780 3895 50  0000 R CNN
F 2 "" H 8850 3850 50  0001 C CNN
F 3 "~" H 8850 3850 50  0001 C CNN
	1    8850 3850
	-1   0    0    1   
$EndComp
Wire Wire Line
	8700 3850 8600 3850
Wire Wire Line
	9500 3850 9400 3850
Text Label 8600 3850 2    50   ~ 0
pot0
Text Label 9400 3850 2    50   ~ 0
pot1
Wire Wire Line
	10300 3850 10200 3850
Text Label 10200 3850 2    50   ~ 0
pot2
Wire Wire Line
	8850 3700 8850 3650
$Comp
L power:GND #PWR020
U 1 1 6257A3E2
P 8850 4050
F 0 "#PWR020" H 8850 3800 50  0001 C CNN
F 1 "GND" H 8855 3877 50  0000 C CNN
F 2 "" H 8850 4050 50  0001 C CNN
F 3 "" H 8850 4050 50  0001 C CNN
	1    8850 4050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR021
U 1 1 6257A737
P 9650 4050
F 0 "#PWR021" H 9650 3800 50  0001 C CNN
F 1 "GND" H 9655 3877 50  0000 C CNN
F 2 "" H 9650 4050 50  0001 C CNN
F 3 "" H 9650 4050 50  0001 C CNN
	1    9650 4050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR022
U 1 1 6257AA37
P 10450 4050
F 0 "#PWR022" H 10450 3800 50  0001 C CNN
F 1 "GND" H 10455 3877 50  0000 C CNN
F 2 "" H 10450 4050 50  0001 C CNN
F 3 "" H 10450 4050 50  0001 C CNN
	1    10450 4050
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR017
U 1 1 6257ADF5
P 8850 3650
F 0 "#PWR017" H 8850 3500 50  0001 C CNN
F 1 "+3.3V" H 8865 3823 50  0000 C CNN
F 2 "" H 8850 3650 50  0001 C CNN
F 3 "" H 8850 3650 50  0001 C CNN
	1    8850 3650
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR018
U 1 1 6257B76D
P 9650 3650
F 0 "#PWR018" H 9650 3500 50  0001 C CNN
F 1 "+3.3V" H 9665 3823 50  0000 C CNN
F 2 "" H 9650 3650 50  0001 C CNN
F 3 "" H 9650 3650 50  0001 C CNN
	1    9650 3650
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR019
U 1 1 6257BB1C
P 10450 3650
F 0 "#PWR019" H 10450 3500 50  0001 C CNN
F 1 "+3.3V" H 10465 3823 50  0000 C CNN
F 2 "" H 10450 3650 50  0001 C CNN
F 3 "" H 10450 3650 50  0001 C CNN
	1    10450 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	10450 3650 10450 3700
Wire Wire Line
	9650 3650 9650 3700
Wire Wire Line
	8850 4000 8850 4050
Wire Wire Line
	9650 4000 9650 4050
Wire Wire Line
	10450 4000 10450 4050
$Comp
L Device:R_POT RV2
U 1 1 6259E7F8
P 9650 3850
F 0 "RV2" H 9580 3804 50  0000 R CNN
F 1 "500k" H 9580 3895 50  0000 R CNN
F 2 "" H 9650 3850 50  0001 C CNN
F 3 "~" H 9650 3850 50  0001 C CNN
	1    9650 3850
	-1   0    0    1   
$EndComp
$Comp
L Device:R_POT RV3
U 1 1 6259EB8B
P 10450 3850
F 0 "RV3" H 10380 3804 50  0000 R CNN
F 1 "500k" H 10380 3895 50  0000 R CNN
F 2 "" H 10450 3850 50  0001 C CNN
F 3 "~" H 10450 3850 50  0001 C CNN
	1    10450 3850
	-1   0    0    1   
$EndComp
$Comp
L Connector:DIN-5_180degree J2
U 1 1 625BCF72
P 3550 2600
F 0 "J2" H 3550 2325 50  0000 C CNN
F 1 "midi_out_port" H 3550 2234 50  0000 C CNN
F 2 "" H 3550 2600 50  0001 C CNN
F 3 "http://www.mouser.com/ds/2/18/40_c091_abd_e-75918.pdf" H 3550 2600 50  0001 C CNN
	1    3550 2600
	1    0    0    -1  
$EndComp
NoConn ~ 3250 2600
NoConn ~ 3850 2600
Wire Wire Line
	3250 2500 3200 2500
Wire Wire Line
	3200 2500 3200 2450
$Comp
L Device:R R6
U 1 1 625EDFBC
P 3200 2300
F 0 "R6" H 3270 2346 50  0000 L CNN
F 1 "33" H 3270 2255 50  0000 L CNN
F 2 "" V 3130 2300 50  0001 C CNN
F 3 "~" H 3200 2300 50  0001 C CNN
	1    3200 2300
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR014
U 1 1 625EE3B3
P 3200 2100
F 0 "#PWR014" H 3200 1950 50  0001 C CNN
F 1 "+3V3" H 3215 2273 50  0000 C CNN
F 2 "" H 3200 2100 50  0001 C CNN
F 3 "" H 3200 2100 50  0001 C CNN
	1    3200 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	3200 2100 3200 2150
Wire Wire Line
	3850 2500 3900 2500
Wire Wire Line
	3900 2500 3900 2450
$Comp
L Device:R R7
U 1 1 625FCE5A
P 3900 2300
F 0 "R7" H 3970 2346 50  0000 L CNN
F 1 "10" H 3970 2255 50  0000 L CNN
F 2 "" V 3830 2300 50  0001 C CNN
F 3 "~" H 3900 2300 50  0001 C CNN
	1    3900 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3900 2150 3900 2100
Text Label 3900 2100 0    50   ~ 0
midi_out
$Comp
L power:GND #PWR016
U 1 1 62615CCE
P 3550 2250
F 0 "#PWR016" H 3550 2000 50  0001 C CNN
F 1 "GND" H 3555 2077 50  0000 C CNN
F 2 "" H 3550 2250 50  0001 C CNN
F 3 "" H 3550 2250 50  0001 C CNN
	1    3550 2250
	-1   0    0    1   
$EndComp
Wire Wire Line
	3550 2300 3550 2250
$Comp
L Connector:DIN-5_180degree J1
U 1 1 6261E0CD
P 1400 2600
F 0 "J1" H 1400 2325 50  0000 C CNN
F 1 "midi_in_port" H 1400 2234 50  0000 C CNN
F 2 "" H 1400 2600 50  0001 C CNN
F 3 "http://www.mouser.com/ds/2/18/40_c091_abd_e-75918.pdf" H 1400 2600 50  0001 C CNN
	1    1400 2600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR015
U 1 1 6261EAD6
P 1400 2250
F 0 "#PWR015" H 1400 2000 50  0001 C CNN
F 1 "GND" H 1405 2077 50  0000 C CNN
F 2 "" H 1400 2250 50  0001 C CNN
F 3 "" H 1400 2250 50  0001 C CNN
	1    1400 2250
	-1   0    0    1   
$EndComp
Wire Wire Line
	1400 2250 1400 2300
NoConn ~ 1100 2600
NoConn ~ 1700 2600
$Comp
L Isolator:4N35 U2
U 1 1 6263A07C
P 2000 1800
F 0 "U2" H 2000 2125 50  0000 C CNN
F 1 "4N35" H 2000 2034 50  0000 C CNN
F 2 "Package_DIP:DIP-6_W7.62mm" H 1800 1600 50  0001 L CIN
F 3 "https://www.vishay.com/docs/81181/4n35.pdf" H 2000 1800 50  0001 L CNN
	1    2000 1800
	1    0    0    -1  
$EndComp
NoConn ~ 2300 1700
$Comp
L Diode:1N914 D4
U 1 1 6264243D
P 1600 1850
F 0 "D4" V 1550 1650 50  0000 L CNN
F 1 "1N914" V 1650 1550 50  0000 L CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 1600 1675 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 1600 1850 50  0001 C CNN
	1    1600 1850
	0    1    1    0   
$EndComp
Wire Wire Line
	1700 1700 1600 1700
Connection ~ 1600 1700
Wire Wire Line
	1600 1700 1050 1700
Wire Wire Line
	1600 2000 1700 2000
Wire Wire Line
	1700 1900 1700 2000
$Comp
L Device:R R5
U 1 1 626BC8FC
P 1700 2250
F 0 "R5" H 1770 2296 50  0000 L CNN
F 1 "220" H 1770 2205 50  0000 L CNN
F 2 "" V 1630 2250 50  0001 C CNN
F 3 "~" H 1700 2250 50  0001 C CNN
	1    1700 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	1700 2400 1700 2500
Wire Wire Line
	1700 2100 1700 2000
Connection ~ 1700 2000
Wire Wire Line
	2300 1900 2350 1900
Wire Wire Line
	2350 1900 2350 1950
$Comp
L power:GND #PWR013
U 1 1 626D8D63
P 2350 1950
F 0 "#PWR013" H 2350 1700 50  0001 C CNN
F 1 "GND" H 2355 1777 50  0000 C CNN
F 2 "" H 2350 1950 50  0001 C CNN
F 3 "" H 2350 1950 50  0001 C CNN
	1    2350 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	2300 1800 2550 1800
Text Label 2650 1800 0    50   ~ 0
midi_in
Wire Wire Line
	1050 2500 1050 1700
Wire Wire Line
	1050 2500 1100 2500
$Comp
L power:+3V3 #PWR012
U 1 1 62710468
P 2550 1400
F 0 "#PWR012" H 2550 1250 50  0001 C CNN
F 1 "+3V3" H 2565 1573 50  0000 C CNN
F 2 "" H 2550 1400 50  0001 C CNN
F 3 "" H 2550 1400 50  0001 C CNN
	1    2550 1400
	1    0    0    -1  
$EndComp
$Comp
L Device:R R4
U 1 1 62710886
P 2550 1600
F 0 "R4" H 2620 1646 50  0000 L CNN
F 1 "330" H 2620 1555 50  0000 L CNN
F 2 "" V 2480 1600 50  0001 C CNN
F 3 "~" H 2550 1600 50  0001 C CNN
	1    2550 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	2550 1450 2550 1400
Wire Wire Line
	2550 1750 2550 1800
Connection ~ 2550 1800
Wire Wire Line
	2550 1800 2650 1800
Wire Wire Line
	3750 5050 5150 5050
Wire Wire Line
	3750 5050 3750 5750
Wire Wire Line
	3700 4850 5150 4850
Wire Wire Line
	3700 4850 3700 5250
Wire Wire Line
	3750 3750 3750 4550
Wire Wire Line
	3400 3750 3750 3750
Wire Wire Line
	3750 4550 5150 4550
Wire Wire Line
	3700 4250 3700 4650
Wire Wire Line
	3700 4650 5150 4650
Wire Wire Line
	1600 5950 1600 6000
Connection ~ 1600 5950
Connection ~ 1900 5750
Wire Wire Line
	2100 5950 2100 6050
Connection ~ 2100 5950
Connection ~ 2400 5750
Wire Wire Line
	2600 5950 2600 6100
Connection ~ 2600 5950
Connection ~ 2900 5750
Wire Wire Line
	3100 5950 3100 6150
Connection ~ 3100 5950
Connection ~ 3400 5750
Wire Wire Line
	3600 5950 3600 6200
Connection ~ 3600 5950
Connection ~ 3400 5250
Connection ~ 3600 5450
Connection ~ 2900 5250
Connection ~ 3100 5450
Connection ~ 2400 5250
Connection ~ 2600 5450
Connection ~ 1900 5250
Connection ~ 2100 5450
Connection ~ 1600 5450
Connection ~ 1600 4950
Connection ~ 1900 4750
Connection ~ 2100 4950
Connection ~ 2400 4750
Connection ~ 2600 4950
Connection ~ 2900 4750
Connection ~ 3100 4950
Connection ~ 3400 4750
Connection ~ 3600 4950
Wire Wire Line
	1400 3750 1900 3750
Connection ~ 1600 4450
Connection ~ 1900 4250
Connection ~ 2100 4450
Connection ~ 2400 4250
Connection ~ 2600 4450
Connection ~ 3400 4250
Connection ~ 3600 4450
Connection ~ 2900 4250
Connection ~ 3100 4450
Connection ~ 3400 3750
Wire Wire Line
	2900 3750 3400 3750
Connection ~ 2900 3750
Wire Wire Line
	2400 3750 2900 3750
Connection ~ 2400 3750
Wire Wire Line
	1900 3750 2400 3750
Connection ~ 1900 3750
Wire Wire Line
	3600 6200 4850 6200
Wire Wire Line
	3100 6150 4800 6150
Wire Wire Line
	4750 6100 2600 6100
Wire Wire Line
	2100 6050 4700 6050
Wire Wire Line
	1600 6000 4650 6000
$Comp
L Switch:SW_Push_45deg SW5
U 1 1 621BCE81
P 3500 3850
F 0 "SW5" H 3500 3569 50  0000 C CNN
F 1 "btn4" H 3500 3660 50  0000 C CNN
F 2 "" H 3500 3850 50  0001 C CNN
F 3 "~" H 3500 3850 50  0001 C CNN
	1    3500 3850
	-1   0    0    1   
$EndComp
$Comp
L Switch:SW_Push_45deg SW4
U 1 1 621BC5D8
P 3000 3850
F 0 "SW4" H 3000 3569 50  0000 C CNN
F 1 "btn3" H 3000 3660 50  0000 C CNN
F 2 "" H 3000 3850 50  0001 C CNN
F 3 "~" H 3000 3850 50  0001 C CNN
	1    3000 3850
	-1   0    0    1   
$EndComp
$Comp
L Switch:SW_Push_45deg SW3
U 1 1 621BBF84
P 2500 3850
F 0 "SW3" H 2500 3569 50  0000 C CNN
F 1 "btn2" H 2500 3660 50  0000 C CNN
F 2 "" H 2500 3850 50  0001 C CNN
F 3 "~" H 2500 3850 50  0001 C CNN
	1    2500 3850
	-1   0    0    1   
$EndComp
$Comp
L Switch:SW_Push_45deg SW2
U 1 1 621BB9DA
P 2000 3850
F 0 "SW2" H 2000 3569 50  0000 C CNN
F 1 "btn1" H 2000 3660 50  0000 C CNN
F 2 "" H 2000 3850 50  0001 C CNN
F 3 "~" H 2000 3850 50  0001 C CNN
	1    2000 3850
	-1   0    0    1   
$EndComp
$Comp
L Switch:SW_Push_45deg SW1
U 1 1 621BB51A
P 1500 3850
F 0 "SW1" H 1500 3569 50  0000 C CNN
F 1 "btn0" H 1500 3660 50  0000 C CNN
F 2 "" H 1500 3850 50  0001 C CNN
F 3 "~" H 1500 3850 50  0001 C CNN
	1    1500 3850
	-1   0    0    1   
$EndComp
$Comp
L Switch:SW_Push_45deg SW6
U 1 1 621BAF40
P 1500 4350
F 0 "SW6" H 1500 4069 50  0000 C CNN
F 1 "btn5" H 1500 4160 50  0000 C CNN
F 2 "" H 1500 4350 50  0001 C CNN
F 3 "~" H 1500 4350 50  0001 C CNN
	1    1500 4350
	-1   0    0    1   
$EndComp
$Comp
L Switch:SW_Push_45deg SW7
U 1 1 621BAA79
P 2000 4350
F 0 "SW7" H 2000 4069 50  0000 C CNN
F 1 "btn6" H 2000 4160 50  0000 C CNN
F 2 "" H 2000 4350 50  0001 C CNN
F 3 "~" H 2000 4350 50  0001 C CNN
	1    2000 4350
	-1   0    0    1   
$EndComp
$Comp
L Switch:SW_Push_45deg SW8
U 1 1 621BA49E
P 2500 4350
F 0 "SW8" H 2500 4069 50  0000 C CNN
F 1 "btn7" H 2500 4160 50  0000 C CNN
F 2 "" H 2500 4350 50  0001 C CNN
F 3 "~" H 2500 4350 50  0001 C CNN
	1    2500 4350
	-1   0    0    1   
$EndComp
$Comp
L Switch:SW_Push_45deg SW9
U 1 1 621B9D3C
P 3000 4350
F 0 "SW9" H 3000 4069 50  0000 C CNN
F 1 "btn8" H 3000 4160 50  0000 C CNN
F 2 "" H 3000 4350 50  0001 C CNN
F 3 "~" H 3000 4350 50  0001 C CNN
	1    3000 4350
	-1   0    0    1   
$EndComp
$Comp
L Switch:SW_Push_45deg SW10
U 1 1 621B9803
P 3500 4350
F 0 "SW10" H 3500 4069 50  0000 C CNN
F 1 "btn9" H 3500 4160 50  0000 C CNN
F 2 "" H 3500 4350 50  0001 C CNN
F 3 "~" H 3500 4350 50  0001 C CNN
	1    3500 4350
	-1   0    0    1   
$EndComp
$Comp
L Switch:SW_Push_45deg SW15
U 1 1 621B9267
P 3500 4850
F 0 "SW15" H 3500 4569 50  0000 C CNN
F 1 "btn14" H 3500 4660 50  0000 C CNN
F 2 "" H 3500 4850 50  0001 C CNN
F 3 "~" H 3500 4850 50  0001 C CNN
	1    3500 4850
	-1   0    0    1   
$EndComp
$Comp
L Switch:SW_Push_45deg SW14
U 1 1 621B8C87
P 3000 4850
F 0 "SW14" H 3000 4569 50  0000 C CNN
F 1 "btn13" H 3000 4660 50  0000 C CNN
F 2 "" H 3000 4850 50  0001 C CNN
F 3 "~" H 3000 4850 50  0001 C CNN
	1    3000 4850
	-1   0    0    1   
$EndComp
$Comp
L Switch:SW_Push_45deg SW13
U 1 1 621B8486
P 2500 4850
F 0 "SW13" H 2500 4569 50  0000 C CNN
F 1 "btn12" H 2500 4660 50  0000 C CNN
F 2 "" H 2500 4850 50  0001 C CNN
F 3 "~" H 2500 4850 50  0001 C CNN
	1    2500 4850
	-1   0    0    1   
$EndComp
$Comp
L Switch:SW_Push_45deg SW12
U 1 1 621B8096
P 2000 4850
F 0 "SW12" H 2000 4569 50  0000 C CNN
F 1 "btn11" H 2000 4660 50  0000 C CNN
F 2 "" H 2000 4850 50  0001 C CNN
F 3 "~" H 2000 4850 50  0001 C CNN
	1    2000 4850
	-1   0    0    1   
$EndComp
$Comp
L Switch:SW_Push_45deg SW11
U 1 1 621B7C55
P 1500 4850
F 0 "SW11" H 1500 4569 50  0000 C CNN
F 1 "btn10" H 1500 4660 50  0000 C CNN
F 2 "" H 1500 4850 50  0001 C CNN
F 3 "~" H 1500 4850 50  0001 C CNN
	1    1500 4850
	-1   0    0    1   
$EndComp
$Comp
L Switch:SW_Push_45deg SW16
U 1 1 621B7955
P 1500 5350
F 0 "SW16" H 1500 5069 50  0000 C CNN
F 1 "btn15" H 1500 5160 50  0000 C CNN
F 2 "" H 1500 5350 50  0001 C CNN
F 3 "~" H 1500 5350 50  0001 C CNN
	1    1500 5350
	-1   0    0    1   
$EndComp
$Comp
L Switch:SW_Push_45deg SW21
U 1 1 621B70A1
P 1500 5850
F 0 "SW21" H 1500 5569 50  0000 C CNN
F 1 "btn20" H 1500 5660 50  0000 C CNN
F 2 "" H 1500 5850 50  0001 C CNN
F 3 "~" H 1500 5850 50  0001 C CNN
	1    1500 5850
	-1   0    0    1   
$EndComp
$Comp
L Switch:SW_Push_45deg SW17
U 1 1 621B6D29
P 2000 5350
F 0 "SW17" H 2000 5069 50  0000 C CNN
F 1 "btn16" H 2000 5160 50  0000 C CNN
F 2 "" H 2000 5350 50  0001 C CNN
F 3 "~" H 2000 5350 50  0001 C CNN
	1    2000 5350
	-1   0    0    1   
$EndComp
$Comp
L Switch:SW_Push_45deg SW18
U 1 1 621B6864
P 2500 5350
F 0 "SW18" H 2500 5069 50  0000 C CNN
F 1 "btn17" H 2500 5160 50  0000 C CNN
F 2 "" H 2500 5350 50  0001 C CNN
F 3 "~" H 2500 5350 50  0001 C CNN
	1    2500 5350
	-1   0    0    1   
$EndComp
$Comp
L Switch:SW_Push_45deg SW19
U 1 1 621B63D8
P 3000 5350
F 0 "SW19" H 3000 5069 50  0000 C CNN
F 1 "btn18" H 3000 5160 50  0000 C CNN
F 2 "" H 3000 5350 50  0001 C CNN
F 3 "~" H 3000 5350 50  0001 C CNN
	1    3000 5350
	-1   0    0    1   
$EndComp
$Comp
L Switch:SW_Push_45deg SW20
U 1 1 621B5B99
P 3500 5350
F 0 "SW20" H 3500 5069 50  0000 C CNN
F 1 "btn19" H 3500 5160 50  0000 C CNN
F 2 "" H 3500 5350 50  0001 C CNN
F 3 "~" H 3500 5350 50  0001 C CNN
	1    3500 5350
	-1   0    0    1   
$EndComp
$Comp
L Switch:SW_Push_45deg SW25
U 1 1 621B56C9
P 3500 5850
F 0 "SW25" H 3500 5569 50  0000 C CNN
F 1 "btn24" H 3500 5660 50  0000 C CNN
F 2 "" H 3500 5850 50  0001 C CNN
F 3 "~" H 3500 5850 50  0001 C CNN
	1    3500 5850
	-1   0    0    1   
$EndComp
$Comp
L Switch:SW_Push_45deg SW24
U 1 1 621B5282
P 3000 5850
F 0 "SW24" H 3000 5569 50  0000 C CNN
F 1 "btn23" H 3000 5660 50  0000 C CNN
F 2 "" H 3000 5850 50  0001 C CNN
F 3 "~" H 3000 5850 50  0001 C CNN
	1    3000 5850
	-1   0    0    1   
$EndComp
$Comp
L Switch:SW_Push_45deg SW23
U 1 1 621B4E7F
P 2500 5850
F 0 "SW23" H 2500 5569 50  0000 C CNN
F 1 "btn22" H 2500 5660 50  0000 C CNN
F 2 "" H 2500 5850 50  0001 C CNN
F 3 "~" H 2500 5850 50  0001 C CNN
	1    2500 5850
	-1   0    0    1   
$EndComp
$Comp
L Switch:SW_Push_45deg SW22
U 1 1 621B43C6
P 2000 5850
F 0 "SW22" H 2000 5569 50  0000 C CNN
F 1 "btn21" H 2000 5660 50  0000 C CNN
F 2 "" H 2000 5850 50  0001 C CNN
F 3 "~" H 2000 5850 50  0001 C CNN
	1    2000 5850
	-1   0    0    1   
$EndComp
Wire Notes Line
	4050 3350 1200 3350
Wire Notes Line
	4050 6550 1200 6550
Wire Notes Line
	1200 3350 1200 6550
Wire Notes Line
	4050 3350 4050 6550
Text Notes 1250 6500 0    50   ~ 10
Controls Button matrix
Wire Notes Line
	8350 3350 10850 3350
Wire Notes Line
	8350 4550 10850 4550
Wire Notes Line
	10850 3350 10850 4550
Wire Notes Line
	8350 3350 8350 4550
Text Notes 9900 4500 0    50   ~ 10
Controls potentiometers
Wire Notes Line
	4400 1000 4400 3150
Wire Notes Line
	4400 3150 750  3150
Wire Notes Line
	750  3150 750  1000
Wire Notes Line
	750  1000 4400 1000
Text Notes 4000 1150 0    50   ~ 10
MIDI I/O
Wire Notes Line
	7250 4300 8300 4300
Wire Notes Line
	8300 4300 8300 5850
Wire Notes Line
	8300 5850 7250 5850
Wire Notes Line
	7250 5850 7250 4300
Text Notes 7300 5800 0    50   ~ 10
Controls LEDs
Text Notes 5300 3400 0    50   ~ 0
Pico powered by 5V USB cable
Wire Wire Line
	1900 4250 2400 4250
Wire Wire Line
	2100 3950 2100 4450
Wire Wire Line
	1600 3950 1600 4450
Wire Wire Line
	1400 4250 1900 4250
Wire Wire Line
	2400 4250 2900 4250
Wire Wire Line
	2600 3950 2600 4450
Wire Wire Line
	2900 4250 3400 4250
Wire Wire Line
	3100 3950 3100 4450
Wire Wire Line
	3400 4250 3700 4250
Wire Wire Line
	3600 3950 3600 4450
Wire Wire Line
	2900 4750 3400 4750
Wire Wire Line
	3100 4450 3100 4950
Wire Wire Line
	3400 4750 5150 4750
Wire Wire Line
	3600 4450 3600 4950
Wire Wire Line
	2400 4750 2900 4750
Wire Wire Line
	2600 4450 2600 4950
Wire Wire Line
	1900 4750 2400 4750
Wire Wire Line
	2100 4450 2100 4950
Wire Wire Line
	1600 4450 1600 4950
Wire Wire Line
	1400 4750 1900 4750
Wire Wire Line
	1400 5250 1900 5250
Wire Wire Line
	1600 4950 1600 5450
Wire Wire Line
	1900 5250 2400 5250
Wire Wire Line
	2100 4950 2100 5450
Wire Wire Line
	2400 5250 2900 5250
Wire Wire Line
	2600 4950 2600 5450
Wire Wire Line
	2900 5250 3400 5250
Wire Wire Line
	3100 4950 3100 5450
Wire Wire Line
	3400 5250 3700 5250
Wire Wire Line
	3600 4950 3600 5450
Wire Wire Line
	3400 5750 3750 5750
Wire Wire Line
	3600 5450 3600 5950
Wire Wire Line
	2900 5750 3400 5750
Wire Wire Line
	3100 5450 3100 5950
Wire Wire Line
	2400 5750 2900 5750
Wire Wire Line
	2600 5450 2600 5950
Wire Wire Line
	1900 5750 2400 5750
Wire Wire Line
	2100 5450 2100 5950
Wire Wire Line
	1600 5450 1600 5950
Wire Wire Line
	1400 5750 1900 5750
$Comp
L Device:R R?
U 1 1 6283A119
P 6450 1450
F 0 "R?" V 6243 1450 50  0000 C CNN
F 1 "100k" V 6334 1450 50  0000 C CNN
F 2 "" V 6380 1450 50  0001 C CNN
F 3 "~" H 6450 1450 50  0001 C CNN
	1    6450 1450
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 6283A793
P 6450 1600
F 0 "R?" V 6350 1600 50  0000 C CNN
F 1 "390" V 6250 1600 50  0000 C CNN
F 2 "" V 6380 1600 50  0001 C CNN
F 3 "~" H 6450 1600 50  0001 C CNN
	1    6450 1600
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6300 1450 6200 1450
Wire Wire Line
	6200 1600 6300 1600
Text Label 6200 1600 2    50   ~ 0
audio_pwm_H
Text Label 6200 1450 2    50   ~ 0
audio_pwm_L
Wire Wire Line
	6650 1600 6600 1600
Wire Wire Line
	6650 1600 6650 1450
Wire Wire Line
	6650 1450 6600 1450
Connection ~ 6650 1450
$Comp
L Amplifier_Audio:LM386 U?
U 1 1 6286D7C3
P 8700 1550
F 0 "U?" H 9044 1596 50  0000 L CNN
F 1 "LM386" H 9044 1505 50  0000 L CNN
F 2 "" H 8800 1650 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm386.pdf" H 8900 1750 50  0001 C CNN
	1    8700 1550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6286DDFC
P 8600 1950
F 0 "#PWR?" H 8600 1700 50  0001 C CNN
F 1 "GND" H 8605 1777 50  0000 C CNN
F 2 "" H 8600 1950 50  0001 C CNN
F 3 "" H 8600 1950 50  0001 C CNN
	1    8600 1950
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 6286E205
P 8600 1000
F 0 "#PWR?" H 8600 850 50  0001 C CNN
F 1 "+5V" H 8615 1173 50  0000 C CNN
F 2 "" H 8600 1000 50  0001 C CNN
F 3 "" H 8600 1000 50  0001 C CNN
	1    8600 1000
	1    0    0    -1  
$EndComp
Wire Wire Line
	8600 1000 8600 1050
Wire Wire Line
	8600 1850 8600 1950
Wire Wire Line
	7600 1450 7600 1500
$Comp
L power:GND #PWR?
U 1 1 628A1B95
P 7600 1950
F 0 "#PWR?" H 7600 1700 50  0001 C CNN
F 1 "GND" H 7605 1777 50  0000 C CNN
F 2 "" H 7600 1950 50  0001 C CNN
F 3 "" H 7600 1950 50  0001 C CNN
	1    7600 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	7600 1950 7600 1800
Wire Wire Line
	7750 1650 7800 1650
Wire Wire Line
	7800 1650 7800 1450
Wire Wire Line
	8150 1450 8400 1450
NoConn ~ 8700 1850
NoConn ~ 8800 1850
$Comp
L Device:C C?
U 1 1 628CB77A
P 8400 1050
F 0 "C?" V 8148 1050 50  0000 C CNN
F 1 "100n" V 8239 1050 50  0000 C CNN
F 2 "" H 8438 900 50  0001 C CNN
F 3 "~" H 8400 1050 50  0001 C CNN
	1    8400 1050
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 628CC576
P 8200 1100
F 0 "#PWR?" H 8200 850 50  0001 C CNN
F 1 "GND" H 8205 927 50  0000 C CNN
F 2 "" H 8200 1100 50  0001 C CNN
F 3 "" H 8200 1100 50  0001 C CNN
	1    8200 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	8200 1100 8200 1050
Wire Wire Line
	8200 1050 8250 1050
Wire Wire Line
	8550 1050 8600 1050
Connection ~ 8600 1050
Wire Wire Line
	8600 1050 8600 1250
$Comp
L Device:C C?
U 1 1 628E5EAB
P 8900 1050
F 0 "C?" V 8648 1050 50  0000 C CNN
F 1 "10u" V 8739 1050 50  0000 C CNN
F 2 "" H 8938 900 50  0001 C CNN
F 3 "~" H 8900 1050 50  0001 C CNN
	1    8900 1050
	0    1    1    0   
$EndComp
Wire Wire Line
	8750 1050 8700 1050
Wire Wire Line
	8700 1050 8700 1250
Wire Wire Line
	9050 1050 9100 1050
Wire Wire Line
	9100 1050 9100 1100
$Comp
L power:GND #PWR?
U 1 1 629094CA
P 9100 1100
F 0 "#PWR?" H 9100 850 50  0001 C CNN
F 1 "GND" H 9105 927 50  0000 C CNN
F 2 "" H 9100 1100 50  0001 C CNN
F 3 "" H 9100 1100 50  0001 C CNN
	1    9100 1100
	1    0    0    -1  
$EndComp
$Comp
L Device:CP1 C?
U 1 1 62909B68
P 8000 1450
F 0 "C?" V 8252 1450 50  0000 C CNN
F 1 "100u" V 8161 1450 50  0000 C CNN
F 2 "" H 8000 1450 50  0001 C CNN
F 3 "~" H 8000 1450 50  0001 C CNN
	1    8000 1450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7850 1450 7800 1450
$Comp
L Device:CP1 C?
U 1 1 6292E48B
P 9500 1550
F 0 "C?" V 9752 1550 50  0000 C CNN
F 1 "100u" V 9661 1550 50  0000 C CNN
F 2 "" H 9500 1550 50  0001 C CNN
F 3 "~" H 9500 1550 50  0001 C CNN
	1    9500 1550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9350 1550 9000 1550
$Comp
L power:GND #PWR?
U 1 1 6294DB07
P 8350 1950
F 0 "#PWR?" H 8350 1700 50  0001 C CNN
F 1 "GND" H 8355 1777 50  0000 C CNN
F 2 "" H 8350 1950 50  0001 C CNN
F 3 "" H 8350 1950 50  0001 C CNN
	1    8350 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	8350 1950 8350 1650
Wire Wire Line
	8350 1650 8400 1650
$Comp
L Device:R_POT RV?
U 1 1 628977ED
P 7600 1650
F 0 "RV?" H 7530 1696 50  0000 R CNN
F 1 "10k" H 7530 1605 50  0000 R CNN
F 2 "" H 7600 1650 50  0001 C CNN
F 3 "~" H 7600 1650 50  0001 C CNN
	1    7600 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	6650 1450 6950 1450
Wire Wire Line
	6950 1450 6950 1600
Wire Wire Line
	6950 1950 6950 1900
$Comp
L power:GND #PWR?
U 1 1 628656AC
P 6950 1950
F 0 "#PWR?" H 6950 1700 50  0001 C CNN
F 1 "GND" H 6955 1777 50  0000 C CNN
F 2 "" H 6950 1950 50  0001 C CNN
F 3 "" H 6950 1950 50  0001 C CNN
	1    6950 1950
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 6284DA56
P 6950 1750
F 0 "C?" H 7065 1796 50  0000 L CNN
F 1 "180p" H 7065 1705 50  0000 L CNN
F 2 "" H 6988 1600 50  0001 C CNN
F 3 "~" H 6950 1750 50  0001 C CNN
	1    6950 1750
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 6298DB63
P 7300 1450
F 0 "R?" V 7093 1450 50  0000 C CNN
F 1 "680" V 7184 1450 50  0000 C CNN
F 2 "" V 7230 1450 50  0001 C CNN
F 3 "~" H 7300 1450 50  0001 C CNN
	1    7300 1450
	0    1    1    0   
$EndComp
Wire Wire Line
	7150 1450 6950 1450
Connection ~ 6950 1450
Wire Wire Line
	7450 1450 7600 1450
$Comp
L Connector:AudioJack3 J?
U 1 1 629A85FF
P 10600 1750
F 0 "J?" H 10320 1775 50  0000 R CNN
F 1 "AudioJack3" H 10320 1684 50  0000 R CNN
F 2 "" H 10600 1750 50  0001 C CNN
F 3 "~" H 10600 1750 50  0001 C CNN
	1    10600 1750
	-1   0    0    -1  
$EndComp
Wire Wire Line
	10400 1650 10350 1650
Wire Wire Line
	10350 1650 10350 1750
Wire Wire Line
	10350 1750 10400 1750
Wire Wire Line
	10400 1850 10400 1950
$Comp
L power:GND #PWR?
U 1 1 629D1972
P 10400 1950
F 0 "#PWR?" H 10400 1700 50  0001 C CNN
F 1 "GND" H 10405 1777 50  0000 C CNN
F 2 "" H 10400 1950 50  0001 C CNN
F 3 "" H 10400 1950 50  0001 C CNN
	1    10400 1950
	1    0    0    -1  
$EndComp
$Comp
L Device:Speaker LS?
U 1 1 629E9B91
P 10650 1150
F 0 "LS?" H 10820 1146 50  0000 L CNN
F 1 "Speaker" H 10820 1055 50  0000 L CNN
F 2 "" H 10650 950 50  0001 C CNN
F 3 "~" H 10640 1100 50  0001 C CNN
	1    10650 1150
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPDT SW?
U 1 1 629EB442
P 9900 1550
F 0 "SW?" H 9900 1835 50  0000 C CNN
F 1 "SW_SPDT" H 9900 1744 50  0000 C CNN
F 2 "" H 9900 1550 50  0001 C CNN
F 3 "~" H 9900 1550 50  0001 C CNN
	1    9900 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	9700 1550 9650 1550
Wire Wire Line
	10100 1650 10350 1650
Connection ~ 10350 1650
$Comp
L power:GND #PWR?
U 1 1 62A562EA
P 10400 1300
F 0 "#PWR?" H 10400 1050 50  0001 C CNN
F 1 "GND" H 10405 1127 50  0000 C CNN
F 2 "" H 10400 1300 50  0001 C CNN
F 3 "" H 10400 1300 50  0001 C CNN
	1    10400 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	10400 1300 10400 1250
Wire Wire Line
	10400 1250 10450 1250
Wire Wire Line
	10100 1450 10200 1450
Wire Wire Line
	10200 1450 10200 1150
Wire Wire Line
	10200 1150 10450 1150
$EndSCHEMATC