#include <LiquidCrystal.h>
const int SENSOR_TEMP = A0;//analog pin related to temperature sensor
const int SWITCH_PIN = 6;
const int MOTOR_PIN=10;

const float TEMP_LIMIT = 30.0; //over this temperature the motor starts

LiquidCrystal lcd (12,11,5,4,3,2);
int sensorValue; //values read from sensor
bool isLcdOn=1;

void setup() {
  Serial.begin(9600);
  pinMode(SWITCH_PIN, INPUT);
  pinMode(MOTOR_PIN, OUTPUT);
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Air Coller");
  lcd.setCursor(0,1);
  lcd.print("by mbrioski");
  lcd.blink();
  delay(2000);
  lcd.noDisplay();
  isLcdOn=0;
  digitalWrite(MOTOR_PIN, LOW);
}

void loop() {
  float temp = getTemperature(getVoltage(analogRead(SENSOR_TEMP)));
  displayLcdInfos(temp);
  if(temp > TEMP_LIMIT) {
    digitalWrite(MOTOR_PIN, HIGH);
  }else{
    digitalWrite(MOTOR_PIN, LOW);
  }
  delay(1000);
}

/**
 * Display lcd infos about temperature
 */
void displayLcdInfos(float temperature) {
  if(!isLcdOn) {
    lcd.display();
    lcd.noBlink();
    isLcdOn=1;
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temp limit:");
  lcd.print(TEMP_LIMIT);
  lcd.setCursor(0,1);
  lcd.print("Temp: ");
  lcd.print(temperature);
}

/**
 * Get voltage from sensor value
 */
float getVoltage(float value) {
  return (value/1024.0) * 5.0;
}
/**
 * Get temperature from voltage
 */
float getTemperature(float voltage) {
  return (voltage - 0.5) * 100;
}

/**
 * Write to serial debug Values
 */
void debugValuesTemperature(int sensorValue, float voltage, float temperature) {
 Serial.println("#########");
 Serial.print("Sensor Value: ");
 Serial.print(sensorValue);
 Serial.print(", Voltage: ");
 Serial.print(voltage);
 Serial.print(", Temparature: ");
 Serial.println(temperature);
 Serial.println("#########");
}
