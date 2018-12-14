#include <M5Stack.h>

const int MQ_PIN = 35;  //pin analógico
const int MQ_DELAY = 100;   
int valores [200];
int i = 0;
int contador = 0;
int contadorg = 0;
bool estadoGrafico = false;
float escalar = 200.0 / 4095.0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  M5.begin();
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(2);
}

void loop() {
  
  contador++;
  // put your main code here, to run repeatedly:
  if(i == 200) i = 0;
  
  //Se rellena el array con los valores obtenidos del pin
  for(int i = 0; i < 200; i++){
    valores[i] = analogRead(MQ_PIN);
    //Cuando llegue al final del array
    //vuelve a tomar otros 200 valores
  }

  //DATOS EN M5STACK

  if(contador == 100){
    contador = 0;
    if(estadoGrafico == false){
    
    limpiarPantalla();
    
    M5.Lcd.print("Maxima : ");
    int resmax = (maxima(&valores[0]));
    M5.Lcd.println(resmax);
    M5.Lcd.print("Valor en volts : ");
    M5.Lcd.println(sacarVolts(resmax));

    M5.Lcd.println();

    M5.Lcd.print("Minima : ");
    int resmin = (minima(&valores[0]));
    M5.Lcd.println(resmin);
    M5.Lcd.print("Valor en volts : ");
    M5.Lcd.println(sacarVolts(resmin));
  
    M5.Lcd.println();

    M5.Lcd.print("Media : ");
    int resmed = (media(&valores[0]));
    M5.Lcd.println(resmed);
    M5.Lcd.print("Valor en volts : ");
  M5.Lcd.println(sacarVolts(resmed));
    }
    
    if(estadoGrafico == true){
      //M5.Lcd.drawLine(0,200,320,200,0xff80);//X
      //M5.Lcd.drawLine(20,215,20,0,0xff80);//Y
      M5.Lcd.drawLine(contadorg, 0, contadorg, 200, 0);
      M5.Lcd.drawPixel(contadorg, 200-(analogRead(35))*escalar, 0xff80);
      contadorg++;
    }
  }
  
  if(M5.BtnA.wasPressed()){
      limpiarPantalla();  
     
    if(estadoGrafico == false){
      estadoGrafico = true;
      Serial.println(estadoGrafico);
      contador = 0;
    } else {
    estadoGrafico = false;
    contador = 0;
      }
      M5.update();
    }
    
    M5.update();
    delay(10);
}  

int maxima(int *p){
  int resultadoMax = 0;
  for(int j = 0; j < 200; j++){
    if(p[j] > resultadoMax) resultadoMax = p[j];
  }
  return resultadoMax;
}

int minima(int *p){
  int resultadoMin = 4095;
  for(int j = 0; j < 200; j++){
    if(p[j] < resultadoMin) resultadoMin = p[j];
  }
  return resultadoMin;
}

int media(int *p){
  int mediatotal = 0;
  for (int j = 0; j < 200; j++) {
    mediatotal = mediatotal + p[i];
  }
  int res;
  res = mediatotal / 200;
  return res;
}

double sacarVolts(unsigned int var){
    double volts = var * (5.0/4095.0);
    return volts;
}

void limpiarPantalla(){
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0,0);  
}
