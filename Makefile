#
# This is a project Makefile. It is assumed the directory this Makefile resides in is a
# project subdirectory.
#
#
# This is a project Makefile. It is assumed the directory this Makefile resides in is a
# project subdirectory.
#

#EXTRA_COMPONENT_DIRS = /opt/desarrollo/espidf/components
SW_VERSION :="`date +'%y%m%d%H%M'`"
CFLAGS := -DVERSION_SW=$(SW_VERSION)
PROJECT_NAME := iotOnOff

#EXTRA_COMPONENT_DIRS = /opt/esp/componentes
#COMPONENT_PRIV_INCLUDEDIRS = /opt/esp/componentes
#EXCLUDE_COMPONENTS := spiffs

include $(IDF_PATH)/make/project.mk
#COMPONENT_EMBED_TXTFILES :=  ${PROJECT_PATH}/certificado_ota/ca_cert.pem

# PARAMETROS DE CONFIGURACION PARA OTA

 
EJECUTABLE_COPIAR=instalar.py
SERVIDOR_OTA = "jajicaiot.ddns.net"
PUERTO_OTA = 8070
DIR_REPOSITORIO = /opt/trastero
DIR_INSTALL = firmware
PREFIJO_OTA = "newVersion"
DIR_LASTVERSION = "lastVersion"
URL = "/firmware/$(PROJECT_NAME)/"
BUILD_DIR = build
PROJECT_VER = $(SW_VERSION)


instalar:	ota	
	python $(EJECUTABLE_COPIAR) $(SERVIDOR_OTA) $(PUERTO_OTA) $(PROJECT_NAME) $(DIR_REPOSITORIO) $(BUILD_DIR) $(PROJECT_VER) $(PREFIJO_OTA) $(DIR_LASTVERSION) $(URL)
