#define LED_BUILTIN 2  // Define the built-in LED pin for ESP32

#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

static const int rate1 = 500;
static const int rate2 = 1000;

static const int led_pin = LED_BUILTIN;

void toggleLED1(void *parameter) {
  while (1) {
    digitalWrite(led_pin, HIGH);
    vTaskDelay(rate1 / portTICK_PERIOD_MS);
    digitalWrite(led_pin, LOW);
    vTaskDelay(rate1 / portTICK_PERIOD_MS);
  }
}
void toggleLED2(void *parameter) {
  while (1) {
    digitalWrite(led_pin, HIGH);
    vTaskDelay(rate2 / portTICK_PERIOD_MS);
    digitalWrite(led_pin, LOW);
    vTaskDelay(rate2 / portTICK_PERIOD_MS);
  }
}

void setup() {
  pinMode(led_pin, OUTPUT);

  xTaskCreatePinnedToCore(
      toggleLED1,
      "Toggle LED 1",
      1024,
      NULL,
      1,
      NULL,
      app_cpu);
      
  xTaskCreatePinnedToCore(
      toggleLED2,
      "Toggle LED 2",
      1024,
      NULL,
      1,
      NULL,
      app_cpu);
}

void loop() {
}