#define buzzer_pin 18
#define button_pin 21

int buttonState;            // the current reading from the input pin
int lastButtonState = HIGH;  // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

bool reseted = false;
// measure
bool measuring = false;
bool start_measure = false;
bool released_measure = false;
unsigned long dot_time = 0;
unsigned long space_time = 0;
unsigned long pressed_time = 0;
unsigned long released_time = 0;

void reset(){
  measuring = false;
  start_measure = false;
  released_measure = false;
  dot_time = millis();
  space_time = millis();
  pressed_time = millis();
  released_time = millis();
}
void setup(){
  Serial.begin(9600);
  pinMode(buzzer_pin, OUTPUT);
  pinMode(button_pin, INPUT_PULLUP);
}

void loop(){
  int reading = digitalRead(button_pin);

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == LOW) {
        digitalWrite(buzzer_pin, HIGH);
        if(!start_measure){
          measuring = true;
          start_measure = true;
          dot_time = millis();
        }
        if(released_measure){
          released_measure = false;
          released_time = millis() - space_time;
          Serial.print("Space: ");
          Serial.println(released_time);
        }
      }
      else{
        digitalWrite(buzzer_pin, LOW);
        if(start_measure){
          start_measure = false;
          pressed_time = millis() - dot_time;
          Serial.print("Dot: ");
          Serial.println(pressed_time);
        }
        if(measuring){
          reseted = false;
          if(!released_measure){
            space_time = millis();
            released_measure = true; 
          }
        }
        
      }
    }
  }

  if(millis() - space_time > 2000.0){
    if(!reseted){
      reset();
      reseted = true;
      Serial.println("KONZZ");
    }
  }
  
  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
}
