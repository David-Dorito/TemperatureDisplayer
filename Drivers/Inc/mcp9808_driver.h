#ifndef MCP9808_DRIVER_H_
#define MCP9808_DRIVER_H_

#include <stdint.h>

#define MCP9808_RESOLUTION_05           0
#define MCP9808_RESOLUTION_025          1
#define MCP9808_RESOLUTION_0125         2
#define MCP9808_RESOLUTION_00625        3

#define MCP9808_ALERTTRIGGER_ALL        0
#define MCP9808_ALERTTRIGGER_CRITONLY   1

#define MCP9808_ALERTOPMODE_COMPARATOR  0
#define MCP9808_ALERTOPMODE_INTERRUPT   1

#define MCP9808_ALERTPOLARITY_LOW       0
#define MCP9808_ALERTPOLARITY_HIGH      1

#define MCP9808_ALERTHYSTERESIS_0_0     0
#define MCP9808_ALERTHYSTERESIS_1_5     1
#define MCP9808_ALERTHYSTERESIS_3_0     2
#define MCP9808_ALERTHYSTERESIS_6_0     3

typedef struct {
    float LowTempTrigger;
    float HighTempTrigger;
    float CritTempTrigger;
    uint8_t AlertCtrl;
    uint8_t AlertTrigger;
    uint8_t AlertOpMode;
    uint8_t AlertPolarity;
    uint8_t AlertHysteresis;
    uint8_t SlaveAddr;
    uint8_t Resolution;
} MCP9808_Config;

typedef struct {
    void* pI2cHandle;
    void (*I2C_MasterTransmitData)(void* pI2cHandle, uint16_t slaveAddr, uint8_t addrMode, uint8_t* pTxBuffer, uint16_t len);
    void (*I2C_MasterReceiveData)(void* pI2cHandle, uint16_t slaveAddr, uint8_t addrMode, uint8_t* pRxBuffer, uint16_t len);
    MCP9808_Config Config;
} MCP9808_Handle;

void MCP9808_Init(MCP9808_Handle* pMcp9808Handle);
float MCP9808_GetTemperature(MCP9808_Handle* pMcp9808Handle);
void MCP9808_SetSleepMode(MCP9808_Handle* pMcp9808Handle, uint8_t isEnabled);

#endif