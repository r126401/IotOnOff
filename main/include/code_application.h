/*
 * code_application.h
 *
 *  Created on: 22 dic 2023
 *      Author: esp8266
 */

#ifndef MAIN_INCLUDE_CODE_APPLICATION_H_
#define MAIN_INCLUDE_CODE_APPLICATION_H_

#include "esp_err.h"
#include "common_data.h"
#include "esp_timer.h"

esp_err_t init_local_parameters_device(DATOS_APLICACION *datosApp);
esp_err_t app_task(DATOS_APLICACION *datosApp);
enum ESTADO_RELE relay_operation(DATOS_APLICACION *datosApp, enum TIPO_ACTUACION_RELE tipo, enum ESTADO_RELE operacion);
void activate_timer_led(int timing);
void cancel_timer_led();
void command_status(DATOS_APLICACION *datosApp, cJSON *command);
void command_op_relay_remote(DATOS_APLICACION *datosApp, cJSON *command);


#endif /* MAIN_INCLUDE_CODE_APPLICATION_H_ */
