//******************************************************************************
// 載入函式庫
//******************************************************************************
#include <LiquidCrystal.h>
#include "MPU6050.h"
#include "Hall.h"

//******************************************************************************
// 定義腳位
//******************************************************************************
#define pin_bluetooth_RXD 0
#define pin_bluetooth_TXD 1
#define pin_hall_1 2
#define pin_hall_2 3
#define pin_lcd_RS 9
#define pin_lcd_E 8
#define pin_lcd_D4 7
#define pin_lcd_D5 6
#define pin_lcd_D6 5
#define pin_lcd_D7 4
#define pin_pwm_output 10
#define pin_stop_anytime 12
#define pin_sda A4
#define pin_scl A5

//******************************************************************************
// 常數
//******************************************************************************
// 藍芽
const int baudrate = 9600;   // bps
// 輪子
const int wheel_magnetN = 18;
const double wheel_R = 0.275; // m
// 踏板
const int gear_magnetN = 6;
const double gear_R = 0.105; // m
const double gear_m = 2;     // kg
//const double I = gear_R*gear_R*gear_m/2+2*crank_m*crank_l*crank_l/3;
const double I = gear_R*gear_R*gear_m/2;
// 曲柄
const double crank_m = 0.3;       // kg
const double crank_l = 0.175;     // m
// 功率上下限
const double pedalPower_MAX = 10;
const double pedalPower_MIN = 0;

//******************************************************************************
// 全域變數
//******************************************************************************
// 計算腳踏圈數
double rps = 0;
double pre_rps = 0;
double rpm = 0;
// 車體角度
double gySlope = 0;
double pre_gySlope = 0;       //  degree
// 車體速度與加速度
double bikeSpeed = 0;         //  km/h
double pre_bikeSpeed = 0;
double acceleration = 0;      //  m/s^2
// 腳踏力
double pedalTorque= 0;        //  N
double pre_pedalTorque = 0;
double pedalPower = 0;        //  N-m
double pre_pedalPower = 0;
// 馬達輸出
double PWM = 0;
// 模式開關
boolean autoMode = true;
// 助力控制參數
double bestBikeSpeed = 17.6;
double bestBikeSpeed_interval = 3;
double lasttime;

//******************************************************************************
// 建立裝置物件
//******************************************************************************
LiquidCrystal LCD1602(pin_lcd_RS, pin_lcd_E, pin_lcd_D4, pin_lcd_D5, pin_lcd_D6, pin_lcd_D7);
MPU6050 GY521;
Hall Gear(pin_hall_1, gear_magnetN);
Hall Wheel(pin_hall_2, wheel_magnetN);

//******************************************************************************
// 初始化設定
//******************************************************************************
void setup() {
  //設定鮑率
  Serial.begin(baudrate);
  //中斷函式初始化
  //霍爾感測器--踏板
  attachInterrupt(0, ISR_0, FALLING);
  //霍爾感測器--後輪
  attachInterrupt(1, ISR_1, FALLING);
  //初始化LCD
  LCD1602.begin(16, 2);
  //初始化GY-521
  GY521.initialize();
  //初始化output
  pinMode(pin_pwm_output, OUTPUT);
  pinMode(11, OUTPUT);
  //初始化剎車按鈕
  pinMode(pin_stop_anytime, INPUT);
  //錯誤偵測
  if(!Serial.available()) {
    LCD1602.clear();
    LCD1602.print("BT connect failed");
    while(true);
  }
  if(!GY521.testConnection()) {
    LCD1602.clear();
    LCD1602.print("GY521 connect failed!");
    while(true);
  }
}

//******************************************************************************
// 主迴圈
//******************************************************************************
void loop() {
  // 看門狗
  if((millis()-Gear._nowTime)>5000) {
    Gear._preTime = 0;       //前一個時間點
    Gear._preOmega = 0;
    Gear._nowOmega = 0;
    Gear._nowAlpha = 0;
  }
  if((millis()-Wheel._nowTime)>5000) {
    Wheel._preTime = 0;       //前一個時間點
    Wheel._preOmega = 0;
    Wheel._nowOmega = 0;
    Wheel._nowAlpha = 0;
    lasttime = millis();
  }
  // 更新狀態
  drivesUpdate();
  // 剎車功能
  //  if(!pin_stop_anytime) {
  //    autoMode = false;
  //  }
  //  else {
  //    autoMode = true;
  //  }
  // 助力模式 or 非助力模式 
  // PWM輸出
  if(autoMode){
    if((millis()-lasttime)>100) {
      PWMOutput();
    }
    lasttime = millis();
  }
  // 顯示螢幕
  showLCD();
  // 與手機APP同步
  syncBT();
  // 測試用
  // Serial.println((int)(255*PWM));
}

//******************************************************************************
// 中斷副程式 for 霍爾感應器
//******************************************************************************
void ISR_0() {
  Gear.stateUpdate();
}

void ISR_1() {
  Wheel.stateUpdate();
}
