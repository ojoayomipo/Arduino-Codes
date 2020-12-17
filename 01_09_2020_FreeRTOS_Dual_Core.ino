#ifndef LED_BUILTIN
#define LED_BUILTIN 2
#endif
TaskHandle_t TaskBlink;
void Blink(void *pvParameters);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  //Set up task 1 to run on core 0
  xTaskCreatePinnedToCore(
    Blink,
    "TaskBlink",
    10000,
    NULL,
    2,
    &TaskBlink,
    0);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println(millis());
}

void Blink(void *pvparameters) {
  pinMode(LED_BUILTIN, OUTPUT);


  for (;;) {
    Serial.print("Blink running on core ");
    Serial.println(xPortGetCoreID());
    digitalWrite(LED_BUILTIN, HIGH);
    vTaskDelay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    vTaskDelay(1000);
  }
}
