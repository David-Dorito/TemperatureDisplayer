#ifndef MCP9808_DRIVER_H_
#define MCP9808_DRIVER_H_

#include <stdint.h>

#define MCP9808_RESOLUTION_05           0b00
#define MCP9808_RESOLUTION_025          0b01
#define MCP9808_RESOLUTION_0125         0b10
#define MCP9808_RESOLUTION_00625        0b11

#define MCP9808_ALTERTRIGGER_ALL        0
#define MCP9808_ALTERTRIGGER_CRITONLY   1

#define MCP9808_ALERTOPMODE_COMPARATOR  0
#define MCP9808_ALERTOPMODE_INTERRUPT   1

#define MCP9808_ALERTPOLARITY_LOW       0
#define MCP9808_ALERTPOLARITY_HIGH      1

typedef struct {
    float LowTempTrigger;
    float HighTempTrigger;
    float CritTempTrigger;
    uint8_t AlertCtrl;
    uint8_t AlertTrigger;
    uint8_t AlertOpMode;
    uint8_t AlertPolarity;
    uint8_t SlaveAddr;
    uint8_t Resolution;
} MCP9808_Config;

typedef struct {
    void* pI2cHandle;
    void (*I2C_MasterTransmitData)(void* pI2cHandle, u16 slaveAddr, u8 addrMode, uint8_t* pTxBuffer, u16 len);
    void (*I2C_MasterReceiveData)(void* pI2cHandle, u16 slaveAddr, u8 addrMode, uint8_t* pRxBuffer, u16 len);
    MCP9808_Config Config;
} MCP9808_Handle;

void MCP9808_Init(MCP9808_Handle* pMcp9808Handle);
float MCP9808_GetTemperature(MCP9808_Handle* pMcp9808Handle);
void MCP9808_SetSleepMode(MCP9808_Handle* pMcp9808Handle, uint8_t isEnabled);

#endif