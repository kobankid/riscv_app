#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint64_t tmp = 0;
uint16_t v_out[1024];


int main(int argc, char* argv[])
{
    float test = 100.0;
    uint16_t v_array1[32] = {1, 2, 3, 4, 5, 6, 7, 8,
                             9, 10, 11, 12, 13, 14, 15, 16,
                             17, 18, 19, 20, 21, 22, 23, 24,
                             25, 26, 27, 28, 29, 30, 31, 32};
    uint16_t v_array2[32] = {1, 2, 3, 4, 5, 6, 7, 8,        
                             9, 10, 11, 12, 13, 14, 15, 16, 
                             17, 18, 19, 20, 21, 22, 23, 24,
                             25, 26, 27, 28, 29, 30, 31, 32};
    uint64_t mask = 0;
    uint64_t ustatus = 0;
    uint64_t csr_tmp = 0;
    uint64_t vl = 16;
    volatile uint64_t counter = 0xFFFFFFFF;

    memset(v_out, 0, 1024*2);

    printf("counter = %ld\n", counter);

    __asm__ __volatile__ ("csrr %0, hpmcounter3\r\n" : "=&r" (counter));
    __asm__ __volatile__ ("li a0, 32\r\n");
    __asm__ __volatile__ ("nop\r\n");
    __asm__ __volatile__ ("nop\r\n");
    __asm__ __volatile__ ("nop\r\n");
    __asm__ __volatile__ ("nop\r\n");
    __asm__ __volatile__ ("vsetvli %0, %1, e32\r\n" : "=&r" (csr_tmp) : "r" (vl));

    // __asm__ __volatile__ ("sd t0, %0\r\n" : "=m" (tmp));
    // printf("csr_vl = 0x%016x\n", csr_tmp);

    __asm__ __volatile__ ("vle16.v v1, (%0)\r\n" : :"r" (v_array1));
    __asm__ __volatile__ ("vle16.v v2, (%0)\r\n" : :"r" (v_array2));
    __asm__ __volatile__ ("vadd.vv v3, v1, v2\r\n");
    /* __asm__ __volatile__ ("li a5, 0x1e208\r\n"); */
    /* __asm__ __volatile__ ("vse16.v v3, (a5)\r\n"); */
    /* __asm__ __volatile__ ("li a5, %lo(0x1e208)\r\n"); */
    /* __asm__ __volatile__ ("li a5, %0 \r\n" : : "r" (v_out)); */
    __asm__ __volatile__ ("vse16.v v3, %0 \r\n" : "=g" (v_out));

    for (int i = 0; i < 32; i++) {
        printf("v_array1[%d] = %d\n", i, v_array1[i]);
        printf("v_array2[%d] = %d\n", i, v_array2[i]);
        printf("v_out[%d] = %d\n", i, v_out[i]);
    }

    __asm__ __volatile__ ("csrr %0, vstart\r\n" : "=&r" (csr_tmp));
    printf("vstart = 0x%016x\n", csr_tmp);
    __asm__ __volatile__ ("csrr %0, vxsat\r\n" : "=&r" (csr_tmp));
    printf("vxsat = 0x%016x\n", csr_tmp);
    __asm__ __volatile__ ("csrr %0, vxrm\r\n" : "=&r" (csr_tmp));
    printf("vxrm = 0x%016x\n", csr_tmp);
    __asm__ __volatile__ ("csrr %0, vcsr\r\n" : "=&r" (csr_tmp));
    printf("vcsr = 0x%016x\n", csr_tmp);
    __asm__ __volatile__ ("csrr %0, vl\r\n" : "=&r" (csr_tmp));
    printf("vl = 0x%016x\n", csr_tmp);
    __asm__ __volatile__ ("csrr %0, vtype\r\n" : "=&r" (csr_tmp));
    printf("vtype = 0x%016x\n", csr_tmp);
    __asm__ __volatile__ ("csrr %0, vlenb\r\n" : "=&r" (csr_tmp));
    printf("vlenb = 0x%016x\n", csr_tmp);

    printf("Hello world!%f sizeof(float) = %d\n", test, sizeof(int));
    printf("counter = %ld\n", counter);
    __asm__ __volatile__ ("csrr %0, hpmcounter3" : "=&r" (counter));

    exit(0);

    return 0;
}
