# Electronic-Speed-Controller
Developers: Amir Seidakhmetov and Joshua Wilbur

Driver code for the H-Bridge circuit is found in /Core/Src. The files main.c, 
H_bridge.c, user_input.c and rpm_feedback.c contain custom code developed 
for this project. 

# Operation Guide
* Construct circuit shown in the latest schematic version with the parts listed in the expense report.
* Optional: Order two PCBs using the files in /H_Bridge_KiCAD and /STM32_KiCAD.
* Program STM32 chip with the code, found in this repository, using SWD.
* Power on circuit and controller.
* For safety, the device starts in an OFF state. Shift the direction switch once to begin operation.
* Use the potentiometer to set a desired speed within the range of 60 to 200 RPM.


# Software TODO:
* Flesh out README with pictures of PCB, prototype, schematic