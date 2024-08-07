# Arduino Projects

TM1637 Display Project, or lab_1 demonstrates how to use a TM1637 4-digit 7-segment display module with an Arduino. 
The display shows various sequences of numbers and characters using custom-defined segments.

Temperature and Humidity Display Project, or lab_2 uses an Arduino, a TM1637 4-digit 7-segment display, and a DHT11 temperature and humidity sensor to display temperature in Fahrenheit and humidity in percentage on the 7-segment display.

Keypad and LCD Menu System, or lab_3 uses an Arduino, a 4x4 matrix keypad, a LiquidCrystal I2C display, and EEPROM to create a simple menu-driven system.


## Components
* Arduino board (Arduino Mega)
* Jumper wires
  
`lab_1`

* TM1637 4-digit 7-segment display module

`lab_2`

- DHT11 Temperature and Humidity Sensor
- TM1637 4-digit 7-segment display

`lab_3`

- 4x4 Matrix Keypad
- LiquidCrystal I2C Display


## Libraries Required
- `TM1637Display` to control the TM1637 4-digit 7-segment display
- `DHT` to read data from DHT sensors
- `LiquidCrystal_I2C` for lcd display
- `EEPROM` for memory management
  
<!-- This is commented out.
## Code Description
<details>
  <summary>lab_1</summary>

*kim1_4*      Counts down from 100 to 0 in steps of 2, displaying each number. Displays the character "MIN" after clearing the display.
Counts up from 0 to 100 in steps of 2, displaying each number.

*kim2_1*      Counts down from 200 to 0 in steps of 20, displaying each number with a decimal point. Clears the display.
Counts up from 0 to 200 in steps of 20, displaying each number with a decimal point.

*kim3_4*      Continuously scrolls the string "TRAIN LEFT" across the display.

*Main Loop*    sets the brightness of the display and calls the defined routines in sequence

</details>
<details>
  <summary>lab_2</summary>
  
*temperature* displays the temperature in Fahrenheit on the 7-segment display and prints it to the serial monitor.

*humidity* displays the humidity percentage on the 7-segment display and prints it to the serial monitor.
</details>
<details>
  <summary>lab_3</summary>
  
</details>
 -->
## Wokwi Simulation
You can view and interact with the simulation of this project on Wokwi: 

* `lab1`  [TM1637 Display Project](//https://wokwi.com/projects/376034534469872641)

* `lab2`  [Temperature and Humidity Display](//https://wokwi.com/projects/376037042816877569)

* `lab3`  [Keypad and LCD Menu System](//https://wokwi.com/projects/376034534469872641)
