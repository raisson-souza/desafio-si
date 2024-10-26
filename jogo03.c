const int numLEDs = 5;
const int leds[numLEDs] = {2, 3, 4, 5, 6}; // Pinos dos LEDs
const int botao = 7; // Pino do botão
int nivel = 1; // Nível do jogo, que aumenta a cada acerto
int tempoLED = 1000; // Tempo inicial de 1 segundo entre os LEDs
int ledAtual = 0; // LED atualmente aceso
bool direcaoHorario = true; // Direção inicial (horário)

bool jogoAtivo = true; // Estado do jogo

void setup() {
  // Inicializa a comunicação serial
  Serial.begin(9600);

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
    Serial.print("LED aceso: ");
    Serial.println(ledAtual); // Exibe o LED atual aceso no console
    delay(tempoLED);
    apagarLED(ledAtual);

    // Verifica se o botão foi pressionado durante o LED do meio
    if (ledAtual == numLEDs / 2 && digitalRead(botao) == LOW) {
      // Acerto, avança de nível
      avancarNivel();
      Serial.println("Botão pressionado: ACERTO!"); // Indica acerto ao pressionar o botão
    } else if (ledAtual == (direcaoHorario ? numLEDs - 1 : 0) && digitalRead(botao) == HIGH) {
      // Se o jogador não acertou durante a sequência, reinicia em direção oposta
      inverterDirecao();
      Serial.println("Oportunidade perdida, mudando direção.");
    }

    // Se o botão for pressionado sem estar no LED certo
    if (digitalRead(botao) == LOW) {
      Serial.println("Botão pressionado"); // Exibe mensagem no console quando o botão é pressionado
    }

    // Avança para o próximo LED na direção atual
    ledAtual = proximoLED();
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
  Serial.print("Nível: ");
  Serial.println(nivel);
  Serial.println("Aumentando dificuldade.");
}

// Função para inverter a direção do jogo e reiniciar a sequência
void inverterDirecao() {
  direcaoHorario = !direcaoHorario; // Inverte a direção
  ledAtual = direcaoHorario ? 0 : numLEDs - 1; // Reinicia a sequência no extremo oposto
}

// Função para calcular o próximo LED com base na direção
int proximoLED() {
  if (direcaoHorario) {
    return (ledAtual + 1) % numLEDs;
  } else {
    return (ledAtual - 1 + numLEDs) % numLEDs; // Modulo para garantir que seja positivo
  }
}
