# Mega Drive SRAM & Mapper Diagnostics

Test ROM for diagnosing issues with memory mapping & SRAM on emulators and consoles.

<p align="center">
    <img src="https://github.com/rhargreaves/sram-playground/raw/main/docs/screenshot.png" width="600" />
</p>

## Build

Using Docker:

```sh
./docker-make release
```

## Intended Usage

### Bank Mapping Tests

Set `static bool test_bank_mapper = true;` in [main.c](src/main.c).

The bank mapping tests attempt to read from data which is spaced out by 512 KB, as declared in the [`data.res`](res/data.res) file:

```
ALIGN
BIN data1 data.bin 524288 2 0 NONE FALSE
BIN data2 data.bin 524288 2 0 NONE FALSE
BIN data3 data.bin 524288 2 0 NONE FALSE
BIN data4 data.bin 524288 2 0 NONE FALSE
BIN data5 data.bin 524288 2 0 NONE FALSE
BIN data6 data.bin 524288 2 0 NONE FALSE
BIN data7 data.bin 524288 2 0 NONE FALSE
BIN data8 data.bin 524288 2 0 NONE FALSE
BIN data9 data.bin 524288 2 0 NONE FALSE
BIN data10 data.bin 524288 2 0 NONE FALSE
```

The tests check:

* Near data (that which requires no use of bank mapping) can be accessed fine.
* Far data cannot be accessed if it's not been explicitly mapped in
* Far data can be accessed when it's mapped in.

Ultimately this is just a template to provide an easy way to test mapping across devices and is supposed to be modified according to your own needs.

### SRAM tests

Set `static bool test_sram = true;` in [main.c](src/main.c).

These are adhoc tests for supporting the differences between working with SRAM in the Everdrive PRO and X7. Not suitable for general use.
