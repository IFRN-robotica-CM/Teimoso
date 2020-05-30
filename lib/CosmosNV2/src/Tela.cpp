
#include <Arduino.h>
#include "Constantes.h"
#include "Tela.h"

// ----------------------------------- Classe Tela --------------------------------------- //

Tela::Tela() {
  display = Adafruit_SSD1306(128, 64, &Wire, 4);
}

void Tela::iniciar() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  configurarCorDoTexto(BRANCO);
  configurarTamanhoDoTexto(2);
}

void Tela::configurarCursor(uint16_t x, uint16_t y) {
  display.setCursor(x, y);
}

void Tela::mostrar() {
  display.display();
}

void Tela::limpar() {
  display.clearDisplay();
}

void Tela::configurarTamanhoDoTexto(uint8_t tamanho) {
  display.setTextSize(tamanho);
}

void Tela::configurarCorDoTexto(uint16_t cor) {
  display.setTextColor(cor);
}

void Tela::escrever(const char* texto) {
  display.print(texto);
}

void Tela::escrever(int numero) {
  display.print(numero);
}

void Tela::escrever(float numero) {
  display.print(numero);
}

void Tela::escrever(long numero) {
  display.print(numero);
}

void Tela::escrever(unsigned long numero) {
  display.print(numero);
}

void Tela::desenharImagem(uint16_t x, uint16_t y, const uint8_t imagem[], uint16_t altura, 
                             uint16_t largura, uint16_t cor) 
{
  display.drawBitmap(x, y, imagem, largura, altura, cor);
}
