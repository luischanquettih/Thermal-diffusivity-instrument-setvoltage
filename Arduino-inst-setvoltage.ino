/*
 * Convertirmos el arduino en un instrumento que setee voltajes
 * lo hará en el pin PWM 9
 * *IDN? --> Devolvera THERMAL DIFFUSITIVY INSTRUMENT, MODEL ARDUINO UNO, Jun 20 2022 5:30:00
 * SYSTem:THD:TEMPerature1? --> devolvera temperatura de la termocupla 1
 * SYSTem:THD:TEMPerature2? --> devolvera temperatura de la termocupla 2
 * SYSTem:THD:VOLTage X--> pondrá el valor de voltaje de 0-255
*/

#include "Arduino.h"
#include "Vrekrer_scpi_parser.h"

SCPI_Parser instrument;
const int salidaPWM = 9;
int valor = 0;

void setup() {
  instrument.RegisterCommand(F("*IDN?"), &Identify);
  instrument.SetCommandTreeBase(F("SYSTem:THD"));
  instrument.RegisterCommand(F(":VOLTage"), &SetVoltage);
  instrument.RegisterCommand(F(":TEMPerature1?"), &GetTemperature1);
  instrument.RegisterCommand(F(":TEMPerature2?"), &GetTemperature2);

  Serial.begin(9600);
  pinMode(salidaPWM,OUTPUT);
  analogWrite(salidaPWM,0);
}

void loop() {
  instrument.ProcessInput(Serial, "\n");
}

void Identify(SCPI_C commands, SCPI_P parameters, Stream& interface){  
  interface.println(F("THERMAL DIFFUSITIVY INSTRUMENT, MODEL ARDUINO UNO, Jun 20 2022 5:30:00"));
}

void SetVoltage(SCPI_C commands, SCPI_P parameters, Stream& interface){
  if(parameters.Size() > 0){
    valor = constrain(String(parameters[0]).toInt(),0,255);
    analogWrite(salidaPWM,valor);
  }
}

void GetTemperature1(SCPI_C commands, SCPI_P parameters, Stream& interface){
  interface.println(String(10));
}

void GetTemperature2(SCPI_C commands, SCPI_P parameters, Stream& interface){
  interface.println(String(20));
} 
