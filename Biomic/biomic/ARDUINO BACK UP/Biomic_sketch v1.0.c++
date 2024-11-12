#include <OneWire.h>

/* 
  Sketch generado por el Thing "BIOMIC" de Arduino IoT Cloud
  https://create.arduino.cc/cloud/things/0c394528-717a-43e9-944e-d59297f444e3 

  Descripción de las Variables de Arduino IoT Cloud
1
  Las siguientes variables se generan automáticamente y se actualizan cuando hay cambios en el Thing
  
  float gas;
  
  float ph;
  
  float tDS;
  
  float temperature;
  
  bool bomb;
  
  bool filtrado;
  
  bool leds;

  Las variables que están marcadas como LEER/ESCRIBIR en el Thing en la nube también tendrán funciones
  que se llaman cuando sus valores se cambian desde el Panel de control.

 Estas funciones se generan con el Thing y se agregan al final de este sketch.
*/
// aquí vamos a declarar las funciones importándolas desde las bibliotecas 

 /* la biblioteca de "thing.properties.h" es la que se encuentra
 en la parte superior en las pestañas de las derechas que se ve en el thingProperties.h
  
  */
#include "thingProperties.h"

float temp;

// estas son las variables de los reles
// 3 está conectado al pin digital número 3 y controla el rele de la bomba de oxígeno del bioreactor
const int rele_Ox = 11;
// el rele led está conectado al pin digital número 4 y controla el rele de los leds de arriba y de abajo del bioreactor
const int rele_LedsUp = 10;
const int rele_LedsDn = 9;
// la electroválvula es un poco más especial ya que solo va a funcionar poco rato y al final del voidloop(); lo explicaré de mejor manera
const int rele_Val = 8;
/* este es la bomba de agua y se activa junto con la electroválvula para darle un equilibrio al agua y hacer que las microalgas se puedan volver a 
reproducir de forma más sencilla debido a la inyección de nutrientes y va conectado al IN del Rele y ese a la vez al pin digital
número 6 */
const int rele_bomb = 7;

//ph
float po;
void setup() {
  // Inicializar serial y esperar a que se abra el puerto:
  Serial.begin(9600);
  // Este retraso da la oportunidad de esperar a un Monitor Serie sin bloquear si no se encuentra ninguno
  delay(1500); 

  // declaramos variables y la función de las variables que estaban 
  pinMode(rele_Ox, OUTPUT);
  pinMode(rele_LedsUp, OUTPUT);
  pinMode(rele_LedsDn, OUTPUT);
  pinMode(rele_Val, OUTPUT);
  pinMode(rele_bomb, OUTPUT);
 // las salidas son OUTPUT porque está saliendo la señal para cambiarla
  
  // Definido en thingProperties.h
  initProperties();


  
  // Conectar a Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  /*
     La siguiente función te permite obtener más información
     
     relacionada con el estado de la red y la conexión de IoT Cloud y errores
     
     cuanto mayor sea el número, más información detallada obtendrás.
     
     El valor predeterminado es 0 (solo errores).
     
     El máximo es 4
 */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();
  // Tu código aquí 


  //formula del sensor de gas
  float Co2 = analogRead(A4);
  if (Co2 > 20 and Co2 < 100){
    gas = Co2;
  }
  Serial.print("Gas");
  Serial.println(Co2);
  Serial.println(gas);
  
 
  // ph
  po = (1023 - analogRead(A2))/73.07;
  Serial.println("ph");
  Serial.println(po);
  ph = po;
  
  // sensor de temperatura 
  temp = analogRead(A0);
  temp = 22;
  if (temp > 20 and temp < 40){

    temperature = temp;
  }
  
  /*float tempe = analogRead(A5);
  temp = tempe / 10;
  
  if(temp > 0 and temp < 100) {
    temperature = temp;
  }
*/
  
  Serial.println("temperatura");
  Serial.println(temp);

  //tds
  float tDSP = analogRead(A1);
  if(tDSP > 30 and tDS <1000){
    tDS = tDSP + 228;
    
  }
  else{
    
  }
  Serial.println("tds");
  Serial.println(tDS);
          
}

/*
  Dado que Bomb es una variable LEER/ESCRIBIR, se ejecuta onBombChange() cada vez que se recibe un nuevo valor de IoT Cloud.
*/
void onBombChange(){
  // Agrega tu código aquí para actuar sobre el cambio de Bomb
  if(bomb){
    digitalWrite(rele_Ox , LOW);
  }
    
  else{
    digitalWrite(rele_Ox, HIGH);
  }

}
/*
  Dado que Filtrado es una variable LEER/ESCRIBIR, se ejecuta onFiltradoChange() cada vez que se recibe un nuevo valor de IoT Cloud.
*/
void onFiltradoChange() {
  // Agrega tu código aquí para actuar sobre el cambio de Filtrado
  if(filtrado){
    digitalWrite(rele_Val, HIGH);
    digitalWrite(rele_bomb, HIGH);
  }
  else{
    digitalWrite(rele_Val, LOW);
    digitalWrite(rele_bomb,LOW);
    }

}
/*
  Dado que Leds es una variable LEER/ESCRIBIR, se ejecuta onLedsChange() cada vez que se recibe un nuevo valor de IoT Cloud.
*/
void onLedsChange(){
  // Agrega tu código aquí para actuar sobre el cambio de Leds
  if(leds){
    digitalWrite(rele_LedsUp , HIGH);
    digitalWrite(rele_LedsDn, HIGH);
  }
  else {
    digitalWrite(rele_LedsUp, LOW);
    digitalWrite(rele_LedsDn, LOW);
    }
}
