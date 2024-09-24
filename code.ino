int led_vermelho = 4;   // Define o pino para o LED vermelho
int led_amarelo = 3;    // Define o pino para o LED amarelo
int led_verde = 2;      // Define o pino para o LED verde

int buzzer = 9;         // Define o pino para o buzzer
int sensor_ult_trig = 11; // Define o pino TRIG do sensor ultrassônico
int sensor_ult_echo = 10;  // Define o pino ECHO do sensor ultrassônico

void setup() {
  // Configura todos os LEDs como saída
  pinMode(led_vermelho, OUTPUT);
  pinMode(led_amarelo, OUTPUT);
  pinMode(led_verde, OUTPUT);
  
  // Configura o buzzer como saída
  pinMode(buzzer, OUTPUT);
  
  // Inicializa os pinos do sensor ultrassônico (para uso posterior)
  pinMode(sensor_ult_trig, OUTPUT);
  pinMode(sensor_ult_echo, INPUT);
}

void loop() {
  long duration, distance; // Declara variáveis para armazenar a duração do pulso e a distância
  
  // Limpa o pino do TRIG antes de enviar um novo pulso
  digitalWrite(sensor_ult_trig, LOW);
  delayMicroseconds(2); // Aguarda 2 microsegundos
  
  // Envia um pulso de 10 microsegundos para o TRIG
  digitalWrite(sensor_ult_trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(sensor_ult_trig, LOW);
    
  // Lê a duração do pulso no pino ECHO
  duration = pulseIn(sensor_ult_echo, HIGH);
  
  // Calcula a distância em centímetros
  distance = duration * 0.034 / 2; // Fórmula: distância = (tempo * velocidade do som) / 2
  
  Serial.print("Distância: "); // Imprime a distância no console serial
  Serial.print(distance);
  Serial.print(" cm");
  
  // Controla os LEDs e o buzzer com base na distância
  if (distance < 51 && distance > 40) {
    digitalWrite(led_vermelho, LOW);   // Desliga o LED vermelho
    digitalWrite(led_amarelo, LOW);    // Desliga o LED amarelo
    digitalWrite(led_verde, HIGH);     // Liga o LED verde
    tone(buzzer, 250);                  // Emite um som de 250 Hz
  } else if (distance < 39 && distance > 30) {
    digitalWrite(led_vermelho, LOW);   // Desliga o LED vermelho
    digitalWrite(led_amarelo, HIGH);   // Liga o LED amarelo
    digitalWrite(led_verde, LOW);      // Desliga o LED verde
    tone(buzzer, 500);                  // Emite um som de 500 Hz
  } else if (distance < 29 && distance > 20) {
    digitalWrite(led_vermelho, HIGH);  // Liga o LED vermelho
    digitalWrite(led_amarelo, LOW);    // Desliga o LED amarelo
    digitalWrite(led_verde, LOW);      // Desliga o LED verde
    tone(buzzer, 1000);                 // Emite um som de 1000 Hz
  } else {
    digitalWrite(led_vermelho, LOW);   // Desliga todos os LEDs
    digitalWrite(led_amarelo, LOW);
    digitalWrite(led_verde, LOW);
    noTone(buzzer);                    // Desliga o buzzer
  }
}
