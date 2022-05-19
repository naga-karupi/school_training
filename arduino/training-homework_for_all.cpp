#define ERROR_VAL -1

//don't change these value
struct stack{
  int8_t arr[100] = {0};
  uint8_t now_pos = 0;
} hex_stack;

uint8_t pop(){
  if(hex_stack.now_pos == 0) return ERROR_VAL;
  hex_stack.now_pos--;
  return hex_stack.arr[hex_stack.now_pos];
}

uint8_t push(uint8_t input){
  if(hex_stack.now_pos == 100)return ERROR_VAL;
  hex_stack.arr[hex_stack.now_pos] = input;
  hex_stack.now_pos++;
  return 0;
}

uint8_t check_now_pos(){
  return hex_stack.now_pos;
}


void setup(){
  pinMode(2, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  if(Serial.available()){
    int i = 0;
    char string[100];
     while(Serial.available()){
       string[i] = Serial.read();
       i++;
     }
    int sint = atoi(string);
    
    for(int i = 0; sint>>4*i; i++){
      int push_error = push((sint>>(4*i))&0xF);
      if(push_error){
        digitalWrite(2, HIGH);
        while(1){
        }
      }
    }
    
    while(check_now_pos()){
      int i = pop();
      
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