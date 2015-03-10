#include "NetComm.h"
#include "crc-16.h"

const int LOOP_HZ = 10;
const int LOOP_DELAY = (int) (1000 / LOOP_HZ);

NetComm comm;
ControlData control;

void updateState() {
    ControlData data;
    if(comm.getData(&data)) {
        memcpy(&control, &data, 3);
    }
}

void printData(ControlData& data) {
    char out[64];
    sprintf(out, "Fwd:%d Rev:%d Left:%d Right:%d", data.forward, data.reverse,
            data.left, data.right);
    Serial.println(out);
}

void setup() {
    Serial.begin(9600);
}

void loop() {
    updateState();
    if(control.isTeleop) {
        printData(control);
    } else {
        Serial.println("Autonomous");
    }
    delay(LOOP_DELAY);
}
