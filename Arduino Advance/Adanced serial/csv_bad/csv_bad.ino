String inString = "";
float x,y;
void setup() {
  Serial.begin(9600);
  pinMode(25,OUTPUT);
  inString.reserve(200);
}
void loop() {
  digitalWrite(25,1); delay(2000);
  digitalWrite(25,0); delay(2000);
}
void serialEvent(){
  while (Serial.available()){
   char c= (char)Serial.read();   
    if (c=='\n'){
       y= inString.toFloat();
       Serial.println(sqrt(x*x+y*y),5);
       inString="";
    }
    else if (c==','){
      x= inString.toFloat();
      inString="";
    }
    else
     inString+=c;
  }
}

