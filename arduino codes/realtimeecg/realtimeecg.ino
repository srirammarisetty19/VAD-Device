//code to generate and feed ecg signal samples time stretched by a period suitable for the balloon
float arr[]={99,95,95,97,96,96,97,97,97,95,95,97,96,98,97,98,99,97,98,97,100,102,100,99,101,100,100,99,99,98,97,96,93,95,95,96,97,95,95,95,94,94,93,97,96,94,95,94,94,95,95,96,95,96,94,95,95,95,95,94,95,95,93,94,94,95,96,95,95,95,93,94,95,96,95,96,96,96,97,96,96,95,95,95,94,94,93,95,100,101,106,108,100,98,93,95,97,95,96,95,95,96,96,97,96,95,97,96};

int i,j;
int flag=0;
//const int analogInPin = A0;  
//int sensorValue = 0;    
long int time; 
void setup() {
  // initialize digital pin 13 as an output.
    //digitalWrite(analogInPin, HIGH);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);

  //digitalWrite(2,HIGH);
  //digitalWrite(3,HIGH);
  
  pinMode(8, OUTPUT);//pin for the air pump
  pinMode(9,OUTPUT);//pin for vacuum pump
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  
  while(1)
  {
  for(i=0;i<108;)//200 samples generated using a matlab code
  {//sensorValue = analogRead(analogInPin);velostat
  while((arr[i]<95) || (arr[i]<105))
  {
    if(i==108) break;
    digitalWrite(8,HIGH);
    digitalWrite(9,LOW);
    //Serial.print(i);
    Serial.println(arr[i]);
    
    i++;
    delay(9);
    
  }

  while((arr[i]>105) || ((arr[i]<105) &&(arr[i]>95)))
  { if(i==108) break;
    digitalWrite(8,LOW);
    digitalWrite(9,HIGH);
    //Serial.print(i);
    Serial.println(arr[i]);
 
    i++;
    delay(9);
  }
  // print the results to the serial monitor:
  //Serial.print("sensor = " );
  //Serial.println(sensorValue);
    
    
  }
   
   
  // wait for a second
  }
  
}
