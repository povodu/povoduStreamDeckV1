//Gerekli kütüphaneleris tanımlıyoruz.
#include <OLED_I2C.h>
#include <Keypad.h>
#include "Keyboard.h"
#include <Encoder.h>

//Gerekli pinler ve değişkenleri tanımlıyoruz.
Encoder RotaryEncoderA(4, 5);
Encoder RotaryEncoderB(7, 8);

short positionEncoderA = -999;
short positionEncoderB = -999;

const byte satir = 2;
const byte sutun = 5;

char klavyeMatrix[satir][sutun] = {
  {'0', '1', '2', '3', '4'},
  {'5', '6', '7', '8', '9'},
};

byte satirPin[satir] = {A1, A2};
byte sutunPin[sutun] = {10, 16, 14, 15, A0};

OLED ekranOLED(SDA, SCL);

Keypad klavye = Keypad(makeKeymap(klavyeMatrix), satirPin, sutunPin, satir, sutun);

extern uint8_t mic1[], mic2[], mic3[], mic4[], mic5[], mic6[];
extern uint8_t kamera1[], kamera2[], kamera3[];
extern uint8_t sahne1[], sahne2[], sahne3[];
extern uint8_t youtube[], instagram[];
extern uint8_t mute[], sound[];
extern uint8_t povodu[];

bool micDurum = 0;
bool sesDurum = 0;

void setup()
{
  if (!ekranOLED.begin(SSD1306_128X64))
    while (1)
      ;

  Serial.begin(9600);
  Keyboard.begin();

  ekranOLED.clrScr();
  yazdir(povodu);
}

void loop()
{
  encoderA();
  encoderB();

  char basilanTus = klavye.getKey();
  Serial.println(basilanTus);
  
  //Eğer sıfırıncı tuşa basıldıysa bu işlemler yapılıyor.
  if (basilanTus == '0')
  {
    yazdir(kamera1);
    
    Keyboard.press(KEY_DOWN_ARROW);
    Keyboard.releaseAll();
    
    delay(1000);
    yazdir(povodu);
    //Önce bir animasyonu sonra basılmasını istediğimiz tuşlar en son da bir animasyon daha gerçekleşiyor.
  }
  //Eğer birinci tuşa basıldıysa bu işlemler yapılıyor.
  if (basilanTus == '1')
  {
    yazdir(kamera2);
    
    Keyboard.press(KEY_DOWN_ARROW);
    Keyboard.releaseAll();

    delay(1000);
    yazdir(povodu);
  }
  //Eğer ikinci tuşa basıldıysa bu işlemler yapılıyor.
  if (basilanTus == '2')
  {
    yazdir(kamera3);
    delay(1000);
    yazdir(povodu);
  }
  //Eğer üçüncü tuşa basıldıysa bu işlemler yapılıyor.
  if (basilanTus == '3') // Mikrofon
  {
    if (micDurum)
    {
      micAcik();
      
      micDurum = 0;
      delay(1000);
      yazdir(povodu);
    }

    else
    {
      micKapali();
      
      micDurum = 1;
      delay(1000);
      yazdir(povodu);
    }
  }
  //Eğer dördüncü tuşa basıldıysa bu işlemler yapılıyor.
  if (basilanTus == '4')
  {
    if (sesDurum)
    {
      yazdir(sound);
      sesDurum = 0;
      delay(1000);
      yazdir(povodu);
    }

    else
    {
      yazdir(mute);
      sesDurum = 1;
      delay(1000);
      yazdir(povodu);
    }
  }
  //Eğer beşinci tuşa basıldıysa bu işlemler yapılıyor.
  if (basilanTus == '5')
  {
    yazdir(sahne1);
    delay(1000);
    yazdir(povodu);
  }
  //Eğer altıncı tuşa basıldıysa bu işlemler yapılıyor.
  if (basilanTus == '6')
  {
    yazdir(sahne2);
    delay(1000);
    yazdir(povodu);
  }
  //Eğer yedinci tuşa basıldıysa bu işlemler yapılıyor.
  if (basilanTus == '7')
  {
    yazdir(sahne3);
    delay(1000);
    yazdir(povodu);
  }
  //Eğer sekizinci tuşa basıldıysa bu işlemler yapılıyor.
  if (basilanTus == '8')
  {
    yazdir(instagram);
    delay(1000);
    yazdir(povodu);
  }
  //Eğer dokuzuncu tuşa basıldıysa bu işlemler yapılıyor.
  if (basilanTus == '9')
  {

    yazdir(youtube);
    delay(1000);
    yazdir(povodu);
  }

  delay(10);
}
//Mikrofon animasyonları
void micAcik()
{
  yazdir(mic6);
  yazdir(mic5);
  yazdir(mic4);
  yazdir(mic3);
  yazdir(mic2);
  yazdir(mic1);
}

void micKapali()
{
  yazdir(mic1);
  yazdir(mic2);
  yazdir(mic3);
  yazdir(mic4);
  yazdir(mic5);
  yazdir(mic6);
}
//OLED ekrana yazdırma fonksiyonu.
void yazdir(uint8_t *grafik)
{

  ekranOLED.clrScr();
  ekranOLED.drawBitmap(0, 0, grafik, 128, 64);
  ekranOLED.update();
  delay(50);
}

//Encoderların ne yapmasını istiyorsak buradan değiştiriyoruz.
void encoderA()
{
  long newPos = RotaryEncoderA.read() / 4;

  if (newPos != positionEncoderA && newPos > positionEncoderA)
  {
    positionEncoderA = newPos;
    //Serial.println(positionEncoderA);
    Keyboard.write(KEY_LEFT_ARROW);
  }

  if (newPos != positionEncoderA && newPos < positionEncoderA)
  {
    positionEncoderA = newPos;
    //Serial.println(positionEncoderA);
    Keyboard.write(KEY_RIGHT_ARROW);
  }
}

void encoderB()
{
  long newPos = RotaryEncoderB.read() / 4;
  if (newPos != positionEncoderB && newPos > positionEncoderB)
  {
    positionEncoderB = newPos;
    //Serial.println(positionEncoderB);
    Keyboard.press(KEY_UP_ARROW);
    Keyboard.release(KEY_UP_ARROW);
  }

  if (newPos != positionEncoderB && newPos < positionEncoderB)
  {
    positionEncoderB = newPos;
    //Serial.println(positionEncoderB);
    Keyboard.press(KEY_DOWN_ARROW);
    Keyboard.release(KEY_DOWN_ARROW);
  }
}
