#define LED_BUILTIN 2  // Define the built-in LED pin for ESP32

#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

static const int led_pin = LED_BUILTIN;

void toggleLED(void *parameter) {
  while (1) {
    digitalWrite(led_pin, HIGH);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    digitalWrite(led_pin, LOW);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void setup() {
  pinMode(led_pin, OUTPUT);

  xTaskCreatePinnedToCore(
      toggleLED,
      "Toggle LED",
      1024,
      NULL,
      1,
      NULL,
      app_cpu);
}

void loop() {
  vTaskDelay(1);
}