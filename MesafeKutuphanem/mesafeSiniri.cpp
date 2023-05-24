#include "mesafeSiniri.h"

int trig;
int echo;

void mesafePinler(int t, int e){
  pinMode(t,OUTPUT);
  pinMode(e, INPUT);
  //Globale atma işlemini gerçekleştirdim.
  trig=t;
  echo=e;  
}

int mesafe(){//mesafe değerini döndürecek
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  int sure= pulseIn(echo,HIGH);
  int mesafe_deger =(sure/2)/29.1;
  return mesafe_deger;
  
}
