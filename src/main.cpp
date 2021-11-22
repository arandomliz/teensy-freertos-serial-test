#if __has_include("arduino_freertos.h")
#include <arduino_freertos.h>
#endif

#include <Arduino.h>
#include <SPI.h>


#define STO_KNEE 40
#define SERIAL_TEST Serial7

#define CS_KNEE 10
#define DRDY_KNEE 14

#if __has_include("arduino_freertos.h")
static void led_task(void*) {
  while (true) {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    if (digitalRead(LED_BUILTIN))
      Serial.println("Hey");
    vTaskDelay(pdMS_TO_TICKS(250));
  }
}
#endif


void test_serial() {
  Serial.println("Starting send");
  SERIAL_TEST.begin(115200);
  digitalWrite(STO_KNEE, LOW);

  SERIAL_TEST.print("MO=0\r");
  SERIAL_TEST.print("UM=1\r");
  Serial.println("Doing flush");
  SERIAL_TEST.flush();
  Serial.println("Done");
}


inline void test_spi() {
  pinMode(CS_KNEE, OUTPUT);
  pinMode(DRDY_KNEE, INPUT);

  SPI.begin();
  SPI.transfer(0x00);
}

void setup() {
  pinMode(STO_KNEE, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);

  while (!Serial) {
    delay(50);
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  }

  test_spi();
  test_serial();

  Serial.println("Done all");

#if __has_include("arduino_freertos.h")
  xTaskCreate(led_task, "led_task", 128, nullptr, 2, nullptr);
  vTaskStartScheduler();
#endif
}

void loop() {}
