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
 void Actuator::report(Stream &uart)
 {
     StaticJsonDocument<256> doc;              //La cantidad de caracteres que va a tener el mensaje Json     
     doc["name"] = this->getName();                  //Se añade name y el valor a la cadena del mensaje JSON
     doc["id"] = this->getId();                      //Se añade id y el valor a la cadena del mensaje JSON
     doc["type"] = "Actuator";                       //Se añade actuador y el valor a la cadena del mensaje JSON
     doc["act_type"] = this->getType();              //Se añade type y el valor a la cadena del mensaje JSON
     serializeJson(doc, uart);
 }