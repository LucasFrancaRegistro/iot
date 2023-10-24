TaskHandle_t task1;
TaskHandle_t task2;
SemaphoreHandle_t mutex;

float temp = 0.0;
float umi = 0.0;

void minhaTask1(void *pvParameters){
  Serial.println("começou a task 1");
  while (true){
    xSemaphoreTake(mutex, portMAX_DELAY);
    temp = temp +0.24;
    umi = umi + 0.51;
    xSemaphoreGive(mutex);
    delay(1300);
  }
}

void minhaTask2(void *pvParameters){
  Serial.println("começou a task 2");
  while (true){
    xSemaphoreTake(mutex, portMAX_DELAY);
    temp = temp - 0.09;
    umi = umi - 0.23;
    xSemaphoreGive(mutex);
    delay(800);
  }
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  mutex = xSemaphoreCreateMutex();

  if (mutex == NULL){
    Serial.println("erro ao criar o mutex");
  };

  Serial.println("criando a task 1");
  xTaskCreatePinnedToCore(
    minhaTask1, //funcao da task
    "minhatask1", //nome da task
    1000, //tamanho da task
    NULL, //parametros da task
    1, //prioridade da task
    &task1, //task handle
    0 //core loop - 1)
    );

    Serial.println("criando task 2");
    xTaskCreatePinnedToCore(
    minhaTask2, //funcao da task
    "minhatask2", //nome da task
    1000, //tamanho da task
    NULL, //parametros da task
    1, //prioridade da task
    &task2, //task handle
    1 //core loop - 1)
    );

}

void loop() {
  // put your main code here, to run repeatedly:
  xSemaphoreTake(mutex, portMAX_DELAY);
  Serial.print("temp ");
  Serial.println(temp);
  Serial.print("umi ");
  Serial.println(umi);
  xSemaphoreGive(mutex);
  delay(1000);
  

}
