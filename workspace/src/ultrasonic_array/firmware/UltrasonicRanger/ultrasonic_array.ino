#define NUM_PINS 5
#include <stdarg.h>


void p(char *fmt, ... ){
        char buf[128]; // resulting string limited to 128 chars
        va_list args;
        va_start (args, fmt );
        vsnprintf(buf, 128, fmt, args);
        va_end (args);
        Serial.print(buf);
}

// the program will send pings cyclically to the pins listed here
int pingPins[NUM_PINS] = {9, 8, 6, 7, 10};

// keep track of the latest distance from each sensor
float distances[NUM_PINS] = {0, 0, 0, 0, 0};

String pinNames[NUM_PINS] = {"Center     ", 
                             "Front-Right", 
                             "Back-Right ",
                             "Back-Left  ",
                             "Front-Left "};

// TODO: keep track of length of time since each measurement was taken
//       remember to not count 0's!

long index;

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  index = 0;
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
  long duration = pulseIn(pinNum, HIGH);

  // convert the time into a distance
  float dist_cm = microsecondsToCentimeters(duration);
  return dist_cm;
}


float microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return float(microseconds) / 29 / 2;
}


void loop() {
  
  String activePinName = pinNames[index];
  
  int activePin = pingPins[index];

  float distance = measureDistance(activePin);

  distances[index] = distance;

  
  p(" %d  %d  %d  %d  %d\n", 
    int(distances[4]), int(distances[0]), int(distances[1]), int(distances[3]), int(distances[2]));
    
  index += 1;
  index = index % NUM_PINS;
  
  delay(5);
}

