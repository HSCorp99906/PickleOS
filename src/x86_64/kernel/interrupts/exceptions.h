#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include "IDT.h"


void div_0_ex(int_frame32_t*);
void overflow_ex(int_frame32_t*);
void bre_ex(int_frame32_t*);
void invld_opcode_ex(int_frame32_t*);
void dev_na_ex(int_frame32_t*);
void double_fault_ex(int_frame32_t*);
void cso_ex(int_frame32_t*);
void invld_tss_ex(int_frame32_t*);
void seg_np_ex(int_frame32_t*);
void ss_fault_ex(int_frame32_t*);
void gp_fault_ex(int_frame32_t*);
void page_fault_ex(int_frame32_t*);
void float_ex(int_frame32_t*);


#endif
