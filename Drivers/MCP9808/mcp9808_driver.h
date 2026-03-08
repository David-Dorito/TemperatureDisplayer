#ifndef MCP9808_DRIVER_H_
#define MCP9808_DRIVER_H_

#include "../Internal/types.h"

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
    u8 AlertCtrl;
    u8 AlertTrigger;
    u8 AlertOpMode;
    u8 AlertPolarity;
    u8 AlertHysteresis;
    u8 SlaveAddr;
    u8 Resolution;
} MCP9808_Config;

typedef struct {
    void (*I2C_MasterTransmitData)(void* pI2cHandle, u16 slaveAddr, u8 addrMode, u8* pTxBuffer, u16 len);
    void (*I2C_MasterReceiveData)(void* pI2cHandle, u16 slaveAddr, u8 addrMode, u8* pRxBuffer, u16 len);
} MCP9808_Transport;

typedef struct {
    MCP9808_Config Config;
    void* pI2cHandle;
    MCP9808_Transport* pTransport;
} MCP9808_Handle;

/*************************************\
  fn: @MCP9808_Init
  
  param1 MCP9808_Handle*: the handle of the temperature sensor
  
  return:
  
  desc: initializes the temperature sensor
  
  note:
  
\**************************************/
void MCP9808_Init(MCP9808_Handle* pMcp9808Handle);

/*************************************\
  fn: @MCP9808_GetTemperature
  
  param1 MCP9808_Handle*: the handle of the temperature sensor
  
  return float: the temperature as a float
  
  desc: initializes the temperature sensor
  
  note:
  
\**************************************/
float MCP9808_GetTemperature(MCP9808_Handle* pMcp9808Handle);

/*************************************\
  fn: @MCP9808_SetSleepMode
  
  param1 MCP9808_Handle*: the handle of the temperature sensor
  param2 u8: enable or disable the sleep mode
  
  return: 
  
  desc: enables or disables the sleep mode of the peripheral
  
  note:
  
\**************************************/
void MCP9808_SetSleepMode(MCP9808_Handle* pMcp9808Handle, u8 isEnabled);

#endif