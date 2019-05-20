# The software

Once you finished soldering the PCB you need to burn the bootloader. This step enables the control of the device over USB.

To burn the bootloader, first install the Arduino program and select 'Tools -> Board -> Lilypad Arduino USB'. You may then either use a 'tag-connector' connected to a USBTinyISP or a normal cable for ICSP (you will have to solder the IDC 6 pins socket in this case) to burn the bootloader. Click 'Tools -> Burn Bootloader'.

Once the bootloader has been burned you should be able to select the device from the Arduino program when it is connected with a USB cable. It should appear in 'Tools -> Port -> xxx Lilypad Arduino USB'. You can now open the [Arduino project](https://github.com/Hackuarium/simple-spectro/tree/master/arduino) and program the spectrophotometer.

In order to set reasonable parameters you should make a reset either from the Serial menu or from the LCD ('Utilities -> Reset'). The spectrophotometer is now ready to be used.
