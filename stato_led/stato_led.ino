const int A=1;
const int B=2;

const int r=8;
const int v=9;
const int g=10;

int stateButtonA=0;
int stateButtonB=0;
int stateLedR=0;
int stateLedV=0;
int stateLedG=0;

void setup()
{
  pinMode(1, INPUT);
  pinMode(2, INPUT);
  
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
}

void loop()
{
  stateButtonA=digitalRead(A);
  stateButtonB=digitalRead(B);
  
  stateLedG=stateButtonA&&stateButtonB;
  stateLedV=!stateButtonA&&stateButtonB;
  stateLedR=stateButtonA&&!stateButtonB;
  
  digitalWrite(r, stateLedR);
  digitalWrite(g, stateLedG);
  digitalWrite(v, stateLedV);
  delay(1000);
}
