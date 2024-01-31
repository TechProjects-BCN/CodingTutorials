// Import library to interact with Infrared Sensor
#include <IRremote.h>

// Pin used when using infrared sensor and defining the sensor incode.
const long RECV_PIN = 7;
IRrecv irrecv(RECV_PIN);

void setup(){
  // We start the serial port to enable communication with Serial Monitor
	Serial.begin(9600);
  // Start comms with IR sensor
	IrReceiver.begin(RECV_PIN, ENABLE_LED_FEEDBACK);
}

void loop(){
  // If new data is available
	if(IrReceiver.decode()){
    // Get that data and decode it.
		String irNum = String(IrReceiver.decodedIRData.command,HEX);
    // Print the received data. This will be a string of data, like "1927392" that will represent the button clicked.
		Serial.println(irNum);
    // Continue receiving data 
		IrReceiver.resume();
	}
}
