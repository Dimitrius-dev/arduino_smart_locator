/*
 Регистратор данных с использованием SD карт

 Пример сохранения данных с аналоговых портов на SD карте.
 Данные будут сохраняться в файле в виде набора строк с разделителем полей в виде символа ","

 Схема подключения:
 * Аналоговые сенсоры подключаются к аналоговым пинам
 * Модуль SD карты подключен в SPI по стандартной схеме:
 ** MOSI - пин 11
 ** MISO - пин12
 ** CLK - пин 13
 ** CS - pin 4
 */
#include <CustomStepper.h> 

//#include <SD.h>

//#include <LiquidCrystal.h>

/*
//двигатель



#define CHIP_SL 4

#define RS 2
#define E  3
#define D4 5
#define D5 6
#define D6 7
#define D7 8
*/

#define IN1 13
#define IN2 12
#define IN3 11
#define IN4 10

#define BZ 2

//датчик расстояния
#define ECHO 4
#define TRIG 3



//--------------
//переменные
long long int dur{},dist{};
CustomStepper eng(IN1, IN2, IN3, IN4);

//--------------
void Beep(int fr,int del){
  tone(BZ,fr);
  delay(del);
  noTone(BZ);
}

float getDis(){
  digitalWrite(TRIG, LOW);
  delayMicroseconds(5);
  digitalWrite(TRIG, HIGH);

  // Выставив высокий уровень сигнала, ждем около 10 микросекунд. В этот момент датчик будет посылать сигналы с частотой 40 КГц.
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  dur = pulseIn(ECHO,HIGH);

  //delay(300);
  
  if(dur<0){
    return 0;
  }
  else{
    return (dur/2)/29.1;
  }
  
  
  }
  
void setup() {
  Serial.begin(9600);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  Beep(1200,300);

  eng.setRPM(8);//8
  eng.setSPR(4096);

  
  Serial.println("start");
  delay(2000);
  
}

void loop() {
  if(eng.isDone()){
    eng.setDirection(CW);
    eng.rotateDegrees(10);
    Serial.println(getDis());
    
  }
  
  

  eng.run(); 
  
}
