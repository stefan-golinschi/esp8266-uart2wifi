
# ESP8266-uart2wifi
Transparent serial communication sketch in Arduino IDE.  
This is useful for remote uart debugging.

# How it works
Using the default settings from ``config.h``, the 8266 module will create a **hidden** AP with the following settings:  

 * **SSID**: ``openNAS_debug``

 * **PSK**: ``RHbuQ5hKIdAt``

Then, it will listen on ``23/TCP``.

To send and receive UART info from the target board, you should use ``telnet`` with ``mode character`` enabled. Also, double-check that the baudrate defined in ``config.h`` matches the target board's baudrate.

### Example:
```
# connect to 8266's SSID, then run telnet
telnet 10.10.10.1 23

# escape using CTRL+]
mode character

# continue by hitting RETURN
```



# Tested on
So far it's tested on an Wemos R1 mini board, using UART0.

| R1 mini pin# | Target board pin# |
|--------------|-------------------|
| D7 [RX2]     | UART_TX           |
| D8 [TX2]     | UART_RX           |
| G  [GND]     | GND               |


**NOTICE**: When programming the R1 mini, you should not connect the UART wires to your target board. The communication will only work after the ``Serial.swap()`` call. Read more [here](https://arduino-esp8266.readthedocs.io/en/latest/reference.html#serial).

