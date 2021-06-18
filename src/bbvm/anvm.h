#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#define VERSION "BBVM v0.0.1"
#define DEFAULTBIN "test.bin"

#include "Cpu.h"
#include "Screen.h"
#include "Input.h"
#include "Gpu.h"
#include "Storage.h"
#include "ErrorLog.h"

// ------ Environment --------
// CPU
extern Cpu *cpu;
// SCREEN
extern Screen *scn;
// MEMORY
extern unsigned char *vmem;
// KEYBOARD
extern Keyboard *keybd;
// GPU
extern Gpu *gpu;
// STORAGE
extern Storage *storage;
