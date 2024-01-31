## Overview
This is the tutorial for using an IR Sensor + IR controller, that will enable you to send information via an Infrared Sensor to your arduino.

To start with, connect the sensor with you arduino as follows:
![image](https://github.com/TechProjects-BCN/CodingTutorials/assets/61521609/1df6d0ca-3648-4c6d-8b42-bf33da9ee4c1)

If necessary you can check out the following tinkercad simulation with everything already setup: https://www.tinkercad.com/things/a1GCEIRIJQj-infrared-sensor-tutorial?sharecode=v-_A8yWjWPb0q4YjnG0HE0iu94PQPZnwLSSlr3UUagQ

The idea is that this sensor will receive a binary combination of 1s and 0s that will uniquely represent the button pressed.

## Code walk-through
So how can we use this?

Let's walk through the code. To start with, we are importing the IRremote library, which contains the class ```IRrecv``` that allows us to interphase with the sensor more easily.
```
#include <IRremote.h>
```
Now we'll set the pin where the sensor is connected and create an object from the class ```IRrecv```. You can think as an object as creating a sensor in the code so we can talk to it.
```
const long RECV_PIN = 7;
IRrecv irrecv(RECV_PIN);
```

Then, we'll code the setup function, that will only run when we start the arduino or reset it. Here we'll start the serial communication, that will allow us to send messages to the Serial Monitor and start the sensor itself so it starts to receive data.
```
Serial.begin(9600);
IrReceiver.begin(RECV_PIN, ENABLE_LED_FEEDBACK);
```

Finally, we'll start to use the data in the loop function. Initially we'll check if the sensor has received any new data and then we'll convert it to a Hexadecimal Code, which will act as a unique identifier of which button has been pressed.
```
// If new data is available
	if(IrReceiver.decode()){
    // Get that data and decode it.
		String irNum = String(IrReceiver.decodedIRData.command,HEX);
    // Print the received data. This will be a string of data, like "1927392" that will represent the button clicked.
		Serial.println(irNum);
    // Continue receiving data 
		IrReceiver.resume();
	}
```
After converting the data we'll print it out to the Serial Monitor and resume the checking for new incoming data.

## How to interpret the incoming data
After you setup the above, if you open the serial monitor you'll see a random string of numbers printed out every time you press a button in the controller.
Notice that this string is the same every time you press the same button.

So, if we want to turn on an LED after we press the power button, let's first check what code shows up when pressing that button.
In the example above in tinkercad, the string ```0``` is printed every time, so that's our identifier.

Now, let's append the code for this button turning on:
```
//...
const int LED_PIN = 5;
//...
void setup(){
  //...
  pinMode(LED_PIN, OUTPUT);
  //...
}

void loop(){
	if(IrReceiver.decode()){
  //...
  if (irNum == "0")
  {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }
  //...
  }
}
```
