#include <SoftwareSerial.h>
#include <Stepper.h>

SoftwareSerial mySerial(2,3);
String command;
char c = " ";
int step_mode = 4;

int stepsPerRevolution = 1024 * (step_mode/4) ;
int mysteps = 1 * stepsPerRevolution;
Stepper myStepper(stepsPerRevolution,8,9,10,11,step_mode);

bool state = false;
bool ciclo = false;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  myStepper.setSpeed(60);
}

void loop() {
  if(state == false){
    mySerial.write("AT+CON0035FFE4E97C");
  }
  while(mySerial.available() && ciclo == false){
    c = mySerial.read();
    command.concat(c);
    if(c == 'T' || c == 'A' || c == 'E' || c == 'F' || c == '#'){
        ciclo = true;
     }
  }
  
  if(command == "OK+CONN" ||command == "OK+CONNA"){
      myStepper.step(-mysteps);
      state = true;
      Serial.println("connesso");
  }
  
  if(command =="OK+CONNE"||command =="OK+CONNF"||command == "OK+LOST"){
    if(state != false){
      myStepper.step(mysteps);
    }
    state = false;
    Serial.println("non connesso");
  }

  command = "";
  ciclo = false;
  delay(200);
}
