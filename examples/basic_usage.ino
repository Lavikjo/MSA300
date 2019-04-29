#include <MSA300.h>
#include <Wire.h>


void setup() {

    Serial.begin(9600);
    Serial.println("MSA300 test");

    // Initialize MSA300 with ID using i2c
    MSA300 accel = MSA300(1234);

    // Establish connection to sensor
    if(!accel.begin()) {
        Serial.println("No MSA300 detected!");
    }

    // Set measurement range from to +/- 4g
    accel.setRange(MSA300_RANGE_4_G);

    // Set datarate to 500 Hz
    accel.setDataRate(MSA300_DATARATE_500_HZ);

}



void loop() {

    //Fetch results
    acc_t result;
    accel.getAcceleration(&result);

    //Print results
    Serial.print("X: ");
    Serial.println(result.result.x);
    Serial.print("Y: ");
    Serial.println(result.result.y);
    Serial.print("Z: ");
    Serial.println(result.result.z);

    delay(500);
}