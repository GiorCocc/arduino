//Primo esempio di macchina a stati finiti semplice realizzata con Arduino
//Nicola Delmonte
//Corso di Elementi e Laboratorio di Elettronica Digitale - Università di Parma
// A.A. 2020/2021
//LED che può essere acceso in 4 modi (stati) diversi:
//1=spento 2=acceso 100% 3=acceso 50% 4=lampeggiante

int var_stato = 1; //variabile di stato

void setup()
{
  pinMode(3, OUTPUT); //usiamo il pin 3 per avere la possibilità di modulare (PWM) la corrente media erogata al LED (50% e 100%)
  pinMode(2, INPUT); //usiamo il pin 2 per leggere il valore dell'unico ingresso primario esterno (pulsante N.O. pull-up)
}

void loop()
{
  switch(var_stato){
    
    case 1:
      loop1();
    break;
    
    case 2:
      loop2();
    break;
    
    case 3:
      loop3();
    break;
    
    case 4:
      loop4();
    break;
  }
}

//bisogna definire i "sub-loop" come delle funzioni,
//una per ogni rispettivo stato

void loop1() {
  digitalWrite(3, LOW); //Stato 1 led spento
  
  if (digitalRead(2)) {
    var_stato = 2;                //se il pulsante viene premuto mentre la FSM è nello stato 1, deve passare allo stato 2
    delay(300);                   //conviene aggiungere un piccolo delay per non avere cambi di stato molto rapidi e non capire cosa sta accadendo
  }
}
      
void loop2() {
  digitalWrite(3, HIGH);          //Stato 2 led acceso al 100% 

  if (digitalRead(2)) {
    var_stato = 3;                //se il pulsante viene premuto mentre la FSM è nello stato 2, deve passare allo stato 3
    delay(300);                   //come in loop1()
  } 
}

void loop3() {
  analogWrite(3,127);             //PWM con Duty Cycle = 50%  (vedi Reference Language di Arduino)
  
  if (digitalRead(2)) {
    var_stato = 4;                //se il pulsante viene premuto mentre la FSM è nello stato 3, deve passare allo stato 4
    delay(300);                   //come in loop1()
  } 
}

//Per il blinking e per fa si che non sia una condizione che bllocca la macchina
//servono due variabili per il conteggio del tempo
//una per l'istante iniziale (t0) e una per il tempo
//che è passato dall'istante iniziale (delta_t)

unsigned long t0, delta_t =0;

//e serve una variabile per indicare lo stato del led

int led_state = LOW;

void loop4() {
  delta_t = millis() - t0;
  if (delta_t >= 500) {                   //così avrò accensioni e spegnimenti di durata pari a 1/2 sec
    led_state = !led_state;               //così passiamo da stato on a off e viceversa
    digitalWrite(3, led_state);
    t0 = millis();                        //aggiorniamo t0 con il tempo di funzionamento attuale di Arduino
  }
    if (digitalRead(2)) {
      var_stato = 1;                      //se il pulsante viene premuto mentre la FSM è nello stato 4, deve passare allo stato 1
      delay(300);                         //come in loop1()
    } 
}
