# koinexrino

#### Objective

This application retrieves xrp price from koinex website and displays it in a oled(0.96") display using Nodemcu. The code reloads the price every 40 seconds.   

#### Version 1 (v1)
It displays only XRP value right now. 

#### Technical Specification 
Below listed items are required for this project. I have not calculated the power consuption for this application at the time of development, feel free to play with the battery capacity. </br>
It is not necessary to use nodemcu for this project however you can use arduino nano with esp8266 or even explore more options for it. I have used nodemcu to simplify the connection part of both MCU and WIFI unit.</br>
Make sure that you buy I2C oled display for this project.
     

| Item                    | Quantity      |
| ----------------------- |:-------------:|
| Nodemcu                 | 1             |
| Oled display(0.96")     | 1             |
| Battery(600mah)         | 1             |
| Battery Charger(TP4056) | 1             |

Will update the circuit and rest of the project related images once done.


#### Working Issues
⋅⋅* I was so dumb that I didn't check the **https** example provided in the arduino rather was trying http example from the internet and was hitting **https** site using the **http** example. Atleast was able to get the https example. Will update version 2 using https and update the application with some cleaner code ofcourse.

-wolf
