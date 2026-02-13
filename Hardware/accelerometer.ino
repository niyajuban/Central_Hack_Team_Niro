#include <Wire.h>

const int MPU_ADDR = 0x68; 

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22); // SDA->21, SCL->22
  delay(100);

  // WAKE UP SENSOR
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // Wake up
  Wire.endTransmission(true);
}

void loop() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);  // Start reading at ACCEL_XOUT_H
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 6, true); 

  // Read raw 16-bit integers
  int16_t AcX = Wire.read()<<8 | Wire.read();      
  int16_t AcY = Wire.read()<<8 | Wire.read();  
  int16_t AcZ = Wire.read()<<8 | Wire.read();  

  // PRINT ONLY DATA: x,y,z
  Serial.print(AcX); Serial.print(",");
  Serial.print(AcY); Serial.print(",");
  Serial.println(AcZ);
  
  delay(10); // 100Hz Sampling
}
