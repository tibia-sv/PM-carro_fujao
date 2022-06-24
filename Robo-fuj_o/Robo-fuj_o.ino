#define IN1 2
#define IN2 3
#define IN3 8
#define IN4 12
#define pwmD 9
#define pwmE 10
#define trigF 6
#define trigT 4
#define echoF 7
#define echoT 5

int distanciaF;
int distanciaT;
int estado = 1;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(pwmD, OUTPUT);
  pinMode(pwmE, OUTPUT);
  pinMode(trigF, OUTPUT);
  pinMode(trigT, OUTPUT);
  pinMode(echoF, INPUT);
  pinMode(echoT, INPUT);
}


void loop() {
  distanciaF = ler_distanciaF();
  distanciaT = ler_distanciaT();

 
  
  while(distanciaF <= 10 && distanciaT <= 10){
    motor(0);
    delay(200);
    distanciaT = ler_distanciaT();
    distanciaF = ler_distanciaF();
  }
    while(distanciaF>10 && distanciaT <= 10){
      estado = 1;
      motor(50);
      delay(200);
      distanciaF = ler_distanciaF();
      distanciaT = ler_distanciaT();
    }
    while(distanciaT>10 && distanciaF <= 10){
      estado = 2;
      motor(-50);
      delay(200);
      distanciaT = ler_distanciaT();
      distanciaF = ler_distanciaF();
    }
    while(distanciaT > 10 && distanciaF > 10){
      if(estado == 1){
      motor(50);
      delay(200);
      distanciaT = ler_distanciaT();
      distanciaF = ler_distanciaF();
      }
      if(estado == 2){
      motor(-50);
      delay(200);
      distanciaT = ler_distanciaT();
      distanciaF = ler_distanciaF();
      }
    }
}

void motor(int vel){
  vel = map(vel, -100, 100, -255, 255);
  if(vel>0){
    digitalWrite(IN1, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN4, LOW);
    analogWrite(pwmD, vel);
    analogWrite(pwmE, vel);
  }else{
    digitalWrite(IN1, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN4, HIGH);
    analogWrite(pwmD, -vel);
    analogWrite(pwmE, -vel);
  }
}

float ler_distanciaF(){
  digitalWrite(trigF, LOW);
  delayMicroseconds(2);
  digitalWrite(trigF, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigF, LOW);
  
  long duration = pulseIn(echoF, HIGH);
  float distancia = ((duration * 0.034)/ 2.0);
  return distancia;
}

float ler_distanciaT(){
  digitalWrite(trigT, LOW);
  delayMicroseconds(2);
  digitalWrite(trigT, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigT, LOW);
  
  long duration = pulseIn(echoT, HIGH);
  float distancia = ((duration * 0.034)/ 2.0);
  return distancia;
}
