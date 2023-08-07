# Desktop-PC-to-Mona-Robot-Communication
Control the Mona Robot from a Desktop PC

In this code, Arduino Mona Robot (ESP32) is controlled by a PC through the wifi network using UDP.

**Hardware Required**
Arduino Mono Robot (inbuilt ESP32 Board)
PC

**To use:**
In this code, set the SSID and password of the network that will be used to control Mona_ESP. Compile and upload the code to Mona_ESP. Open a serial terminal (For example, the Arduino serial Monitor)	and check what the IP is given to Mona_ESP. Modify in the file 'Control_client_udp.ino' the host value, and enter the IP read from the terminal in the previous step. Save the file. Run with Arduino IDE the file 'Control_client_udp.ino'. Enjoy controlling Mona_ESP through the wifi via UDP.
