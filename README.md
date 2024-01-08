# template

Es un proyecto basado en los componentes del repositorio components y que puede trabajar tanto para un esp8266 como para un esp32 o esp32s3

Para poder crear un nuevo proyecto y empezar a trabajar es necesario hacer los siguiente:

git clone --recursive git@github.com:r126401/template.git

Una vez tienes el proyecto en el repositorio es necesario hacer:

cd template
git submodule add git@github.com:r126401/components.git
cd components
git submodule add git@github.com:r126401/user_interface.git

Dependiendo del tipo de dispositivo será necesario copiar el fichero sdkconfig_dispositivo a sdkconfig.

Por ejemplo, para un esp8266 habria que hacer cp sdkconfig_esp8266 sdkconfig
Una vez realizado, se puede compilar el proyecto con make o idf.py dependiendo del proyecto.



