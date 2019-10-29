deps_config := \
	/home/pierre/esp/esp-idf/components/app_trace/Kconfig \
	/home/pierre/esp/esp-idf/components/aws_iot/Kconfig \
	/home/pierre/esp/esp-idf/components/bt/Kconfig \
	/home/pierre/esp/esp-idf/components/driver/Kconfig \
	/home/pierre/esp/esp-idf/components/efuse/Kconfig \
	/home/pierre/esp/esp-idf/components/esp32/Kconfig \
	/home/pierre/esp/esp-idf/components/esp_adc_cal/Kconfig \
	/home/pierre/esp/esp-idf/components/esp_event/Kconfig \
	/home/pierre/esp/esp-idf/components/esp_http_client/Kconfig \
	/home/pierre/esp/esp-idf/components/esp_http_server/Kconfig \
	/home/pierre/esp/esp-idf/components/esp_https_ota/Kconfig \
	/home/pierre/esp/esp-idf/components/espcoredump/Kconfig \
	/home/pierre/esp/esp-idf/components/ethernet/Kconfig \
	/home/pierre/esp/esp-idf/components/fatfs/Kconfig \
	/home/pierre/esp/esp-idf/components/freemodbus/Kconfig \
	/home/pierre/esp/esp-idf/components/freertos/Kconfig \
	/home/pierre/esp/esp-idf/components/heap/Kconfig \
	/home/pierre/esp/esp-idf/components/libsodium/Kconfig \
	/home/pierre/esp/esp-idf/components/log/Kconfig \
	/home/pierre/esp/esp-idf/components/lwip/Kconfig \
	/home/pierre/esp/esp-idf/components/mbedtls/Kconfig \
	/home/pierre/esp/esp-idf/components/mdns/Kconfig \
	/home/pierre/esp/esp-idf/components/mqtt/Kconfig \
	/home/pierre/esp/esp-idf/components/nvs_flash/Kconfig \
	/home/pierre/esp/esp-idf/components/openssl/Kconfig \
	/home/pierre/esp/esp-idf/components/pthread/Kconfig \
	/home/pierre/esp/esp-idf/components/spi_flash/Kconfig \
	/home/pierre/esp/esp-idf/components/spiffs/Kconfig \
	/home/pierre/esp/esp-idf/components/tcpip_adapter/Kconfig \
	/home/pierre/esp/esp-idf/components/unity/Kconfig \
	/home/pierre/esp/esp-idf/components/vfs/Kconfig \
	/home/pierre/esp/esp-idf/components/wear_levelling/Kconfig \
	/home/pierre/esp/esp-idf/components/wifi_provisioning/Kconfig \
	/home/pierre/esp/esp-idf/components/app_update/Kconfig.projbuild \
	/home/pierre/esp/esp-idf/components/bootloader/Kconfig.projbuild \
	/home/pierre/esp/esp-idf/components/esptool_py/Kconfig.projbuild \
	/home/pierre/esp/ESP32_FreeRTOS/PWM_pjfixer/main/Kconfig.projbuild \
	/home/pierre/esp/esp-idf/components/partition_table/Kconfig.projbuild \
	/home/pierre/esp/esp-idf/Kconfig

include/config/auto.conf: \
	$(deps_config)

ifneq "$(IDF_TARGET)" "esp32"
include/config/auto.conf: FORCE
endif
ifneq "$(IDF_CMAKE)" "n"
include/config/auto.conf: FORCE
endif

$(deps_config): ;
