#define TX_PIN_BIT 0 

#define TX_HIGH() (PORTB |= (1 << TX_PIN_BIT)) 
#define TX_LOW()  (PORTB &= ~(1 << TX_PIN_BIT))

const int BIT_DELAY = 104; 

void setup() {
  DDRB |= (1 << TX_PIN_BIT);
  
  TX_HIGH();
}

void loop() {
  sendChar('a');
  delay(100);
}

void sendChar(char data) {
  TX_LOW();
  delayMicroseconds(BIT_DELAY);
  
  for (int i = 0; i < 8; i++) {
    if (data & (1 << i)) {
      TX_HIGH(); // 비트가 1이면 HIGH (5V)
    } else {
      TX_LOW();  // 비트가 0이면 LOW (0V)
    }
    delayMicroseconds(BIT_DELAY);
  }
  
  TX_HIGH();
  delayMicroseconds(BIT_DELAY);
}