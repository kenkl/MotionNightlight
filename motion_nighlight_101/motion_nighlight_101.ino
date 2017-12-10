// motion nightlight to provide red light for my 2am trip to go pee. this
// helps prevent sleep disturbance as well as retaining my night-vision
//
// v1.0.0 - initial published version, with non-blocking delay, 5 second warning, and slow-fade on/off.
//   photos of this version:  http://i.imgur.com/70N5cCH.jpg
//                            http://i.imgur.com/6uAZnqK.jpg
//                            http://i.imgur.com/RgfqifA.jpg
//   GitHub:  https://github.com/kenkl/MotionNightlight
// v1.0.1 - add CdS to override when there's already light.
//   photos of this version: https://i.imgur.com/vyOHSgM.jpg
//                           https://i.imgur.com/iOk3FRM.jpg
//                           https://i.imgur.com/hyUuhFa.jpg

#define LED 13 // onboard led - also used for 5-second warning
#define iLED 5 // the LED panel - providing the light for seeing. RED LEDs! Connected through NPN.
bool iLEDState = false;
#define fade 4 // the base fade-delay interval (fadeON/fadeOFF use multipliers)
#define pLED 4 // pilot LED. PIRs don't always have a pilot light on-board. optional
#define pIR 6 // the PIR itself - active HIGH.
#define ledDelay 33000 // ms, of course - how long does the nightlight stay on after PIR trigger?
unsigned long nowcount, delaycount; // tracking time for non-blocking delays
#define cds A2  // ambient light sensor - mute the light if there's already light on
const int threshold = 500; // the threshold for ambient light to mute the LED panel
bool ambientHigh = false; // flag whether ambient light is above the threshold

void setup()
{
  pinMode(iLED, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(pLED, OUTPUT);
  pinMode(pIR, INPUT);

  startupFlair();
  digitalWrite(LED, LOW);
  digitalWrite(pLED, LOW);
  digitalWrite(iLED, LOW);
}

void startupFlair(void) {
  // Prove that we're up and running
  digitalWrite(pLED, HIGH);
  for(int i=0; i < 5; i++) {
    digitalWrite(LED, HIGH);
    delay(250);
    digitalWrite(LED, LOW);
    delay(250);
  }
  digitalWrite(LED, HIGH);
  fadeON();
  delay(250);
  fadeOFF();
  delay(250);
  fadeON();
  delay(250);
  fadeOFF();
  delay(500);
    
}

void fadeON(void) {
  // a somewhat gentle activation of the LED panel
  if(iLEDState == true) return; // we're already on; don't need to do anything here
  if(ambientHigh == true) return; // ambient light is high enough to not turn on
  for(int i=0; i < 255; i++) {
    analogWrite(iLED, i);
    delay(fade);
  }
  digitalWrite(iLED, HIGH);
  iLEDState = true;
}

void fadeOFF(void) {
  // a somewhat gentle deactivation of the LED panel
  if(iLEDState == false) return; // we're already off; don't need to do anything here. when does this happen?
  if(ambientHigh == true) return; // ambient light is higher than threshold, we should already be off; do nothing. do we ever get here?
  for(int i=255; i > 0; i--) {
    analogWrite(iLED, i);
    delay(fade*2);
  }
  digitalWrite(iLED, LOW);
  iLEDState = false;
}

void loop()
{

  nowcount = millis();

  // if ambient light is above the threshold, turn off the LED panel and set a flag to prevent it coming on for now.
  if(analogRead (cds) > threshold) {
    digitalWrite(iLED, LOW); 
    ambientHigh = true; 
    iLEDState = false; 

  }
  else ambientHigh = false;
  
  // if the pIR sensor has tripped, update delaycount accordingly.  
  if(digitalRead(pIR) == HIGH) {
    delaycount = nowcount + ledDelay ;
    //digitalWrite(pLED, HIGH);  //optional, depending on whether the PIR already has an LED,
  }
  else digitalWrite(pLED, LOW);
  
  // now, check that delaycount has not yet been reached and turn on/off
  // the red LEDs accordingly.
  
  if(millis() <= delaycount) {
    fadeON();
    //five-second warning that we'll be plunged into darkness. 
    if((delaycount - millis()) <= 5000)  digitalWrite(LED, HIGH);
    else digitalWrite(LED, LOW);
  }
  else {
    fadeOFF();
    digitalWrite(LED, LOW);
  }
}

