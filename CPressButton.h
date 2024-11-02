// Author Petr Cernohorsky
// CPressButton v1.0.0
// This class works with HW buttons for the Arduino family. 
// It works with one press, as well as with a pressed button.

#include <Arduino.h>

class CPressButton  {
  public: 
    CPressButton(int pin);
    void initialization();
    long press();
    int getPin();
    bool previousState();
    bool pressOne();
    bool pressLong(int miliSec);
  
  private:
    long timePress = 0;
    int pin;
    bool prevState = false;
    int iteration = 0;
    unsigned long timeAction = 0;
};

bool CPressButton::pressLong(int miliSec){
  if(this->press()  > 0){
    if(this->timeAction < millis()){
      this->timeAction = millis() + miliSec;
      return true;
    }else{
      return false;
    }
  }else{
    this->timeAction = 0;
    return false;
  }
}

CPressButton::CPressButton(int pin){
  this->pin = pin;
  pinMode(pin, INPUT);
}

bool CPressButton::pressOne(){
  if((this->press()  > 0) && (!this->previousState())){
    return true;
  }
  else{
    return false;
  }
}

bool CPressButton::previousState(){
  return this->prevState;
}

long CPressButton::press(){
  return this->timePress;
}
int CPressButton::getPin(){
  return this->pin;
}
void CPressButton::initialization(){
  if(digitalRead(this->pin) == HIGH){
    if(this->timePress == 0){
      this->timePress = millis();
    }
    if((!this->prevState) && (this->iteration == 1)){
      this->prevState = true;
    }
    this->iteration++;
  }
  else{
    this->timePress = 0;
    this->prevState = false;
    this->iteration = 0;
  }

}
