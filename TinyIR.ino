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
 
#include <SoftwareSerial.h>

//Array for 32 bits of the signal
int pArray[32];
bool ledState = 0;
bool pressed = 0;

const int rx = 3;
const int tx = 4; //Physical pin 3 to Arduino TX
int led = 3;

SoftwareSerial mySerial(rx, tx);

void setup() {
  mySerial.begin(9600);
  pinMode(led, OUTPUT);
}

void loop() {
  //Get the pulses from pin 2 (physical pin 7) and store them in pArray
  getPulses(2, &pArray[0]);
  
  //Print address segment (bits 1-8)
  mySerial.print("Addr: ");
  for (int i = 0; i <= 7; i++){
    mySerial.print(pArray[i]);
  }

  //Print command segment (bits 18-25)
  mySerial.print(" Cmd: ");
  for (int i = 17; i <= 24; i++){
    mySerial.print(pArray[i]);
  }
  mySerial.println();

  //Power button turns an LED on or off
  int kArray[] = {0,0,1,0,0,0,0,1};
  if (check(&pArray[0], &kArray[0])){
    if (ledState){
      digitalWrite(led, LOW);
      ledState = 0;
    }else{
      digitalWrite(led, HIGH);
      ledState = 1;
    }
    pArray[0] += 1;
  }
  mySerial.println(check(&pArray[0], &kArray[0]));
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

bool check(int *input, int *key){
  bool state = true;
  for (int i = 0; i < 8; i++){
    if (input[i+17] != key[i]){
      state = false;
    }
    mySerial.print(input[i+17]);
    mySerial.print(key[i]);
    mySerial.println();
  }
  return state;
}
