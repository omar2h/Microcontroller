#include "tm4c123gh6pm.h"
#define PORTF_MASK       (1U<<5)
#define DARK             (0U)
#define RED              (1U<<1)
#define BLUE             (1U<<2)
#define GREEN            (1U<<3)
#define YELLOW           (1U<<1 | 1U<<3)
#define SKYBLUE          (1U<<2 | 1U<<3)
#define PINK             (1U<<1 | 1U<<2)
#define WHITE            (1U<<1 | 1U<<2 |1U<<3)
#define Left_SW          (1U<<4)
#define Right_SW         (1U)

void PORTF_init(void);