# Electronic-Speed-Controller
Developers: Amir Seidakhmetov and Joshua Wilbur

Driver code for the H-Bridge circuit is found in /Core/Src. The files main.c, HBridge.c and feedback.c contain custom code developed for this project. 
A more detailed README will be created in the future.

Image of prototype to test STM32 output (7/19/24)
![image](https://github.com/user-attachments/assets/b47a6323-f5db-4954-950a-a9ec15e21c73)


# Software TODO
* Raise PWM voltage to greater than 3V. Currently it is ~2.5V at 100% duty 
  cycle, this is close to the minimum IR2011 V_IL <= 2.2V.
* Add team names to files we authored
* Look into making the potentiometer input an interrupt (see main.c 82)
* Start building feedback program, need to set up another ADC for that.
* Research programming the STM32L476RG without a dev board.
* Wireless controller (if time avails).