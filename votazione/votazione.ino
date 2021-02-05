const int votazione = 2;
const int respinto = 3;
const int approvato = 4;

const int button_president = 8;
const int button_1 = 9;
const int button_2 = 10;
const int button_3 = 11;

int stateButtonPresident = 0;
int stateButton1 = 0;
int stateButton2 = 0;
int stateButton3 = 0;

unsigned long tempo_inizio;
unsigned long tempo_fine;

void setup()
{
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);

  Serial.begin(9600);

}

void loop()
{
  stateButtonPresident = digitalRead(button_president);
  tempo_inizio = 0;

  if (stateButtonPresident)
  {
    digitalWrite(votazione, stateButtonPresident);
    digitalWrite(approvato, LOW);
    digitalWrite(respinto, LOW);

    tempo_inizio = millis();
    tempo_fine = tempo_inizio + 10000;

    while (tempo_inizio < tempo_fine)
    {
      int uno = digitalRead(button_1);
      int due = digitalRead(button_2);
      int tre = digitalRead(button_3);

      if (uno == 1) stateButton1 = uno;
      else if (due == 1) stateButton2 = due;
      else if (tre == 1) stateButton3 = tre;

//      Serial.print(stateButton1);
//      Serial.print(stateButton2);
//      Serial.print(stateButton3);
//      Serial.print("\n");
      tempo_inizio = millis();
    }
    stateButtonPresident = 0;
    digitalWrite(votazione, stateButtonPresident);
    tempo_inizio = 0;
  }

  int verde = (stateButton1 && stateButton3) || (stateButton1 && stateButton2) || (stateButton2 && stateButton3);
  int rosso = !verde;

  digitalWrite(approvato, verde);
  digitalWrite(respinto, rosso);
}
