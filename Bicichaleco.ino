#include <SoftwareSerial.h>

int derecha = 3;
int izquierda = 2; 

SoftwareSerial BT(10, 11);

int noteFreqArr[] = {
49.4, 52.3, 55.4, 58.7, 62.2, 65.9, 69.9, 74, 78.4, 83.1, 88, 93.2, 
98.8, 105, 111, 117, 124, 132, 140, 148, 157, 166, 176, 186, 
198, 209, 222, 235, 249, 264, 279, 296, 314, 332, 352, 373, 
395, 419, 444, 470, 498, 527, 559, 592, 627, 665, 704, 746, 
790, 837, 887, 940, 996, 1050, 1110, 1180, 1250, 1320, 1400, 1490, 
1580, 1670, 1770, 1870, 1990, 2100};

void setup()
{
  BT.begin(115200);
  Serial.begin(9600);
  pinMode(derecha, OUTPUT);
  pinMode(izquierda, OUTPUT);


  digitalWrite(13, HIGH);
}

void play(int noteInt, long length, long breath=20)
{
  length = length - breath;
  buzz(4, noteFreqArr[noteInt], length);
  if(breath>0)
  {
    delay(breath);
  }
}

 void buzz(int targetPin, long frequency, long length) 
 {
  long delayValue = 1000000/frequency/2; // calculate the delay value between transitions
  //// 1 second's worth of microseconds, divided by the frequency, then split in half since
  //// there are two phases to each cycle
  long numCycles = frequency * length/ 1000; // calculate the number of cycles for proper timing
  //// multiply frequency, which is really cycles per second, by the number of seconds to 
  //// get the total number of cycles to produce
  for (long i=0; i < numCycles; i++){ // for the calculated length of time...
    digitalWrite(targetPin,HIGH); // write the buzzer pin high to push out the diaphram
    delayMicroseconds(delayValue); // wait for the calculated delay value
    digitalWrite(targetPin,LOW); // write the buzzer pin low to pull back the diaphram
    delayMicroseconds(delayValue); // wait againf or the calculated delay value
  }
 }
  
void loop()
{
  delay(2000);
  
  while(BT.available() > 0)
  {
    int numero = BT.parseInt();
    
    if(numero != -1)
    {
      switch(numero)
      {
        case 400: //Cuando, por el bluetooth, nos envían una señal para girar a la derecha.
        play(17, 1000);
        play(17, 250);
        break;
        
        case 300:
        play(28, 1000);
        play(28, 250);
        play(28, 250);
        break;
        
        default:
        
        break;
      }
    }
    Serial.println(numero);
  }

}
