#include <Arduino.h>
#include "peripheal.h"
#include "task.h"

//Se crea la clase sensor la cual hereda los atributos y funciones de peripheal y task
class Sensor: public Peripheal, public Task<float, int> {
private:
  //Tiene adicionalmente de los atributos de los padres (name,id) el atributo (units)
  String units;
public:
  //Esta es la función constructora para crear instancias de Sensor, hereda de Peripheal (name,id)
  Sensor(String name, String units, uint16_t id = random(0, 0xFFFF)): Peripheal(name, id) {
    //Se asigna al stributo units el string recibido por la función
    this->units = units;
  }
};