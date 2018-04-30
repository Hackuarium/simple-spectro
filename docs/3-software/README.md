# The software

When you finish soldering the PCB you need to burn the boot loader. Before this step you will not be able to control the device from USB.

To burn the boot loader you should first install the Arduino program and select in 'Tools -> Board -> Lilypad Arduino USB'. You may then either use a 'tag-connector' connected to a USBTinyISP or a normal cable for ICSP (you will have to solder the IDC 6 pins socket in this case).

Once the bootloader has been burned you should be able to select it from the Arduino program when it is connected with a USSB cable. It should appear in 'Tools -> Port -> xxx Lilypad Arduino USB'. You can now open the eagle project and program the spectrophotometer.

In order to set reasonable parameters you should make a reset either from the Serial menu or from the LCD (Utilities -> Reset). The spectrophotometer is now ready to be used. 
