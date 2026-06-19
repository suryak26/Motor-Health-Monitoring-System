#define CURRENT_PIN      34
#define TEMP_PIN         35
#define VIBRATION_PIN    32

#define MOTOR_LED        18
#define ALARM_LED        19
#define BUZZER_LED       21
#define FAULT_LED        22

unsigned long startTime = 0;
float runtimeHours = 0;

float motorCurrent;
float motorTemp;
float vibration;

bool faultStatus = false;
String healthStatus = "GOOD";

void setup() {

  Serial.begin(115200);

  pinMode(MOTOR_LED, OUTPUT);
  pinMode(ALARM_LED, OUTPUT);
  pinMode(BUZZER_LED, OUTPUT);
  pinMode(FAULT_LED, OUTPUT);

  startTime = millis();

  Serial.println("Motor Health Monitoring Controller");
}

void loop() {

  // Read potentiometers
  int currentADC = analogRead(CURRENT_PIN);
  int tempADC = analogRead(TEMP_PIN);
  int vibrationADC = analogRead(VIBRATION_PIN);

  // Convert to engineering values
  motorCurrent = map(currentADC, 0, 4095, 0, 20);     // 0-20 A
  motorTemp    = map(tempADC, 0, 4095, 20, 120);      // 20-120 C
  vibration    = map(vibrationADC, 0, 4095, 0, 100);  // 0-100 %

  // Runtime calculation
  runtimeHours = (millis() - startTime) / 3600000.0;

  faultStatus = false;

  // Health logic

  if (motorTemp > 90 || vibration > 80 || motorCurrent > 18)
  {
    healthStatus = "FAULT";
    faultStatus = true;
  }
  else if (motorTemp > 70 || vibration > 60 || motorCurrent > 15)
  {
    healthStatus = "WARNING";
  }
  else
  {
    healthStatus = "GOOD";
  }

  // Output control

  if (healthStatus == "GOOD")
  {
    digitalWrite(MOTOR_LED, HIGH);
    digitalWrite(ALARM_LED, LOW);
    digitalWrite(BUZZER_LED, LOW);
    digitalWrite(FAULT_LED, LOW);
  }

  else if (healthStatus == "WARNING")
  {
    digitalWrite(MOTOR_LED, HIGH);
    digitalWrite(ALARM_LED, HIGH);
    digitalWrite(BUZZER_LED, LOW);
    digitalWrite(FAULT_LED, LOW);
  }

  else
  {
    digitalWrite(MOTOR_LED, LOW);
    digitalWrite(ALARM_LED, HIGH);
    digitalWrite(BUZZER_LED, HIGH);
    digitalWrite(FAULT_LED, HIGH);
  }

  // Serial monitor output

  Serial.println("--------------------------------");

  Serial.print("Motor Current : ");
  Serial.print(motorCurrent);
  Serial.println(" A");

  Serial.print("Temperature   : ");
  Serial.print(motorTemp);
  Serial.println(" C");

  Serial.print("Vibration     : ");
  Serial.print(vibration);
  Serial.println(" %");

  Serial.print("Runtime Hours : ");
  Serial.println(runtimeHours, 4);

  Serial.print("Health Status : ");
  Serial.println(healthStatus);

  Serial.print("Fault Status  : ");
  Serial.println(faultStatus);

  delay(1000);
}

