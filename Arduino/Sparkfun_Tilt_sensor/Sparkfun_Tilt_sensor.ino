//Sparkfun tilt sensor simple sketch code with debouncing

// these constants won't change:
const int ledPin = 13;      // led connected to digital pin 13
const int tiltSensor = 2; // the piezo is connected to analog pin 0

// these variables will change:
int sensorReading;      // variable to store the value read from the sensor pin
int ledState = LOW;       // variable used to store the last LED status, to toggle the light
int tiltState;            // the current reading from the input pin
int lastTiltState = HIGH; // the previous reading from the input pin

long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {
 pinMode(ledPin, OUTPUT); // declare the ledPin as as OUTPUT
 pinMode(tiltSensor, INPUT); // declare the tiltSensor as as INPUT
}

void loop() {
  // read the sensor and store it in the variable sensorReading:
  sensorReading = digitalRead(tiltSensor);    
  
  // check to see if the sensor was tilted
  // (i.e. the input went from HIGH to LOW), and you've waited 
  // long enough since the last change to ignore any noise:  

  // If the tilt changed, due to noise or tilting: 
  if (sensorReading != lastTiltState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  } 
   if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:
    
    // if the button state has changed:
    if (sensorReading != tiltState){
      tiltState = sensorReading;
      
    // if the sensor reading is low
      if (sensorReading == LOW) {
        // make the status of the ledPin to go on:
        ledState = HIGH;   
        // update the LED pin itself:        
        digitalWrite(ledPin, ledState);
        // dalay the LED on for one second:
        delay(500);
      }
      // otherwise if it is high
      else if (sensorReading == HIGH){
        // make the status of the ledPin to stay off:
        ledState = LOW;
        // update the LED pin itself:
        digitalWrite(ledPin, ledState);
      }
    }
   }
  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastTiltState = sensorReading; 
  // delay to avoid overloading the serial port buffer:
  delay(100);  
}
