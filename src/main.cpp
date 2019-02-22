#include <Arduino.h>
#include <sensor.h>

//Name, id random y units
Sensor sensor = Sensor(String("lm35"), String("°C"));


//Se crea una funcion para leer temperatura con una entrada var que no se esta usando
float readTemp(int var){
  return (float(analogRead(0)/1023.0)*5.0);
}

void setup() {
  Serial.begin(9600);     //Velocidad de la comunicacion serial
  //ya que sensor hereda de Task, se utiliza la funcion attach de este para añadir la funcion
  //en este caso quedaria: sensor.attach(float (analogread())
  sensor.attach(readTemp);  
}

void loop() {
  //ya que sensor hereda de Task, se utiliza la funcion run de este para añadir la funcion
  //En este caso el (0) no hace nada ya readTemp no necesita parametros de entrada
  Serial.println(sensor.run(0));   
  while(1){
  Serial.println(sensor.run(0));   
  delay(1000);
  }
}



