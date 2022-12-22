#include <stdint>
#ifndef  TERMINAL_H
#define TERMINAL_H
typedef struct ST_terminalData_t
{
    float transAmount;
    float maxTransAmount;
    uint8_t transactionDate[11];
}ST_terminalData_t;

#endif
