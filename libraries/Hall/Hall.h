//**************************************
//*�N���P���� library for Arduino Uno
//*2016-03-10
//*�d�R��
//**************************************
#ifndef Hall_h
#define Hall_h

#include <inttypes.h>
/*
// For Arduino 1.0 and earlier
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
*/
class Hall{
public:
  //@�ܼ�
	unsigned long 
  unsigned char m_pin;
	unsigned double m_r = 29;				//(cm)
  unsigned double pml = 2*PI*m_r;
	unsigned double preTime = 0;       //�e�@�Ӯɶ��I
  unsigned double nowTime = 0;       //�{�b���ɶ��I
  double preSpeed = 0;
  double nowSpeed = 0;
  double nowAcc = 0;
  //�غc��
  void Hall(void);
  //��k
  void set(unsigned char pin, unsigned double r); 
  void stateUpdate();
  double getSpeed();
  double getAcc();
protected:
private:
};

#endif
