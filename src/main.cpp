#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <sensor.h>
#include <actuator.h>
#include <peripheal.h>
#include <trigger.h>
#include <functions.h>
#include <line.h>
#include <Wire.h>
#include <hd44780.h>                       // main hd44780 header
#include <hd44780ioClass/hd44780_I2Cexp.h> // i2c expander i/o class header
#include <WiFiClient.h>





#define ROJO 0x00FF0000 
uint8_t state = 0;

//Creacion de instancias
//Sensores
Sensor encoder_rueda = Sensor(String("KY040"), String("cm"));

Sensor request_button = Sensor(String("Button in"), String("state"));

Sensor finish_button = Sensor(String("Button out"), String("state"));

Line tarea = Line(0,0,"default"); //Se crea una instancia vacia para luego sobreescribirla

//Declare object of class HTTPClient

//Se crea una instancia de la clase actuador para crear un objeto llamado "electrovalvula"  con atributos name y type
Actuator valvula = Actuator(String("0.8Mpa"), String("Electrovalvula"));

// //Se crea una instancia de la clase Trigger para crear un objeto llamado "Trigger1"  con atributos comparison y value (==0 ?)
Trigger<int> trigger_valve = Trigger<int>('=', int(0));


// long timer = millis();



void setup() {
  

  Serial.begin(9600);     //Velocidad de la comunicacion serial
  pinMode(D8, OUTPUT);
  pinMode(D6, INPUT);
  pinMode(D5, INPUT);

  attachInterrupt (D6,zerofcn,RISING);    //Interrupcion para zero
  encoder_rueda.attach(pulseReading);  

  request_button.attach(digitalPinRead);
  finish_button.attach(digitalPinRead);

  valvula.attach(dwrite);    //Se añade la función que dispara la válvula conectada al pin digital 0

  lcd.begin(LCD_COLS, LCD_ROWS);
  lcd.clear();

  WiFi.mode(WIFI_STA);
  WiFi.begin("HOME-A9BC", "2024AA4E158B3787");    //WiFi connection
 
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection
 
    delay(500);
    lcd.setCursor(0,0);
    lcd.print("Connecting");
 
  }
  lcd.setCursor(0,0);
  lcd.print("WiFi Connected");
  delay(1000);
}

void loop() {
  
  //Finite state switch
  switch (state)
  {
    case 0:  //Antes de solicitar una tarea
      lcd.setCursor(0,0);
      lcd.print("Solicitar Linea");  
      if (request_button.run(D5)){
        state = 1;  
      }

      break;

    case 1:  //Solicitando tarea de la base de datos
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Solicitando"); 
      delay(200); 
      if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status first
        Serial.println("conecto");
        WiFiClient client;

        HTTPClient http;

        if (http.begin(client, "http://192.168.1.53:8080/helloesp")) { // HTTP
          Serial.println("accedio a la pagina");
          int httpCode = http.GET(); //Send the request
    
          if (httpCode > 0) { //Check the returning code if 200
            Serial.println("leyo el contenido");
            String payload = http.getString();   //Get the request response payload
            DynamicJsonDocument doc(2000);
            DeserializationError error = deserializeJson(doc, payload);
            if (error)
              Serial.println("error de deserializacion");
            tarea.setValues(doc["id"],doc["medida"],doc["color"]); //Se setean los valores leidos de la base de datos
            tarea.report(Serial);
    
          }
          else {
            Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
          }
        }
        http.end();   //Close connection
        }
        state = 2;
      break;

      case 2:  //Antes de solicitar una tarea
        lcd.setCursor(0,0);
        lcd.print("c:");
        lcd.print(tarea.getColor());
        lcd.print(",Val.req: ");
        lcd.print(tarea.getCms());
        if (encoder_rueda.run(0)>=tarea.getCms())
          state=3;
      break;

      case 3:  //Cortando la linea
        lcd.setCursor(0,0);
        lcd.print("Corte la linea");
        valvula.run(1);                //Prenda la valvula en D8
        if (request_button.run(D5)){   //Si ya termino de cortar valla a enviar datos a la nube
          state = 4;  
          valvula.run(0);              //Apague la valvula
        }
      break;

      case 4:  //Enviando a listas
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Enviando"); 
        delay(200); 
        if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status first
          Serial.println("conecto");
          WiFiClient client2;

          HTTPClient http2;

          if (http2.begin(client2, "http://192.168.1.53:8080/addesp")) { // HTTP
            Serial.println("accedio a la pagina");
            http2.addHeader("Content-Type", "application/json");  //Specify content-type header
            DynamicJsonDocument doc(300);
            doc["id"] = tarea.getId();
            doc["medida"] = tarea.getCms();
            doc["color"] = tarea.getColor();
            
            char JSONmessageBuffer[300];
            serializeJson(doc, JSONmessageBuffer);
            //Serial.println(JSONmessageBuffer);
            int httpCode2 = http2.POST(JSONmessageBuffer);   //Send the request
            String payload2 = http2.getString();                                        //Get the response payload
        
            Serial.println(httpCode2);   //Print HTTP return code
            Serial.println(payload2);    //Print request response payload

            http2.end(); //Close connection
          }
        state=0;
        }
      break;
  
  }
  // Siempre Lea el encoder
  lcd.setCursor(0,1);  //En la linea de abajo
  lcd.print("Val. medido: ");
  lcd.print(static_cast<int>(encoder_rueda.run(0)));   

}





