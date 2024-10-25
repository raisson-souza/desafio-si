// hot potato https://docs.google.com/document/d/1FJIRRBNjGgHSEqICPN-LT2eB78wS7skzRDfmSL34gbs/edit?tab=t.0#heading=h.e3qogyettd65

// Configuração do número de jogadores
const int numJogadores = 4;
const int leds[numJogadores] = {2, 3, 4, 5}; // Pinos dos LEDs
const int botoes[numJogadores] = {6, 7, 8, 9}; // Pinos dos botões

int jogadorAtual = 0; // LED que está aceso
int tempoLimite = 5000; // Tempo limite para cada jogador (em milissegundos)
unsigned long tempoInicio = 0; // Armazena o tempo inicial de cada rodada
bool jogadorEliminado[numJogadores] = {false, false, false, false}; // Jogadores ativos

void setup() {
  // Configuração dos LEDs e botões
  for (int i = 0; i < numJogadores; i++) {
    pinMode(leds[i], OUTPUT);
    pinMode(botoes[i], INPUT_PULLUP);
  }

  // Inicia o jogo com o primeiro jogador
  acenderLED(jogadorAtual);
  tempoInicio = millis();
}

void loop() {
  // Verifica o tempo para o jogador atual
  unsigned long tempoAtual = millis();
  if (tempoAtual - tempoInicio > tempoLimite) {
    eliminarJogador(jogadorAtual);
    passarParaProximoJogador();
  }

  // Verifica se algum jogador pressionou o botão para passar o LED
  if (digitalRead(botoes[jogadorAtual]) == LOW) {
    passarParaProximoJogador();
  }
}

// Função para acender o LED do jogador atual
void acenderLED(int jogador) {
  for (int i = 0; i < numJogadores; i++) {
    digitalWrite(leds[i], LOW);
  }
  digitalWrite(leds[jogador], HIGH);
}

// Função para eliminar um jogador
void eliminarJogador(int jogador) {
  jogadorEliminado[jogador] = true;
}

// Função para passar o LED para o próximo jogador ativo
void passarParaProximoJogador() {
  do {
    jogadorAtual = (jogadorAtual + 1) % numJogadores;
  } while (jogadorEliminado[jogadorAtual]);

  acenderLED(jogadorAtual);
  tempoInicio = millis(); // Reinicia o tempo para o novo jogador
}
