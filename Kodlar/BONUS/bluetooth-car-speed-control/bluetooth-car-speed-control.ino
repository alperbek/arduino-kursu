#include <SoftwareSerial.h>
/*

Bu taslak HC05 Bluetooth modulu ile model arabanin 
kontrolunu L298 motor surucusu ile devir kontrollu (MAHiz,MBHiz) 
olarak gerceklestirmektedir.

Programin tus kontrolleri (FIGBLRJH) "Arduino Bluetooth RC Car" uygulamasina
gore ayarlanmistir. Uygulamanin simgesi ve ekran goruntusu taslak 
klasorunde yer alir. Bu uygulamanin yerine herhangi bir uygulama kullanilabilir. 
Bir uygulamanin gonderdigi tuslari gormek icin "hc05-monitor" uygulamasini kullanin.

Arduino Bluetooth RC Car
https://play.google.com/store/apps/details?id=braulio.calle.bluetoothRCcontroller&hl=en_US

Yazan: Ozgur Koca, Aralik 2018 / Tankado.com


   Baglanti semasi:
   Bluetooth  Arduino
   ------------------
   RX     =>  2 (Tx)
   TX     =>  3 (Rx)
*/
SoftwareSerial maviDis(3, 2);  // RX,TX

const byte MAA = 8; //L298 IN1
const byte MAK = 9; //L298 IN2
const byte MBA = 10; //L298 IN3
const byte MBK = 11; //L298 IN4

byte MAHiz = 5; // Motor A hiz kontrol pini 
byte MBHiz = 6; // Motor B hiz kontrol pini

void dur() {
  digitalWrite(MAA, LOW);
  digitalWrite(MAK, LOW);
  digitalWrite(MBA, LOW);
  digitalWrite(MBK, LOW);
  analogWrite(MAHiz, 0);
  analogWrite(MBHiz, 0);
}

void ileri() {
  digitalWrite(MAA, HIGH);
  digitalWrite(MAK, LOW);
  digitalWrite(MBA, HIGH);
  digitalWrite(MBK, LOW);
}

void geri() {
  digitalWrite(MAA, LOW);
  digitalWrite(MAK, HIGH);
  digitalWrite(MBA, LOW);
  digitalWrite(MBK, HIGH);
}

void setup()
{  
  pinMode(MAA, OUTPUT);
  pinMode(MAK, OUTPUT);
  pinMode(MBA, OUTPUT);
  pinMode(MBK, OUTPUT);
  
  maviDis.begin(9600);
  maviDis.println("Program basladi.");
  Serial.begin(9600);
  Serial.println("Program basladi.");
}

void loop()
{       
  if (maviDis.available()) {

    char komut = maviDis.read();

    Serial.print(komut);
    
    // Forward = ileri
    if ('F' == komut) {
        ileri();
        analogWrite(MAHiz, 255);
        analogWrite(MBHiz, 255);
    }

    // Ileri sag
    if ('I' == komut) {
      ileri();        
      analogWrite(MAHiz, 255);
      analogWrite(MBHiz, 150);
    }

    // Ileri sol
    if ('G' == komut) {
      ileri();
      analogWrite(MAHiz, 150);
      analogWrite(MBHiz, 255);
    } 
    
    // Backward = geri
    if ('B' == komut) {
      geri();
      analogWrite(MAHiz, 255);
      analogWrite(MBHiz, 255);
    }

    // Kendi etrafinda sola don
    if ('L' == komut ) {
      digitalWrite(MAA, HIGH);
      digitalWrite(MAK, LOW);
      digitalWrite(MBA, LOW);
      digitalWrite(MBK, HIGH);
      analogWrite(MAHiz, 255);
      analogWrite(MBHiz, 255);
    }

    // Kendi etrafinda saga don
    if ('R' == komut) {
      digitalWrite(MAA, LOW);
      digitalWrite(MAK, HIGH);
      digitalWrite(MBA, HIGH);
      digitalWrite(MBK, LOW);
      analogWrite(MAHiz, 255);
      analogWrite(MBHiz, 255);
    }
    
    // Geri sag
    if ('J' == komut) {
      geri();
      analogWrite(MAHiz, 255);
      analogWrite(MBHiz, 150);
    }
    
    // Geri sol
    if ('H' == komut) {
      geri();
      analogWrite(MAHiz, 150);
      analogWrite(MBHiz, 255);
    }

    // Dur
    if ('S' == komut)
    dur();
  }
}
