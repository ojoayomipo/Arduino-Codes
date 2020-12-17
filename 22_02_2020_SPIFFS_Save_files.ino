#include "SPIFFS.h"

void setup() {
Serial.begin(115200);

if (!SPIFFS.begin(true)){
  Serial.println("An Error occurred while mounting SPIFFS");
  return;
}
File file = SPIFFS.open("/test.txt");
if (!file){
  Serial.println("Failed to open file");
  return;
}
Serial.println("File Content: ");
while (file.available()){
  Serial.write(file.read());
}
file.close();
}

void loop() {
  // put your main code here, to run repeatedly:

}
