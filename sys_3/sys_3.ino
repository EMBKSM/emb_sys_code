// D8 핀을 비트뱅 송신용으로 사용
#define TX_PIN_BIT 0 // PORTB의 0번 비트 (D8)
#define TX_HIGH() (PORTB |= (1 << TX_PIN_BIT))
#define TX_LOW()  (PORTB &= ~(1 << TX_PIN_BIT))

const int BIT_DELAY = 104; // 9600bps (약 104us)

void setup() {
  DDRB |= (1 << TX_PIN_BIT);
  TX_HIGH();
  
  Serial.begin(9600); 
}

void loop() {
  sendChar('a'); // 'a' 전송
  delay(100);    // 관측 용이성을 위한 지연
}

void sendChar(char data) {
  TX_LOW(); // Start Bit
  delayMicroseconds(BIT_DELAY);
  
  for (int i = 0; i < 8; i++) { // Data Bits
    if (data & (1 << i)) TX_HIGH();
    else                 TX_LOW();
    delayMicroseconds(BIT_DELAY);
  }
  
  TX_HIGH(); // Stop Bit
  delayMicroseconds(BIT_DELAY);
}