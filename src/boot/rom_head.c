#include "genesis.h"

// clang-format off
__attribute__((externally_visible)) const ROMHeader rom_header = {
#if (ENABLE_BANK_SWITCH != 0)
    .console        = "SEGA SSF        ",
#else
    .console        = "SEGA MEGA DRIVE ",
#endif
    .copyright      = "(C)             ",
    .title_local    = "DEMONSTRATION PROGRAM                           ",
    .title_int      = "DEMONSTRATION PROGRAM                          ",
    .serial         = "GM 00000000-00",
    .checksum       = 0x000,
    .IOSupport      = "JD              ",
    .rom_start      = 0x00000000,
#if (ENABLE_BANK_SWITCH != 0)
    .rom_end        = 0x003FFFFF,
#else
    .rom_end        = 0x000FFFFF,
#endif
    .ram_start      = 0xE0FF0000,
    .ram_end        = 0xE0FFFFFF,
    .sram_sig       = "RA",
    .sram_type      = 0xF820,
    .sram_start     = 0x00200000,
    .sram_end       = 0x0020FFFF,
    .modem_support  = "            ",
    .notes          = "                                        ",
    .region         = "JUE             "
};
