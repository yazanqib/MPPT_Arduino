#include <PWM.h>
// Global Var
  float current_old=0.0;
  float voltage_old=0.0;
  float power_old=0.0;
  float D_old=0.7;  //initial value 
  float D=0.5;      // initial value
  float Delta=0.1;  // initial value
  float PWM_value= 255*D;

 int led = 11;                // Arduino pin
int32_t frequency = 51000; //frequency (in Hz)
void setup() {
 InitTimersSafe();
  Serial.begin(9600);
  //changing the PWM frequancy 
  bool success = SetPinFrequencySafe(led, frequency);
    if(success) {
    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);   
     Serial.println("Freq has been changed");
    }
  delay(100);

   pwmWrite(led,PWM_value); // starting freq 
     //delay(10000);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin A0 and A1:
  Serial.print("Voltage and Current");
  int sensorValueVoltage = analogRead(A0);
  int sensorValueCurrent = analogRead(A1);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage_new = sensorValueVoltage * (5.0 / 1023.0);
  float current_new = sensorValueCurrent * (5.0 / 1023.0);
  // print out the value you read:
  Serial.println(voltage_new);
  Serial.println(current_new);  
  delay (4000);

// calculate power
float power_new=voltage_new*current_new;
  Serial.print("Current Power: ");
  Serial.println(power_new);
    Serial.print("Starting PWM: ");
  Serial.println(PWM_value);
  
// Apply MPPT 
if((power_new-power_old)!=0.0)
{
    Serial.println("MPPT if (1) statment is now active");

  if ((power_new-power_old)>0)
  {
        Serial.println("MPPT if (2) statment is now active");

    if ((voltage_new- voltage_old)>0)
    {
      D = D_old - Delta;
     Serial.println("MPPT if (3) statment is now active");

      
     }
    else
    {
     D = D_old + Delta; 
       Serial.println("MPPT else (2) statment is now active");

    }
   }
 else
   {
    if ((voltage_new- voltage_old)>0)
    {
      D = D_old + Delta;
      
     Serial.println("MPPT if (4) statment is now active");

     }
    else
    {
     D = D_old - Delta; 
       Serial.println("MPPT else (3) statment is now active");

    }
   }
}
 else
 {
  Serial.println("MPPT else (1) statment is now active");
  D_old=D;
  }

  
  // Apply PWM signal
PWM_value=255*D;
 pwmWrite(led,PWM_value);
 delay (50);
 /// prepare for the next loop
 voltage_old=voltage_new;
  current_old=current_new;
  power_old=power_new;
  D_old=D;
/// Display the current power
Serial.println("power is");
Serial.println(power_old);
  delay(100);
}

