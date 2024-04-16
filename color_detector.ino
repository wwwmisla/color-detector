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

#include <Adafruit_NeoPixel.h>

//  Declarando pinos
#define PINNP 3
#define PINLDR A0


//  Iniciando NeoPixel
Adafruit_NeoPixel led = Adafruit_NeoPixel(1, PINNP, NEO_RGB + NEO_KHZ800);

//  Declarando variáveis
int leitura   = 0;
int minR      = 2000, maxR = 0;
int minG      = 2000, maxG = 0;
int minB      = 2000, maxB = 0;

void setup() {
  //  Preparando sensores
  led.begin();
  led.show(); //  Inicia o NeoPixel e apaga qualquer cor exibida anteriormente
  Serial.begin(9600); //  Inicializa a comunicação serial para depuração

  calibrarCores();  //  Chama a função para calibrar as cores no início 
}

void loop() {
  // Iniciando leitura
  leitura = analogRead(PINLDR); //  Realiza uma leitura do LDR

  Serial.println(leitura);  //  Imprime a leitura do LDR no Monitor Serial

  // Detectando cores
  if (leitura <= maxR && leitura >= minR) { //  Verifica se a leitura está dentro dos limites de cor vermelha
    Serial.println("Vermelho"); //  Se sim, imprime "Vermelho" no Monitor Serial
  } else if (leitura <= maxG && leitura >= minG) {  //  Verifica se a leitura está dentro dos limites de cor verde
    Serial.println("Verde");  //  Se sim, imprime "Verde" no Monitor Serial
  } else if (leitura <= maxB && leitura >= minB) {  //  Verifica se a leitura está dentro dos limites de cor azul
    Serial.println("Azul"); //  Se sim, imprime "Azul" no Monitor Serial
  }

  delay(500);
}

//  Função para calibrar as cores vermelho, verde e azul
void calibrarCores() {
  // Chama a função calibraLDR para calibrar cada cor individualmente
  calibraLDR("Vermelho", minR, maxR);  //  Calibração da cor vermelha
  calibraLDR("Verde", minG, maxG);     //  Calibração da cor verde
  calibraLDR("Azul", minB, maxB);      //  Calibração da cor azul
}

//  Função para calibrar uma cor específica | calibraLDR
void calibraLDR(const char *cor, int &minVal, int &maxVal) { //cor -> especificar a cor que será calibrada
  int r = 0, g = 0, b = 0;

  /* Determina a cor a ser exibida no NeoPixel durante a calibração
  strcmp(): foi utilizado para comparar Strings, nesse caso a String cor com as Strings("Vermelho", "Verde" e "Azul"), 
  pois, assim saberemos qual cor está sendo calibrada no momento e que saibamos o valor de r, g e b corretamente para a cor atual durante a calibração.
  */
  if (strcmp(cor, "Vermelho") == 0) {
    r = 255;
  } else if (strcmp(cor, "Verde") == 0) {
    g = 255;
  } else if (strcmp(cor, "Azul") == 0) {
    b = 255;
  }
  
  //  Configura o NeoPixel para exibir a cor específica durante a calibração
  led.setPixelColor(0, r, g, b);
  led.show(); //  Atualiza o NeoPixel para exibir a cor configurada
  delay(1500);
  led.setPixelColor(0, 255, 255, 255); // NeoPixel
  led.show(); //  Atualiza o NeoPixel para apagar qualquer cor exibida anteriormente
  
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
