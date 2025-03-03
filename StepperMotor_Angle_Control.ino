//Pins arduino -> driver
const int dirPin = 2; // C, CCW
const int stepPin = 3;
const int ms1 = 4;
const int ms2 = 5;
const int ms3 = 6;
//Motor
const int StepsperRev = 200;
const int microsteps = 16;
const int TotalStepsperRev =  StepsperRev * microsteps;

void setup() {

  pinMode(dirPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(ms1, OUTPUT);
  pinMode(ms2, OUTPUT);
  pinMode(ms3, OUTPUT);

  setMicroStepping(microsteps, ms1, ms2, ms3);

  Serial.begin(9600);
  Serial.println("Enter Angle in Degrees:");
  
}

void loop() {
  if (Serial.available())
  {
    float angle = Serial.parseFloat();
    Serial.print("Rotating to angle:");
    Serial.println(angle);

    int steps = (angle/360.0) * TotalStepsperRev;

    if (steps > 0)
    {
      digitalWrite(dirPin, 1); //CW
    }
    else
    {
      digitalWrite(dirPin, 0); //CCW
    }

    rotateMotor(abs(steps));
  }
}

void rotateMotor(int steps)
{
  for(int i = 0; i < steps; i++)
  {
    digitalWrite(stepPin, 1);
    delay(500);
    digitalWrite(stepPin, 0);
    delay(500);
  }
}

void setMicroStepping(int microsteps, int ms1, int ms2, int ms3)
{
  switch(microsteps){
    case 2:
      digitalWrite(ms1, 1);
      digitalWrite(ms2, 0);
      digitalWrite(ms3, 0);
      break;
    case 4:
      digitalWrite(ms1, 0);
      digitalWrite(ms2, 1);
      digitalWrite(ms3, 0);
      break;
    case 8:
      digitalWrite(ms1, 1);
      digitalWrite(ms2, 1);
      digitalWrite(ms3, 0);
      break;
    case 16:
      digitalWrite(ms1, 1);
      digitalWrite(ms2, 1);
      digitalWrite(ms3, 1);
      break;
    default:
      digitalWrite(ms1, 0);
      digitalWrite(ms2, 0);
      digitalWrite(ms3, 0);
      break;
  }
}