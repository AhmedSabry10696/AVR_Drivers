## Atmega32 Microcontroller Drivers (layered software architecture):

### Atmega32 Microcontroller kit:

### Implemented Drivers:
1. DIO Driver: (leds, buttons, keypad, 7_seg, LCD, DC Motors, Stepper Motors).
2. ADC Driver: (voltmeter, temp sensor{lm35}, pressure sensor{MPX4110}).
3. External Interrupt Driver.
4. Timers Driver: (timer0{8 bit}, timer1{16 bit})
5. Servo Motor Driver{PWM}
6. Ultrasonic Driver: (Input Capture Unit).
7. UART Driver: (Synchronous and Asynchronous concept, Uart Stack).
8. SPI Driver.
9. I2C Driver.
10. Watch Dog Timer Driver.
11. Internal EEPROM Driver.

Note: All interrupts implemented using call back functions and there are a lot of tips and tricks related to static and dynamic design.

### don't hesitate to contact me if you have any questions or feedback:
Linkedin Account👇:
**https://www.linkedin.com/in/ahmedsabry10696/**