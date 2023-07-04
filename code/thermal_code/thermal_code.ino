#include "thermal_camera.h"
#include <SoftwareSerial.h>

SoftwareSerial soft(3, 2);
thermal_camera tc(soft);

void setup()
{
  Serial.begin(9600);
  soft.begin(9600);
  tc.begin();
}

void loop()
{
  if ( Serial.available() )
  {
    int cmd = Serial.read();
    if ( cmd == '1' )
    {
      float max_value, min_value;
      if ( tc.get_min_max_temperature(max_value, min_value) == true )
      {
        Serial.print("MAX : ");
        Serial.print(max_value);
        Serial.print(",");
        Serial.print("MIN : ");
        Serial.print(min_value);
        Serial.println("");
      }
      else
      {
        Serial.println("FAILED");
      }
    }
  }
}
