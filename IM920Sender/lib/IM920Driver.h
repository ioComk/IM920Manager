#pragma once

#include <Arduino.h>
#include <SoftwareSerial.h>

// length of buffer
#define IM920_BUFFER_SIZE 80

class IM920Driver
{
public:
  // constructor
  IM920Driver(SoftwareSerial *ser);
  // read 1 character
  char read();
  // return true if buffer contains data
  bool available();
  // send string data to im920 with "\r\n"
  void send(const char str[]);
  // get last line data
  void get_last_line(char buff[IM920_BUFFER_SIZE]);
  // get the length of line data
  int16_t get_line_length();
  // true if new line received
  bool get_line_changed();

private:
  SoftwareSerial *_ser;              // Serial which connected to IM920
  uint8_t *_current_line;            // reading line
  uint8_t *_last_line;               // last line
  uint8_t _line1[IM920_BUFFER_SIZE]; // buffer of line data 1
  uint8_t _line2[IM920_BUFFER_SIZE]; // buffer of line data 1
  uint16_t _idx;                     // length of _current_line
  uint16_t _line_length;             // length of _last_line
  bool _line_changed;                // true if line changed
};

// constructor
IM920Driver::IM920Driver(SoftwareSerial *ser)
{
  _ser = ser;

  _current_line = _line1;
  _idx = 0;

  _last_line = _line2;
  _line_length = 0;

  _line_changed = false;
}

// read 1 character
char IM920Driver::read()
{
  char c = 0;

  if (_ser->available())
    c = _ser->read();
  else
    return c;

  _idx = min(IM920_BUFFER_SIZE - 2, _idx);
  _current_line[_idx] = c;
  _idx++;

  if (c == '\n')
  {
    _current_line[_idx] = '\0';

    uint8_t *temp;
    temp = _current_line;
    _current_line = _last_line;
    _last_line = temp;

    _line_length = _idx;
    _idx = 0;
    _line_changed = true;
  }

  return c;
}

// return true if buffer contains data
bool IM920Driver::available()
{
  return _ser->available();
}

// send string data to im920 with "\r\n"
void IM920Driver::send(const char str[])
{
  _ser->print(str);
  _ser->print("\r\n");
}

// get last line data
void IM920Driver::get_last_line(char buff[IM920_BUFFER_SIZE])
{
  _line_changed = false;
  for (int i = 0; i < _line_length; i++)
    buff[i] = _last_line[i];
  buff[_line_length] = '\0';
}

// get the length of line data
int16_t IM920Driver::get_line_length()
{
  return _line_length;
}

// true if new line received
bool IM920Driver::get_line_changed()
{
  return _line_changed;
}