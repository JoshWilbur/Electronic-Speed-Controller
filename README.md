# Electronic-Speed-Controller

Developers: Amir Seidakhmetov and Joshua Wilbur

This repository contains firmware to drive a 36V Electronic Speed Controller (ESC) for a DC motor. This project has been tested to handle a 3A load without issue. Motor speed is monitored and controlled using a hall effect sensor and PID feedback. 

Driver code for the H-Bridge circuit is found in /Core/Src. The files main.c,
H_bridge.c, user_input.c and rpm_feedback.c contain custom code developed
for this project.

Images of the schematic are found below, along with an operation guide.

![H-Bridge Schematic](Schematics/H_Bridge_SchematicV7.pdf) \
![STM32 Schematic](Schematics/STM32_Control_SchematicV3.pdf)

# Operation Guide

* Construct circuit shown in the latest schematic version with the parts listed in the expense report.
* Optional: Order two PCBs using the files in /H_Bridge_KiCAD and /STM32_KiCAD.
* Program STM32 chip with the code, found in this repository, using SWD.
* Power on circuit and controller.
* For safety, the device starts in an OFF state. Shift the direction switch once to begin operation.
* Use the potentiometer to set a desired speed within the range of 60 to 200 RPM.
