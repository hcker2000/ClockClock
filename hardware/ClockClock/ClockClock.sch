EESchema Schematic File Version 4
LIBS:ClockClock-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L power:GND #PWR?
U 1 1 5B97D6F2
P 2350 4850
F 0 "#PWR?" H 2350 4600 50  0001 C CNN
F 1 "GND" H 2355 4677 50  0000 C CNN
F 2 "" H 2350 4850 50  0001 C CNN
F 3 "" H 2350 4850 50  0001 C CNN
	1    2350 4850
	1    0    0    -1  
$EndComp
$Comp
L Device:R BUZZ
U 1 1 5B97F53B
P 6350 2500
F 0 "BUZZ" H 6420 2546 50  0000 L CNN
F 1 "10k" H 6420 2455 50  0000 L CNN
F 2 "" V 6280 2500 50  0001 C CNN
F 3 "~" H 6350 2500 50  0001 C CNN
	1    6350 2500
	1    0    0    -1  
$EndComp
$Comp
L Device:R VIBE
U 1 1 5B97F679
P 6350 4050
F 0 "VIBE" H 6420 4096 50  0000 L CNN
F 1 "10k" H 6420 4005 50  0000 L CNN
F 2 "" V 6280 4050 50  0001 C CNN
F 3 "~" H 6350 4050 50  0001 C CNN
	1    6350 4050
	1    0    0    -1  
$EndComp
$Comp
L Device:R LED
U 1 1 5B97F6C2
P 6350 5300
F 0 "LED" H 6420 5346 50  0000 L CNN
F 1 "10k" H 6420 5255 50  0000 L CNN
F 2 "" V 6280 5300 50  0001 C CNN
F 3 "~" H 6350 5300 50  0001 C CNN
	1    6350 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 3850 5450 3850
$Comp
L Connector:Conn_01x04_Male J?
U 1 1 5B97FFEF
P 2450 2650
F 0 "J?" V 2510 2363 50  0000 R CNN
F 1 "OLED" V 2601 2363 50  0000 R CNN
F 2 "" H 2450 2650 50  0001 C CNN
F 3 "~" H 2450 2650 50  0001 C CNN
	1    2450 2650
	0    -1   1    0   
$EndComp
Wire Wire Line
	2550 2850 2550 3750
Wire Wire Line
	2550 3750 4450 3750
Wire Wire Line
	2650 2850 2650 3650
Wire Wire Line
	2650 3650 4450 3650
Wire Wire Line
	2350 2850 2350 3350
Wire Wire Line
	4450 3350 2350 3350
Connection ~ 2350 3350
Wire Wire Line
	2350 3350 2350 4850
$Comp
L Device:Q_NMOS_GDS Q?
U 1 1 5B981561
P 6550 2150
F 0 "Q?" H 6755 2196 50  0000 L CNN
F 1 "Q_NMOS_GDS" H 6755 2105 50  0000 L CNN
F 2 "" H 6750 2250 50  0001 C CNN
F 3 "~" H 6550 2150 50  0001 C CNN
	1    6550 2150
	1    0    0    -1  
$EndComp
$Comp
L Device:Q_NMOS_GDS Q?
U 1 1 5B9815DF
P 6550 3650
F 0 "Q?" H 6755 3696 50  0000 L CNN
F 1 "Q_NMOS_GDS" H 6755 3605 50  0000 L CNN
F 2 "" H 6750 3750 50  0001 C CNN
F 3 "~" H 6550 3650 50  0001 C CNN
	1    6550 3650
	1    0    0    -1  
$EndComp
$Comp
L Device:Q_NMOS_GDS Q?
U 1 1 5B98163C
P 6550 4900
F 0 "Q?" H 6755 4946 50  0000 L CNN
F 1 "Q_NMOS_GDS" H 6755 4855 50  0000 L CNN
F 2 "" H 6750 5000 50  0001 C CNN
F 3 "~" H 6550 4900 50  0001 C CNN
	1    6550 4900
	1    0    0    -1  
$EndComp
$Comp
L wemos_mini:WeMos_mini U?
U 1 1 5B97D5EE
P 4950 3600
F 0 "U?" H 4950 4343 60  0000 C CNN
F 1 "WeMos_mini" H 4950 4237 60  0000 C CNN
F 2 "" H 5500 2900 60  0000 C CNN
F 3 "http://www.wemos.cc/Products/d1_mini.html" H 4950 4131 60  0000 C CNN
	1    4950 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	6350 2650 6650 2650
Wire Wire Line
	6650 2650 6650 2350
Wire Wire Line
	6350 2350 6350 2150
$Comp
L power:GND #PWR?
U 1 1 5B9828D8
P 6650 2650
F 0 "#PWR?" H 6650 2400 50  0001 C CNN
F 1 "GND" H 6655 2477 50  0000 C CNN
F 2 "" H 6650 2650 50  0001 C CNN
F 3 "" H 6650 2650 50  0001 C CNN
	1    6650 2650
	1    0    0    -1  
$EndComp
Connection ~ 6650 2650
Wire Wire Line
	6350 5450 6650 5450
Wire Wire Line
	6650 5450 6650 5100
Wire Wire Line
	6350 4900 6350 5150
$Comp
L power:GND #PWR?
U 1 1 5B982B28
P 6650 5450
F 0 "#PWR?" H 6650 5200 50  0001 C CNN
F 1 "GND" H 6655 5277 50  0000 C CNN
F 2 "" H 6650 5450 50  0001 C CNN
F 3 "" H 6650 5450 50  0001 C CNN
	1    6650 5450
	1    0    0    -1  
$EndComp
Connection ~ 6650 5450
Wire Wire Line
	6350 4200 6650 4200
Wire Wire Line
	6650 4200 6650 3850
Wire Wire Line
	6350 3650 6350 3900
$Comp
L power:GND #PWR?
U 1 1 5B982DC5
P 6650 4200
F 0 "#PWR?" H 6650 3950 50  0001 C CNN
F 1 "GND" H 6655 4027 50  0000 C CNN
F 2 "" H 6650 4200 50  0001 C CNN
F 3 "" H 6650 4200 50  0001 C CNN
	1    6650 4200
	1    0    0    -1  
$EndComp
Connection ~ 6650 4200
Wire Wire Line
	6350 3650 6350 3550
Wire Wire Line
	6350 3550 5450 3550
Connection ~ 6350 3650
Wire Wire Line
	5450 3650 5850 3650
Wire Wire Line
	5850 3650 5850 4900
Wire Wire Line
	5850 4900 6350 4900
Connection ~ 6350 4900
Wire Wire Line
	5450 3450 6050 3450
Wire Wire Line
	6050 3450 6050 2150
Wire Wire Line
	6050 2150 6350 2150
Connection ~ 6350 2150
$EndSCHEMATC
