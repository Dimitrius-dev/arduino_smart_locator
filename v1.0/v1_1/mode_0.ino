
void hello(){
  Beep(700,30);
  lcd.setCursor(0, 0);
  lcd.print("IVBO-01-20");
  lcd.setCursor(0, 1);
  lcd.print("Project locator ");
  delay(1500);
  lcd.clear();

  Beep(700,30);
  lcd.setCursor(0, 0);
  lcd.print("Belov D.S.");
  lcd.setCursor(0, 1);
  lcd.print("Syhanov N.A.");
  delay(1500);
  Beep(700,30);
  lcd.setCursor(0, 0);
  lcd.print("Pushkina A.A.");
  lcd.setCursor(0, 1);
  lcd.print("Golneva A.A.");
  delay(1500);
}

void mode0(){
  hello();
  lcd.clear();
}
