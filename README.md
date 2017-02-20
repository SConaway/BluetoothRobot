# RobotControl
An Arduino-based Bluetooth Robot

Versions
=
---
Obstacle Avoiding Robot - github.com/SConaway/RobotControl/

IR Robot - github.com/SConaway/IRRobot

Line Tracking Robot - github.com/SConaway/LTMRobot

Based on:
*  Arduino UNO R3
*  L298N motor driver
*  HC-06 Bluetooth UART Module
*  HC-SR04 Ultrasonic Module

Once code is uploaded, this becomes a remote-controlled robot.

I based it off of https://www.amazon.com/gp/product/B01M2Z9ZTV/ with my own custom shield. Everything but the HC-06, which uses ReceiveOnlySoftwareSerial on pin A2, and the Ultrasonic Sensor whose Echo and Trigger are A0 and A1, respectively, is the same.

Credits
=
---


NewPing - Ultrasonic Library for Arduino - https://bitbucket.org/teckel12/arduino-new-ping/wiki/Home
