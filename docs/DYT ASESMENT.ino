#include <LiquidCrystal_SR_LCD3.h>
const int PIN_LCD_STROBE = 2;
const int PIN_LCD_CLOCK = 3;
const int PIN_LCD_DATA = 4;
int pingPin = 13;
int echoPin = 12;
long duration, cm;

int a=11;
int b=10;
int c=9;
int d=8;
int e=7;
int f=6;
int g=5;

int score = 3;

LiquidCrystal_SR_LCD3 lcd(PIN_LCD_DATA, PIN_LCD_CLOCK, PIN_LCD_STROBE );
LiquidCrystal_SR_LCD3 lcd2(PIN_LCD_DATA, PIN_LCD_CLOCK, PIN_LCD_STROBE );

int buzzer = A5;
int tombol = 0;
String obstacleAtas  = "XOXXOXOO";
String obstacleBawah = "OOXXXOXO";
String panah = "<";
boolean gameRun=false;
boolean ulang=true;
int statusPanah=0;
String positionCursor;
char charO='O';
char charX='X';

void setup() {
  // put your setup code here, to run once:
  for(int i=11; i>=5; i--){
    pinMode(i, OUTPUT);
  }
  
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  lcd.begin(16, 2);
  lcd.home();
  lcd.setCursor(0,0);
  lcd.print("Nama: Wahyu N.");
  lcd.setCursor(0,1);
  lcd.print("NIM: 6706160059"); 
  
  Serial.println("Tekan spasi untuk memulai game");
}

void loop() {
  displayScoreSevenSegment();
  // put your main code here, to run repeatedly:

  if(Serial.available() > 0 && gameRun==false){ //read the incoming byte 
    tombol = Serial.read();
    if(tombol == 32){
      Serial.println("Space");
      lcd.clear();
      Serial.print("Game Dimulai");
      lcd.clear();
      gameRun=true;
      ulang=true;
    }
  }

  if(gameRun==true){
    lcd.clear();
    while (ulang==true){
      runObstacle(); 
      ulang=false;
    }
    if(score>0){
      gameRun=false;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Your Score : ");
      lcd.setCursor(0,1);
      lcd.print(score);
    }
    if(score==0){
      gameRun=false;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("GAME OVER!!!");
    }
    
  }
}

void runObstacle() {
  int muncul=30;
  boolean tampil=true;
  String tambahKarakter;
  int karakterAtasKe=0;
  int karakterBawahKe=0;
  boolean tampilAtas=true;
  String karakterAtas;
  String karakterBawah;
  for (int i=1; i<=30; i++){
    if(score==0){
       gameRun=true;
       ulang=false;
       loop();
    }
    sensorUltrasonic();
    
    if(tampil==true){
      
      if(tampilAtas==true){
        lcd.setCursor(0,1);
        karakterBawah = "  " + karakterBawah;
        lcd.print(karakterBawah);
        lcd.setCursor(0,0);
        karakterAtas = obstacleAtas[karakterAtasKe] + karakterAtas;
        lcd.print(karakterAtas);
        karakterAtasKe++;
        tampil=false;
        tampilAtas=false;
        karakterBawah = "  " + karakterBawah;
        Serial.print("Isi baris atas : ");
        Serial.println(obstacleAtas[karakterAtasKe]);
        Serial.print("Isi baris atas : ");
        Serial.println(" ");
        char obstacleKarakter = obstacleAtas[karakterAtasKe-2];
        if(statusPanah == 119){
          lcd.setCursor(15, 0);
          lcd.print(panah);
          lcd.setCursor(15, 1);
          lcd.print(" ");
          if(i > 8){
            if(obstacleKarakter == charO){
              score = score + 1;
            }else{
              score = score - 1;
            }
          }
          displayScoreSevenSegment();
        }else if(statusPanah == 115){
          lcd.setCursor(15, 0);
          lcd.print(" ");
          lcd.setCursor(15, 1);
          lcd.print(panah);
        }
      } else {
        lcd.setCursor(0,0);
        karakterAtas = "  " + karakterAtas;
        lcd.print(karakterAtas);
        
        lcd.setCursor(0,1);
        karakterBawah = obstacleBawah[karakterBawahKe] + karakterBawah;
        lcd.print(karakterBawah);
        karakterBawahKe++;
        tampil=false;
        tampilAtas=true;
        karakterAtas = "  " + karakterAtas;
        Serial.print("Isi baris bawah : ");
        Serial.println(obstacleBawah[karakterBawahKe-2]);
        Serial.print("Isi baris bawah : ");
        Serial.println(" ");
        char obstacleKarakter = obstacleBawah[karakterBawahKe];
        if(statusPanah == 119){
          lcd.setCursor(15, 0);
          lcd.print(panah);
          lcd.setCursor(15, 1);
          lcd.print(" ");
        }else if(statusPanah == 115){
          lcd.setCursor(15, 0);
          lcd.print(" ");
          lcd.setCursor(15, 1);
          lcd.print(panah);
          if(i > 8){
            if(obstacleKarakter == charO){
              score = score + 1;
            }else{
              score = score - 1;
            }
          }
          displayScoreSevenSegment(); 
        }
        
      }
      buttonSW();
      delay(cm);
    } else {
      karakterAtas = " " + karakterAtas;
      karakterBawah = " " + karakterBawah;
      tampil=true;
    }

  }
}

void buttonSW(){
    if(Serial.available() > 0){ //read the incoming byte 
      tombol = Serial.read();
      Serial.print("Input Keyboard : ");
      switch(tombol){ 
        case 119:
          Serial.println("w");
          lcd.setCursor(15, 0);
          lcd.print(panah);
          lcd.setCursor(15, 1);
          lcd.print(" ");
          statusPanah = 119;
          break; 
        case 115:
          Serial.println("s");
          lcd.setCursor(15, 0);
          lcd.print(" ");
          lcd.setCursor(15, 1);
          lcd.print(panah);
          statusPanah = 115;
          break;
      }
    }
}

void displayScoreSevenSegment(){
  if (score==0){
    digitalWrite(a,HIGH);  
    digitalWrite(b,HIGH);  
    digitalWrite(c,HIGH);  
    digitalWrite(d,HIGH);  
    digitalWrite(e,HIGH);  
    digitalWrite(f,HIGH);  
    digitalWrite(g,LOW); 
  }if (score==1){
    digitalWrite(a,LOW);  
    digitalWrite(b,HIGH);  
    digitalWrite(c,HIGH);  
    digitalWrite(d,LOW);  
    digitalWrite(e,LOW);  
    digitalWrite(f,LOW);  
    digitalWrite(g,LOW);   
  }if (score==2){
    digitalWrite(a,HIGH);  
    digitalWrite(b,HIGH);  
    digitalWrite(c,LOW);  
    digitalWrite(d,HIGH);  
    digitalWrite(e,HIGH);  
    digitalWrite(f,LOW);  
    digitalWrite(g,HIGH);
  }if (score==3){
    digitalWrite(a,HIGH);  
    digitalWrite(b,HIGH);  
    digitalWrite(c,HIGH);  
    digitalWrite(d,HIGH);  
    digitalWrite(e,LOW);  
    digitalWrite(f,LOW);  
    digitalWrite(g,HIGH);
  }if (score==4){
    digitalWrite(a,LOW);  
    digitalWrite(b,HIGH);  
    digitalWrite(c,HIGH);  
    digitalWrite(d,LOW);  
    digitalWrite(e,LOW);  
    digitalWrite(f,HIGH);  
    digitalWrite(g,HIGH);
  }if (score==5){
    digitalWrite(a,HIGH);  
    digitalWrite(b,LOW);  
    digitalWrite(c,HIGH);  
    digitalWrite(d,HIGH);  
    digitalWrite(e,LOW);  
    digitalWrite(f,HIGH);  
    digitalWrite(g,HIGH);
  }if (score==6){
    digitalWrite(a,HIGH);  
    digitalWrite(b,LOW);  
    digitalWrite(c,HIGH);  
    digitalWrite(d,HIGH);  
    digitalWrite(e,HIGH);  
    digitalWrite(f,HIGH);  
    digitalWrite(g,HIGH);
  }if (score==7){
    digitalWrite(a,HIGH);  
    digitalWrite(b,HIGH);  
    digitalWrite(c,HIGH);  
    digitalWrite(d,LOW);  
    digitalWrite(e,LOW);  
    digitalWrite(f,LOW);  
    digitalWrite(g,LOW);
  }if (score==8){
    digitalWrite(a,HIGH);  
    digitalWrite(b,HIGH);  
    digitalWrite(c,HIGH);  
    digitalWrite(d,HIGH);  
    digitalWrite(e,HIGH);  
    digitalWrite(f,HIGH);  
    digitalWrite(g,HIGH);
  }if (score==9){
    digitalWrite(a,HIGH);  
    digitalWrite(b,HIGH);  
    digitalWrite(c,HIGH);  
    digitalWrite(d,HIGH);  
    digitalWrite(e,LOW);  
    digitalWrite(f,HIGH);  
    digitalWrite(g,HIGH);
  } 
}

void sensorUltrasonic(){
  pinMode(pingPin,OUTPUT);
  digitalWrite(pingPin,LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin,LOW);
  pinMode(echoPin, INPUT); 
  duration = pulseIn(echoPin, HIGH); cm =
  microsecondsToCentimeters(duration);

  if(cm < 300){
    digitalWrite(buzzer, HIGH);
  } else {
    digitalWrite(buzzer, LOW);
  }
}

long microsecondsToCentimeters(long microseconds) { 
  return microseconds / 29 / 2;
}
