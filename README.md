# hw4_1

How to set up this program?
1. Connect the Tx and Rx of XBee chip to D1 and D0 of mbed, respectively.
2. Connect the mbed board and XBee to PC 
3. Compile and run the program.
4. Compile and run the python program.
5. Press the reset button.

What are the results?
1. Type "pabc" in terminal, and the TextLCD will show "abc" in the left top angle.
2. Type "p123" in terminal, and the TextLCD will show "123" after the previously typed "abc".
3. Type "l1 1" in terminal, and then type "p123" in TextLCD, and the TextLCD will show "123123" on the screen. Because the command "l1 1" means move to first row and column of the TextLCD, and the "p123" means show "123" on the previously indicated place.
