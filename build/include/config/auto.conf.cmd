deps_config := \
	/Users/arturgomes/esp/esp-idf/components/app_trace/Kconfig \
	/Users/arturgomes/esp/esp-idf/components/aws_iot/Kconfig \
	/Users/arturgomes/esp/esp-idf/components/bt/Kconfig \
	/Users/arturgomes/esp/esp-idf/components/driver/Kconfig \
	/Users/arturgomes/esp/esp-idf/components/esp32/Kconfig \
	/Users/arturgomes/esp/esp-idf/components/esp_adc_cal/Kconfig \
	/Users/arturgomes/esp/esp-idf/components/ethernet/Kconfig \
	/Users/arturgomes/esp/esp-idf/components/fatfs/Kconfig \
	/Users/arturgomes/esp/esp-idf/components/freertos/Kconfig \
	/Users/arturgomes/esp/esp-idf/components/heap/Kconfig \
	/Users/arturgomes/Documents/KairOS/components/hmc5883l/Kconfig \
	/Users/arturgomes/Documents/KairOS/components/i2cdev/Kconfig \
	/Users/arturgomes/esp/esp-idf/components/libsodium/Kconfig \
	/Users/arturgomes/esp/esp-idf/components/log/Kconfig \
	/Users/arturgomes/esp/esp-idf/components/lwip/Kconfig \
	/Users/arturgomes/esp/esp-idf/components/mbedtls/Kconfig \
	/Users/arturgomes/esp/esp-idf/components/openssl/Kconfig \
	/Users/arturgomes/esp/esp-idf/components/pthread/Kconfig \
	/Users/arturgomes/esp/esp-idf/components/spi_flash/Kconfig \
	/Users/arturgomes/esp/esp-idf/components/spiffs/Kconfig \
	/Users/arturgomes/esp/esp-idf/components/tcpip_adapter/Kconfig \
	/Users/arturgomes/esp/esp-idf/components/wear_levelling/Kconfig \
	/Users/arturgomes/esp/esp-idf/components/bootloader/Kconfig.projbuild \
	/Users/arturgomes/esp/esp-idf/components/esptool_py/Kconfig.projbuild \
	/Users/arturgomes/esp/esp-idf/components/partition_table/Kconfig.projbuild \
	/Users/arturgomes/esp/esp-idf/Kconfig

include/config/auto.conf: \
	$(deps_config)


$(deps_config): ;
