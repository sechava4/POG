#include <Arduino.h>
#include "peripheal.h"
#include "task.h"
#include "ArduinoJson.h"

//Clase actuador que hereda de Peripheal y Task donde T = bool y P = uint16_t

class Actuator: public Peripheal, public Task<bool, uint16_t> {
private:
  String type;    //Atributo tipo adicional a los de Peripheal y Task
public:

//Funciones que puede realizar el objeto además de las de peripheal y Task
//Funcion constructora en donde se asigna el  string tipo al Atributo tipo
  Actuator(String name, String type, uint16_t id = random(0, 0xFFFF)): Peripheal(name, id) {
      this->type = type;
  }

  //Se declara la funcion getType solamente
  String getType();

  //Se declara la funcion report
  void report(Stream &uart);
};


//Acá esta el código de la funciongetType
String Actuator::getType(){
  return this->type;  //Retorna el atributo type como un string
};

//Acá esta el código de la funcion report
void Actuator::report(Stream &uart){
    StaticJsonBuffer<200> jsonBuffer;               //La cantidad de caracteres que va a tener el mensaje Json
    JsonObject& res = jsonBuffer.createObject();    //Se crea el onjeto json llamado res
    res["name"] = this->getName();                  //Se añade name y el valor a la cadena del mensaje JSON
    res["id"] = this->getId();                      //Se añade id y el valor a la cadena del mensaje JSON
    res["type"] = "Actuator";                       //Se añade actuador y el valor a la cadena del mensaje JSON
    res["act_type"] = this->getType();              //Se añade type y el valor a la cadena del mensaje JSON
    String out;                                     //Se declara una variable string
    res.prettyPrintTo(out);                         //Se crea un string con todo el mensaje Json (res)
    uart.println(out);                              //uart va a tomar el valor de Serial o Serial 1, etc...
}