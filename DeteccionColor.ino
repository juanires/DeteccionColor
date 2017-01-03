#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define LED 8
#define OUT 3

volatile int numeroInterrupciones;
int pinInterrupcion = OUT;
int frecuencias[4];
int flag;
unsigned long tiempoInicial;
unsigned long tiempoTranscurrido;
unsigned long p1;
int p2;

void setup() {
  Serial.begin(9600);
  configurarPines();
  //configurarSensor();
  configurarInterrupciones();
  noInterrupts(); //Se deshabilitan las interrupciones
  flag = 0;
  numeroInterrupciones = 0;
  tiempoInicial = 0;
  tiempoTranscurrido = 0;
  p2=0;
}

void loop() {

  if(flag <4){
  
    obtenerFrecuencia(flag);
    tiempoInicial = micros();
    interrupts(); //Se habilitan las interrupciones
    numeroInterrupciones=0;
    while(!(numeroInterrupciones == 4)); //Mientras no se produzcan dos interrupciones, se queda en el bucle
    noInterrupts(); //Cuando ya paso el tiempo, se deshabilitan las interrupciones
    tiempoTranscurrido = micros() - tiempoInicial;
    frecuencias[flag]= (1000000/((tiempoTranscurrido /4)*2)); //Veces interrupidas - 1 (cantidad de periodos). dividido el tiempo (en segundos). Esto da la frecuencia en Hz
    numeroInterrupciones=0;
    flag++;
  }
  else{
    flag = 0; //Si se capturaron las 4 frecuencias, se pone el contador a 0
    //p2=0;
    for(int i=0; i<4; i++){
      Serial.println(frecuencias[i]);
    }
    Serial.println("------");
    //Serial.println(millis()-p1);
    //Serial.println("------");
  }
  //delay(1);

}

/*
 * Se configuran los pines si son entrada o salida
 */
void configurarPines(){ 

   pinMode(S0,OUTPUT);
   pinMode(S1,OUTPUT);
   pinMode(S2,OUTPUT);
   pinMode(S3,OUTPUT);
   pinMode(LED,OUTPUT);
   pinMode(OUT,INPUT_PULLUP);
}


/*
 * Se configura inicialmente el sensor
 */
void configurarSensor(){
   digitalWrite(S0,HIGH);// Modo de baja frecuencia (2%) 
   digitalWrite(S1,LOW); // Modo de baja frecuencia (2%) 
   digitalWrite(LED,HIGH); // Se enciende la iluminacion del sensor
}


/*
 * Esta funcion cambia el estado de ciertos pines (de acuerdo al char parametro)
 * para capturar las frecuencias RGB o CLEAR
 */

void configurarInterrupciones(){
    configurarIntExterna(); //Interrupciones externas  
}

void configurarIntExterna(){
  attachInterrupt(digitalPinToInterrupt(pinInterrupcion), ISR_IE, CHANGE);  
}

void ISR_IE(){
  numeroInterrupciones++;
}

void obtenerFrecuencia(int c){
/*
  switch(c){
    case 0:{ //Captura luminosidad
          digitalWrite(S2,HIGH); 
          digitalWrite(S3,LOW);
          break;
    }
    case 1:{ //Captura frecuencia Red
         digitalWrite(S2,LOW); 
         digitalWrite(S3,LOW);
         break;
    }
    case 2:{//Captura frecuencia Green
         digitalWrite(S2,HIGH); 
         digitalWrite(S3,HIGH);
         break;
    }
    case 3:{//Captura frecuencia Blue
        digitalWrite(S2,LOW); 
        digitalWrite(S3,HIGH);
        break;
    }
  }//Cierre switch */
}

