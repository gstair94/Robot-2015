#include "NetComm.h"
#include "crc-16.h"

NetComm comm;

void setup() {
	Serial.begin(9600);
}

void printData(ControlData data) {
	char out[64];
	sprintf(out, "Fwd:%d Rev:%d Left:%d Right:%d", data.forward, data.reverse, data.left,
			data.right);
	Serial.println(out);
}

void loop() {
	ControlData data;
	if (comm.getData(&data)) {
		printData(data);
	} else {
		Serial.println("Invalid data");
	}
}
