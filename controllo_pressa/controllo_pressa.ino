const int destra = 2;
const int sinistra=3;
const int pressa=7;

const int rosso=6;
const int verde=5;
const int blu=4;

int stateDestra=0;
int stateSinistra=0;
int statePressa=0;

void setup()
{
  pinMode(destra, INPUT);
    pinMode(sinistra, INPUT);
    pinMode(pressa, INPUT);
  
    pinMode(rosso, OUTPUT);
    pinMode(verde, OUTPUT);
    pinMode(blu, OUTPUT);
}

void loop()
{
  stateDestra=digitalRead(destra);
  stateSinistra=digitalRead(sinistra);
  statePressa=digitalRead(pressa);
  
  int Blu=statePressa&&stateDestra&&stateSinistra;
  int Verde=!statePressa&&stateDestra&&stateSinistra;
  int Rosso=!Verde;
    
  digitalWrite(rosso, Rosso);
  digitalWrite(verde, Verde);
  digitalWrite(blu, Blu);
  
}
