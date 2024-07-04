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


//DATOS_APLICACION datosApp;


static const char *TAG = "main.c";
DATOS_APLICACION datosApp;



void app_main()
{


	/**
	 * 1.- Init data structure to Application
	 */
	init_data_app(&datosApp);
	/**
	 * 2.- init hw used in the device to specific project
	 */
	if (init_hw_device(&datosApp) != ESP_OK) {
		send_event(__func__, EVENT_ERROR_APP);
		return;

	}

	/**
	 * 3.- Init device. the device load all configurations to work
	 */

	ESP_LOGI(TAG, ""TRAZAR"COMIENZO DE LA APLICACION version", INFOTRAZA);
	if (init_device(&datosApp) != ESP_OK) {
		ESP_LOGE(TAG,""TRAZAR" Error to initiate the device", INFOTRAZA);
		return;
	}



	/**
	 * 4.- Check if the device is in upgrade phase. If the device is not in upgrade phase,
	 * the device starting normally
	 */

	if (get_upgrade_data(&datosApp) == ESP_OK) {
		send_event(__func__, EVENT_UPGRADE_FIRMWARE);
		init_wifi_device(&datosApp);
		upgrade_ota_esp8266(&datosApp);
	} else {
		ESP_LOGI(TAG, ""TRAZAR" Device initialized succesfully", INFOTRAZA);
		init_services_device(&datosApp);
	}



	/**
	 * Put here new tasks associated to project
	 */





}
