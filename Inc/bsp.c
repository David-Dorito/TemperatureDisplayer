#include "bsp.h"

#define I2C_OWNADDR         0x2E

static void PCD8544_SetPixelColor_Bridge(void* pHandle, u16 posX, u16 posY, u32 color);
static void SPI_TransmitData_Bridge(void* pSpiHandle, u8* pTxBuffer, u16 len);
static void GPIO_WritePin_Bridge(void* pHandle, u8 isEnabled);
static void I2C_MasterTransmitData_Bridge(void* pI2cHandle, u16 slaveAddr, u8 addrMode, uint8_t* pTxBuffer, u16 len);
static void I2C_MasterReceiveData_Bridge(void* pI2cHandle, u16 slaveAddr, u8 addrMode, uint8_t* pRxBuffer, u16 len);

GPIO_Handle buttonPin = (GPIO_Handle){
    .pGPIOx = GPIOA,
    .Config = (GPIO_Config){
        .PinNumber = 10,
        .PinMode = GPIO_PINMODE_INPUT,
        .PupdCtrl = GPIO_PUPDCTRL_PULLUP,
        .RtFtDetect = GPIO_RTFTDETECT_FT
    }
};

SPI_Handle lcdSpiHandle = (SPI_Handle){
    .pSPIx = SPI1,
    .Config = (SPI_Config){
        .BusConfig = SPI_BUSCONFIG_FULLDUPLEX,
        .BitOrder = SPI_BITORDER_MSBFIRST,
        .CPHA = SPI_CPHA_FIRSTEDGE,
        .CPOL = SPI_CPOL_LOW,
        .DeviceMode = SPI_DEVICEMODE_MASTER,
        .SclkSpeed = SPI_SCLKSPEED_DIV64,
        .SSM = SPI_SSM_SOFTWARE,
        .DFF = SPI_DFF_8BIT
    }
};

GPIO_Handle lcdResetPin = (GPIO_Handle){
    .pGPIOx = GPIOA,
    .Config = (GPIO_Config){
        .PinNumber = 1,
        .PinMode = GPIO_PINMODE_OUTPUT,
        .OpSpeed = GPIO_OPSPEED_VERYHIGH,
        .OpType = GPIO_OPTYPE_PP,
        .RtFtDetect = GPIO_RTFTDETECT_NONE
    }
};

GPIO_Handle lcdSelectPin = (GPIO_Handle){
    .pGPIOx = GPIOA,
    .Config = (GPIO_Config){
        .PinNumber = 2,
        .PinMode = GPIO_PINMODE_OUTPUT,
        .OpSpeed = GPIO_OPSPEED_HIGH,
        .OpType = GPIO_OPTYPE_PP,
        .RtFtDetect = GPIO_RTFTDETECT_NONE
    }
};

GPIO_Handle lcdDcPin = (GPIO_Handle){
    .pGPIOx = GPIOA,
    .Config = (GPIO_Config){
        .PinNumber = 3,
        .PinMode = GPIO_PINMODE_OUTPUT,
        .OpSpeed = GPIO_OPSPEED_MED,
        .OpType = GPIO_OPTYPE_PP,
        .RtFtDetect = GPIO_RTFTDETECT_NONE
    }
};

GPIO_Handle lcdSckPin = (GPIO_Handle){
    .pGPIOx = GPIOA,
    .Config = (GPIO_Config){
        .PinNumber = 5,
        .PinMode = GPIO_PINMODE_ALTFUN,
        .AltFunNumber = 5,
        .OpSpeed = GPIO_OPSPEED_HIGH,
        .OpType = GPIO_OPTYPE_PP,
        .RtFtDetect = GPIO_RTFTDETECT_NONE
    }
};

GPIO_Handle lcdMosiPin = (GPIO_Handle){
.pGPIOx = GPIOA,
.Config = (GPIO_Config){
    .PinNumber = 7,
    .PinMode = GPIO_PINMODE_ALTFUN,
    .AltFunNumber = 5,
    .OpSpeed = GPIO_OPSPEED_HIGH,
    .OpType = GPIO_OPTYPE_PP,
    .RtFtDetect = GPIO_RTFTDETECT_NONE
}
};

GPIO_Handle lcdBacklightPin = (GPIO_Handle){
    .pGPIOx = GPIOA,
    .Config = (GPIO_Config){
        .PinNumber = 9,
        .PinMode = GPIO_PINMODE_OUTPUT,
        .OpSpeed = GPIO_OPSPEED_LOW,
        .OpType = GPIO_OPTYPE_PP,
        .RtFtDetect = GPIO_RTFTDETECT_NONE
    }
};

I2C_Handle sensorI2cHandle = (I2C_Handle){
    .pI2Cx = I2C1,
    .Config = (I2C_Config){
        .DefaultAckCtrl = I2C_DEFAULTACKCTRL_EN,
        .FMDutyCycle = I2C_FMDUTYCYCLE_2BY1,
        .OwnAddr = I2C_OWNADDR,
        .OwnAddrMode = I2C_OWNADDRMODE_7BIT,
        .SclSpeed = I2C_SCLSPEED_STD,
        .SclStretching = I2C_SCLSTRETCHING_EN
    }
};

GPIO_Handle sensorSdaPin = (GPIO_Handle){
    .pGPIOx = GPIOB,
    .Config = (GPIO_Config){
        .PinNumber = 9,
        .PinMode = GPIO_PINMODE_ALTFUN,
        .AltFunNumber = 4,
        .OpSpeed = GPIO_OPSPEED_MED,
        .OpType = GPIO_OPTYPE_OD,
        .PupdCtrl = GPIO_PUPDCTRL_NOPUPD,
        .RtFtDetect = GPIO_RTFTDETECT_NONE
    }
};

GPIO_Handle sensorSclPin = (GPIO_Handle){
    .pGPIOx = GPIOB,
    .Config = (GPIO_Config){
        .PinNumber = 8,
        .PinMode = GPIO_PINMODE_ALTFUN,
        .AltFunNumber = 4,
        .OpSpeed = GPIO_OPSPEED_MED,
        .OpType = GPIO_OPTYPE_OD,
        .PupdCtrl = GPIO_PUPDCTRL_NOPUPD,
        .RtFtDetect = GPIO_RTFTDETECT_NONE
    }
};

MCP9808_Transport sensorTransport = {
    .I2C_MasterTransmitData = I2C_MasterTransmitData_Bridge,
    .I2C_MasterReceiveData = I2C_MasterReceiveData_Bridge
};

MCP9808_Handle sensorHandle = (MCP9808_Handle){
    .pI2cHandle = &sensorI2cHandle,
    .pTransport = &sensorTransport,
    .Config = (MCP9808_Config){
        .AlertCtrl = DISABLE,
        .AlertOpMode = MCP9808_ALERTOPMODE_COMPARATOR,
        .AlertPolarity = LOW,
        .AlertTrigger = MCP9808_ALERTTRIGGER_ALL,
        .CritTempTrigger = 120.0f,
        .HighTempTrigger = 100.0f,
        .LowTempTrigger = -20.0f,
        .SlaveAddr = 0x18,
        .Resolution = MCP9808_RESOLUTION_0125
    }
};

u8 pLcdFrameBuffer[PCD8544_SCREEN_SIZE] = {0};

PCD8544_Transport lcdTransport = {
    .SPI_TransmitData = SPI_TransmitData_Bridge,
    .GPIO_WritePin = GPIO_WritePin_Bridge,
    .Delay = UnpreciseDelay
};

PCD8544_Handle lcdHandle = (PCD8544_Handle){
    .pFrameBuffer = pLcdFrameBuffer,
    .pSpiHandle = &lcdSpiHandle,
    .pCsPin = &lcdSelectPin,
    .pDcPin = &lcdDcPin,
    .pResPin = &lcdResetPin,
    .pLedPin = &lcdBacklightPin,
    .pVccPin = NULL,
    .pTransport = &lcdTransport
};

GfxLib_Transport gfxlibTransport = {
    .DrawPixelFunc = PCD8544_SetPixelColor_Bridge,
};

GfxLib_Handle gfxlibHandle = (GfxLib_Handle){
    .pFont = &basicFont,
    .pDisplayHandle = &lcdHandle,
    .pTransport = &gfxlibTransport
};


static void PCD8544_SetPixelColor_Bridge(void* pHandle, u16 posX, u16 posY, u32 color)
{
    PCD8544_SetPixelColor((PCD8544_Handle*)pHandle, color? TRUE : FALSE, posX, posY);
}

static void SPI_TransmitData_Bridge(void* pHandle, u8* pTxBuffer, u16 len)
{
    SPI_TransmitData((SPI_Handle*)pHandle, pTxBuffer, len);
}

static void GPIO_WritePin_Bridge(void* pHandle, u8 isEnabled)
{
    GPIO_WritePin((GPIO_Handle*)pHandle, isEnabled);
}

static void I2C_MasterTransmitData_Bridge(void* pI2cHandle, u16 slaveAddr, u8 addrMode, uint8_t* pTxBuffer, u16 len)
{
    I2C_MasterTransmitData((I2C_Handle*)pI2cHandle, slaveAddr, addrMode, pTxBuffer, len);
}

static void I2C_MasterReceiveData_Bridge(void* pI2cHandle, u16 slaveAddr, u8 addrMode, uint8_t* pRxBuffer, u16 len)
{
    I2C_MasterReceiveData((I2C_Handle*)pI2cHandle, slaveAddr, addrMode, pRxBuffer, len);
}

void BSP_Init()
{
    SYSCFG_PCLK_EN();
    IRQ_ItCtrl(IRQ_NO_EXTI15_10, ENABLE);
    
    GPIO_Init(&buttonPin);

    GPIO_Init(&lcdResetPin);
    GPIO_Init(&lcdSelectPin);
    GPIO_Init(&lcdDcPin);
    GPIO_Init(&lcdMosiPin);
    GPIO_Init(&lcdSckPin);
    GPIO_Init(&lcdBacklightPin);

    GPIO_Init(&sensorSclPin);
    GPIO_Init(&sensorSdaPin);
    
    SPI_Init(&lcdSpiHandle);
    
    I2C_Init(&sensorI2cHandle);
    
    PCD8544_Init(&lcdHandle);
    PCD8544_SetBacklight(&lcdHandle, ENABLE);
    
    MCP9808_Init(&sensorHandle);
}