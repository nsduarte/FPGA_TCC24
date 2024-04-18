/************ Includes ************/

#include "PmodGYRO.h"
#include "sleep.h"
#include "xil_cache.h"
#include "xil_printf.h"


/************ Funções ************/

void INICIAR();

void RUN();

void LIMPAR();

void ATIVAR_CACHE();

void DESATIVAR_CACHE();

/************ Variáveis Globais ************/

PmodGYRO sensor;

/************ Aplicação ************/

int main() {
   INICIAR();
   RUN();
   LIMPAR();
   return 0;
}

void INICIAR() {
   ATIVAR_CACHES();
   GYRO_begin(&sensor, XPAR_PMODGYRO_0_AXI_LITE_SPI_BASEADDR,
         XPAR_PMODGYRO_0_AXI_LITE_GPIO_BASEADDR);

   // Configurar Threshold Registers
   GYRO_setThsXH(&sensor, 0x0F);
   GYRO_setThsYH(&sensor, 0x0F);
   GYRO_setThsZH(&sensor, 0x0F);

   GYRO_enableInt1(&sensor, GYRO_INT1_XHIE);    // Threshold interrupção
   GYRO_enableInt2(&sensor,GYRO_REG3_I2_DRDY); // Data Rdy/FIFO interrupção
}

void RUN() {
   int16_t xAxis = 0;
   int16_t yAxis = 0;
   int16_t zAxis = 0;
   int8_t temp = 0;
   int trig = 0;

//   print("Iniciando...\n\r");
   while (1) {
      usleep(500000);

      if (GYRO_Int1Status(&sensor) != 0) {
         xil_printf("\x1B[2J");
         xil_printf("\x1B[H");
//         xil_printf("Threshold alcançado\n\r");
         trig = 1;
      }
      if (GYRO_Int2Status(&sensor) != 0) {
         if (trig == 1) {
            trig = 0;
         } else {
            xil_printf("\x1B[2J"); // Limpar tela
            xil_printf("\x1B[H");  // Resetar cursor para 0,0
         }
//         xil_printf("Lendo dados..\n\r\n\r");

         xAxis = GYRO_getX(&sensor);
         yAxis = GYRO_getY(&sensor);
         zAxis = GYRO_getZ(&sensor);
         temp = GYRO_getTemp(&sensor);

//         temp = 0;
         temp = (temp - 32) * 5/9;

//         xil_printf("X Axis: 0x%04x\n\r", xAxis & 0xFFFF);
//         xil_printf("Y Axis: 0x%04x\n\r", yAxis & 0xFFFF);
//         xil_printf("Z Axis: 0x%04x\n\r", zAxis & 0xFFFF);

         xil_printf("X Axis: %d\n\r", xAxis);
         xil_printf("Y Axis: %d\n\r", yAxis);
         xil_printf("Z Axis: %d\n\r", zAxis);

         xil_printf("\n\r");

         xil_printf("Temperatura: %dC\n\r", temp);
      }
   }
}

void LIMPAR() {
   GYRO_end(&myDevice);
   DESATIVAR_CACHES();
}

void ATIVAR_CACHES() {
#ifdef __MICROBLAZE__
#ifdef XPAR_MICROBLAZE_USE_DCACHE
   Xil_DCacheEnable();
#endif
#ifdef XPAR_MICROBLAZE_USE_ICACHE
   Xil_ICacheEnable();
#endif
#endif
}

void DESATIVAR_CACHES() {
#ifdef __MICROBLAZE__
#ifdef XPAR_MICROBLAZE_USE_DCACHE
   Xil_DCacheDisable();
#endif
#ifdef XPAR_MICROBLAZE_USE_ICACHE
   Xil_ICacheDisable();
#endif
#endif
}