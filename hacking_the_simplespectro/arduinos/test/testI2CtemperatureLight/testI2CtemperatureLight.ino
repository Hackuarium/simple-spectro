// we use the real I2C port

#define SDA_PORT PORTD
#define SDA_PIN 1
#define SCL_PORT PORTD
#define SCL_PIN 0

#define I2C_TIMEOUT 10
#define I2C_FASTMODE 1


#include <SoftWire.h> 

SoftWire Wire = SoftWire();

#define NCT75 0b1001000

void setup() {
  Serial.begin(9600);

#define POWER_ON_DSL237  PORTE |= 1 << PE2; DDRE |= 1 << PE2; delay(100);
#define POWER_OFF_DSL237 PORTE &= ~ (1 << PE2); delay(100);

  
  Wire.begin();

  writeConfig(NCT75, 1 << 5); // use use oneshot mode to consume 3ua
}

// Main Program Infinite loop
void loop() {
  POWER_ON_DSL237
  float temperature = readTemperature(NCT75);
  Serial.println(temperature);
  delay(500);
    POWER_OFF_DSL237
  temperature = readTemperature(NCT75);
  Serial.println(temperature);
  delay(500);
}

// we have a good reproductivity if we average on 50 values ...

float readTemperature(byte address) {
  float temperature = 0;
  for (byte i = 0; i < 50; i++) {
    oneShot(address);
    delay(50); // one shot should take max 48.5 ms
    Wire.requestFrom(address, 2);
    temperature += (((Wire.read() << 8) | Wire.read()) >> 4) * 0.0625;
  }
  return temperature / 50;
}

void writeConfig(byte address, byte value) {
  Wire.beginTransmission(address);
  Wire.write(0x01);               // Address the Configuration register
  Wire.write(value);         // configuration
  Wire.endTransmission();
  Wire.beginTransmission(address);
  Wire.write(0x00);   // go back o the address to read tempearture
  Wire.endTransmission();
}

void oneShot(byte address) {
  Wire.beginTransmission(address);
  Wire.write(0x04);
  Wire.write(0); // need to write whatever value
  Wire.endTransmission();
  Wire.beginTransmission(address);
  Wire.write(0x00);   // go back o the address to read tempearture
  Wire.endTransmission();
}


