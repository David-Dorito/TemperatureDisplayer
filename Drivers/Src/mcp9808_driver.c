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

#define CONFIG_ALERTMOD         0
#define CONFIG_ALERTPOL         1
#define CONFIG_ALERTSEL         2
#define CONFIG_ALERTCNT         3
#define CONFIG_INTCLEAR         4
#define CONFIG_SHUTDOWN         5
#define CONFIG_THYST            9

#define TEMPREG_SIGN            12

#define I2C_ADDRMODE_7BIT       0

static u16 FloatToReg(float temp, uint8_t res);
static float ResToFloat(uint8_t res);

void MCP9808_Init(MCP9808_Handle* pMcp9808Handle)
{
    u16 commands[5] = {0};
    
    // register pointer
    commands[0] = REG_CONFIG;

    // config register
    commands[1] |= pMcp9808Handle->Config.AlertOpMode & 0b1;
    commands[1] |= pMcp9808Handle->Config.AlertPolarity & 0b1;
    commands[1] |= pMcp9808Handle->Config.AlertTrigger & 0b1;
    commands[1] |= pMcp9808Handle->Config.AlertCtrl & 0b1;
    commands[1] |= pMcp9808Handle->Config.AlertHysteresis & 0b11;
    
    // T_upper, T_lower, T_crit registers
    commands[2] = FloatToReg(pMcp9808Handle->Config.HighTempTrigger, pMcp9808Handle->Config.Resolution);
    commands[3] = FloatToReg(pMcp9808Handle->Config.LowTempTrigger, pMcp9808Handle->Config.Resolution);
    commands[4] = FloatToReg(pMcp9808Handle->Config.CritTempTrigger, pMcp9808Handle->Config.Resolution);
    
    // write registers
    pMcp9808Handle->I2C_MasterTransmitData(pMcp9808Handle->pI2cHandle, pMcp9808Handle->Config.SlaveAddr, I2C_ADDRMODE_7BIT, (u8*)commands, sizeof(commands)/sizeof(commands[0]));
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

static u16 FloatToReg(float temp, uint8_t res)
{
    int16_t raw = temp / ResToFloat(res);
    if (raw > 0x7FF) raw = 0x7FF;

    // Determine how many LSBs are unused
    uint8_t unused_bits = 0;
    switch(res) {
        case MCP9808_RESOLUTION_05:    unused_bits = 3; break; // 9-bit
        case MCP9808_RESOLUTION_025:   unused_bits = 2; break; // 10-bit
        case MCP9808_RESOLUTION_0125:  unused_bits = 1; break; // 11-bit
        case MCP9808_RESOLUTION_00625: unused_bits = 0; break; // 12-bit
    }

    // Mask unused bits
    raw &= ~((1 << unused_bits) - 1);

    // Set sign bit if negative
    if (temp < 0)
        raw |= (1U << TEMPREG_SIGN);

    return (u16)raw;
}

static float ResToFloat(uint8_t res)
{
    if (res == MCP9808_RESOLUTION_05) return 0.5f;
    else if (res == MCP9808_RESOLUTION_025) return 0.25f;
    else if (res == MCP9808_RESOLUTION_0125) return 0.125f;
    else if (res == MCP9808_RESOLUTION_00625) return 0.0625f;
}