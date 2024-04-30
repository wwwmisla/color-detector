# Color Detector (Detector de Cor)

[![Licence](https://img.shields.io/github/license/Ileriayo/markdown-badges?style=for-the-badge)](./LICENSE)
![Badge em Desenvolvimento](http://img.shields.io/static/v1?label=STATUS&message=DESENVOLVIDO&color=GREEN&style=for-the-badge)

<div style="display: inline_block">

<img width="300px" align="right" src="https://ai.thestempedia.com/wp-content/uploads/2022/07/LDR.png" alt="LDR">

## Índice

- [Título e Imagem de capa](#color-detector)
- [Descrição do projeto](#-descrição-do-projeto)
- [Como usar](#-como-usar)
- [Do It Yourself](#-do-it-yourself)
- [Tecnologias Utilizadas](#%EF%B8%8F-tecnologias-utilizadas)
- [Licença](#%EF%B8%8F-licença)

</div>

## :page_facing_up: Descrição do Projeto 

<br>

<img width="300px" align="left" src="https://uk.pi-supply.com/cdn/shop/products/8-LED-NeoPixels-Ring-Top_1200x1200.png?v=1571708735" alt="NeoPixel">

<br>


<p align="justify">O <strong>Color Detector</strong> é um projeto de detector de cor utilizando um LDR (Light Dependent Resistor) e um LED RGB NeoPixel. O objetivo é detectar e visualizar visualmente cores diferentes com base na intensidade da luz.
</p>

#### Funcionalidades

- <strong>Detecção de Cor:</strong> O sensor de luz LDR é utilizado para medir a intensidade da luz em um determinado ambiente. Com base nessa intensidade, o código determina se a cor detectada é vermelha, verde ou azul.
- <strong>Calibração de Cores:</strong> Antes de utilizar o detector, é necessário realizar uma calibração para cada uma das cores. Durante o processo de calibração, o LED NeoPixel emite luz na cor específica, permitindo ao usuário ajustar o sensor de luz para obter leituras precisas.
- <strong>Visualização de Cores:</strong> Após a calibração, o NeoPixel exibe visualmente a cor detectada, por exemplo, se a cor detectada for vermelha, o NeoPixel acenderá em vermelho; se for verde, acenderá em verde; e se for azul, acenderá em azul.

#### Componentes Necessários

<div align="center">

| Componente                  | Quantidade                       |
|-----------------------------|----------------------------------|
| Arduino Uno ou similar      | 1                                |
| LDR           | 1                                |
| LED RGB NeoPixel            | 1                                |
| Resistores                  | Se necessário, dependendo da configuração do circuito       |

</div>

<br>

## :gear: Como Usar

### Instalação e Uso

<p>Este tutorial irá guiá-lo através do passo a passo de como utilizar o código <strong>color_detector.ino</strong> que está localizado neste repositório.</p>

- Baixar o arquivo ZIP:
  - Você pode baixar o arquivo <strong>color_detector.ino</strong> diretamente do GitHub, basta apenas clicar no botão "Code" e selecionar a opção "Download ZIP";
    - OBS.: Junto com o arquivo <strong>color_detector.ino</strong>, serão baixados também os arquivos <strong>LICENSE</strong> e <strong>README.md</strong>, mas esses são arquivos de documentação do repositório os quais você pode editá-los ou excluí-los conforme sua necessidade.

- Clonar o Repositório:
  - Se preferir, você pode clonar este repositório para o seu computador, usando o seguinte comando no terminal:
    ```sh
    git clone https://github.com/umroboporaluno/color_detector.git
    ```

- Abrindo e Editando o Arquivo .ino: 
  - Depois de realizar o download do arquivo .ino em seu computador, abra-o em um editor de código, o Arduino IDE, por exemplo. Nessa etapa você já pode editar o código conforme necessário para atender a sua demanda. Certifique-se de verificar se há erros e corrigi-los, se preciso for.

- Carregando o Código na Placa Arduino:
    - Depois de fazer as alterações desejadas, conecte ao seu computador sua placa Arduino (via USB) e posteriormente selecione a placa e a porta corretas no Arduino IDE.  Em seguida, clique no botão "Verify/Compile" para detectar possíveis erros de sintaxe ou de compilação, caso não haja erros, pressione o botão "Upload" para carregar o código na sua placa e testá-lo.
      - Siga as instruções para calibrar as cores antes de usar o detector de cor;
      - Após a calibração, utilize o detector de cor conforme necessário.

## :construction_worker: Do It Yourself

```c++
> color_detector.ino

// O código do Arduino é lido de cima para baixo, então iremos seguir esse padrão no tutorial!

/**
* Vamos começar incluindo a biblioteca Adafruit_NeoPixel que nos permite controlar o componente neopixel.
* Tutorial de uso e documentação da biblioteca: https://github.com/adafruit/Adafruit_NeoPixel
**/
#include <Adafruit_NeoPixel.h>	

/**
* Agora vamos iniciar os pinos para o circuito!
* Defina o número de leds no NeoPixel, neste caso estamos usando apenas 1, logo, a variável NUMLEDS é 1;
* Defina algum pino digital como o pino do NeoPixel, neste exemplo usamos o pino 3 na variável PINNP;
* Em seguida defina algum pino analógico como o pino do LDR, nos usamos o pino A0 na variável PINLDR.
**/
#define NUMLEDS 1
#define PINNP 3
#define PINLDR A0

/**
* Aqui, nos vamos iniciar o NeoPixel usando uma função da biblioteca que nós adicinamos anteriormente, 
* a partir desse momento, neste exemplo o NeoPixel começa a ser referenciado como "led".
**/ 
Adafruit_NeoPixel led = Adafruit_NeoPixel(NUMLEDS, PINNP, NEO_GRB + NEO_KHZ800);

/**
* Então, vamos declarar algumas váriáveis que vamos usar na detecção, como a vaíável de leitura, que se chama leitura e
* pela lógica do sensor, também precisamos de intervalos de valores que vão ser definidos por váriáveis, como:
* "maxR" que armazena o maior valor lido na calibração na cor vermelha, por isso o prefixo "max" e o sufixo "R"
* que se refera "red"(vermelho, em inglês) e o menor valor é guardado na minR. A mesma lógica é aplicada para as outras cores.
* 
* ATENÇÃO: Note que a váriável de mínimo começa com um valor alto porque se fosse iniciada com 0, não seria atualizada.
**/
int leitura   = 0;
int minR      = 2000, maxR = 0;
int minG      = 2000, maxG = 0;
int minB      = 2000, maxB = 0;

/**
* Agora vamos a nossa função void setup(), nela vamos ligar o NeoPixel e fazer a calibração
* das cores para a detecção.
* A calibração inicial é importante para estabelecer os limites
* de leitura do LDR em diferentes condições de iluminação, garantindo uma detecção precisa das cores.
**/
void setup() {
  //	Preparando sensores.
  led.begin();
  led.show(); 
  Serial.begin(9600); 

  //	Calibrando cores no início.
  calibraRed();		//  Calibra a cor Vermelha.
  calibraGreen();	//  Calibra a cor Verde.
  calibraBlue();	//  Calibra a cor Azul.
}
// Fim da função void setup().

/**
* Após iniciar os nossos componentes e calibrar a leitura, vamos para a função void loop(),
* nela, o LDR será lido e esse valor passará por laços de seleção que vão verificar se
* ele está em algum dos intervalos que foram obtidos na calibração.
**/
void loop() {
  //	Iniciando leitura.
  leitura = analogRead(PINLDR);	//  Realiza uma leitura do LDR.

  Serial.println(leitura); //  Imprime a leitura do LDR no Monitor Serial.

  //	Detectando cores
  if (leitura < maxR && leitura > minR) { //  Verifica se a leitura está dentro dos limites de cor vermelha.
    Serial.println("Vermelho"); //  Se sim, imprime "Vermelho" no Monitor Serial.
  } else if (leitura < maxG && leitura > minG) {  //  Verifica se a leitura está dentro dos limites de cor verde.
    Serial.println("Verde");  //  Se sim, imprime "Verde" no Monitor Serial.
  } else if (leitura < maxB && leitura > minB) {  //  Verifica se a leitura está dentro dos limites de cor azul.
    Serial.println("Azul"); //  Se sim, imprime "Azul" no Monitor Serial.
  }

  delay(500);
}
// Fim da função void loop().

/**
* Aqui criamos as funções calibraRed(), calibraGreen() e calibraBlue(). 
* A calibração é simples, primeiro o led acenderá na cor a qual ele vai calibrar, 
* e após isso aguarda 1,5 segundos para iniciar a leitura e armazenar os valores nas variáveis.
* Esse processo é repetido três vezes, um para cada cor. Após a calibração, o LED é definido
* como branco para indicar que a calibração foi concluída com sucesso.
**/
void calibraRed() {
  //Calibrando Vermelho.
  led.setPixelColor(0, 255, 0, 0); //	Indicando que a cor Vermelho será calibrada.
  led.show();
  delay(1500);
  led.setPixelColor(0, 255, 255, 255); 
  led.show();
  calibraLDR(minR, maxR);
  delay(1500);
}

void calibraGreen() {
  //Calibrando Verde.
  led.setPixelColor(0, 0, 255, 0); //	Indicando que a cor Verde será calibrada.
  led.show();
  delay(1500);
  led.setPixelColor(0, 255, 255, 255); 
  led.show();
  calibraLDR(minG, maxG);
  delay(1500);
}

void calibraBlue() {
  //Calibrando Azul.
  led.setPixelColor(0, 0, 0, 255); //	Indicando que a cor Azul será calibrada.
  led.show();
  delay(1500);
  led.setPixelColor(0, 255, 255, 255); 
  led.show();
  calibraLDR(minB, maxB);
  delay(1500);
}

/**
* Essa é a função que faz a leitura de calibração de cada cor, nessa leitura o utilizador deve
* deixar o sensor logo acima da cor a ser calibrada, e após 100 leituras, o menor e o maior valor
* vão ser enviados pras váriáveis que declaramos anteriormente.
**/
void calibraLDR(int &minVal, int &maxVal) { 
  //  Inicializa os valores mínimos e máximos com os limites máximos possíveis.
  minVal = 2000;
  maxVal = 0;

  //  Loop para realizar várias leituras do LDR e calibrar os valores mínimos e máximos de uma forma mais precisa. 
  for (int i = 0; i < 100; i++) {
    leitura = analogRead(PINLDR); //  Realiza uma leitura do LDR.

    //  Atualiza o valor mínimo se a leitura atual for menor do que o valor mínimo atual.
    if (leitura < minVal) {
      minVal = leitura;
    }
    //  Atualiza o valor máximo se a leitura atual for maior do que o valor máximo atual.
    if (leitura > maxVal) {
      maxVal = leitura;
    }

    delay(100);
  }
}

```
Para mais informações de como o código funciona, <a href="./color_detector.ino">Acesse o código aqui</a>.

## :hammer_and_wrench: Tecnologias Utilizadas

<div align="center">

![YouTube](https://img.shields.io/badge/YouTube-%23FF0000.svg?style=for-the-badge&logo=YouTube&logoColor=white)
![Arduino](https://img.shields.io/badge/-Arduino-00979D?style=for-the-badge&logo=Arduino&logoColor=white)
![GitHub](https://img.shields.io/badge/github-%23000000.svg?style=for-the-badge&logo=github&logoColor=white)
![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)

</div>

# :card_index_dividers: Licença
Licença MIT. Para mais informações sobre a licença, <a href="./LICENSE">Clique aqui</a>

<img src="https://github.com/umroboporaluno/.github/blob/main/profile/ura-logo.png" alt="URA Logo" width="100" align="right" />