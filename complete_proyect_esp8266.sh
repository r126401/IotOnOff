#!/bin/sh

device=$1

echo el dispositivo es $device

if [ "$1" = "esp8266" ]; then

echo "cp sdkconfig_esp8266 sdkconfig"
cp sdkconfig_esp8266 sdkconfig

else


if [ "$1" = "esp32" ]; then

echo "cp sdkconfig_esp32 sdkconfig"
cp sdkconfig_esp32 sdkconfig
else


if [ "$1" = "esp32s3" ]; then

echo "cp sdkconfig_esp32s3 sdkconfig"
cp sdkconfig_esp32s3 sdkconfig

else

echo "Error al elegir el dispositivo"
return

fi
fi
fi


echo "Desconectando el proyecto del template"
git remote remove origin
echo "Importando componentes"
git submodule add git@github.com:r126401/components.git
cd components
echo "importando user_interface"
git submodule add git@github.com:r126401/user_interface.git
cd ..
echo "copiando el sdkconfig"
cp sdkconfig_esp8266 sdkconfig
git init
git add .





