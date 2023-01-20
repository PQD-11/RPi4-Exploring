#!/bin/bash
LED_GPIO=4

function setLED
{
	echo $1 >> "/sys/class/gpio/gpio$LED_GPIO/value"
}

if [ $# -ne 1 ];
then 
	echo "Error that indicates invalid number of arguments"
	exit 2
fi

if [ "$1" == "setup" ]; then
	echo "Exporting GPIO number $1"
	echo $LED_GPIO >> "/sys/class/gpio/export"
	sleep 1
	echo "out" >> "/sys/class/gpio/gpio$LED_GPIO/direction"
elif [ "$1" == "on" ]; then
	echo "Turning the LED on"
	setLED 1
elif [ "$1" == "off" ]; then
	echo "Turning the LED off"
	setLED 0 
elif [ "$1" == "status" ]; then
	state=$(cat "/sys/class/gpio/gpio$LED_GPIO/value")
	echo "The LED state is: $state"
elif [ "$1" == "close" ]; then
	echo "Unexporting GPIO number $LED_GPIO"
	echo $LED_GPIO >> "/sys/class/gpio/unexport"
fi
