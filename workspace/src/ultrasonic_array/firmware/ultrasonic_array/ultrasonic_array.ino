#include <stdarg.h>


// the program will send pings cyclically to the pins listed here
#define NUM_PINS 6
int pingPins[NUM_PINS] = {6, 7, 8, 9, 10, 12};
int distances[NUM_PINS] = {0, 0, 0, 0, 0, 0};
float max_range = 400;  // cm

unsigned long max_wait = 29 * max_range;  // us
long index;


void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  index = 0;
}


void serial_printf(char *fmt, ... ){
        char buf[128]; // resulting string limited to 128 chars
        va_list args;
        va_start (args, fmt );
        vsnprintf(buf, 128, fmt, args);
        va_end (args);
        Serial.print(buf);
}


float measureDistance(int pinNum){

  // send pulse
  pinMode(pinNum, OUTPUT);
  digitalWrite(pinNum, LOW);
  delayMicroseconds(2);
  digitalWrite(pinNum, HIGH);
  delayMicroseconds(5);
  digitalWrite(pinNum, LOW);

  // wait for echo
  pinMode(pinNum, INPUT);
  long duration = pulseIn(pinNum, HIGH, max_wait);

  // convert the time into a distance
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  float dist_cm = float(duration) / 29 / 2;
  return dist_cm;
}



void loop() {
  
//  String activePinName = pinNames[index];
  
  int activePin = pingPins[index];
  float distance = measureDistance(activePin);
  distances[index] = int(distance);
  
  serial_printf("%d:%03d, %d:%03d, %d:%03d, %d:%03d, %d:%03d, %d:%03d\n", 
                pingPins[0], distances[0],
                pingPins[1], distances[1],
                pingPins[2], distances[2],
                pingPins[3], distances[3],
                pingPins[4], distances[4],
                pingPins[5], distances[5]
                );
  
  index += 1;
  index = index % NUM_PINS;
  
  delay(25);
}
