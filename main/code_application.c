/*
 * iotOnoff.c
 *
 *  Created on: 6 sept. 2020
 *      Author: t126401
 */



#include "dialogos_json.h"

#include "esp_err.h"
#include "esp_log.h"
#include "common_data.h"
#include "programmer.h"
#include "api_json.h"
#include "driver/gpio.h"
#include "conexiones.h"

#include "user_interface.h"
#include "esp_timer.h"
#include "logging.h"
#include "events_device.h"



static const char *TAG = "APPLICATION";
xQueueHandle cola_gpio = NULL;


static esp_timer_handle_t timer_led;


#define GPIO_OUTPUT_PIN_SEL  ((1ULL<<CONFIG_GPIO_PIN_RELE) | (1ULL<<CONFIG_GPIO_PIN_LED))
#define GPIO_INPUT_PIN_SEL  ((1ULL<<CONFIG_GPIO_PIN_BOTON) | (1ULL<<CONFIG_GPIO_PIN_RELE))

#define NUM_REPETICIONES    3
#define TIMER_SHORT 250000



enum ESTADO_RELE relay_operation(DATOS_APLICACION *datosApp, enum TIPO_ACTUACION_RELE tipo, enum ESTADO_RELE operacion) {

	enum ESTADO_RELE rele;

	switch (tipo) {
	case MANUAL:
	case REMOTA:
		if (gpio_get_level(CONFIG_GPIO_PIN_RELE) == OFF) {
			ESP_LOGW(TAG, ""TRAZAR" OFF-->ON", INFOTRAZA);
			rele = ON;
		} else {
			ESP_LOGW(TAG, ""TRAZAR" ON-->OFF", INFOTRAZA);
			rele = OFF;
		}
		break;
	default:
		rele = operacion;
		break;
	}
	//gpio_rele_out();
	gpio_set_level(CONFIG_GPIO_PIN_RELE, rele);
	gpio_set_level(CONFIG_GPIO_PIN_LED, rele);
	ESP_LOGW(TAG, ""TRAZAR"RELE =  %d", INFOTRAZA, gpio_get_level(CONFIG_GPIO_PIN_RELE));


	return rele;
}










static void isr_handler(void *dato) {

	send_event_device(__func__, EVENT_SHORT_PUSH_BUTTON);

}


esp_err_t start_application(DATOS_APLICACION *datosApp) {

	esp_err_t error = ESP_OK;

    datosApp->datosGenerales->botonPulsado = false;

    ESP_LOGE(TAG, ""TRAZAR"INICIALIZAR PARAMETROS PARTICULARES DE LA APLICACION", INFOTRAZA);
    gpio_config_t io_conf;

    //interrupt of rising edge
    io_conf.intr_type = GPIO_INTR_NEGEDGE;
    //bit mask of the pins, use GPIO4/5 here
    io_conf.pin_bit_mask = GPIO_INPUT_PIN_SEL;
    //set as input mode
    io_conf.mode = GPIO_MODE_INPUT;
    //enable pull-up mode
    io_conf.pull_up_en = 1;
    gpio_config(&io_conf);

    //disable interrupt
    io_conf.intr_type = GPIO_INTR_DISABLE;
    //set as output mode
    io_conf.mode = GPIO_MODE_OUTPUT;
    //bit mask of the pins that you want to set,e.g.GPIO15/16
    io_conf.pin_bit_mask = GPIO_OUTPUT_PIN_SEL;
    //disable pull-down mode
    io_conf.pull_down_en = 0;
    //disable pull-up mode
    io_conf.pull_up_en = 0;
    //configure GPIO with the given settings
    gpio_config(&io_conf);


    //create a queue to handle gpio event from isr
    cola_gpio = xQueueCreate(5, sizeof(DATOS_APLICACION));

    gpio_install_isr_service(0);
    //hook isr handler for specific gpio pin
    gpio_isr_handler_add(CONFIG_GPIO_PIN_BOTON, isr_handler, (void *) NULL);

    return error;


}

void process_timer_led(void* arg) {

	if (gpio_get_level(CONFIG_GPIO_PIN_LED) == 0) {
		gpio_set_level(CONFIG_GPIO_PIN_LED, ON);
	} else {
		gpio_set_level(CONFIG_GPIO_PIN_LED, OFF);
	}



}




esp_err_t init_code_application(DATOS_APLICACION *datosApp) {





    const esp_timer_create_args_t repeater_timer_led_args = {
            .callback = &process_timer_led,
            /* name is optional, but may help identify the timer when debugging */
            .name = "repeater manage button",
			.arg = (void*) NULL
    };


	//gpio_rele_in_out();
	gpio_set_level(CONFIG_GPIO_PIN_RELE, OFF);
	esp_timer_create(&repeater_timer_led_args, &timer_led);
	start_application(datosApp);

	return ESP_OK;

}


void cancel_timer_led() {

	esp_timer_stop(timer_led);
	gpio_set_level(CONFIG_GPIO_PIN_LED, OFF);



}





void activate_timer_led(int timing) {



	esp_timer_stop(timer_led);
    esp_timer_start_periodic(timer_led, timing);




}

void command_status(DATOS_APLICACION *datosApp, cJSON *command) {

	ESP_LOGI(TAG, ""TRAZAR"Consultamos el estado de la aplicacion", INFOTRAZA);
    cJSON_AddNumberToObject(command, APP_COMAND_ESTADO_RELE, gpio_get_level(CONFIG_GPIO_PIN_RELE));
    cJSON_AddNumberToObject(command, DEVICE_STATE, datosApp->datosGenerales->estadoApp);
    cJSON_AddNumberToObject(command, PROGRAMMER_STATE, datosApp->datosGenerales->estadoProgramacion);
    escribir_programa_actual(datosApp, command);
    codigoRespuesta(command,RESP_OK);



}

void command_op_relay_remote(DATOS_APLICACION *datosApp, cJSON *command) {

	ESP_LOGI(TAG, ""TRAZAR"Consultamos el estado de la aplicacion", INFOTRAZA);
    cJSON_AddNumberToObject(command, APP_COMAND_ESTADO_RELE, gpio_get_level(CONFIG_GPIO_PIN_RELE));
    cJSON_AddNumberToObject(command, DEVICE_STATE, datosApp->datosGenerales->estadoApp);
    cJSON_AddNumberToObject(command, PROGRAMMER_STATE, datosApp->datosGenerales->estadoProgramacion);
    escribir_programa_actual(datosApp, command);
    codigoRespuesta(command,RESP_OK);



}


esp_err_t app_task(DATOS_APLICACION *datosApp) {



	return ESP_OK;
}



