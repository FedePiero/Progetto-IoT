#include <SoftwareSerial.h>
SoftwareSerial mySerial(2,3);
String command;
char c = " ";
bool state = false;
bool ciclo = false;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
}
void loop() {
  if(state == false){
    mySerial.write("AT+CON0035FFE4E97C");
  }
  while(mySerial.available() && ciclo == false){
    c = mySerial.read();
    command.concat(c);
    if(c == 'T' || c == 'A' || c == 'E' || c == 'F' || c == '#'){
        Serial.println(command);
        Serial.write("\n");
        ciclo = true;     }  }

//si sono connessi
  if(command == "OK+CONN" ||command == "OK+CONNA"){
      state = true;
      Serial.println("Connesso");
  }
//si è persa la connessione
  if(command =="OK+CONNE"||command =="OK+CONNF"||command == "OK+LOST"){
    if(state != false){
      Serial.println("Non Connesso");
    }
    state = false;
  }
//si resettano i parametri
  command = "";
  ciclo = false;
  delay(100);
}
