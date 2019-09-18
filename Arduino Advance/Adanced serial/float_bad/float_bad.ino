String inString = "";
void setup() {
  Serial.begin(9600);  pinMode(27,OUTPUT);
  inString.reserve(50);
}
void loop() {
  digitalWrite(27,HIGH);delay(2000);
  digitalWrite(27,LOW);delay(2000);
}
void serialEvent(){
  while (Serial.available()){
   char c= (char)Serial.read();   
    if (c=='\n'){
          float f= inString.toFloat();
          Serial.println(sqrt(f),5);
          inString="";
    }
    else
     inString+=c;
  }
}

