
#ifndef _Tela_h
#define _Tela_h

#include <Arduino.h>
#include "Adafruit_SSD1306.h"

// ----------------------------------- Classe Tela --------------------------------------- //

class Tela
{
  public:
    Tela();
    void iniciar();
    void configurarCursor(uint16_t x, uint16_t y);
    void mostrar();
    void limpar();

    void configurarTamanhoDoTexto(uint8_t tamanho);
    void configurarCorDoTexto(uint16_t cor);
    void escrever(const char* texto);
    void escrever(int numero);
    void escrever(float numero);
    void escrever(long numero);
    void escrever(unsigned long numero);

    void desenharImagem(uint16_t x, uint16_t y, const uint8_t imagem[], uint16_t altura, 
                        uint16_t largura, uint16_t cor);
  private:
    Adafruit_SSD1306 display;
};

#endif
