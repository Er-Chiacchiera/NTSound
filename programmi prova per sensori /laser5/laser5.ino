#include <Wire.h>  //"#include Wire.h
#include <VL53L0X.h>  //#include VL53L0X.h
VL53L0X sensor;

#define HIGH_ACCURACY

void setup()
{
  Serial.begin(9600);
  delay(10);
  Wire.begin();
  sensor.init();
  sensor.setTimeout(500);

#if defined LONG_RANGE
  
  sensor.setSignalRateLimit(0.1);
  // increase laser pulse periods (defaults are 14 and 10 PCLKs)
  sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);//default
  sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);//default
  //sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 28);//default
  //sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 20);//default
#endif

#if defined HIGH_SPEED
  // reduce timing budget to 20 ms (default is about 33 ms)
  sensor.setMeasurementTimingBudget(20000);//default
#elif defined HIGH_ACCURACY
  // increase timing budget to 200 ms
  sensor.setMeasurementTimingBudget(200000);
#endif
}

void loop()
{

  long DISTANCE = (sensor.readRangeSingleMillimeters()/25.4001);
  if (sensor.timeoutOccurred())
  {
    Serial.print("Distance (READING): ");
    Serial.print(" TIMEOUT"); 
  }
  else
  {
    Serial.print("Distance   (feet): ");
    Serial.println(DISTANCE/12);
    Serial.print("Distance (inches): ");
    Serial.println(DISTANCE);
  }
  
  Serial.println();
  Serial.println();
  Serial.println();
  delay(100);
}
