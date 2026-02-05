#include <genesis.h>
#include "data.h"

void test_banks(void)
{
    CON_write("Bank Test Program\n-----------------\n");
    CON_write("test_data1 = 0x%x\n", data1[0]);
    CON_write("test_data2 = 0x%x\n", data2[0]);
    CON_write("test_data3 = 0x%x\n", data3[0]);
    CON_write("test_data4 = 0x%x\n", data4[0]);
    CON_write("test_data5 = 0x%x\n", data5[0]);
    CON_write("test_data6 = 0x%x\n", data6[0]);
    CON_write("test_data7 = 0x%x\n", data7[0]);
    CON_write("test_data8 = 0x%x\n", ((u8*)FAR(data8))[0]);
    CON_write("Done");
}
