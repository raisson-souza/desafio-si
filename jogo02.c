const int numLEDs = 5;
const int leds[numLEDs] = {2, 3, 4, 5, 6}; // Pinos dos LEDs
const int botao = 7; // Pino do botão
int nivel = 1; // Nível do jogo, que aumenta a cada acerto
int tempoLED = 1000; // Tempo inicial de 1 segundo entre os LEDs
int ledAtual = 0; // LED atualmente aceso

bool jogoAtivo = true; // Estado do jogo

void setup() {
  // Configuração dos LEDs e do botão
  for (int i = 0; i < numLEDs; i++) {
    pinMode(leds[i], OUTPUT);
  }
  pinMode(botao, INPUT_PULLUP);

  // Começa o jogo com todos os LEDs apagados
  apagarTodosLEDs();
}

void loop() {
  // Verifica se o jogo está ativo
  if (jogoAtivo) {
    // Liga o LED atual e espera o tempo definido
    acenderLED(ledAtual);
    delay(tempoLED);
    apagarLED(ledAtual);

    // Verifica se o botão foi pressionado durante o LED do meio
    if (ledAtual == numLEDs / 2 && digitalRead(botao) == LOW) {
      // Acerto, avança de nível
      avancarNivel();
    } else if (ledAtual == numLEDs - 1 && digitalRead(botao) == HIGH) {
      // Se o jogador não acertou durante a sequência, termina o jogo
      finalizarJogo();
    }

    // Avança para o próximo LED
    ledAtual = (ledAtual + 1) % numLEDs;
  }
}

// Função para acender um LED específico
void acenderLED(int led) {
  digitalWrite(leds[led], HIGH);
}

// Função para apagar um LED específico
void apagarLED(int led) {
  digitalWrite(leds[led], LOW);
}

// Função para apagar todos os LEDs
void apagarTodosLEDs() {
  for (int i = 0; i < numLEDs; i++) {
    digitalWrite(leds[i], LOW);
  }
}

// Função para avançar de nível, aumentando a velocidade
void avancarNivel() {
  nivel++;
  tempoLED = max(100, tempoLED - 100); // Reduz o tempo até um mínimo de 100ms
  ledAtual = 0; // Reinicia a sequência
}

// Função para finalizar o jogo e acender todos os LEDs
void finalizarJogo() {
  jogoAtivo = false;
  for (int i = 0; i < numLEDs; i++) {
    digitalWrite(leds[i], HIGH);
  }
}
