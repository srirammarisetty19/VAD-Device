// Include the Servo library 
#include <Servo.h> 

//ECG samples
short int arr[]={101,100,100,99,99,98,97,96,93,95,95,96,97,95,95,95,94,94,93,97,96,94,95,94,94,95,95,96,95,96,94,95,95,95,95,94,95,95,93,94,94,95,96,95,95,95,93,94,95,96,95,96,96,96,97,96,96,95,95,95,94,94,93,95,100,101,106,108,100,98,93,95,97,95,96,95,95,96,96,97,96,95,97,96,98,96,98,99,98,100,100,100,99,98,100,100,100,99,97,96,94,94,95,96,95,95,95,95,93,94,94,96,96,94,94,95,96,96,95,97,95,94,95,94,96,96,95,95,95,95,95,94,95,94,95,95,94,95,94,94,96,96,98,96,94,95,97,98,96,97,97,95,95,93,95,95,95,95,97,101,104,108,104,99,95,95,96,96,95,97,95,95,96,96,97,96,96,98,96,97,97,98,99,98,100,100,100,101,100,101,99,97,99,97,97,96,95,96,95,95,94,95,95,94,96,94,95,96,94,96,95,94,96,95,96,96,95,97,97,96,96,95,96,95,96,95,96,97,95,94,94,95,97,96,96,95,95,95,94,95,97,95,95,97,96,96,98,98,96,95,94,95,95,95,94,95,98,103,104,108,105,100,96,95,97,96,94,95,95,95,96,96,97,96,96,96,97,98,97,98,98,98,99,99,100,102,101,100,98,98,97,96,97,94,96,96,94,95,94,95,95,94,95,94,93,94,94,95,95,95,95,95,96,95,95,96,96,95,93,94,95,94,96,94,95,95,95,95,94,95,94,94,95,94,95,95,94,95,95,98,99,96,97,96,95,94,95,96,94,95,94,96,100,101,109,108,101,96,94,97,96,95,98,96,96,97,95,96,95,97,97,96,97,98,99,99,100,102,98,100,99,99,100,99,99,98,98,97,95,96,95,95,96,95,96,95,92,94,93,96,96,95,96,95,95,94,96,97,95,97,95,94,96,94,96,96,95,95,95,95,94,95,97,95,97,96,92,95,95,96,97,96,98,98,98,95,95,95,95,95,96,95,95,98,102,108,108,101,97,94};

// Declare the Servo pin 
int servoPin = 3; 

short int i; //count value for array

//For time calculation
unsigned long previousTime, currentTime;

// Create a servo object 
Servo Servo1; 

void setup() { 
   // We need to attach the servo to the used pin number 
   Servo1.attach(servoPin); 
   Serial.begin(9600);
}

void loop(){ 

  // put your main code here, to run repeatedly:
  while(1)
  {
    //loop through 5 ECG cycle samples
    for (i = 0; i < 450; i++)
    {
      short int tEquivalentValue = 0; //Values that are equivalent to T peak in ECG
      
      //check for R peak
      //Between T peak to R peak - Air pump is OFF and Vacuum pump is ON
      while(arr[i] < 106)
      {
        //Serial.println(i);
        //If last value has reached in this process break from loop
        if(i == 450)
        {
          break;
        } 
        delay(17);
        i++;
      }
      
      //Serial.println("R Peak");
      currentTime = millis();
      Serial.println("--------------");
      Serial.println(currentTime-previousTime);
      Serial.println((-0.06*(currentTime-previousTime))+240);
      if((currentTime-previousTime) < 1100) {
        // Make servo go to 180 degrees 
        Servo1.write(180);
      }
      else {
        Servo1.write((-0.06*(currentTime-previousTime))+240);
      }
        
      previousTime = currentTime;
      
      //Check for T peak
      //Between R peak and T peak - Air pump is ON and Vacuum pump is OFF
      while(tEquivalentValue < 2)
      {
        //Serial.println(i);
        if(i == 450)
        {
           break;
        }
        delay(17);

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
