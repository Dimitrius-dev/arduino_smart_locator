void wrFile_1(bool signalA){
  File myFile = SD.open("datalog.csv", FILE_WRITE);

  
  //-------
  //формирование записи
  sec = millis()/1000;
  sec = sec%60;
  minut = (millis()/1000)/60;
  hour = ((millis()/1000)/60)/60;
  
  myFile.print("h: "); myFile.print(hour);  myFile.print("  ");
  myFile.print("m: "); myFile.print(minut); myFile.print("  ");
  myFile.print("s: "); myFile.print(sec);   myFile.print("  ");

  myFile.print("distance =  "); myFile.print(dist);

  if(angle == 35){
    myFile.print("   right");    
  }
  if(angle == 0){
    myFile.print("   left");    
  }
  if( (signalA)&&(detour == DETOUR) ){
    if( (angle == 0)||(angle == 35) ){
      myFile.print("   active");
    }
    else
    {
      myFile.print("           active");
    }
  }

  myFile.println(" ");

  //-------
  
  myFile.close(); 
  
}



//-----------------------------------------------------------
void wrFile_2(){
  File myFile = SD.open("datalog2.csv", FILE_WRITE);

  
  //-------
  //формирование записи
 
  
  myFile.print("h: "); myFile.print(hour);  myFile.print("  ");
  myFile.print("m: "); myFile.print(minut); myFile.print("  ");
  myFile.print("s: "); myFile.print(sec);   myFile.print("  ");

  myFile.print("distance = "); myFile.print(dist);

  if(angle >= 180){
    myFile.print("   right");    
  }
  if(angle <= -180){
    myFile.print("   left");    
  }

  myFile.println(" ");

  //-------
  
  myFile.close(); 
  
}

void wrFromFile(int num,int *n){
  int buf{},lst{}, i1{};
  
  File frFile = SD.open("buffer.csv");

  if(frFile){
    while(frFile.available()){

      lst = frFile.read();

      if(i1 == num){
        break;
      }
        
      
      if(buf == 32){
        n[i1] = buf;
        i1++;
        continue;  
      }
  
      buf = buf*10 + lst;

    }
    
  }
  else{
    Beep(1200,700);  
  }
  
  frFile.close();
}

void wrToFile(int num,int *n){
  
  File toFile = SD.open("buffer.csv",FILE_WRITE);

  for(int i{};i<num;i++){
    toFile.print(n[i]);
    toFile.print(" ");
  }
  
}

//-----------------------------------------------------------


void mode1(){
  bool signalA{false};

  

  dist = getDist()/58;//получаем дистанцию

  if(dist > MAXR){
    dist = MAXR;
  }

  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print("dist:");
  lcd.print(dist);//выводим
  lcd.print(" val:");
  lcd.print(matrix[angle]);

  sec = millis()/1000;//рассчитываем время
  sec = sec%60;
  minut = (millis()/1000)/60;
  hour = ((millis()/1000)/60)/60;


  
  

  if( ((abs(matrix[angle] - dist))>ACTIVE)&&(matrix[angle] != 0)&&(detour == DETOUR) ){
    for(int i{500};i<1200;i+=20){//сигнализация
      Beep(i,20);  
    }
    signalA = true;  
    
  }
  else{
    //Beep(1200-(dist*10),50);
  }

  //выводим статус
  if(signalA){
    lcd.setCursor(0, 0);
    lcd.print("WARNING");
  }
  else{
    lcd.setCursor(0, 0);
    lcd.print("                ");
  }
  
  
  dist = (matrix[angle] + dist)/2;

  matrix[angle] = dist;

  if(detour == DETOUR){
    wrFile_1(signalA);  
  }
  
  
  if(signalA){
    signalA = false;  
  }

  
  delay(10);
  
  if(direct){
    eng.step(STEPP/36);
    angle -= 1; 
  }
  else{
    eng.step(-(STEPP/36));
    angle += 1;
  }

  if( (angle == 35)||(angle == 0) ) {
    direct = !direct;
  }

  if( (angle == 0)&&(detour != DETOUR) ){
    detour++;   
  }

}
