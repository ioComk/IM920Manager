#include <SoftwareSerial.h>
#include"IM920Driver.h"

const int RX = 8;
const int TX = 9;

SoftwareSerial IM920Serial(RX, TX);
IM920Driver im920(&IM920Serial);

byte val[5] = {1, 2, 3, 4, 10};
String txda = "TXDA ";

void setup() {
  Serial.begin(115200);
  IM920Serial.begin(19200);

  im920.send("ECIO"); //キャラクタ入出力モード
  im920.send("STRT 1"); //高速通信モード[50kbps]

  delay(1000);

  for (int i = 0; i < 5; i++) {
    String str = String(val[i]);
    txda.concat(str);
    txda.concat(',');
  }
}

void loop() {

  Serial.println(txda);

  im920.send(txda.c_str());

  //  delay(5);
}
