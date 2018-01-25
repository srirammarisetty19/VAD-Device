//ECG samples
short int arr[]={101,100,100,99,99,98,97,96,93,95,95,96,97,95,95,95,94,94,93,97,96,94,95,94,94,95,95,96,95,96,94,95,95,95,95,94,95,95,93,94,94,95,96,95,95,95,93,94,95,96,95,96,96,96,97,96,96,95,95,95,94,94,93,95,100,101,106,108,100,98,93,95,97,95,96,95,95,96,96,97,96,95,97,96,98,96,98,99,98,100,100,100,99,98,100,100,100,99,97,96,94,94,95,96,95,95,95,95,93,94,94,96,96,94,94,95,96,96,95,97,95,94,95,94,96,96,95,95,95,95,95,94,95,94,95,95,94,95,94,94,96,96,98,96,94,95,97,98,96,97,97,95,95,93,95,95,95,95,97,101,104,108,104,99,95,95,96,96,95,97,95,95,96,96,97,96,96,98,96,97,97,98,99,98,100,100,100,101,100,101,99,97,99,97,97,96,95,96,95,95,94,95,95,94,96,94,95,96,94,96,95,94,96,95,96,96,95,97,97,96,96,95,96,95,96,95,96,97,95,94,94,95,97,96,96,95,95,95,94,95,97,95,95,97,96,96,98,98,96,95,94,95,95,95,94,95,98,103,104,108,105,100,96,95,97,96,94,95,95,95,96,96,97,96,96,96,97,98,97,98,98,98,99,99,100,102,101,100,98,98,97,96,97,94,96,96,94,95,94,95,95,94,95,94,93,94,94,95,95,95,95,95,96,95,95,96,96,95,93,94,95,94,96,94,95,95,95,95,94,95,94,94,95,94,95,95,94,95,95,98,99,96,97,96,95,94,95,96,94,95,94,96,100,101,109,108,101,96,94,97,96,95,98,96,96,97,95,96,95,97,97,96,97,98,99,99,100,102,98,100,99,99,100,99,99,98,98,97,95,96,95,95,96,95,96,95,92,94,93,96,96,95,96,95,95,94,96,97,95,97,95,94,96,94,96,96,95,95,95,95,94,95,97,95,97,96,92,95,95,96,97,96,98,98,98,95,95,95,95,95,96,95,95,98,102,108,108,101,97,94};

short int i; //count value for array

const int analogInPin = A0; //Analog pin input for Velostat reading 

int sensorValue = 0; // value read from the Velostat

void setup() {
  // put your setup code here, to run once:
  digitalWrite(analogInPin, HIGH);
  pinMode(8, OUTPUT);//pin for the air pump
  pinMode(9,OUTPUT);//pin for vacuum pump
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(1)
  {
    Serial.println("5 Loops Complete");
    //loop through 5 ECG cycle samples
    for (i = 0; i < 450; i++)
    {
      short int tEquivalentValue = 0; //Values that are equivalent to T peak in ECG
      
      //check for R peak
      //Between T peak to R peak - Air pump is OFF and Vacuum pump is ON
      while(arr[i] < 106)
      {
        //If last value has reached in this process break from loop
        if(i == 450)
        {
          break;
        }
        digitalWrite(8, LOW); //air pump OFF
        digitalWrite(9, HIGH); //vacuum pump ON
        sensorValue = analogRead(analogInPin); //reading from Velostat
        Serial.print(arr[i]);
        Serial.print(" ");
        Serial.print("0");
        Serial.print(" ");
        Serial.println(-sensorValue);
        delay(11);
        i++;
      }

      //Check for T peak
      //Between R peak and T peak - Air pump is ON and Vacuum pump is OFF
      while(tEquivalentValue < 2)
      {
        if(i == 450)
        {
           break;
        }
        digitalWrite(8, HIGH); //air pump ON
        digitalWrite(9, LOW); //vacuum pump OFF
        sensorValue = analogRead(analogInPin); //reading from Velostat
        Serial.print(arr[i]);
        Serial.print(" ");
        Serial.print("1");
        Serial.print(" ");
        Serial.println(-sensorValue);
        delay(11);

        //Check for T peak value. If we encounter two such values break.
        if((arr[i]>98)&&(arr[i]<102))
        {
          tEquivalentValue++;
        }

        if(tEquivalentValue == 2)
        {
          break;
        }
        
        i++;
      }
    }
  }
}
