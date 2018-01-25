//code to generate and feed ecg signal samples time stretched by a period suitable for the balloon
short int arr[]={101,100,100,99,99,98,97,96,93,95,95,96,97,95,95,95,94,94,93,97,96,94,95,94,94,95,95,96,95,96,94,95,95,95,95,94,95,95,93,94,94,95,96,95,95,95,93,94,95,96,95,96,96,96,97,96,96,95,95,95,94,94,93,95,100,101,106,108,100,98,93,95,97,95,96,95,95,96,96,97,96,95,97,96,98,96,98,99,98,100,100,100,99,98,100,100,100,99,97,96,94,94,95,96,95,95,95,95,93,94,94,96,96,94,94,95,96,96,95,97,95,94,95,94,96,96,95,95,95,95,95,94,95,94,95,95,94,95,94,94,96,96,98,96,94,95,97,98,96,97,97,95,95,93,95,95,95,95,97,101,104,108,104,99,95,95,96,96,95,97,95,95,96,96,97,96,96,98,96,97,97,98,99,98,100,100,100,101,100,101,99,97,99,97,97,96,95,96,95,95,94,95,95,94,96,94,95,96,94,96,95,94,96,95,96,96,95,97,97,96,96,95,96,95,96,95,96,97,95,94,94,95,97,96,96,95,95,95,94,95,97,95,95,97,96,96,98,98,96,95,94,95,95,95,94,95,98,103,104,108,105,100,96,95,97,96,94,95,95,95,96,96,97,96,96,96,97,98,97,98,98,98,99,99,100,102,101,100,98,98,97,96,97,94,96,96,94,95,94,95,95,94,95,94,93,94,94,95,95,95,95,95,96,95,95,96,96,95,93,94,95,94,96,94,95,95,95,95,94,95,94,94,95,94,95,95,94,95,95,98,99,96,97,96,95,94,95,96,94,95,94,96,100,101,109,108,101,96,94,97,96,95,98,96,96,97,95,96,95,97,97,96,97,98,99,99,100,102,98,100,99,99,100,99,99,98,98,97,95,96,95,95,96,95,96,95,92,94,93,96,96,95,96,95,95,94,96,97,95,97,95,94,96,94,96,96,95,95,95,95,94,95,97,95,97,96,92,95,95,96,97,96,98,98,98,95,95,95,95,95,96,95,95,98,102,108,108,101,97,94};

short int i;

short int peakcnt,lpeakcount;
const int analogInPin = A0;  

// value read from the Velostat
int sensorValue = 0;   

void setup() 
{
  digitalWrite(analogInPin, HIGH);
  pinMode(8, OUTPUT);//pin for the air pump
  pinMode(9,OUTPUT);//pin for vacuum pump
  Serial.begin(9600);
}


void loop() 
{
  while(1)
  {
    peakcnt=0;//r peak count
    
    for(i=0;i<450;i++)
    {
      lpeakcount=0;//t peak count
      
      while(arr[i]<106)//initially before 1st r,air pump is on
      {   
        if(i==450) break;
        //Serial.print(i);Serial.println("air pump on");
        digitalWrite(9,LOW);
        digitalWrite(8,HIGH);
        Serial.println(arr[i]);
        //Serial.print(" ");
        sensorValue = analogRead(analogInPin);
        //Serial.println(140-sensorValue);
        delay(9);
        i++;
      }
      
      //after the 1st r and till the 2nd t wave peak
      while(peakcnt<3)
      {
        //Serial.print(i);Serial.println("vaccuum pump on");
        
        if(i==450)
        {
           break;
        }
          
        Serial.println(arr[i]);
        //Serial.print(" ");
        sensorValue = analogRead(analogInPin);
        //Serial.println(140-sensorValue);
        
        if(arr[i]>106)//r peak--turn on vaccuum pump
        {
          peakcnt++;
        }
        digitalWrite(8,LOW);
        digitalWrite(9,HIGH);
        delay(9);
  
        if((peakcnt>=2)&&(arr[i]>98)&&(arr[i]<102))//between 1st r,upto 2nd t,t peak detection
        {
          lpeakcount++; 
        }
  
        if(lpeakcount==2)//2 t peaks
        {
          peakcnt=3;//to break from the loop
          break;
        }
        
        i++;
        
      }
      
      //Serial.print(i);
      //Serial.println("air pump on");
      //turn on air pump at the 3rd t peak
      if(i==450)
      {
        break;
      }
      
      Serial.println(arr[i]);
      //Serial.print(" ");
      sensorValue = analogRead(analogInPin);
      //Serial.println(140-sensorValue);
      
      digitalWrite(9,LOW);
      digitalWrite(8,HIGH);
      delay(9);
      
    }


    //delayed ECG for test
    peakcnt=0;//r peak count
    
    for(i=0;i<450;i++)
    {
      lpeakcount=0;//t peak count
      
      while(arr[i]<106)//initially before 1st r,air pump is on
      {   
        if(i==450) break;
        //Serial.print(i);Serial.println("air pump on");
        digitalWrite(9,LOW);
        digitalWrite(8,HIGH);
        Serial.println(arr[i]);
        //Serial.print(" ");
        sensorValue = analogRead(analogInPin);
        //Serial.println(140-sensorValue);
        delay(9);

        //repeat the data
        Serial.println(arr[i]);
        //Serial.print(" ");
        sensorValue = analogRead(analogInPin);
        //Serial.println(140-sensorValue);
        delay(9);
        
        i++;
      }
      
      //after the 1st r and till the 2nd t wave peak
      while(peakcnt<3)
      {
        //Serial.print(i);Serial.println("vaccuum pump on");
        
        if(i==450)
        {
           break;
        }
          
        Serial.println(arr[i]);
        //Serial.print(" ");
        sensorValue = analogRead(analogInPin);
        //Serial.println(140-sensorValue);

        //repeat the data
        delay(9);
        Serial.println(arr[i]);
        //Serial.print(" ");
        sensorValue = analogRead(analogInPin);
        //Serial.println(140-sensorValue);
        
        if(arr[i]>106)//r peak--turn on vaccuum pump
        {
          peakcnt++;
        }
        digitalWrite(8,LOW);
        digitalWrite(9,HIGH);
        delay(9);
  
        if((peakcnt>=2)&&(arr[i]>98)&&(arr[i]<102))//between 1st r,upto 2nd t,t peak detection
        {
          lpeakcount++; 
        }
  
        if(lpeakcount==2)//2 t peaks
        {
          peakcnt=3;//to break from the loop
          break;
        }
        
        i++;
        
      }
      
      //Serial.print(i);
      //Serial.println("air pump on");
      //turn on air pump at the 3rd t peak
      if(i==450)
      {
        break;
      }
      
      Serial.println(arr[i]);
      //Serial.print(" ");
      sensorValue = analogRead(analogInPin);
      //Serial.println(140-sensorValue);

      //repeat the data
      delay(9);
      Serial.println(arr[i]);
      //Serial.print(" ");
      sensorValue = analogRead(analogInPin);
      //Serial.println(140-sensorValue);
      
      digitalWrite(9,LOW);
      digitalWrite(8,HIGH);
      delay(9);
      
    }
    //Serial.println("---------------One cycle---------------------");
  }
}
