
// Pinos ===================================
const int pinoLuzUV = 2;
const int pinoSensorDeUmidade = A0;
const int pinoBombaDeAgua = 3;
//==========================================

// Luz UV ==================================
bool luzUVLigada = true;
const unsigned long tempoDesligada = 14UL * 60 * 60 * 1000; // 10 segundos
const unsigned long tempoLigada = 10UL * 60 * 60 * 1000; // 5 segundos
unsigned long tempoInicial = 0;
unsigned long* tempoDeReferencia = &tempoLigada;
//==========================================

// Bomba de agua ===========================
bool bombaLigada = false;
const short minAgua = 900;
const short maxAgua = 500;
//==========================================
void setup() {
  pinMode(pinoLuzUV, OUTPUT);
  pinMode(pinoSensorDeUmidade, INPUT);
  pinMode(pinoBombaDeAgua, OUTPUT);

  //Liga UV
  digitalWrite(pinoLuzUV, LOW);
  //Desliga Bomba
  digitalWrite(pinoBombaDeAgua, HIGH);

  //Timer
  tempoInicial = millis();
}

void loop() {
  UVLight();
  WaterBombManager();
}

void UVLight(){
  if(millis() - tempoInicial >= *tempoDeReferencia){
    switchUV();
  }
}

void WaterBombManager(){
  unsigned short umidade = analogRead(pinoSensorDeUmidade);

  if(!bombaLigada && umidade >= minAgua){
    bombaLigada = true;
    digitalWrite(pinoBombaDeAgua, LOW);
  }else if(bombaLigada && umidade <= maxAgua){
    bombaLigada = false;
    digitalWrite(pinoBombaDeAgua, HIGH);
  }
}
void switchUV(){
  if(luzUVLigada){ 
    //Desliga
    digitalWrite(pinoLuzUV, HIGH);
    tempoDeReferencia = &tempoDesligada;
  }else{
    //Liga
    digitalWrite(pinoLuzUV, LOW);
    tempoDeReferencia = &tempoLigada;
  }

  tempoInicial = millis();
  luzUVLigada = !luzUVLigada;
}
