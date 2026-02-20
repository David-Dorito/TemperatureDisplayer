#include "../Inc/mcp9808_driver.h"

typedef int64_t                 i64;
typedef int32_t                 i32;
typedef int16_t                 i16;
typedef int8_t                  i8;
typedef uint64_t                u64;
typedef uint32_t                u32;
typedef uint16_t                u16;
typedef uint8_t                 u8;

#define REG_CONFIG              0b0001
#define REG_UPPERBOUND          0b0010
#define REG_LOWERBOUND          0b0011
#define REG_CRIT                0b0100
#define REG_TEMP                0b0101
#define REG_MANID               0b0110
#define REG_DEVID               0b0111
#define REG_RES                 0b1000

#define I2C_ADDRMODE_7BIT       0

void MCP9808_Init(MCP9808_Handle* pMcp9808Handle)
{

}

float MCP9808_GetTemperature(MCP9808_Handle* pMcp9808Handle)
{
    u16 data = REG_TEMP;
    pMcp9808Handle->I2C_MasterTransmitData(pMcp9808Handle->pI2cHandle, pMcp9808Handle->Config.SlaveAddr, I2C_ADDRMODE_7BIT, (u8*)&data, 1);
    // ^^ set register pointer to the temperature register
    
    u8 rxBuffer[2];
    pMcp9808Handle->I2C_MasterReceiveData(pMcp9808Handle->pI2cHandle, pMcp9808Handle->Config.SlaveAddr, I2C_ADDRMODE_7BIT, rxBuffer, 2);
    // ^^ get temperature data from temperature register

    data = (rxBuffer[0] << 8) | rxBuffer[1]; // swap bytes because MCP9808 transmits MSB first
    if (data & 0x1000)
        data -= 4096;
    
    data &= 0x0FFF; //mask out sign bit and alert bits
    
    return data * pMcp9808Handle->Config.Resolution;

}

void MCP9808_SetSleepMode(MCP9808_Handle* pMcp9808Handle, uint8_t isEnabled)
{

}