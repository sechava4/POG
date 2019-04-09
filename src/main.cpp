#include <Arduino.h>
#include <sensor.h>
#include <actuator.h>
#include <peripheal.h>
#include <trigger.h>
#include "functions.h"

//Name, id random y units
Sensor sensor_temp = Sensor(String("lm35"), String("°C"));

Sensor sensor_bool = Sensor(String("presencia"), String(""));

//Se crea una instancia de la clase actuador para crear un objeto llamado "servo"  con atributos name y type
Actuator valvula = Actuator(String("AX500"), String("Electrovalvula"));

//Se crea una instancia de la clase Trigger para crear un objeto llamado "Trigger1"  con atributos comparison y value (==0 ?)
Trigger<int> trigger = Trigger<int>("=", int(0));




void setup() {
  Serial.begin(9600);     //Velocidad de la comunicacion serial

  //ya que sensor hereda de Task, se utiliza la funcion attach de este para añadir la funcion
  //en este caso quedaria: sensor.attach(float (analogread()) 
  sensor_temp.attach(readTemp);  


  //añadiendo la funcion a servo
  valvula.attach(trig0);    //Se añade la función que dispara la válvula conectada al pin digital 0
  valvula.run(16);  //Se activa la valvula conectada al pin 16
  //Aca estoy seteando la velocidad a 50 e imprimiendo
  
}

void loop() {

    //ya que sensor hereda de Task, se utiliza la funcion run de este para añadir la tarea a realizar
    //En este caso el (0) no hace nada ya readTemp no necesita parametros de entrada

  valvula.report(Serial);
  Serial.println( );
  

}

