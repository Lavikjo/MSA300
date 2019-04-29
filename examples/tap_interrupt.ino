#include <MSA300.h>
#include <Wire.h>

int counter = 0;
const byte interrupt_pin = 2;
volatile interrupt_t interrupts;

void setup() {

    Serial.begin(9600);
    Serial.println("MSA300 test");

    //Setup interrupt
    pinMode(interrupt_pin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(interrupt_pin), tap, RISING);

    // Initialize MSA300 with ID using i2c
    MSA300 accel = MSA300(1234);

    // Establish connection to sensor
    if(!accel.begin()) {
        Serial.println("No MSA300 detected!");
    }

    // Set measurement range from to +/- 16g
    accel.setRange(MSA300_RANGE_16_G);

    // Set datarate to 500 Hz
    accel.setDataRate(MSA300_DATARATE_500_HZ);

    // Set tap threshold to 2g
    accel.setTapThreshold(2000f);

    // Set tap interrupt duration to 100 ms, quiet to  30 ms and shock to 50 ms
    accel.setTapDuration(MSA300_TAP_DUR_100_MS, 0, 0);

    // Set interrupt to latch permanently
    accel.setInterruptLatch(MSA300_INT_LATCHED);

    // Enable single tap interrupt on interrupt pin 1
    accel.enableSingleTapInterrupt(1);
}



void loop() {

    

    if(interrupts.sTapInt) {

        Serial.print("Number of taps: ");
        Serial.printnln(++counter);
        
        //Check the sign of tap
        uint8_t sign = interrupts.intStatus.tapSign;
        Serial.print("Sign of tap is: ");
        Serial.println(sign ? '+' : '-');
        
        //Check the axis that triggered tap interrupt
        if(interrupts.intStatus.tapFirstX) {
            Serial.println("Tap triggered by x-axis");
        } else if (interrupts.intStatus.tapFirstY) {
            Serial.println("Tap triggered by y-axis");
        } else if (interrupts.intStatus.tapFirstZ) {
            Serial.println("Tap triggered by z-axis");
        }

        //Reset interrupts
        accel.resetInterrupt();
    }
 
}

void tap() {
    //Check if tap interrupt has occured
    interrupts = accel.checkInterrupts();
}