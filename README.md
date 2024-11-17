# Electronic-Speed-Controller
Developers: Amir Seidakhmetov and Joshua Wilbur

A more detailed README will be created in the future.
Driver code for the H-Bridge circuit is found in /Core/Src. The files main.c, H_bridge.c, user_input.c and rpm_feedback.c contain custom code developed for this project. 

Image of prototype to test STM32 output (7/19/24)
![image](https://github.com/user-attachments/assets/b47a6323-f5db-4954-950a-a9ec15e21c73)


# Software TODO (due date)
* Integrate voltage feedback code (by 11/30)
* Get SWD working: https://deepbluembedded.com/stm32-debugging-with-st-link-v2-swd-serial-wire-viewer/ (by 12/1)
* Clean up comments and code (by 12/8)
* Get rid of most global variables once testing is done (by 12/8)
* Upload PCB files (by 12/15)
* Flesh out README with pictures of PCB, prototype, schematic... (after semester)