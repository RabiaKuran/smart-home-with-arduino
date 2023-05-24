#include <mesafeSiniri.h> //Mesafe kontrolünü yapmam için oluşturduğum kütüphanemi ekledim.
#include <SPI.h>
#include <Adafruit_GFX.h>//nokia
#include <Adafruit_PCD8544.h>
#include<Servo.h>
#include <EEPROM.h>
Servo myServoMotor; //verdiğim ismi arduinoya tanıttım
int address = 0; //eeprom için
int led1 = 8; //değişkenlerimi tanımladım.
int led2 = 9;
int buzzerPin = 2;//buzzerin uzun bacağını bağladım
// Yazılım SPI için LCD nesnesi bildir
// Adafruit_PCD8544(CLK,DIN,D/C,CE,RST);
Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);
int derece;

void setup() {//pinMode diyerek tüm pinlerimi tanıttım.
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  Serial.begin(9600);//bant genişliği
  mesafePinler(10, 11);//kütüphanemin icerisinde ki methodumun içine 10,11 degerlerini gönderdim
  pinMode(buzzerPin, OUTPUT);//zilin pinini tanıttım
 

  display.begin();// Ekranı Başlat
  display.setContrast(57);// ekranı en iyi görüntülemeye uyarlamak için kontrastı değiştirebilirsiniz!
  display.clearDisplay();  // Arabelleği temizle.
  display.setTextSize(2);
  display.setTextColor(BLACK);
  display.setCursor(0, 0);
  display.println("WELCOMETO YOUR SMART HOME");
  display.drawRect(0, 0, 83, 47, BLACK);//yazılarımı dikdörtgen seklinin icine aliyor.
  display.display();
  delay(6000);//biraz bekledikten sonra yazıyı değiştiriyor
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(10, 10);
  display.println(" AKILLI EV    UYGULAMANIZ   BASLATILDI");
  display.drawRect(0, 0, 83, 47, BLACK);
  display.display();
  delay(6000);
  display.clearDisplay();
   myServoMotor.attach(12);//12.pinime bağladım
   myServoMotor.write(0);//acı değerini yazdım kapı kapalı olacak
}

void loop() {
  //digitalWrite(buzzerPin, LOW);
  if (Serial.available()) { //Bluetooth aktif mi diye kontrol açtım.
    char veri = Serial.read(); //Seriport ekranına gelen veriyi okur.
    if (veri == 'A') {//telefondan buton kontrolleri icin veri degiskeni kontrolleri olusturdum.
      digitalWrite(led1, HIGH);
    } else if (veri == 'B') {
      digitalWrite(led1, LOW);
    } else if (veri == 'C') {
      digitalWrite(led2, HIGH);
    } else if (veri == 'D') {
      digitalWrite(led2, LOW);
    }else if (veri == 'E') {//uzaktan dugmeye basılınca yeniden sistem kuruluyor
      display.begin();// Ekranı Başlat
      display.setContrast(57);// ekranı en iyi görüntülemeye uyarlamak için kontrastı değiştirebilirsiniz!
      display.clearDisplay();  // Arabelleği temizle.
      display.setTextSize(2);
      display.setTextColor(BLACK);
      display.setCursor(0, 0);
      display.println("WELCOMETO YOUR SMART HOME");
      display.drawRect(0, 0, 83, 47, BLACK);
      display.display();
      delay(6000);
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(BLACK);
      display.setCursor(10, 10);
      display.println(" AKILLI EV    UYGULAMANIZ   BASLATILDI");
      display.drawRect(0, 0, 83, 47, BLACK);
      display.display();
      delay(6000);
      display.clearDisplay();
      
    } else if (veri == 'H') { // açı değeri değişkeninin değerini 0 ile 180 derece arasında değiştirerek servo motoru farklı açı değerlerinde döndürebiliriz
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(BLACK);
      display.setCursor(4, 4);
      display.println("Kapi aciliyor");
      display.drawRect(0, 0, 83, 47, BLACK);
      display.display();
      delay(6000);
      display.clearDisplay();
      for (derece = 0; derece < 90; derece++)
      {
        myServoMotor.write(derece);
      }  
      display.setTextSize(1);
      display.setTextColor(BLACK);
      display.setCursor(5, 5);
      display.println("Kapi acildi");
      display.drawRect(0, 0, 83, 47, BLACK);
      display.display();    

      
    }else if (veri == 'G') {//Kapı kapanıyor
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(BLACK);
      display.setCursor(5, 5);
      display.println("Kapi kapaniyor.");
      display.drawRect(0, 0, 83, 47, BLACK);
      display.display();
      delay(6000);
      display.clearDisplay();     
      for (derece = 90; derece > 1; derece--)
      {
        myServoMotor.write(derece);
      } 
      display.setTextSize(1);
      display.setTextColor(BLACK);
      display.setCursor(5, 5);
      display.println("Kapi kapandi");
      display.drawRect(0, 0, 83, 47, BLACK);
      display.display();
    }
  }
  // EEPROM'un geçerli adresinden bir bayt oku
  int yakinlasma = mesafe();
  EEPROM.write(address,yakinlasma);//kaydedilecek adres ve kaydedilecek değeri belirttim
  //Serial.println(yakinlasma);
  if (yakinlasma < 10 && yakinlasma!=0) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(BLACK);
    display.setCursor(0, 5);
    display.println("Korumali alanacok yaklasildi");
    display.setTextSize(2);
    display.println(EEPROM.read(address));
    display.setTextSize(1);
    display.println("cm yaklasildi");
    display.drawRect(0, 0, 83, 47, BLACK);
    display.display();
    delay(6000);
    display.clearDisplay(); 
    
    Serial.println("zil caldi");
    Serial.println(EEPROM.read(0));//degeri eepromdan okuyor
    digitalWrite(buzzerPin, HIGH);//10cmden yakına yaklasılırsa zil calacak daha sonra susacak, sayı değeri ekranda gösterilecek.
    delay(3000);
    digitalWrite(buzzerPin, LOW);
  } else {
    digitalWrite(buzzerPin, LOW);
  }
}
