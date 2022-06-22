// Belinay Polatcan 210202104
// Ahmet Can Okumus 200202015


#include <LiquidCrystal.h>
#include <Keypad.h>

#define sifre_uzunluk 4

  int yanginSensorPin= A0;
  int yanginSensorbuzzer = 48;
  int hareketSensorPin=13;
  boolean hareketSensordegeri=0;
  int hareketsensor_lamba=34;
  int kapi_ledred=37;
  int kapi_ledgreen=36;
  float sicaklikdegeri;
  int i=0;
  char sifre_eleman=0;
  int keypadgiris=0;
  



char kapi_sifre[sifre_uzunluk]={'1','7','0','1'};
char alinan_sifre[sifre_uzunluk]={0};

const int satir = 4; 
const int sutun = 3; 



char tuslar[satir][sutun] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'#','0','*'}
};


byte satirpin[satir] = {43, 44, 45, 46}; 
byte sutunpin[sutun] = {40, 39, 38}; 



Keypad cKeypad = Keypad( makeKeymap(tuslar), satirpin, sutunpin, satir, sutun );

LiquidCrystal lcd(26,27,28,29,30,31);
 
void sifre_Al(){
   
  
    sifre_eleman=cKeypad.getKey();
    
    
    if(sifre_eleman){

    Serial.print(sifre_eleman);
      
    alinan_sifre[i]=sifre_eleman;
    
    i++;
    
  }
  
 
  
}



bool sifre_Eslestir(){
   

  if(alinan_sifre[0]==kapi_sifre[0] && alinan_sifre[1]==kapi_sifre[1] && alinan_sifre[2]==kapi_sifre[2] && alinan_sifre[3]==kapi_sifre[3]){
    
    return true;
    
  }

  return false;

  
}




   
  
  
void setup() {

    Serial.begin(9600);
    
    analogReference(INTERNAL1V1);
  
    pinMode(kapi_ledred,OUTPUT);
    pinMode(kapi_ledgreen,OUTPUT);
    
     
   lcd.begin(16, 2);
   
   
   
    pinMode(yanginSensorPin, INPUT_PULLUP);
    pinMode(yanginSensorbuzzer, OUTPUT);
    pinMode(hareketSensorPin,INPUT);
    pinMode(hareketsensor_lamba,OUTPUT);
    
}




void loop() {


   // Kapi Sifre 

   sifre_Al();

    
   if(i==4){
    
    i=0;
    
    if(sifre_Eslestir()==true ){
      
      
    digitalWrite(kapi_ledgreen,HIGH);

    
    delay(1000);    

    
    digitalWrite(kapi_ledgreen,LOW);

    
    }
    if(sifre_Eslestir()==false ){
      
      
      digitalWrite(kapi_ledred,HIGH);

      
      delay(1000);

     
      digitalWrite(kapi_ledred,LOW);

    }
    
   }

   
    
    
     // Sicaklik Sensoru

    
 
   sicaklikdegeri=analogRead(A1);
   
   
   sicaklikdegeri=sicaklikdegeri*1100/(1024*10);
   lcd.print("SICAKLIK ");
   lcd.print(sicaklikdegeri);
   lcd.print("*C");
   delay(100);
   lcd.clear();

  
    
    
    if(sicaklikdegeri<20){
      lcd.print("SICAKLIK ");
      lcd.print(sicaklikdegeri);
      lcd.print("*C");
      lcd.setCursor(2,1);
    lcd.print("SICAKLIK DUSTU!");
    }

   
    
    if(sicaklikdegeri>30){
      lcd.print("SICAKLIK ");
      lcd.print(sicaklikdegeri);
      lcd.print("*C");
      lcd.setCursor(0,1);
      lcd.print("SICAKLIKYUKSELDI");
      
    }


    

    // Yangin Sensoru
    
  
   int yanginSensordegeri = digitalRead(yanginSensorPin);
   
   

    if(yanginSensordegeri==HIGH)
    {
      
    digitalWrite(yanginSensorbuzzer, HIGH);
  
     }
     
     else
     {
      
    digitalWrite(yanginSensorbuzzer, LOW); 
    
     } 



   // Hareket Sensoru
  
  
   hareketSensordegeri=digitalRead(hareketSensorPin);
  
  
    if(hareketSensordegeri==1){
    digitalWrite(hareketsensor_lamba,HIGH);
    
     }
    else{
    
    digitalWrite(hareketsensor_lamba,LOW);
    
    
    }


       




}
