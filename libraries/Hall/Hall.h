//**************************************
//*�N���P�������O
//*2016-03-04
//*�d�R��
//**************************************

class Hall{
	//�B��α`��
	const float r = 29;				//(cm)
  //@�ܼ�
  double preTime = 0;       //�e�@�Ӯɶ��I
  double nowTime = 0;       //�{�b���ɶ��I
  double preSpeed = 0;
  double nowSpeed = 0;
  double nowAcc = 0;
  double pml = 2*pi*r;
  //�غc��
  void Hall();
  void Hall(double lenth);
  //��s
  void stateUpdate();
  //�ǭ�
  double getSpeed();
  double getAcc();
}
