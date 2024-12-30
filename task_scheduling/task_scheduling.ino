#define LED_BUILTIN 2  // Define the built-in LED pin for ESP32

#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

static const int rate1 = 500;
static const int rate2 = 1000;

static const int led_pin = LED_BUILTIN;

const char msg[] = "A message that one thread will print.";

//handlers for 2 threads so they will be controlled by the 3rd task.
static TaskHandle_t thread1 = NULL;
static TaskHandle_t thread2 = NULL;

//thread #1 counts the number of threads in the string.
void startThread1(void *parameter){
  int msg_len = strlen(msg);

  while(1){
    Serial.println();
    for(int i = 0; i < msg_len; i++){
      Serial.print(msg[i]);
    }

    Serial.println();
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

//higher priority task
void startThread2(void *parameter){
  while(1) {
    Serial.print('*');
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void setup() {

  Serial.begin(300);

  vTaskDelay(1000 / portTICK_PERIOD_MS);
  Serial.println();
  Serial.println("------FreeRTOS Task Demo------");

  Serial.print("Setup and loop task running on core ");
  Serial.print(xPortGetCoreID());
  Serial.print(" with priority ");
  Serial.print(uxTaskPriorityGet(NULL));

  xTaskCreatePinnedToCore(startThread1,
      "Thread 1",
      1024,
      NULL,
      1,
      &thread1,
      app_cpu);
      
  xTaskCreatePinnedToCore(startThread2,
      "Thread 2",
      1024,
      NULL,
      2,
      &thread2,
      app_cpu);
}

void loop() {

  for (int i = 0; i < 3; i++){
    vTaskSuspend(thread2);
    vTaskDelay(2000 / portTICK_PERIOD_MS);
    vTaskResume(thread2);
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }

  //This deltes the lower priority task.
  if (thread1 != NULL){
    vTaskDelete(thread1);
    thread1 = NULL;
  }
}