//----------------------
//файлы
//----------------------
//библиотеки
#include <Stepper_28BYJ.h>
#include <LiquidCrystal.h>
#include <SD.h> 
//----------------------
//----------------------
//шаговый двигатель
#define IN1 2
#define IN2 3
#define IN3 4
#define IN4 5

#define STEPP 4096
//4096  4078
//----------------------
//бузер
#define BZ 6
//----------------------
//датчик расстояния
#define TRIG 8
#define ECHO A0
//----------------------
//дисплей
#define E 7
#define RS 9

#define D4 A4
#define D5 A3
#define D6 A2
#define D7 A1
//----------------------
//кнопка
#define BUTT A5
//----------------------
//вариативные значения
#define ACTIVE 22//35

#define DETOUR 3 //количество проходов с выключенной сигнализацией

#define MAXR 180 //максимальная дальность просчета

//---------------------------------
//---------------------------------
//глобальные переменные
Stepper_28BYJ eng(STEPP,IN1,IN2,IN3,IN4);
LiquidCrystal lcd(RS, E, D4, D5, D6, D7);

int sec{},minut{},hour{};

int dist{};

bool actB{},add{true},exMode{false},entMode{false};

int timeB1{},mode{};

bool direct{false}; // по часовой - true против часовой - false
int angle{};

int detour{};

int matrix[36];
int bufMatrix[36];


//---------------------------------
//функции

void zero(int num, int *n){
  for(int i{};i<num;i++){
    n[i] = 0;  
  }  
}

void Beep(int fr,int dl){
    tone(BZ,fr);
    delay(dl);
    noTone(BZ);
}


int getDist(){
      digitalWrite(TRIG, LOW);
      delayMicroseconds(5);
      digitalWrite(TRIG, HIGH);
      delayMicroseconds(10);//10
      digitalWrite(TRIG, LOW);
      pinMode(ECHO, INPUT);

  return pulseIn(ECHO, HIGH);
}



//---------------------------------


void setup() {
  pinMode(TRIG, OUTPUT);

  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  
  Serial.begin(9600);
  while(!Serial);

  Serial.println("start");

  for(int i{};i<36;i++){
    matrix[i] = 0;
    bufMatrix[i] = 0;
  }

  lcd.begin(16, 2);

  if (!SD.begin()) {                   // Проверяем, есть ли связь с картой и, если нет, то
    Beep(800,300);
    Beep(400,400);
    lcd.setCursor(0, 0);
    lcd.print("no memory card");
    lcd.setCursor(0, 1);
    lcd.print("insert and reset");
    while(true);
    // Скетч не выполняется дальше.
  }
  else{
    Beep(400,400);
    Beep(800,300);  
  }

  
  lcd.setCursor(0, 0);
  lcd.clear();
  lcd.print("start");
  
  
  eng.setSpeed(13);//8

  //eng.step(-(STEPP/36)*(7));//----------------------------------
  

}




void loop() {
  actB = digitalRead(BUTT);

  if( (actB)&&(add) ) {
    timeB1 = millis()/1000;  
    add = false;
  }


  if( (!add)&&(!actB) ){
    
    if( ((millis()/1000)-timeB1)>1 ){
      if( (((millis()/1000)-timeB1)>3)&&(entMode) ){
        Beep(1000,300);//exit
        exMode = true;
        lcd.clear();

        zero(36,matrix);
        zero(36,bufMatrix);
      }
      else{
        Beep(800,150);//enter
        entMode = true;
        lcd.clear();
      }  
    }
    else if(!entMode){//------------
      Beep(600,50);//change mode
      mode++;
      if(mode==4){
        mode = 0;  
      }

      lcd.clear();
    }
    
    add = true;
  }


  if(mode == 0){
    if(!entMode){
      lcd.setCursor(0, 0);
      lcd.print("MODE:  0");

  
      lcd.setCursor(0, 1);
      lcd.print("show creaters");
    }
    if(entMode){
  
      if(exMode){
        entMode = false;
        exMode = false;  
      }
      else{
        mode0();    
      }
      
      
    }
    
  }
  
  if(mode == 1){
    if(!entMode){    
      lcd.setCursor(0, 0);
      lcd.print("MODE:  1");
      
  
      lcd.setCursor(0, 1);
      lcd.print("start locator");
    }
    if(entMode){

      if(exMode){
        entMode = false;
        exMode = false;   
      }
      else{
        mode1();    
      }

        
    }
  }
  
  if(mode == 2){
    if(!entMode){
      lcd.setCursor(0, 0);
      lcd.print("MODE:  2");
      
  
      lcd.setCursor(0, 1);
      lcd.print("info Microsd");
    }
    if(entMode){
      
      if(exMode){
        entMode = false;
        exMode = false;   
      }
      else{
        mode2();    
      }
  
    }
    
  }
  if(mode == 3){
    if(!entMode){
      lcd.setCursor(0, 0);
      lcd.print("MODE:  3");
  
  
      lcd.setCursor(0, 1);
      lcd.print("version");
    }
    if(entMode){

      if(exMode){
        entMode = false; 
        exMode = false;          
      }
      else{
        mode3();    
      }      
      
    }
    
  }
  
 
  
}
