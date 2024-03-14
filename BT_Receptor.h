#include <BluetoothSerial.h>

BluetoothSerial SerialBT;
#include <stdlib.h>

#include <btstack_port_esp32.h>
#include <btstack_run_loop.h>
#include <btstack_stdio_esp32.h>
#include <uni.h>

#include "sdkconfig.h"

// Sanity check
#ifndef CONFIG_BLUEPAD32_PLATFORM_CUSTOM
#error "Must use BLUEPAD32_PLATFORM_CUSTOM"
#endif


struct uni_platform* get_my_platform(void);

int app_main(void) {
    // Initialize BluetoothSerial
    SerialBT.begin("ESP32_BT"); // Bluetooth device name

    // hci_dump_open(NULL, HCI_DUMP_STDOUT);

#ifndef CONFIG_ESP_CONSOLE_UART_NONE
#ifndef CONFIG_BLUEPAD32_USB_CONSOLE_ENABLE
    btstack_stdio_init();
#endif  // CONFIG_BLUEPAD32_USB_CONSOLE_ENABLE
#endif  // CONFIG_ESP_CONSOLE_UART_NONE

    // Configure BTstack for ESP32 VHCI Controller
    btstack_init();

    // hci_dump_init(hci_dump_embedded_stdout_get_instance());

#ifdef CONFIG_BLUEPAD32_PLATFORM_CUSTOM
     // Must be called before uni_init()
    uni_platform_set_custom(get_my_platform());
#endif  // CONFIG_BLUEPAD32_PLATFORM_CUSTOM

    // Init Bluepad32.
    uni_init(0 /* argc */, NULL /* argv */);

    // Does not return.
    btstack_run_loop_execute();

    return 0;

