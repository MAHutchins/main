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

int tx = 2; //To Arduino TX
int rx = 3;

SoftwareSerial mySerial(rx, tx);

void setup() {
  mySerial.begin(9600);
}

void loop() {
  mySerial.println("Test");
  delay(1000);
}
