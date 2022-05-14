enum {
    LED1 = 0x1,
    LED2 = 0x2,
    LED3 = 0x4,
    LED4 = 0x8,

    LED1_PIN = 2,
    LED2_PIN,
    LED3_PIN,
    LED4_PIN,
};

uint8_t LED = 0;
char input = 0;

uint8_t char_to_int(char);

void setup(){
    for(int i = 2; i<= 5; i++){
        pinMode(i, OUTPUT);
    }

    Serial.begin(9600);
}

void loop(){
    if(Serial.available()) {
        input = char_to_int(Serial.read());
    }
    
    LED ^= 1 << input;

    digitalWrite(LED1_PIN, LED&LED1);
    digitalWrite(LED2_PIN, LED&LED2);
    digitalWrite(LED3_PIN, LED&LED3);
    digitalWrite(LED4_PIN, LED&LED4);

    input = 0;
}

uint8_t char_to_int (char i){
    if(i >= '0'&& i <= '9')return i-'0';
    if(i >= 'A'&& i <= 'F') return i - 'A' +10;

    LED = 0;
    
    while(1){
        LED ^= HIGH;
        for(int i = LED1_PIN; i <= LED4_PIN; i++){
            digitalWrite(i, LED);
        }
        delay(100);
    }
}
