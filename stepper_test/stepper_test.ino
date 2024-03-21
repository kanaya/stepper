#include <SPI.h>

//モーター
#define PIN_SPI_MOSI MOSI
#define PIN_SPI_MISO MISO
#define PIN_SPI_SCK SCK
#define PIN_SPI_SS SS
#define PIN_BUSY 9

#define MOTOR_SPEED 20000 //30000ぐらいで悲鳴をあげる
#define DELAY_TIME 1000


void setup()
{
  Serial.begin(9600);

  delay(1000);
  pinMode(PIN_BUSY, INPUT);
  SPI.begin();
  SPI.setDataMode(SPI_MODE3);
  SPI.setBitOrder(MSBFIRST);

  Serial.println("Hello.");
  digitalWrite(SS, HIGH);

  L6470_resetdevice(); //L6470リセット
  L6470_setup();  //L6470を設定
}


void loop() {

  L6470_run(0, MOTOR_SPEED);
  delay(DELAY_TIME);
  L6470_softstop();
  L6470_run(1, MOTOR_SPEED);
  delay(DELAY_TIME);
  L6470_softstop();
}

void L6470_setup() {
  L6470_setparam_acc(0x40); //[R, WS] 加速度default 0x08A (12bit) (14.55*val+14.55[step/s^2])
  L6470_setparam_dec(0x40); //[R, WS] 減速度default 0x08A (12bit) (14.55*val+14.55[step/s^2])
  L6470_setparam_maxspeed(0x40); //[R, WR]最大速度default 0x041 (10bit) (15.25*val+15.25[step/s])
  L6470_setparam_minspeed(0x01); //[R, WS]最小速度default 0x000 (1+12bit) (0.238*val[step/s])
  L6470_setparam_fsspd(0x3ff); //[R, WR]μステップからフルステップへの切替点速度default 0x027 (10bit) (15.25*val+7.63[step/s])
  L6470_setparam_kvalhold(0x50); //[R, WR]停止時励磁電圧default 0x29 (8bit) (Vs[V]*val/256)
  L6470_setparam_kvalrun(0x50); //[R, WR]定速回転時励磁電圧default 0x29 (8bit) (Vs[V]*val/256)
  L6470_setparam_kvalacc(0x50); //[R, WR]加速時励磁電圧default 0x29 (8bit) (Vs[V]*val/256)
  L6470_setparam_kvaldec(0x50); //[R, WR]減速時励磁電圧default 0x29 (8bit) (Vs[V]*val/256)

  L6470_setparam_stepmood(0x03); //ステップモードdefault 0x07 (1+3+1+3bit)
}