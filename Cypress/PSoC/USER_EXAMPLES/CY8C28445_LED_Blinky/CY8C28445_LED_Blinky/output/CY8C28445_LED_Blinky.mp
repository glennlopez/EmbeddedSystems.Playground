Project:      output/CY8C28445_LED_Blinky
Build Number: 0
Date:         Thu Jan 05 15:08:57 2012
Compiler:     ICCM8C
Version:      7.05.00


Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             lit   0190   00F2 =    242. bytes (rel,con,rom,lit)

       Addr  Global Symbol
      -----  --------------------------------
       0190  LoadConfigTBL_cy8c28445_led_blinky_Bank0
       01F3  LoadConfigTBL_cy8c28445_led_blinky_Bank1
       0282  __lit_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                        func_lit   0282   0002 =      2. bytes (rel,con,rom,proclab)

       Addr  Global Symbol
      -----  --------------------------------
       0282  __func_lit_start
       0284  __func_lit_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                     psoc_config   0284   0127 =    295. bytes (rel,con,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       0284  LoadConfigTBL_cy8c28445_led_blinky_Ordered
       0349  LoadConfigInit
       0349  _LoadConfigInit
       0350  _LoadConfig_cy8c28445_led_blinky
       0350  LoadConfig_cy8c28445_led_blinky
       03AB  __psoc_config_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   03AB   001A =     26. bytes (rel,con,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       03AB  __text_start
       03AB  _main
       03C5  __xidata_start
       03C5  __text_end
       03C7  __xidata_end

Area                               Start  End    Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             TOP   0000   0151 =    337. bytes (abs,ovr,rom,code)

       Addr  Global Symbol
      -----  --------------------------------
       0080  __Start
       014E  _bGetPowerSetting
       014E  bGetPowerSetting

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
               virtual_registers   0000   0002 =      2. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0000  __r1
       0001  __r0

Files Linked      [ module(s) ]

./obj/boot.o	[ boot.asm ]
./obj/main.o	[ main.c ]
<library>	[ psocconfigtbl.asm, psocconfig.asm, r1.asm, r0.asm ]

Area Definitions

-blit:0x190.0x3fff
-bdata:0.0x2ff
-BInterruptRAM:0	allocated at: 0
-Bvirtual_registers	allocated at: 0
-Bcy8c28445_led_blinky_RAM
-rwh:SSCParmBlk:0xf7.0xff

