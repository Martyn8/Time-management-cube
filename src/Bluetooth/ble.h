#ifndef ble_h
#define ble_h

#include <bluefruit.h>

extern BLEDfu bledfu;   // OTA DFU service
extern BLEDis bledis;   // device information
extern BLEUart bleuart; // uart over ble
extern BLEBas blebas;   // battery

/********************************************************BLUETOOTH**************************************************************/

/*
 * Functions responsible for Bluetooth communication 
 */
void startAdv(void);

// callback invoked when central connects
void connect_callback(uint16_t conn_handle);

/**
 * Callback invoked when a connection is dropped
 * @param conn_handle connection where this event happens
 * @param reason is a BLE_HCI_STATUS_CODE which can be found in ble_hci.h
 */
void disconnect_callback(uint16_t conn_handle, uint8_t reason);

#endif