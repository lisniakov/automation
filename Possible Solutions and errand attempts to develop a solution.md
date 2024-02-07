# Possible Solutions and Errand Attempts to Develop a Solution

## Introduction
First of all, for my project concept, I decided to study the standards for clean rooms, their levels and requirements for them. According to ISO 14644-1 and GMP standards, my future monitoring system needs to record and monitor temperature, humidity and, most importantly, the number of particles per cubic meter of the room in which the monitoring is being carried out. Since I chose the production of medical equipment as an abstract enterprise, an ISO 7 clean room suits me best. For a table with the requirements and definition of the level of clean rooms, see the table below:

![image](https://github.com/lisniakov/automation/assets/157028116/9dd238ee-a17e-4005-aa9f-57dcedd50cde)

[Table reference link](https://schillingengineering.de/en/media-library/cleanroom-classes-according-to-iso-14644-1)

As you already understood from the table, the requirements for a clean room of this class are quite high. For example, a class 9 room is essentially an ordinary living space, while you can’t easily get into a class 7 room without special clothing and training on how to work in such a room. Also, in addition to the number of particles, it is very important to maintain a stable level of humidity and temperature conditions. For this class, the recommended temperature is 21+-2 degrees Celsius and a humidity level of 55-65%.

## Sensor Selection
For this, I searched for suitable sensors and the following models turned out to be the most accessible to me: 
- BME280: a module for monitoring temperature and humidity


![BME280](https://github.com/lisniakov/automation/assets/157028116/795a1c90-951b-4e7d-bf78-452c82093046)

- PMS5003: for determining the number of particles of different sizes per cubic meter.
  
![PMS5003](https://github.com/lisniakov/automation/assets/157028116/c0f12c43-b250-403f-a0f3-13e748353c72)

All sensors will be programmed using the ESP8266 microcontroller, which can also be easily purchased in many stores, both online and local.

## Programming and Calibration
Also important is the writing of the program and, of course, how the report itself will look after certain monitoring intervals (for example, every 10 minutes or every 1 minute). Also, if this were done at a real company, it would be necessary to calibrate this monitoring system using third-party special calibration sensors (what is one of the testing stages during validation) and other tests in order for this project to be validated and approved for use in production with a similar level of importance. 

## Future Development
Ideally, it would be to install an alert system in this system that would be triggered when any of the indicators went beyond the established limits, this may be an idea for the next stage/updating of this monitoring system, because it is important not only to develop it but also not stop following trends because with the progress of technology, standards for production and equipment for it change, so in order not to lose quality, you need to continue to develop this system based on the development of other industries.

## Conclusion
At the moment, this is the main idea, which may be adjusted or changed during development, the final decision and version will depend on the program that can be created. dear readers, if you have any ideas/suggestions/tips regarding my idea written above - I will be very glad to read your comments, because a fresh look at the situation can be a good guide!

Thank you for your attention, see soon at the next stage of development!
