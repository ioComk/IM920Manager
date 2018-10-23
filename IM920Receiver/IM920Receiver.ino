#include <SoftwareSerial.h>
#include"IM920Driver.h"

const int RX = 8;
const int TX = 9;

SoftwareSerial IM920Serial(RX, TX);
IM920Driver im920(&IM920Serial);

void setup() {
  Serial.begin(115200);
  IM920Serial.begin(19200);

  im920.send("ECIO"); //キャラクタ入出力モード
  im920.send("STRT 1"); //高速通信モード[50kbps]

  delay(1000);
}

void loop() {

  char buff[IM920_BUFFER_SIZE];
  int n;

  while (im920.available()) {
    // ひたすらreadする
    im920.read();

    // 改行が認識された場合
    if ( im920.get_line_changed() ) {
      // その1行を受け取る
      im920.get_last_line(buff);

      // "OK"や"NG"でなければ表示する
      if ( strcmp(buff, "OK\r\n") != 0 && strcmp(buff, "NG\r\n") != 0) {
        Serial.println("New line >>");
        Serial.println(buff);
      }
    }
  }
//  delay(10);
}
