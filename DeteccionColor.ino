#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define LED 8
#define OUT 3
#define NUMERO_MUESTRAS 25

int frecuencias[4];

void setup() {
  Serial.begin(9600);
  configurarPines();
  configurarSensor();
}

void loop() {

  deteccionCRGB();
  for(int i=0; i<4; i++)
    Serial.println(frecuencias[i]);
  Serial.println("------");
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


void RGB(int c){

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
  }//Cierre switch 
}

void deteccionCRGB(){

  int flag = 0;
  int contador;
  unsigned long tiempoInicial = 0;
  unsigned long tiempoTranscurrido = 0;
  
  while(flag <4){
    RGB(flag);
    for(contador=0; contador < NUMERO_MUESTRAS; contador++){
      tiempoInicial  = tiempoInicial + pulseIn(OUT,HIGH); 
    }
    tiempoTranscurrido = (tiempoInicial*2) /NUMERO_MUESTRAS;
    frecuencias[flag]= (1000000/(tiempoTranscurrido));
    tiempoInicial = 0;
    tiempoTranscurrido =0;
    flag++;
  }
}

