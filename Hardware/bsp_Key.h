#ifndef __BSP_KEY_H
#define __BSP_KEY_H

void MatrixKey_Init(void);
uint8_t MatrixKey_Scan(void);
uint8_t KeyNumGet(void);
void MatrixKey_Tick(void);

#endif

