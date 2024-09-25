# Electronic-Speed-Controller
Developers: Amir Seidakhmetov and Joshua Wilbur

Driver code for the H-Bridge circuit is found in /Core/Src. The files main.c, HBridge.c and interrupt_callbacks.c contain custom code developed for this project. 
A more detailed README will be created in the future.

Image of prototype to test STM32 output (7/19/24)
![image](https://github.com/user-attachments/assets/b47a6323-f5db-4954-950a-a9ec15e21c73)


# Software TODO
* Impliment feedback code 
* Clean up unused code (ie photo-interruptor and DMA stuff)
* Try to use DMA again, it was troublesome the first time around
* Research programming the STM32L476RG without a dev board.
* Wireless controller (if time avails).