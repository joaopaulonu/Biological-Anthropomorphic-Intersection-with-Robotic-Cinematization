// Inclui a biblioteca para controlar os servomotores
#include <Servo.h>

// Define os pinos digitais onde os servomotores estão conectados
#define PINO_SERVO_BASE 9
#define PINO_SERVO_COTOVELO 10

// Cria objetos Servo para cada motor
Servo servoBase;
Servo servoCotovelo;

// Define os comprimentos dos elos (braços) do robô em centímetros
// ATENÇÃO: ajuste esses valores para corresponder ao seu braço robótico
const float comprimentoElo1 = 12.0; // Distância do servo da base ao servo do cotovelo
const float comprimentoElo2 = 10.0; // Distância do servo do cotovelo à ponta do braço

// Variáveis para armazenar os ângulos dos servos em graus
int anguloBase = 0;
int anguloCotovelo = 0;

void setup() {
  // Inicializa a comunicação serial para exibir os resultados
  Serial.begin(9600);
  
  // Anexa os servos aos pinos definidos
  servoBase.attach(PINO_SERVO_BASE);
  servoCotovelo.attach(PINO_SERVO_COTOVELO);
  
  // Move os servos para a posição inicial (0 graus)
  servoBase.write(0);
  servoCotovelo.write(0);
  delay(1000); // Aguarda um segundo para os servos se moverem
}

void loop() {
  // Vamos variar os ângulos e calcular a posição
  // Loop para o servo da base
  for (anguloBase = 0; anguloBase <= 90; anguloBase += 10) {
    servoBase.write(anguloBase);
    delay(500); // Aguarda um momento para o braço se mover
    
    // Loop para o servo do cotovelo
    for (anguloCotovelo = 0; anguloCotovelo <= 90; anguloCotovelo += 10) {
      servoCotovelo.write(anguloCotovelo);
      delay(500); // Aguarda um momento para o braço se mover
      
      // Chama a função para calcular a cinemática direta e imprimir o resultado
      calcularCinematica(anguloBase, anguloCotovelo);
    }
  }
}

// Função para calcular e exibir a posição (X, Y)
void calcularCinematica(int angulo1, int angulo2) {
  // Converte os ângulos de graus para radianos, pois as funções
  // matemáticas de seno e cosseno (sin, cos) usam radianos
  float radiano1 = radians(angulo1);
  float radiano2 = radians(angulo2);
  
  // Equações da Cinemática Direta para um braço de 2 DOF
  // X = L1*cos(theta1) + L2*cos(theta1 + theta2)
  // Y = L1*sin(theta1) + L2*sin(theta1 + theta2)
  
  // Posição X da ponta do braço
  float posX = comprimentoElo1 * cos(radiano1) + comprimentoElo2 * cos(radiano1 + radiano2);
  
  // Posição Y da ponta do braço
  float posY = comprimentoElo1 * sin(radiano1) + comprimentoElo2 * sin(radiano1 + radiano2);
  
  // Imprime os resultados no Monitor Serial do Arduino
  Serial.print("Angulos: Base=");
  Serial.print(angulo1);
  Serial.print(" graus, Cotovelo=");
  Serial.print(angulo2);
  Serial.print(" graus -> ");
  Serial.print("Posicao (X, Y): (");
  Serial.print(posX);
  Serial.print(", ");
  Serial.print(posY);
  Serial.println(")");
}
