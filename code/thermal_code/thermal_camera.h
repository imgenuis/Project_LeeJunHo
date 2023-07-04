class thermal_camera
{
  public:
    Stream *_stream;
    thermal_camera(Stream & stream);
    void begin();
    int wait_stream_available(int required_byte = 1, unsigned int delay_time = 100);
    bool get_min_max_temperature(float & max, float & min);
    bool get_temperature_row(int row, float* min);
};

thermal_camera::thermal_camera(Stream &stream)
{
  _stream = &stream;
}

void thermal_camera::begin()
{
}

int thermal_camera::wait_stream_available(int required_byte, unsigned int delay_time) // 시리얼 신호를 받을때까지 대기 대기시간은 0.1초
{
  if ( _stream->available() >= required_byte) return _stream->available();

  unsigned long start_millis = millis();

  while ( ( millis() - start_millis ) < delay_time )
  {
    if ( _stream->available() >= required_byte ) return _stream->available();
  }
  return 0;
}

bool thermal_camera::get_min_max_temperature(float &max, float& min)
{
  while (_stream->available())
  {
    _stream->read();
  }
  _stream->write('k');
  _stream->write(1);
  if ( wait_stream_available(4, 500) == 0 ) return false;
  int value1 = _stream->read();
  value1 = value1 | ( _stream->read() << 8 );
  int value2 = _stream->read();
  value2 = value2 | ( _stream->read() << 8 );
  max = value1 / 10.0;
  min = value2 / 10.0;
  return true;
}

bool thermal_camera::get_temperature_row(int row, float* data)
{
  row = 7 - row;
  while (_stream->available())
  {
    _stream->read();
  }
  _stream->write('k');
  _stream->write(2);
  _stream->write(row);

  if (wait_stream_available(16, 500) < 16) return false;
  for ( int j = 0; j < 8; j++ )
  {
    int value1 = _stream->read();
    value1 = value1 | ( _stream->read() << 8 );

    data[j] = value1/10.0;
  }
  return true;
}
