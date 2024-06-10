/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/



#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "driver/uart.h"
#include "esp_log.h"
#include "nvs.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_event.h"
#include "mqtt_client.h"
#include "conexiones.h"
#include "configuracion.h"
#include "programmer.h"
#include "ntp.h"
#include "common_data.h"
#include "api_json.h"
#include "lwip/dns.h"
#include "alarmas.h"
#include "user_interface.h"
#include "nvslib.h"

#include <sys/socket.h>
#include <netdb.h>
#include "events_device.h"
#include "code_application.h"

#include "esp_ota_ops.h"
#include "conexiones_mqtt.h"
#include "applib.h"


DATOS_APLICACION datosApp;


static const char *TAG = "PLANTILLA";
TaskHandle_t handle;




void app_main()
{



	ESP_LOGI(TAG, ""TRAZAR"COMIENZO DE LA APLICACION version", INFOTRAZA);
	init_global_parameters_device(&datosApp);
	init_local_parameters_device(&datosApp);
	init_service_device(&datosApp);







	//xTaskCreate(app_task, "app_task", CONFIG_RESOURCE_APP_TASK, (void*) &datosApp, 1, NULL);




}
