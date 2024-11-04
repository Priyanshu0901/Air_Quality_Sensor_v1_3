#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"
#include "air_quality_sensor_v1_3.h"

#define WAIT_TIMEOUT 25000
air_quality_sensor_t air_quality_sensor;

void poll_read_air_quality_sensor(void *pvParameters)
{
  printf("Starting Air Quality Sensor...\n");
  if (initialize_air_quality_sensor(&air_quality_sensor))
  {
    printf("Sensor ready.\n");
  }
  else
  {
    printf("Sensor ERROR!\n");
  }
  while (air_quality_sensor._is_initialized == 1)
  {
    air_quality_sensor_slope(&air_quality_sensor);
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
  vTaskDelete(NULL);
}

void print_read_air_quality_sensor(void *pvParameters)
{
  // Wait for the Sensor to be initialized and get the first read
  uint32_t current_time = (uint32_t)esp_timer_get_time() / 1000;
  uint32_t timeout_time = current_time + WAIT_TIMEOUT;

  while ((!air_quality_sensor._sensor_ready) && current_time < timeout_time)
  {
    current_time = (uint32_t)esp_timer_get_time() / 1000;
  }

  while (air_quality_sensor._sensor_ready)
  {
    char buf[40];
    air_quality_error_to_message(air_quality_sensor._air_quality, buf, 40);
    printf("Time : %lu\tSlope : %d\tRaw Value : %d\n%s\n", (uint32_t)esp_timer_get_time() / 1000, air_quality_sensor._air_quality, air_quality_sensor._sensor_raw_value, buf);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
  vTaskDelete(NULL);
}

void app_main(void)
{
  xTaskCreatePinnedToCore(
      poll_read_air_quality_sensor,   /* Function that implements the task. */
      "poll_read_air_quality_sensor", /* Text name for the task. */
      configMINIMAL_STACK_SIZE * 2,   /* Stack size in words, not bytes. */
      NULL,                           /* Parameter passed into the task. */
      tskIDLE_PRIORITY + 1,           /* Priority at which the task is created. */
      NULL,                           /* Used to pass out the created task's handle. */
      0);                             /* Core ID */

  xTaskCreatePinnedToCore(
      print_read_air_quality_sensor,   /* Function that implements the task. */
      "print_read_air_quality_sensor", /* Text name for the task. */
      configMINIMAL_STACK_SIZE * 2,    /* Stack size in words, not bytes. */
      NULL,                            /* Parameter passed into the task. */
      tskIDLE_PRIORITY,                /* Priority at which the task is created. */
      NULL,                            /* Used to pass out the created task's handle. */
      0);                              /* Core ID */
}
