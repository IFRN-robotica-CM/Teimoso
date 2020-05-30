
/* ----------------------------------------------------------------------------------------- *\
|                                                                                             |
|                                                                                             |
|                                      Código Principal                                       |
|                                                                                             |
|                                                                                             |
\* ----------------------------------------------------------------------------------------- */

/**
 * Ultima atualização: 14/05/2020
 * 
 *  
 */

// ---------------------------------- BIBLIOTECAS USADAS ----------------------------------- //

#include <Arduino.h>
#include <EEPROM.h>
#include "CosmosNV2.h"
#include "Galaxias.h"

// ------------------------------- VARIÁVEIS E CONSTANTES ---------------------------------- //

// Os modos de operação do robô
const byte MODO_AREA_DE_PERCURSO = 1;
const byte MODO_RAMPA            = 2;
const byte MODO_AREA_DE_RESGATE  = 3;

byte modo = 0;           // Essa variável serve para guardar modo atual de operação do robô

char ultimaCurva = 'E';  // Essa variável serve para guardar o lado em que o robô deve desviar do obstáculo

// -------------------------------------- SETUP -------------------------------------------- //

void setup() {
  iniciarModulos();
  buscarModoNaEEPROM();
  esperarBotaoStartSerPressionado();
}

// -------------------------------------- LOOP --------------------------------------------- //

void loop() {
  if (modo == MODO_AREA_DE_PERCURSO) {
    modoAreaDePercurso();
  }

  else if (modo == MODO_RAMPA) {
    modoRampa();
  }

  else if (modo == MODO_AREA_DE_RESGATE) {
    modoAreaDeResgate();
  }
}

// ----------------------------------------------------------------------------------------- //

void iniciarModulos() {
  sensorDistanciaDireito.iniciar();
  sensorDistanciaEsquerdo.iniciar();

  motorDireito.configurarPonteH(L298N);
  motorEsquerdo.configurarPonteH(L298N);

  configurarVelocidadeDosMotores(80, 80);
}

void configurarVelocidadeDosMotores(byte velocidade_motor_esquerdo, byte velocidade_motor_direito) {
  motorEsquerdo.configurarVelocidade(velocidade_motor_esquerdo);
  motorDireito.configurarVelocidade(velocidade_motor_direito);
}

void buscarModoNaEEPROM(){
  /* 
    Não esquecer que na primeira vez que eu for rodar esse código,
    o botão Clear deve estar pressionado
  */
  if (botaoClear.lerEstado() == 1) {              // Se o botão Clear estiver pressionado
    EEPROM.write(0, MODO_AREA_DE_PERCURSO);       // Grava na posição 0 da EEPROM MODO_AREA_DE_PERCURSO
    modo = MODO_AREA_DE_PERCURSO;                 // Assume que o último modo foi MODO_AREA_DE_PERCURSO
  }
  else {
    modo = EEPROM.read(0);                        // Busca o modo na EEPROM
  }
}

void esperarBotaoStartSerPressionado() {
  while (botaoStart.lerEstado() == 0);// Esquanto o botão não for pressionado, o robô fica esperando
  irParaFrente();                     // Após o botão ser pressionado, o robô vai pra frente 
}

// ----------------------------------------------------------------------------------------- //

void modoAreaDePercurso() {
  sensoresDeFaixa.configurarModo(MODO_AREA_DE_PERCURSO);
  
  cronometro_1.configurarTempo(2000);
  cronometro_1.iniciarContagem();

  while (modo == MODO_AREA_DE_PERCURSO) {
    seguirFaixa();
    procurarObstaculosNaPista();
    verificarChegadaNarampa();
  }
}

void seguirFaixa() {
  byte situacao = sensoresDeFaixa.ler(); // Verifica o que os sensores de faixa estão enxergando e guarda na variável "situacao"

  if (situacao == CRUZAMENTO_TOTAL) {
    irParaFrente();
  }

  else if (situacao == CRUZAMENTO_COM_PRETO_NA_ESQUERDA) {
    irParaFrente();
  }

  else if (situacao == CRUZAMENTO_COM_PRETO_NA_DIREITA) {
    irParaFrente();
  }

  else if (situacao == CRUZAMENTO_T) {
    girarNoventaGrausParaEsquerda();
    ultimaCurva = 'E';
  }

  else if (situacao == CURVA_DE_NOVENTA_GRAUS_PARA_A_ESQUERDA) {
    girarNoventaGrausParaEsquerda();
    ultimaCurva = 'E';
  }

  else if (situacao == CURVA_DE_NOVENTA_GRAUS_PARA_A_DIREITA) {
    girarNoventaGrausParaDireita();
    ultimaCurva = 'D';
  }

  else if (situacao == CURVA_SIMPLES_PARA_A_ESQUERDA) {
    virarParaEsquerda();
    esperar(50);
    irParaFrente();
  }

  else if (situacao == CURVA_SIMPLES_PARA_A_DIREITA) {
    virarParaDireita();
    esperar(50);
    irParaFrente();
  }

  else if (situacao == LINHA_RETA or situacao == GAP) {
    irParaFrente();
  }

  else if (situacao == RETORNO_PARA_A_LINHA_PELA_ESQUERDA) {
    retornarParaLinhaPelaEsquerda();
  }

  else if (situacao == RETORNO_PARA_A_LINHA_PELA_DIREITA) {
    retornarParaLinhaPelaEsquerda();
  }
}

void procurarObstaculosNaPista() {
  if (sensorToqueFrontal.lerEstado() == 1) {
    desviarObtaculo();
  }
}

void desviarObtaculo() {
  irParaTras();
  esperar(400);

  if (ultimaCurva == 'E') {
    virarParaEsquerda();
    esperar(1200);

    configurarVelocidadeDosMotores(10, 100);

    irParaFrente();

    cronometro_1.configurarTempo(7000);    // Configura o cronômetro para contar 7 segundos

    while (true) {
      // Se o robô estiver muito próximo ao obstáculo então ele vira um pouco para a direita
      if (sensorDistanciaDireito.ler() <= 3) {
        configurarVelocidadeDosMotores(80, 80);
        virarParaEsquerda();
        esperar(50);
        
        configurarVelocidadeDosMotores(10, 100);
        irParaFrente();
      }

      if (cronometro_1.finalizouContagem()) { // Depois que o cronômetro acabar de contar

        if (sensoresDeFaixa.lerSensorCentral() >= 500) {    // Procura fita preta
          girarNoventaGrausParaDireita();
          cronometro_1.configurarTempo(2000);
          cronometro_1.iniciarContagem();
          break;
        }
      }
    }
  }

  else if (ultimaCurva == 'D') {
    virarParaDireita();
    esperar(1200);

    configurarVelocidadeDosMotores(100, 10);

    irParaFrente();

    cronometro_1.configurarTempo(7000);    // Configura o cronômetro para contar 7 segundos

    while (true) {
      // Se o robô estiver muito próximo ao obstáculo então ele vira um pouco para a esquerda
      if (sensorDistanciaEsquerdo.ler() <= 3) {
        configurarVelocidadeDosMotores(80, 80);
        virarParaDireita();
        esperar(50);
        
        configurarVelocidadeDosMotores(100, 10);
        irParaFrente();
      }

      if (cronometro_1.finalizouContagem()) { // Depois que o cronômetro acabar de contar

        if (sensoresDeFaixa.lerSensorCentral() >= 500) {     // Procura fita preta
          girarNoventaGrausParaEsquerda();
          cronometro_1.configurarTempo(2000);
          cronometro_1.iniciarContagem();
          break;
        }
      }
    }
  }
}

void verificarChegadaNarampa() {
  if (cronometro_1.finalizouContagem()) {

    int distancia_direita  = sensorDistanciaDireito.ler();
    int distancia_esquerda = sensorDistanciaEsquerdo.ler();

    if (distancia_direita <= 15 and distancia_esquerda <= 15) {
      modo = MODO_RAMPA;
    }

    else {
      cronometro_1.iniciarContagem();
    }
  } 
}

// ----------------------------------------------------------------------------------------- //

void modoRampa() {
  sensoresDeFaixa.configurarModo(MODO_RAMPA);

  configurarVelocidadeDosMotores(100, 100);

  cronometro_1.configurarTempo(1000);
  cronometro_1.iniciarContagem();
  
  while (modo == MODO_RAMPA) {
    seguirFaixaDaRampa();
    verificarChegadaNaAreaDeReagate();
  }
}

void seguirFaixaDaRampa() {
  byte situacao =  sensoresDeFaixa.ler();

  if (situacao == CURVA_SIMPLES_PARA_A_ESQUERDA) {
    configurarVelocidadeDosMotores(80, 80);
    virarParaEsquerda();
    esperar(50);

    configurarVelocidadeDosMotores(100, 100);
    irParaFrente();
  }

  else if (situacao == CURVA_SIMPLES_PARA_A_DIREITA) {
    configurarVelocidadeDosMotores(80, 80);
    virarParaDireita();
    esperar(50);

    configurarVelocidadeDosMotores(100, 100);
    irParaFrente();
  }

  else if (situacao == LINHA_RETA) {
    irParaFrente();
  }

  else if (situacao == RETORNO_PARA_A_LINHA_PELA_ESQUERDA) {
    retornarParaLinhaPelaEsquerda();
  }

  else if (situacao == RETORNO_PARA_A_LINHA_PELA_DIREITA) {
    retornarParaLinhaPelaEsquerda();
  }
}

void verificarChegadaNaAreaDeReagate() {
  if (cronometro_1.finalizouContagem()) {

    int distancia_esquerda = sensorDistanciaEsquerdo.ler();

    if (distancia_esquerda > 15) {
    /*
      Atualiza o modo na eeprom para que 
      na próxima vez que o robô for iniciado,
      ele venha direto para esse modo 
    */
      EEPROM.update(0, modo);
      modo = MODO_AREA_DE_RESGATE;
    }

    else {
      cronometro_1.iniciarContagem();
    }
  }
}

// ----------------------------------------------------------------------------------------- //

void modoAreaDeResgate() {
  irParaFrente();
  esperar(3000);
  parar();

  while (true);
}

// ----------------------------------------------------------------------------------------- //

// Faz o robô ir para frente
void irParaFrente() {
  motorDireito.girar(PARA_FRENTE);
  motorEsquerdo.girar(PARA_FRENTE);
}

// Faz o robô ir para trás
void irParaTras() {
  motorDireito.girar(PARA_TRAS);
  motorEsquerdo.girar(PARA_TRAS);
}

// Vira o robô para a esquerda 
void virarParaEsquerda() {
  motorDireito.girar(PARA_FRENTE);
  motorEsquerdo.girar(PARA_TRAS);
}

// Vira o robô para a direita
void virarParaDireita() {
  motorDireito.girar(PARA_TRAS);
  motorEsquerdo.girar(PARA_FRENTE);
}

// Faz com que o robô gire 90° para esquerda
void girarNoventaGrausParaEsquerda() {

  // Vai pra frente

  configurarVelocidadeDosMotores(100, 100);

  irParaFrente();
  esperar(300);

  // Vira para esquerda até que o sensor frontal encontre a linha
  virarParaEsquerda();
  esperar(300);

  int valor_lido = 0;

  do {
    valor_lido = sensoresDeFaixa.lerSensorFrontal();
  } while (valor_lido <= 600);

  // Vai pra frente

  configurarVelocidadeDosMotores(80, 80);
  irParaFrente();
}

// Faz com que o robô fique gire 90° para direita
void girarNoventaGrausParaDireita() {

  // Vai pra frente

  configurarVelocidadeDosMotores(100, 100);

  irParaFrente();
  esperar(150);

  // Vira para direita até que o sensor frontal encontre a linha
  virarParaDireita();
  esperar(150);

  int valor_lido = 0;

  do {
    valor_lido = sensoresDeFaixa.lerSensorFrontal();
  } while (valor_lido <= 600);

  // Vai pra frente

  configurarVelocidadeDosMotores(80, 80);
  irParaFrente();
}

// Função que é executada caso o robô se perca da linha
void retornarParaLinhaPelaEsquerda() {

  // Vira para esquerda até que o sensor frontal encontre a linha

  configurarVelocidadeDosMotores(100, 100);

  virarParaEsquerda();
  esperar(250);

  int valor_lido = 0;

  do {
    valor_lido = sensoresDeFaixa.lerSensorFrontal();
  } while (valor_lido <= 600);

  // Vai pra frente até que o sensor central encontre a linha
  irParaFrente();

  do {
    valor_lido = sensoresDeFaixa.lerSensorCentral();
  } while (valor_lido <= 600);

  // Vira para direita até que o sensor frontal encontre a linha
  virarParaDireita();

  do {
    valor_lido = sensoresDeFaixa.lerSensorFrontal();
  } while (valor_lido <= 600);

  // Vai pra frente

  if (modo == MODO_AREA_DE_PERCURSO) {
    configurarVelocidadeDosMotores(80, 80);
  }

  irParaFrente();
}

// Função que é executada caso o robô se perca da linha
void retornarParaLinhaPelaDireita() {

  // Vira para direita até que o sensor frontal encontre a linha
  configurarVelocidadeDosMotores(100, 100);

  virarParaDireita();
  esperar(250);

  int valor_lido = 0;

  do {
    valor_lido = sensoresDeFaixa.lerSensorFrontal();
  } while (valor_lido <= 600);

  // Vai pra frente até que o sensor central encontre a linha
  irParaFrente();

  do {
    valor_lido = sensoresDeFaixa.lerSensorCentral();
  } while (valor_lido <= 600);

  // Vira para esquerda até que o sensor frontal encontre a linha
  virarParaEsquerda();

  do {
    valor_lido = sensoresDeFaixa.lerSensorFrontal();
  } while (valor_lido <= 600);

  // Vai pra frente

  if (modo == MODO_AREA_DE_PERCURSO) {
    configurarVelocidadeDosMotores(80, 80);
  }

  irParaFrente();
}

// Para o robô
void parar() {
  motorDireito.parar(); 
  motorEsquerdo.parar(); 
} 
