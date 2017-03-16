/* Blinks the received IR signal on an LED
*
* The purpose of this script is to enable the user to decipher
* an IR signal without needing a serial connection.
*/

/*ISP:
 * MISO VCC
 * SCK  MOSI
 * RST  GND
 */

/*ATTiny85
 * RST  VCC
 * PB3  PB2/SCK
 * PB4  PB1/MISO
 * GND  PB0/MOSI
 */

//Array for 32 bits of the signal
int pArray[32];
bool ledState = 0;
bool pressed = 0;

int led = 3; //Physical pin 2 to LED

void setup() {
  pinMode(led, OUTPUT);
}

void loop() {
  //Get the pulses from pin 2 (physical pin 7) and store them in pArray
  getPulses(2, &pArray[0]);
  
  //Blink the command on an LED
  for (int i = 17; i <= 24; i++){
    if (pArray[i]){
      digitalWrite(led, HIGH);
      delay(1000);
      digitalWrite(led, LOW);
      delay(500);
    }else{
      digitalWrite(led, HIGH);
      delay(500);
      digitalWrite(led, LOW);
      delay(500);
    }
  }
  
}

void getPulses(int pin, int *pulses){
  int p;
  int i;
  
  //Clear the space in memory
  for (i = 0; i < 32; i++){
    pulses[i] = 0;
  }

  //Reset i to 0
  i = 0;

  //Get a pulse 32 times
  while (i < 32){
    //Time a HIGH pulse on pin
    p = pulseIn(pin, HIGH);
    //If the pulse is between 300 and 3000 microseconds (exclude start signal and noise)
    if (p > 300 && p < 3000){
      //If the pulse is less than 1200us 
      if (p < 1200){
        //Logical 0
        pulses[i] = 0;
        //Go to the next bit
        i++;
      }else{
        //Logical 1
        pulses[i] = 1;
        //Go to the next bit
        i++;
      }
    }
  }
  delay(500);
}
