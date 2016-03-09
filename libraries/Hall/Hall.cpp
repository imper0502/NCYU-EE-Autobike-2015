//**************************************
//*�N���P�������O
//*2016-03-04
//*�d�R��
//**************************************
#include"Hall.h"
class Hall{

  //�غc��
  void Hall() {
  } 
  void Hall(double lenth) {
    pml = lenth;
  }
  //�����k
  //��s
  void stateUpdate(){     //�Ч�ڳ]�w���~�����_, FALLING mode       
    this.nowTime = millis();
    if(this.preTime==0) {
        this.preTime = this.nowTime;
    }else if(this.preSpeed==0){
        this.nowSpeed = this.pml/(this.nowTime-this.preTime)*36;    //*36 �o(km/hr)
        this.preTime = this.nowTime;
        this.preSpeed = this.nowSpeed;
    }else {
        this.nowSpeed = this.pml/(this.nowTime-this.preTime)*36;
        this.nowAcc = (this.nowSpeed-this.preSpeed)/(this.nowTime-this.preTime);
        this.preTime = this.nowTime;
        this.preSpeed = this.nowSpeed;
    }
  }
  //�ǭ�
  double getSpeed() {
    //stateUpdate();    
    return this.nowSpeed;
  }
  double getAcc() {
    //stateUpdate();
    return this.nowAcc;
  }
}
