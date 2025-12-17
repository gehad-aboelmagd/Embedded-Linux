
# Temperature Logging Sensor 🌡️


### Purpose 🤔
Practicing the CPP smart pointers in the context of embedded systems development.

### Steps 👣

1.  Developing LM35 Sensor Driver (HAL Driver)

2. Develping TemperatureData class that interacts with LM35 API and provides insights about both termperature value, and recording time. 

2. Develping Logger & Display classes with each having a reference to 
TemperatureData object.

3. Getting a shared-ptr to TemperatureData in main.cpp

4. Forwarding this ptr to both Logger, Display classes instances.

5. Looping for some iterations to read, log and display termperature.

```
$ g++ *.cpp
$ sudo ./a.out
``` 
Make sure to run the test using sudo; in privilaged state.

### Outupt 💡
1. Terminal
   
https://github.com/user-attachments/assets/1bff2ba8-f3b4-4e89-9521-818a2488c061

3. log.txt
```
15:37:26 1.000000

15:37:27 1.000000

15:37:28 1.000000

15:37:24 1.000000

15:37:25 1.000000


```
