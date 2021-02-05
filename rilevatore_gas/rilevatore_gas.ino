#include "IRremote.h"
#include <LiquidCrystal.h>

// led
const int verde = 3;
const int giallo = 4;
const int rosso = 5;

// ir
const int ir_receiver = 6;
IRrecv irrecv(ir_receiver);
decode_results results;

// lcd
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// sound
const int sound = 13;

// sensori
const int alcol = 2;
const int alcol_analog = A5;
const int co = 1;
const int co_analog = A4;
const int metano = 0;
const int metano_analog = A3;

// stati
int stateLedRed = 0;
int stateLedYellow = 0;
int stateLedGreen = 0;
int stateSensorCO = 0;
int stateSensorMetano = 0;
int stateSensorAlcol = 0;
int stateSound = 0;

// variabili per salvare i valori dei sensori
int valore_sensore_alcol = 0;
int valore_sensore_co = 0;
int valore_sensore_metano = 0;
int valore_default = 0;

// variabili per la gestione dei tempi
unsigned long tempo_inizio;
unsigned long tempo_fine;
int intervallo = 500;
unsigned long tempo_inizio_led;
unsigned long tempo_fine_led;

// procedura per il suono del cicalino
void sounds()
{
  for (int i = 0; i < 80; i++)
  {
    digitalWrite(sound, HIGH);
    delay(1); //attendo 1ms
    digitalWrite(sound, LOW);
    delay(1);
  }
}

// procedura per far spegnere il led (rosso) - si verifica un blink perchè lo stato del
// led rosso rimane su alto fino a che rimango nel caso di pericolo
void blinking()
{
  tempo_inizio_led = millis();                    // utilizzo il metodo millis per ricavare il tempo iniziale
  tempo_fine_led = tempo_inizio_led + intervallo; // aggiungo al tempo iniziale un intervallo
  while (tempo_inizio_led < tempo_fine_led)
  {
    digitalWrite(rosso, LOW); // spengo il led
    tempo_inizio_led = millis();
  }
}

// gestione degli stati dei led in base al valore registrato dal sensore selezionato
void loop_led(int valore_sensore)
{
  if (valore_sensore <= 650) // imposto ad alto lo stato del led verde e abbassto gli altri
  {
    stateLedRed = 0;
    stateLedYellow = 0;
    stateLedGreen = 1;
    stateSound = 0;
  }
  else if (valore_sensore > 650 && valore_sensore < 850) // imposto ad alto lo stato del led giallo e abbassto gli altri
  {
    stateLedRed = 0;
    stateLedYellow = 1;
    stateLedGreen = 0;
    stateSound = 0;
  }
  else if (valore_sensore >= 850) // imposto ad alto lo stato del led rosso e abbassto gli altri
  {
    stateLedRed = 1;
    stateLedYellow = 0;
    stateLedGreen = 0;

    // quando ricevo un valore alto avvio il suono e il blink del led rosso
    sounds();
    blinking();
  }
}

// procedura per la stampa del Lcd dei dati che devono rimanere visualizzati
void start_print()
{
  lcd.setCursor(0, 1);
  lcd.print("valore: ");
  lcd.setCursor(13, 1);
  lcd.print("PPM");
}

// procedura di temporizzazione per permettere la scrittura
// del valore del sensore in modo leggibile e controllato
void timing()
{
  tempo_inizio = millis();
  tempo_fine = tempo_inizio + intervallo;
  while (tempo_inizio < tempo_fine)
  {
    tempo_inizio = millis();
  }
  tempo_inizio = 0;
}

// procedura per cancellare il nome del sensore dal display per
// permettere di scriverne uno nuovo
void clear_lcd()
{
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 0);
}

// procedura per la stampa del valore del sensore sul display tra la scritta "valore:" e "PPM"
void stampa_valore(int valore_sensore)
{
  lcd.setCursor(8, 1);
  lcd.print(valore_sensore);
}

// procedura per la gestione dei sensori
void sensor()
{
  if (stateSensorAlcol == 1)
  {
    valore_sensore_alcol = map(analogRead(alcol_analog), 0, 1023, 20, 1500); // per migliorare la precisione del rilevamento usare la funzione map() e settare il range di azione del sensore su una scala diversa ma più vicina a quella reale (i valori impostati sono puramente indicativi e non corrispondono a quelli reali di pericolo)
    lcd.setCursor(8, 1);
    lcd.print("    "); // calcello il valore precedentemente stampato a display

    stampa_valore(valore_sensore_alcol);
    Serial.println(valore_sensore_alcol);
    loop_led(valore_sensore_alcol);
  }
  else if (stateSensorCO == 1)
  {
    valore_sensore_co = map(analogRead(co_analog), 0, 1023, 20, 2000);
    lcd.setCursor(8, 1);
    lcd.print("    "); // calcello il valore precedentemente stampato a display

    stampa_valore(valore_sensore_co);
    Serial.println(valore_sensore_alcol);
    loop_led(valore_sensore_co);
  }
  else if (stateSensorMetano == 1)
  {
    valore_sensore_metano = map(analogRead(metano_analog), 0, 1023, 20, 2000);
    lcd.setCursor(8, 1);
    lcd.print("    "); // calcello il valore precedentemente stampato a display

    stampa_valore(valore_sensore_metano);
    Serial.println(valore_sensore_alcol);
    loop_led(valore_sensore_metano);
  }
  else
  {
    stampa_valore(valore_default);
  }
}

// procedura per la gestione della pressione dei numeri del telecomando IR in base ai codici esadecimali
void IR_button()
{
  switch (results.value)
  {
  case 0xFF30CF: // pressione del tasto 1
  {
    clear_lcd();
    lcd.print("MQ-3 Alcol");
    Serial.println("MQ-3 Alcol");
    stateSensorCO = 0;
    stateSensorMetano = 0;
    stateSensorAlcol = 1;
    break;
  }

  case 0xFF18E7: // pressione del tasto 2
  {
    clear_lcd();
    lcd.print("MQ-7 CO");
    Serial.println("MQ-7 CO");
    stateSensorCO = 1;
    stateSensorMetano = 0;
    stateSensorAlcol = 0;
    break;
  }
  case 0xFF7A85: // pressione del tasto 3
  {
    clear_lcd();
    lcd.print("MQ-4 Metano");
    Serial.println("MQ-4 Metano");
    stateSensorCO = 0;
    stateSensorMetano = 1;
    stateSensorAlcol = 0;
    break;
  }
  }
}

void setup()
{
  pinMode(verde, OUTPUT);
  pinMode(giallo, OUTPUT);
  pinMode(rosso, OUTPUT);
  pinMode(sound, OUTPUT);
  pinMode(metano, OUTPUT);
  pinMode(co, OUTPUT);
  pinMode(alcol, OUTPUT);

  Serial.begin(9600);
  irrecv.enableIRIn();

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Rilevamento Gas"); // messaggio di benvenuto
}

void loop()
{

  if (irrecv.decode(&results))
  {
    IR_button();
    irrecv.resume();
  }

  start_print();
  timing();
  sensor();

  // gestione dell'illuminazione dei led in base allo stato assunto dalla FSM
  digitalWrite(verde, stateLedGreen);
  digitalWrite(giallo, stateLedYellow);
  digitalWrite(rosso, stateLedRed);
}
