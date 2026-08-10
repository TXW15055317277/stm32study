#include "SPI_HARDWARE.h"

void SPI_HARD_Init_(void)
{
    // PB3-SCL,PB4-MISO,PB5-MOSI,PB14-CS
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

    // 复用功能选择
    GPIOB->AFR[0] |= GPIO_AF_SPI1 << 12;
    GPIOB->AFR[0] |= GPIO_AF_SPI1 << 16;
    GPIOB->AFR[0] |= GPIO_AF_SPI1 << 20;

    // 工作模式配置，尽管是输入，也要配置为复用而不是输入
    GPIOB->MODER |= GPIO_MODER_MODER3_1;
    GPIOB->MODER &= ~GPIO_MODER_MODER3_0;
    GPIOB->MODER |= GPIO_MODER_MODER4_1;
    GPIOB->MODER &= ~GPIO_MODER_MODER4_0;
    GPIOB->MODER |= GPIO_MODER_MODER5_1;
    GPIOB->MODER &= ~GPIO_MODER_MODER5_0;
    GPIOB->MODER |= GPIO_MODER_MODER14_0;
    GPIOB->MODER &= ~GPIO_MODER_MODER14_1;
    GPIOB->OTYPER &= ~GPIO_OTYPER_OT_3;
    GPIOB->OTYPER &= ~GPIO_OTYPER_OT_4;
    GPIOB->OTYPER &= ~GPIO_OTYPER_OT_5;
    GPIOB->OTYPER &= ~GPIO_OTYPER_OT_14;
    GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR3 | GPIO_OSPEEDER_OSPEEDR4 | GPIO_OSPEEDER_OSPEEDR5 | GPIO_OSPEEDER_OSPEEDR14;
    GPIOB->PUPDR |= GPIO_PUPDR_PUPDR3_0 | GPIO_PUPDR_PUPDR4_0 | GPIO_PUPDR_PUPDR5_0 | GPIO_PUPDR_PUPDR14_0;
    GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPDR3_1 | GPIO_PUPDR_PUPDR4_1 | GPIO_PUPDR_PUPDR5_1 | GPIO_PUPDR_PUPDR14_1);

    // SPI模式0
    SPI1->CR1 &= ~SPI_CR1_CPHA;
    SPI1->CR1 &= ~SPI_CR1_CPOL;

    // 主模式
    SPI1->CR1 |= SPI_CR1_MSTR;

    // 软件模式
    SPI1->CR1 |= SPI_CR1_SSM;
    SPI1->CR1 |= SPI_CR1_SSI;

    // 波特率设置
    SPI1->CR1 &= ~SPI_CR1_BR;

    // 高位先行
    SPI1->CR1 &= ~SPI_CR1_LSBFIRST;

    // 数据为8位
    SPI1->CR1 &= ~SPI_CR1_DFF;

    // 开启SPI DMA
    SPI1->CR2 |= SPI_CR2_TXDMAEN;
    SPI1->CR2 |= SPI_CR2_RXDMAEN;

    // 开启SPI使能
    SPI1->CR1 |= SPI_CR1_SPE;



    // DMA相关，SPI1-RX 流2通道3，SPI1-TX 流3通道3
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;

    // 关闭传输完成中断
    DMA2_Stream2->CR &= ~DMA_SxCR_TCIE;

    // 00外设->存储器， 01存储器->外设
    DMA2_Stream2->CR &= ~DMA_SxCR_DIR;

    // 循环模式
    DMA2_Stream2->CR &= ~DMA_SxCR_CIRC;

    // 外设地址不变，存储器地址递增
    DMA2_Stream2->CR &= ~DMA_SxCR_PINC;
    DMA2_Stream2->CR |= DMA_SxCR_PINC;

    // 数据大小,8位
    DMA2_Stream2->CR &= ~DMA_SxCR_PSIZE;
    DMA2_Stream2->CR &= ~DMA_SxCR_MSIZE;

    // 优先级
    DMA2_Stream2->CR |= DMA_SxCR_PL;

    // 通道选择
    DMA2_Stream2->CR |= DMA_SxCR_CHSEL_0;
    DMA2_Stream2->CR |= DMA_SxCR_CHSEL_1;
    DMA2_Stream2->CR &= ~DMA_SxCR_CHSEL_2;



    // DMA相关，SPI1-RX 流2通道3，SPI1-TX 流3通道3
    // 关闭传输完成中断
    DMA2_Stream3->CR &= ~DMA_SxCR_TCIE;

    // 00外设->存储器， 01存储器->外设
    DMA2_Stream3->CR &= ~DMA_SxCR_DIR_1;
    DMA2_Stream3->CR |= DMA_SxCR_DIR_0;

    // 循环模式
    DMA2_Stream3->CR &= ~DMA_SxCR_CIRC;

    // 外设地址不变，存储器地址递增
    DMA2_Stream3->CR &= ~DMA_SxCR_PINC;
    DMA2_Stream3->CR |= DMA_SxCR_PINC;

    // 数据大小,8位
    DMA2_Stream3->CR &= ~DMA_SxCR_PSIZE;
    DMA2_Stream3->CR &= ~DMA_SxCR_MSIZE;

    // 优先级
    DMA2_Stream3->CR |= DMA_SxCR_PL;

    // 通道选择
    DMA2_Stream3->CR |= DMA_SxCR_CHSEL_0;
    DMA2_Stream3->CR |= DMA_SxCR_CHSEL_1;
    DMA2_Stream3->CR &= ~DMA_SxCR_CHSEL_2;
}

// uint8_t SPI_HARD_SWAP(uint8_t Byte)
// {
//     while ((SPI1->SR & SPI_SR_TXE) == 0)
//     {}
//     SPI1->DR = Byte;

//     while ((SPI1->SR & SPI_SR_RXNE) == 0)
//     {}

//     return (uint8_t)SPI1->DR;
// }

void SPI_DMA_START(uint32_t t_maddr, uint32_t r_maddr)
{
    DMA2_Stream2->CR &= ~DMA_SxCR_EN;
    DMA2_Stream3->CR &= ~DMA_SxCR_EN;

    DMA2->LIFCR |= DMA_LIFCR_CTCIF2 | DMA_LIFCR_CHTIF2 | DMA_LIFCR_CTEIF2 | DMA_LIFCR_CDMEIF2 | DMA_LIFCR_CFEIF2;
    DMA2->LIFCR |= DMA_LIFCR_CTCIF3 | DMA_LIFCR_CHTIF3 | DMA_LIFCR_CTEIF3 | DMA_LIFCR_CDMEIF3 | DMA_LIFCR_CFEIF3;

    DMA2_Stream2->PAR = (uint32_t)&(SPI1->DR);
    DMA2_Stream2->M0AR = r_maddr;
    DMA2_Stream2->NDTR = 1;
    DMA2_Stream3->PAR = (uint32_t)&(SPI1->DR);
    DMA2_Stream3->M0AR = t_maddr;
    DMA2_Stream3->NDTR = 1;

    DMA2_Stream2->CR |= DMA_SxCR_EN;
    DMA2_Stream3->CR |= DMA_SxCR_EN;

    while ((DMA2->LISR & DMA_LISR_TCIF2) == 0)
    {}
    while ((DMA2->LISR & DMA_LISR_TCIF3) == 0)
    {}
}

void SPI_HARD_START(void)
{
    GPIOB->ODR &= ~GPIO_ODR_ODR_14;
}

void SPI_HARD_STOP(void)
{
    GPIOB->ODR |= GPIO_ODR_ODR_14;
}
