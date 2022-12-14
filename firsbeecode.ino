#include <Wire.h>
#include <MPU6050.h>
#include "RTClib.h"
#include <math.h>
#define SW1 10

MPU6050 mpu;
RTC_DS3231 rtc;
boolean check = false;
DateTime now;
byte lastButtonState = LOW;
byte battState = LOW;
bool SW1_status = HIGH;
float voltage;
float vDivider; 
float R1 = 10000;
float R2 = 10000;

static byte bPin = A11;
static byte battEn = 4;


void setup() 
{
  Serial.begin(115200);
  vDivider = (R2 / (R1 + R2));
  Serial.println("Initialize MPU6050");

  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_16G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }

  mpu.setAccelPowerOnDelay(MPU6050_DELAY_3MS);

  mpu.setIntFreeFallEnabled(false);  
  mpu.setIntZeroMotionEnabled(false);
  mpu.setIntMotionEnabled(false);
  
  mpu.setDHPFMode(MPU6050_DHPF_5HZ);

  mpu.setMotionDetectionThreshold(2);
  mpu.setMotionDetectionDuration(5);

  mpu.setZeroMotionDetectionThreshold(4);
  mpu.setZeroMotionDetectionDuration(2);	
  
  checkSettings();

  pinMode(SW1, INPUT_PULLUP);

  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  pinMode(6, OUTPUT);
  digitalWrite(6, LOW);  

  pinMode(9, OUTPUT);

  
}

void checkSettings()
{
  Serial.println();
  
  Serial.print(" * Sleep Mode:                ");
  Serial.println(mpu.getSleepEnabled() ? "Enabled" : "Disabled");

  Serial.print(" * Motion Interrupt:     ");
  Serial.println(mpu.getIntMotionEnabled() ? "Enabled" : "Disabled");

  Serial.print(" * Zero Motion Interrupt:     ");
  Serial.println(mpu.getIntZeroMotionEnabled() ? "Enabled" : "Disabled");

  Serial.print(" * Free Fall Interrupt:       ");
  Serial.println(mpu.getIntFreeFallEnabled() ? "Enabled" : "Disabled");
  
  Serial.print(" * Motion Threshold:          ");
  Serial.println(mpu.getMotionDetectionThreshold());

  Serial.print(" * Motion Duration:           ");
  Serial.println(mpu.getMotionDetectionDuration());

  Serial.print(" * Zero Motion Threshold:     ");
  Serial.println(mpu.getZeroMotionDetectionThreshold());

  Serial.print(" * Zero Motion Duration:      ");
  Serial.println(mpu.getZeroMotionDetectionDuration());
  
  Serial.print(" * Clock Source:              ");
  switch(mpu.getClockSource())
  {
    case MPU6050_CLOCK_KEEP_RESET:     Serial.println("Stops the clock and keeps the timing generator in reset"); break;
    case MPU6050_CLOCK_EXTERNAL_19MHZ: Serial.println("PLL with external 19.2MHz reference"); break;
    case MPU6050_CLOCK_EXTERNAL_32KHZ: Serial.println("PLL with external 32.768kHz reference"); break;
    case MPU6050_CLOCK_PLL_ZGYRO:      Serial.println("PLL with Z axis gyroscope reference"); break;
    case MPU6050_CLOCK_PLL_YGYRO:      Serial.println("PLL with Y axis gyroscope reference"); break;
    case MPU6050_CLOCK_PLL_XGYRO:      Serial.println("PLL with X axis gyroscope reference"); break;
    case MPU6050_CLOCK_INTERNAL_8MHZ:  Serial.println("Internal 8MHz oscillator"); break;
  }
  
  Serial.print(" * Accelerometer:             ");
  switch(mpu.getRange())
  {
    case MPU6050_RANGE_16G:            Serial.println("+/- 16 g"); break;
    case MPU6050_RANGE_8G:             Serial.println("+/- 8 g"); break;
    case MPU6050_RANGE_4G:             Serial.println("+/- 4 g"); break;
    case MPU6050_RANGE_2G:             Serial.println("+/- 2 g"); break;
  }  

  Serial.print(" * Accelerometer offsets:     ");
  Serial.print(mpu.getAccelOffsetX());
  Serial.print(" / ");
  Serial.print(mpu.getAccelOffsetY());
  Serial.print(" / ");
  Serial.println(mpu.getAccelOffsetZ());

  Serial.print(" * Accelerometer power delay: ");
  switch(mpu.getAccelPowerOnDelay())
  {
    case MPU6050_DELAY_3MS:            Serial.println("3ms"); break;
    case MPU6050_DELAY_2MS:            Serial.println("2ms"); break;
    case MPU6050_DELAY_1MS:            Serial.println("1ms"); break;
    case MPU6050_NO_DELAY:             Serial.println("0ms"); break;
  }  
  
  Serial.println();
}

void loop()
{
  byte buttonState = digitalRead(SW1);
  if (buttonState != lastButtonState) {
    lastButtonState = buttonState;
    if (buttonState == LOW) {
      battState = (battState == HIGH) ? LOW: HIGH;
      digitalWrite(battEn, battState);
    }
  }
  Vector rawAccel = mpu.readRawAccel();
  Vector normAccel = mpu.readNormalizeAccel();
  Vector scalAccel = mpu.readScaledAccel();
  Activites act = mpu.readActivites();
  Vector rawgyro = mpu.readRawGyro();
  Vector normalgyro = mpu.readNormalizeGyro();

  voltage = analogRead(bPin);
  voltage = (voltage / 1024) * 3.35;
  voltage = voltage / vDivider;

  if(voltage == 0){
    while(voltage == 0){
      voltage = analogRead(bPin);
      voltage = (voltage / 1024) * 3.35;
      voltage = voltage / vDivider;
      byte buttonState = digitalRead(SW1);
    if (buttonState != lastButtonState) {
      lastButtonState = buttonState;
    if (buttonState == LOW) {
      battState = (battState == HIGH) ? LOW: HIGH;
      digitalWrite(battEn, battState);
    }
  }
    }
    digitalWrite(13, HIGH);
    digitalWrite(6, HIGH);
    delay(2000);

    digitalWrite(13, LOW);
    digitalWrite(6, LOW);
  }
  if(normalgyro.ZAxis > 720){
    digitalWrite(13, HIGH);
    digitalWrite(6, HIGH);
    tone(9, 1000, 1000);
  }
  else{
    digitalWrite(13, LOW);
    digitalWrite(6, LOW);
  }

  Serial.println(scalAccel.ZAxis);
  if((scalAccel.ZAxis > 3 || scalAccel.ZAxis < -3) && (normalgyro.ZAxis > 720)){
    digitalWrite(13, LOW);
    digitalWrite(6, LOW);
    now = rtc.now();
    check = true;
  }
Vector value = mpu.readScaledAccel();
  if(check){
    DateTime neww = rtc.now();
    double sekunnit1 = (now.hour() * 3600) + (now.minute() * 60) + now.second();
    double sekunnit2 = (neww.hour() * 3600) + (neww.minute() * 60) + neww.second();

    double seconds = fabs(sekunnit1 - sekunnit2);
    if(seconds >= 10){
      while(value.ZAxis <  1.5 && value.ZAxis > -1.5){
        check = false;
        DateTime neww = rtc.now();
        double sekunnit1 = (now.hour() * 3600) + (now.minute() * 60) + now.second();
        double sekunnit2 = (neww.hour() * 3600) + (neww.minute() * 60) + neww.second();

        double seconds = fabs(sekunnit1 - sekunnit2);
        Serial.println(seconds);
          if(seconds >= 60){
            while(value.ZAxis <  1.5 && value.ZAxis > -1.5){
              Serial.println(value.ZAxis);
              tone(9, 1000, 2000);
              value = mpu.readScaledAccel();
            }
            break;
          }
        
        value = mpu.readScaledAccel();
      }
      delay(5000);
    }
  }

}
