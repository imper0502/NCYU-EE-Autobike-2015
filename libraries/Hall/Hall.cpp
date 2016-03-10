//**************************************
//*�N���P���� library for Arduino Uno
//*2016-03-10
//*�d�R��
//**************************************
// For Arduino 1.0 and earlier
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include"Hall.h"
//�غc��
void Hall::Hall() {
} 
void Hall::set(unsigned char pin, unsigned double r); 
  m_pin = pin; 
	m_r = r;
  pinMode(m_pin, INPUT_PULLUP);
  if(m_pin==2) {
  	attachInterrupt(0, this.stateUpdate, FALLING);
	}
  if(m_pin==3) {
  	attachInterrupt(1, this.stateUpdate, FALLING);
	}
}
//��k
void Hall::stateUpdate(){
  this.nowTime = millis();
    if(this.preTime==0) {
      this.preTime = this.nowTime;
  }else if(this.preSpeed==0){
      this.nowSpeed = this.pml/(this.nowTime-this.preTime)*36;    //" *36 " �o(km/hr)
      this.preTime = this.nowTime;
      this.preSpeed = this.nowSpeed;
  }else {
      this.nowSpeed = this.pml/(this.nowTime-this.preTime)*36;
      this.nowAcc = (this.nowSpeed-this.preSpeed)/(this.nowTime-this.preTime)/3.6;//" /3.6 "�o(m/s) 
      this.preTime = this.nowTime;
      this.preSpeed = this.nowSpeed;
  }
}
//�ǭ�
double Hall::getSpeed() {  
  return this.nowSpeed;
}
double Hall::getAcc() {
	stateUpdate();
  return this.nowAcc;
}
