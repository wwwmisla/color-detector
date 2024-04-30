/*
    Color_Detector (Detector de cores)

    Detector de cor baseado nos componentes NeoPixel e LDR

    Código comentado: https://youtu.be/oHn-RooDAao
    
    O circuito:
    * Pino do NeoPixel conectado ao terminal digital 3
    * Pino do LDR conectado ao terminal analógico A0

    Criado em 23/07/2023 | Atualizado em 16/04/2024
    Por Um Robô por Aluno

    Copyright (c) 2024 Um Robô por Aluno. Todos os direitos reservados.
*/

#include <Adafruit_NeoPixel.h>	//	Bibilioteca para usar o NeoPixel

//  Declarando pinos
#define NUMLEDS 1
#define PINNP 3
#define PINLDR A0

//  Iniciando NeoPixel 
Adafruit_NeoPixel led = Adafruit_NeoPixel(NUMLEDS, PINNP, NEO_GRB + NEO_KHZ800);	//	Troquei o RGB por GRB, pois, queria que a cor Vermelha viesse primeiro

//  Declarando variáveis
int leitura   = 0;
int minR      = 2000, maxR = 0;
int minG      = 2000, maxG = 0;
int minB      = 2000, maxB = 0;

void setup() {
  //	Preparando sensores
  led.begin();
  led.show(); 
  Serial.begin(9600); 

  //	Calibrando cores no início
  calibraRed();		//  Calibra a cor Vermelha
  calibraGreen();	//  Calibra a cor Verde
  calibraBlue();	//  Calibra a cor Azul
}

void loop() {
  //	Iniciando leitura
  leitura = analogRead(PINLDR);	//  Realiza uma leitura do LDR

  Serial.println(leitura); //  Imprime a leitura do LDR no Monitor Serial

  //	Detectando cores
  if (leitura < maxR && leitura > minR) { //  Verifica se a leitura está dentro dos limites de cor vermelha
    Serial.println("Vermelho"); //  Se sim, imprime "Vermelho" no Monitor Serial
  } else if (leitura < maxG && leitura > minG) {  //  Verifica se a leitura está dentro dos limites de cor verde
    Serial.println("Verde");  //  Se sim, imprime "Verde" no Monitor Serial
  } else if (leitura < maxB && leitura > minB) {  //  Verifica se a leitura está dentro dos limites de cor azul
    Serial.println("Azul"); //  Se sim, imprime "Azul" no Monitor Serial
  }

  delay(500);
}

void calibraRed() {
  //Calibrando Vermelho
  led.setPixelColor(0, 255, 0, 0); //	Indicando que a cor Vermelho será calibrada
  led.show();
  delay(1500);
  led.setPixelColor(0, 255, 255, 255); 
  led.show();
  calibraLDR(minR, maxR);
  delay(1500);
}

void calibraGreen() {
  //Calibrando Verde
  led.setPixelColor(0, 0, 255, 0); //	Indicando que a cor Verde será calibrada
  led.show();
  delay(1500);
  led.setPixelColor(0, 255, 255, 255); 
  led.show();
  calibraLDR(minG, maxG);
  delay(1500);
}

void calibraBlue() {
  //Calibrando Azul
  led.setPixelColor(0, 0, 0, 255); //	Indicando que a cor Azul será calibrada
  led.show();
  delay(1500);
  led.setPixelColor(0, 255, 255, 255); 
  led.show();
  calibraLDR(minB, maxB);
  delay(1500);
}

//  Função para calibrar o LDR
void calibraLDR(int &minVal, int &maxVal) { 
  //  Inicializa os valores mínimos e máximos com os limites máximos possíveis
  minVal = 2000;
  maxVal = 0;

  //  Loop para realizar várias leituras do LDR e calibrar os valores mínimos e máximos de uma forma mais precisa possível
  for (int i = 0; i < 100; i++) {
    leitura = analogRead(PINLDR); //  Realiza uma leitura do LDR

    //  Atualiza o valor mínimo se a leitura atual for menor do que o valor mínimo atual
    if (leitura < minVal) {
      minVal = leitura;
    }
    //  Atualiza o valor máximo se a leitura atual for maior do que o valor máximo atual
    if (leitura > maxVal) {
      maxVal = leitura;
    }

    delay(100);
  }
}