const int a=13;
const int b=12;
const int c=11;
const int d=10;
const int e=9;
const int f=8;
const int g=7;

const int button=2;

int numero=6;

int A,B,C=0;

int state_a=0;
int state_b=0;
int state_c=0;
int state_d=0;
int state_e=0;
int state_f=0;
int state_g=0;
int state_button=0;


void setup()
{
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  
  pinMode(2, INPUT);
}

void loop()
{
  state_button=digitalRead(button);
  if(state_button)
  {
    numero=random(1,7);
  }

  if(numero==1)
  {
    A=1;
    B=0;
    C=0;
  } else if(numero==2)
  {
    A=0;
    B=1;
    C=0;
  } else if(numero==3)
  {
    A=1;
    B=1;
    C=0;
  } else if(numero==4)
  {
    A=0;
    B=0;
    C=1;
  } else if(numero==5)
  {
    A=1;
    B=0;
    C=1;
  } else if(numero==6)
  {
    A=0;
    B=1;
    C=1;
  }
   
  
  state_a = (C && A) || B;
  state_b = (!C) || ((!A) && (!B));
  state_c = A || C;
  state_d = (C && A) || B;
  state_e = B &&(!A);
  state_f = C;
  state_g = C || B;
  
  digitalWrite(a,state_a); //prova per vedere se si accende il led
  digitalWrite(b,state_b);
  digitalWrite(c,state_c);
  digitalWrite(d,state_d);
  digitalWrite(e,state_e);
  digitalWrite(f,state_f);
  digitalWrite(g,state_g);
  
  
}
