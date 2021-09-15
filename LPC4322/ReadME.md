1. at the root of DAPLink repo, run

```cpp
progen generate -f projects.yaml -p lpc4322_hani_iot_if -t uvision
```

2. to get Keil MDK project to build, and test with the following 
debug initialization script:

```cpp

/*----------------------------------------------------------------------------
  Setup()  configure PC & SP for RAM Debug
 *----------------------------------------------------------------------------*/
FUNC void Setup (void) {
    SP = _RDWORD(0x1A010000+0x0);        // Setup Stack Pointer
    PC = _RDWORD(0x1A010000+0x4);        // Setup Program Counter
    _WDWORD(0xE000ED08, 0x0000C000+0x0); // Setup Vector Table Offset Register (done in system file)
}

/*----------------------------------------------------------------------------
  OnResetExec() executed after reset via uVision's 'Reset'-button
 *----------------------------------------------------------------------------*/
FUNC void OnResetExec (void)
{
}

LOAD %L INCREMENTAL                                  // load the application


Setup();                                             // Setup for Running

BS main
g

```

---
.NFC, 2021/09/15

