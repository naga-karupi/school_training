#define ERROR_VAL -1

class stack{
  int8_t arr[100] = {0};
  uint8_t now_pos = 0;
  
public:
  uint8_t pop(){
    if(now_pos == 0) return ERROR_VAL;
    now_pos--;
    return arr[now_pos];
  }

  uint8_t push(uint8_t input){
    if(now_pos == 100)return ERROR_VAL;
    arr[now_pos] = input;
    now_pos++;
    return 0;
  }

  uint8_t check_now_pos(){
    return now_pos;
  }
};

void setup(){
  pinMode(2, OUTPUT);
  Serial.begin(9600);
}

stack hex_stack;

void loop(){
  if(Serial.available()){
    String s = Serial.readString();
    int sint = s.toInt();
    
    for(int i = 0; sint>>4*i; i++){
      int push_error = hex_stack.push((sint>>(4*i))&0xF);
      if(push_error){
        digitalWrite(2, HIGH);
    }
    
    while(hex_stack.check_now_pos()){
      int i = hex_stack.pop();
      
      if(i <= 0 && i >= 9){
        Serial.write(i+'0');
      }else if(i <= 0xA && i >= 0xF){
        Serial.write(i+'A');
      }else{
        digitalWrite(2, HIGH);
        while(1);
      }
    }
  }
}