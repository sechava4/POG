#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <sensor.h>
#include <actuator.h>
#include <peripheal.h>
#include <trigger.h>
#include "functions.h"

float i1=0.6;

uint8_t GPIO_Pin = D2;    //Interruptpin
//Name, id random y units

//Creacion de instancias
//Sensores
Sensor encoder_rueda = Sensor(String("lm35"), String("cm"));

Sensor request_button = Sensor(String("Button in"), String("state"));

Sensor finish_button = Sensor(String("Button out"), String("state"));

//Declare object of class HTTPClient
HTTPClient http;

//Se crea una instancia de la clase actuador para crear un objeto llamado "electrovalvula"  con atributos name y type
Actuator valvula = Actuator(String("0.8Mpa"), String("Electrovalvula"));

//Se crea una instancia de la clase Trigger para crear un objeto llamado "Trigger1"  con atributos comparison y value (==0 ?)
Trigger<int> trigger_valve = Trigger<int>('=', int(0));



//hacer boton solicitar tarea

void setup() {
  Serial.begin(9600);     //Velocidad de la comunicacion serial

  attachInterrupt (GPIO_Pin,rotarydetect,RISING);
  
  //ya que sensor hereda de Task, se utiliza la funcion attach de este para añadir la funcion
  //en este caso quedaria: sensor.attach(float (analogread()) 
  encoder_rueda.attach(readTemp);  


  //añadiendo la funcion a servo
  valvula.attach(dwrite);    //Se añade la función que dispara la válvula conectada al pin digital 0
  //Aca estoy seteando la velocidad a 50 e imprimiendo
  
}

void loop() {


  //if(trigger_valve.Listen(i1)){
  //  valvula.run(16);       //Se activa la valvula conectada al pin 16
  //dist_cm = double(wheel_radious*degrees_per_pulse*pulses);
  Serial.println(pulses);
  //}
  //valvula.report(Serial);
  //Serial.println( );
  
  

}






