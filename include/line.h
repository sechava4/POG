#include <Arduino.h>
#include "peripheal.h"
#include "task.h"
#include "ArduinoJson.h"

//Clase actuador que hereda de Peripheal y Task donde T = bool y P = uint16_t

class Line:public Task<bool, uint16_t> {
private:
  String Color;
  int medida; 
  uint16_t id;   

public:

//Funciones que puede realizar el objeto además de las de peripheal y Task
//Funcion constructora en donde se asigna el  string tipo al Atributo tipo
  Line(String Color,int cm, uint16_t id = random(0, 0xFFFF)) 
  {
      this->Color = Color;
      this->medida = cm;
  }

  //Se declara la funcion solamente
  String getColor();

  int getCms();

  //Se declara la funcion report
  void report(Stream &uart);
};


//Acá esta el código de la funciongetType
String Line::getColor(){
  return this->Color;  //Retorna el atributo type como un string
};

int Line::getCms(){
  return this->medida;  //Retorna el atributo type como un string
};

//Acá esta el código de la funcion report
 void Line::report(Stream &uart)
 {
     StaticJsonDocument<256> doc;              //La cantidad de caracteres que va a tener el mensaje Json     
     doc["type"] = "Line";                       //Se añade actuador y el valor a la cadena del mensaje JSON
     doc["act_type"] = this->getColor();              //Se añade type y el valor a la cadena del mensaje JSON
     serializeJson(doc, uart);
 }