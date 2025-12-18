// --- 비트뱅 송신 설정 (Step 2와 동일) ---
#define TX_PIN_BIT 0 // PORTB 0번 (D8)
#define TX_HIGH() (PORTB |= (1 << TX_PIN_BIT))
#define TX_LOW()  (PORTB &= ~(1 << TX_PIN_BIT))
const int BIT_DELAY = 104; // 9600bps

void setup() {
  // 1. 비트뱅 송신용 핀 설정 (D8)
  DDRB |= (1 << TX_PIN_BIT);
  TX_HIGH(); // Idle 상태 유지

  // 2. 하드웨어 시리얼 설정 (수신 및 USB 출력용)
  // D0핀은 RX로 자동 설정됩니다.
  Serial.begin(9600);
  
  Serial.println("--- Loopback Test Start ---");
}

void loop() {
  // 1. D8 핀으로 'a'를 송신 (비트뱅)
  sendChar('a');

  // 2. 하드웨어 시리얼(D0)이 데이터를 받을 시간을 아주 잠깐 줌
  // (비트뱅 함수 실행 중에 이미 하드웨어 RX는 동작하고 있음)
  delay(10); 

  // 3. 수신된 데이터가 있는지 확인
  if (Serial.available() > 0) {
    char receivedData = Serial.read(); // 버퍼에서 읽기
    
    // 4. 결과를 PC 화면에 출력
    Serial.print("Sent: a / Received: ");
    Serial.println(receivedData);
    
    // 만약 데이터가 깨진다면 비트폭(BIT_DELAY) 미세 조정 필요
  }
  
  delay(1000); // 1초마다 반복
}

// 비트뱅 송신 함수
void sendChar(char data) {
  TX_LOW(); // Start Bit
  delayMicroseconds(BIT_DELAY);
  
  for (int i = 0; i < 8; i++) {
    if (data & (1 << i)) TX_HIGH();
    else                 TX_LOW();
    delayMicroseconds(BIT_DELAY);
  }
  
  TX_HIGH(); // Stop Bit
  delayMicroseconds(BIT_DELAY);
}