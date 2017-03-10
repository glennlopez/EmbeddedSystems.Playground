;******************************************************************************
;* TI ARM C/C++ Codegen                                        PC v16.9.0.LTS *
;* Date/Time created: Fri Mar 10 00:22:00 2017                                *
;******************************************************************************
	.compiler_opts --abi=eabi --arm_vmrs_si_workaround=off --code_state=16 --diag_wrap=off --embedded_constants=on --endian=little --float_support=FPv4SPD16 --hll_source=on --object_format=elf --silicon_version=7M4 --symdebug:dwarf --symdebug:dwarf_version=3 --unaligned_access=on 
	.thumb

$C$DW$CU	.dwtag  DW_TAG_compile_unit
	.dwattr $C$DW$CU, DW_AT_name("../GPIO.c")
	.dwattr $C$DW$CU, DW_AT_producer("TI TI ARM C/C++ Codegen PC v16.9.0.LTS Copyright (c) 1996-2015 Texas Instruments Incorporated")
	.dwattr $C$DW$CU, DW_AT_TI_version(0x01)
	.dwattr $C$DW$CU, DW_AT_comp_dir("D:\Github Clones\EmbeddedSystems.Playground\Texas Instruments\TM4C123G\Projects\GPIO_4C123\Debug")

$C$DW$1	.dwtag  DW_TAG_subprogram
	.dwattr $C$DW$1, DW_AT_name("EnableInterrupts")
	.dwattr $C$DW$1, DW_AT_TI_symbol_name("EnableInterrupts")
	.dwattr $C$DW$1, DW_AT_declaration
	.dwattr $C$DW$1, DW_AT_external
	.dwattr $C$DW$1, DW_AT_decl_file("../GPIO.c")
	.dwattr $C$DW$1, DW_AT_decl_line(0x1a)
	.dwattr $C$DW$1, DW_AT_decl_column(0x06)
	.dwendtag $C$DW$1


$C$DW$2	.dwtag  DW_TAG_subprogram
	.dwattr $C$DW$2, DW_AT_name("WaitForInterrupt")
	.dwattr $C$DW$2, DW_AT_TI_symbol_name("WaitForInterrupt")
	.dwattr $C$DW$2, DW_AT_declaration
	.dwattr $C$DW$2, DW_AT_external
	.dwattr $C$DW$2, DW_AT_decl_file("../GPIO.c")
	.dwattr $C$DW$2, DW_AT_decl_line(0x1b)
	.dwattr $C$DW$2, DW_AT_decl_column(0x06)
	.dwendtag $C$DW$2

;	D:\EngineeringSoftware\CCS\ccsv7\tools\compiler\ti-cgt-arm_16.9.0.LTS\bin\armacpia.exe -@C:\\Users\\Glenn\\AppData\\Local\\Temp\\1393612 
	.sect	".text"
	.clink
	.thumbfunc SysTick_Handler
	.thumb
	.global	SysTick_Handler

$C$DW$3	.dwtag  DW_TAG_subprogram
	.dwattr $C$DW$3, DW_AT_name("SysTick_Handler")
	.dwattr $C$DW$3, DW_AT_low_pc(SysTick_Handler)
	.dwattr $C$DW$3, DW_AT_high_pc(0x00)
	.dwattr $C$DW$3, DW_AT_TI_symbol_name("SysTick_Handler")
	.dwattr $C$DW$3, DW_AT_external
	.dwattr $C$DW$3, DW_AT_TI_begin_file("../GPIO.c")
	.dwattr $C$DW$3, DW_AT_TI_begin_line(0x20)
	.dwattr $C$DW$3, DW_AT_TI_begin_column(0x06)
	.dwattr $C$DW$3, DW_AT_decl_file("../GPIO.c")
	.dwattr $C$DW$3, DW_AT_decl_line(0x20)
	.dwattr $C$DW$3, DW_AT_decl_column(0x06)
	.dwattr $C$DW$3, DW_AT_TI_max_frame_size(0x00)
	.dwpsn	file "../GPIO.c",line 32,column 27,is_stmt,address SysTick_Handler,isa 1

	.dwfde $C$DW$CIE, SysTick_Handler
;----------------------------------------------------------------------
;  32 | void SysTick_Handler(void){                                            
;----------------------------------------------------------------------

;*****************************************************************************
;* FUNCTION NAME: SysTick_Handler                                            *
;*                                                                           *
;*   Regs Modified     : A1,A2                                               *
;*   Regs Used         : A1,A2,LR                                            *
;*   Local Frame Size  : 0 Args + 0 Auto + 0 Save = 0 byte                   *
;*****************************************************************************
SysTick_Handler:
;* --------------------------------------------------------------------------*
	.dwcfi	cfa_offset, 0
	.dwpsn	file "../GPIO.c",line 33,column 3,is_stmt,isa 1
;----------------------------------------------------------------------
;  33 | GPIO_PORTF_DATA_R ^= 0x04;                                             
;----------------------------------------------------------------------
        LDR       A2, $C$CON1           ; [DPU_3_PIPE] |33| 
        LDR       A1, [A2, #0]          ; [DPU_3_PIPE] |33| 
        EOR       A1, A1, #4            ; [DPU_3_PIPE] |33| 
        STR       A1, [A2, #0]          ; [DPU_3_PIPE] |33| 
	.dwpsn	file "../GPIO.c",line 34,column 1,is_stmt,isa 1
$C$DW$4	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$4, DW_AT_low_pc(0x00)
	.dwattr $C$DW$4, DW_AT_TI_return

        BX        LR                    ; [DPU_3_PIPE] 
        ; BRANCH OCCURS                  ; [] 
	.dwattr $C$DW$3, DW_AT_TI_end_file("../GPIO.c")
	.dwattr $C$DW$3, DW_AT_TI_end_line(0x22)
	.dwattr $C$DW$3, DW_AT_TI_end_column(0x01)
	.dwendentry
	.dwendtag $C$DW$3

	.sect	".text"
	.clink
	.thumbfunc main
	.thumb
	.global	main

$C$DW$5	.dwtag  DW_TAG_subprogram
	.dwattr $C$DW$5, DW_AT_name("main")
	.dwattr $C$DW$5, DW_AT_low_pc(main)
	.dwattr $C$DW$5, DW_AT_high_pc(0x00)
	.dwattr $C$DW$5, DW_AT_TI_symbol_name("main")
	.dwattr $C$DW$5, DW_AT_external
	.dwattr $C$DW$5, DW_AT_TI_begin_file("../GPIO.c")
	.dwattr $C$DW$5, DW_AT_TI_begin_line(0x28)
	.dwattr $C$DW$5, DW_AT_TI_begin_column(0x06)
	.dwattr $C$DW$5, DW_AT_decl_file("../GPIO.c")
	.dwattr $C$DW$5, DW_AT_decl_line(0x28)
	.dwattr $C$DW$5, DW_AT_decl_column(0x06)
	.dwattr $C$DW$5, DW_AT_TI_max_frame_size(0x08)
	.dwpsn	file "../GPIO.c",line 40,column 17,is_stmt,address main,isa 1

	.dwfde $C$DW$CIE, main
;----------------------------------------------------------------------
;  40 | void main(void) {                                                      
;  41 | // Initialization routine                                              
;----------------------------------------------------------------------

;*****************************************************************************
;* FUNCTION NAME: main                                                       *
;*                                                                           *
;*   Regs Modified     : A1,A2,A3,A4,V9,SP,LR,SR,D0,D0_hi,D1,D1_hi,D2,D2_hi, *
;*                           D3,D3_hi,D4,D4_hi,D5,D5_hi,D6,D6_hi,D7,D7_hi,   *
;*                           FPEXC,FPSCR                                     *
;*   Regs Used         : A1,A2,A3,A4,V9,SP,LR,SR,D0,D0_hi,D1,D1_hi,D2,D2_hi, *
;*                           D3,D3_hi,D4,D4_hi,D5,D5_hi,D6,D6_hi,D7,D7_hi,   *
;*                           FPEXC,FPSCR                                     *
;*   Local Frame Size  : 0 Args + 0 Auto + 4 Save = 4 byte                   *
;*****************************************************************************
main:
;* --------------------------------------------------------------------------*
	.dwcfi	cfa_offset, 0
        PUSH      {A4, LR}              ; [DPU_3_PIPE] 
	.dwcfi	cfa_offset, 8
	.dwcfi	save_reg_to_mem, 14, -4
	.dwcfi	save_reg_to_mem, 3, -8
	.dwpsn	file "../GPIO.c",line 42,column 5,is_stmt,isa 1
;----------------------------------------------------------------------
;  42 | initPortF();                                                           
;----------------------------------------------------------------------
$C$DW$6	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$6, DW_AT_low_pc(0x00)
	.dwattr $C$DW$6, DW_AT_name("initPortF")
	.dwattr $C$DW$6, DW_AT_TI_call

        BL        initPortF             ; [DPU_3_PIPE] |42| 
        ; CALL OCCURS {initPortF }       ; [] |42| 
	.dwpsn	file "../GPIO.c",line 43,column 5,is_stmt,isa 1
;----------------------------------------------------------------------
;  43 | SysTick_Pulse(16000);                                                  
;----------------------------------------------------------------------
        MOV       A1, #16000            ; [DPU_3_PIPE] |43| 
$C$DW$7	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$7, DW_AT_low_pc(0x00)
	.dwattr $C$DW$7, DW_AT_name("SysTick_Pulse")
	.dwattr $C$DW$7, DW_AT_TI_call

        BL        SysTick_Pulse         ; [DPU_3_PIPE] |43| 
        ; CALL OCCURS {SysTick_Pulse }   ; [] |43| 
	.dwpsn	file "../GPIO.c",line 44,column 5,is_stmt,isa 1
;----------------------------------------------------------------------
;  44 | EnableInterrupts();                                                    
;----------------------------------------------------------------------
$C$DW$8	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$8, DW_AT_low_pc(0x00)
	.dwattr $C$DW$8, DW_AT_name("EnableInterrupts")
	.dwattr $C$DW$8, DW_AT_TI_call

        BL        EnableInterrupts      ; [DPU_3_PIPE] |44| 
        ; CALL OCCURS {EnableInterrupts }  ; [] |44| 
	.dwpsn	file "../GPIO.c",line 46,column 11,is_stmt,isa 1
;----------------------------------------------------------------------
;  46 | while(1){                                                              
;----------------------------------------------------------------------
;* --------------------------------------------------------------------------*
;*   BEGIN LOOP ||$C$L1||
;*
;*   Loop source line                : 46
;*   Loop closing brace source line  : 48
;*   Known Minimum Trip Count        : 1
;*   Known Maximum Trip Count        : 4294967295
;*   Known Max Trip Count Factor     : 1
;* --------------------------------------------------------------------------*
||$C$L1||:    
	.dwpsn	file "../GPIO.c",line 47,column 9,is_stmt,isa 1
;----------------------------------------------------------------------
;  47 | WaitForInterrupt();                                                    
;----------------------------------------------------------------------
$C$DW$9	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$9, DW_AT_low_pc(0x00)
	.dwattr $C$DW$9, DW_AT_name("WaitForInterrupt")
	.dwattr $C$DW$9, DW_AT_TI_call

        BL        WaitForInterrupt      ; [DPU_3_PIPE] |47| 
        ; CALL OCCURS {WaitForInterrupt }  ; [] |47| 
	.dwpsn	file "../GPIO.c",line 46,column 11,is_stmt,isa 1
        B         ||$C$L1||             ; [DPU_3_PIPE] |46| 
        ; BRANCH OCCURS {||$C$L1||}      ; [] |46| 
;* --------------------------------------------------------------------------*
	.dwattr $C$DW$5, DW_AT_TI_end_file("../GPIO.c")
	.dwattr $C$DW$5, DW_AT_TI_end_line(0x32)
	.dwattr $C$DW$5, DW_AT_TI_end_column(0x01)
	.dwendentry
	.dwendtag $C$DW$5

	.sect	".text"
	.clink
	.thumbfunc SysTick_Pulse
	.thumb
	.global	SysTick_Pulse

$C$DW$10	.dwtag  DW_TAG_subprogram
	.dwattr $C$DW$10, DW_AT_name("SysTick_Pulse")
	.dwattr $C$DW$10, DW_AT_low_pc(SysTick_Pulse)
	.dwattr $C$DW$10, DW_AT_high_pc(0x00)
	.dwattr $C$DW$10, DW_AT_TI_symbol_name("SysTick_Pulse")
	.dwattr $C$DW$10, DW_AT_external
	.dwattr $C$DW$10, DW_AT_TI_begin_file("../GPIO.c")
	.dwattr $C$DW$10, DW_AT_TI_begin_line(0x3a)
	.dwattr $C$DW$10, DW_AT_TI_begin_column(0x06)
	.dwattr $C$DW$10, DW_AT_decl_file("../GPIO.c")
	.dwattr $C$DW$10, DW_AT_decl_line(0x3a)
	.dwattr $C$DW$10, DW_AT_decl_column(0x06)
	.dwattr $C$DW$10, DW_AT_TI_max_frame_size(0x08)
	.dwpsn	file "../GPIO.c",line 58,column 40,is_stmt,address SysTick_Pulse,isa 1

	.dwfde $C$DW$CIE, SysTick_Pulse
$C$DW$11	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$11, DW_AT_name("param")
	.dwattr $C$DW$11, DW_AT_TI_symbol_name("param")
	.dwattr $C$DW$11, DW_AT_type(*$C$DW$T$13)
	.dwattr $C$DW$11, DW_AT_location[DW_OP_reg0]


;*****************************************************************************
;* FUNCTION NAME: SysTick_Pulse                                              *
;*                                                                           *
;*   Regs Modified     : A1,A2,SP,SR                                         *
;*   Regs Used         : A1,A2,SP,LR,SR                                      *
;*   Local Frame Size  : 0 Args + 4 Auto + 0 Save = 4 byte                   *
;*****************************************************************************
SysTick_Pulse:
;* --------------------------------------------------------------------------*
	.dwcfi	cfa_offset, 0
        SUB       SP, SP, #8            ; [DPU_3_PIPE] 
	.dwcfi	cfa_offset, 8
$C$DW$12	.dwtag  DW_TAG_variable
	.dwattr $C$DW$12, DW_AT_name("param")
	.dwattr $C$DW$12, DW_AT_TI_symbol_name("param")
	.dwattr $C$DW$12, DW_AT_type(*$C$DW$T$13)
	.dwattr $C$DW$12, DW_AT_location[DW_OP_breg13 0]

;----------------------------------------------------------------------
;  58 | void SysTick_Pulse(unsigned long param){                               
;----------------------------------------------------------------------
        STR       A1, [SP, #0]          ; [DPU_3_PIPE] |58| 
	.dwpsn	file "../GPIO.c",line 60,column 5,is_stmt,isa 1
;----------------------------------------------------------------------
;  60 | NVIC_ST_CTRL_R           =      0;                                     
;----------------------------------------------------------------------
        LDR       A2, $C$CON2           ; [DPU_3_PIPE] |60| 
        MOVS      A1, #0                ; [DPU_3_PIPE] |60| 
        STR       A1, [A2, #0]          ; [DPU_3_PIPE] |60| 
	.dwpsn	file "../GPIO.c",line 61,column 5,is_stmt,isa 1
;----------------------------------------------------------------------
;  61 | NVIC_ST_RELOAD_R         =      param - 1;                             
;----------------------------------------------------------------------
        LDR       A2, $C$CON3           ; [DPU_3_PIPE] |61| 
        LDR       A1, [SP, #0]          ; [DPU_3_PIPE] |61| 
        SUBS      A1, A1, #1            ; [DPU_3_PIPE] |61| 
        STR       A1, [A2, #0]          ; [DPU_3_PIPE] |61| 
	.dwpsn	file "../GPIO.c",line 62,column 5,is_stmt,isa 1
;----------------------------------------------------------------------
;  62 | NVIC_ST_CURRENT_R        =      0;                                     
;----------------------------------------------------------------------
        LDR       A2, $C$CON4           ; [DPU_3_PIPE] |62| 
        MOVS      A1, #0                ; [DPU_3_PIPE] |62| 
        STR       A1, [A2, #0]          ; [DPU_3_PIPE] |62| 
	.dwpsn	file "../GPIO.c",line 63,column 5,is_stmt,isa 1
;----------------------------------------------------------------------
;  63 | NVIC_SYS_PRI3_R         |=      0x50000000;                            
;----------------------------------------------------------------------
        LDR       A2, $C$CON5           ; [DPU_3_PIPE] |63| 
        LDR       A1, [A2, #0]          ; [DPU_3_PIPE] |63| 
        ORR       A1, A1, #1342177280   ; [DPU_3_PIPE] |63| 
        STR       A1, [A2, #0]          ; [DPU_3_PIPE] |63| 
	.dwpsn	file "../GPIO.c",line 64,column 5,is_stmt,isa 1
;----------------------------------------------------------------------
;  64 | NVIC_ST_CTRL_R          |=      0x07;                                  
;----------------------------------------------------------------------
        LDR       A2, $C$CON2           ; [DPU_3_PIPE] |64| 
        LDR       A1, [A2, #0]          ; [DPU_3_PIPE] |64| 
        ORR       A1, A1, #7            ; [DPU_3_PIPE] |64| 
        STR       A1, [A2, #0]          ; [DPU_3_PIPE] |64| 
	.dwpsn	file "../GPIO.c",line 67,column 1,is_stmt,isa 1
        ADD       SP, SP, #8            ; [DPU_3_PIPE] 
	.dwcfi	cfa_offset, 0
$C$DW$13	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$13, DW_AT_low_pc(0x00)
	.dwattr $C$DW$13, DW_AT_TI_return

        BX        LR                    ; [DPU_3_PIPE] 
        ; BRANCH OCCURS                  ; [] 
	.dwattr $C$DW$10, DW_AT_TI_end_file("../GPIO.c")
	.dwattr $C$DW$10, DW_AT_TI_end_line(0x43)
	.dwattr $C$DW$10, DW_AT_TI_end_column(0x01)
	.dwendentry
	.dwendtag $C$DW$10

	.sect	".text"
	.clink
	.thumbfunc initPortF
	.thumb
	.global	initPortF

$C$DW$14	.dwtag  DW_TAG_subprogram
	.dwattr $C$DW$14, DW_AT_name("initPortF")
	.dwattr $C$DW$14, DW_AT_low_pc(initPortF)
	.dwattr $C$DW$14, DW_AT_high_pc(0x00)
	.dwattr $C$DW$14, DW_AT_TI_symbol_name("initPortF")
	.dwattr $C$DW$14, DW_AT_external
	.dwattr $C$DW$14, DW_AT_TI_begin_file("../GPIO.c")
	.dwattr $C$DW$14, DW_AT_TI_begin_line(0x47)
	.dwattr $C$DW$14, DW_AT_TI_begin_column(0x06)
	.dwattr $C$DW$14, DW_AT_decl_file("../GPIO.c")
	.dwattr $C$DW$14, DW_AT_decl_line(0x47)
	.dwattr $C$DW$14, DW_AT_decl_column(0x06)
	.dwattr $C$DW$14, DW_AT_TI_max_frame_size(0x08)
	.dwpsn	file "../GPIO.c",line 71,column 21,is_stmt,address initPortF,isa 1

	.dwfde $C$DW$CIE, initPortF
;----------------------------------------------------------------------
;  71 | void initPortF(void){    unsigned long volatile delay;                 
;  73 | // Port Clock Control                                                  
;----------------------------------------------------------------------

;*****************************************************************************
;* FUNCTION NAME: initPortF                                                  *
;*                                                                           *
;*   Regs Modified     : A1,A2,A3,SP,SR                                      *
;*   Regs Used         : A1,A2,A3,SP,LR,SR                                   *
;*   Local Frame Size  : 0 Args + 4 Auto + 0 Save = 4 byte                   *
;*****************************************************************************
initPortF:
;* --------------------------------------------------------------------------*
	.dwcfi	cfa_offset, 0
        SUB       SP, SP, #8            ; [DPU_3_PIPE] 
	.dwcfi	cfa_offset, 8
$C$DW$15	.dwtag  DW_TAG_variable
	.dwattr $C$DW$15, DW_AT_name("delay")
	.dwattr $C$DW$15, DW_AT_TI_symbol_name("delay")
	.dwattr $C$DW$15, DW_AT_type(*$C$DW$T$24)
	.dwattr $C$DW$15, DW_AT_location[DW_OP_breg13 0]

	.dwpsn	file "../GPIO.c",line 74,column 5,is_stmt,isa 1
;----------------------------------------------------------------------
;  74 | SYSCTL_RCGC2_R          |=      0x00000020;                            
;----------------------------------------------------------------------
        LDR       A2, $C$CON6           ; [DPU_3_PIPE] |74| 
        LDR       A1, [A2, #0]          ; [DPU_3_PIPE] |74| 
        ORR       A1, A1, #32           ; [DPU_3_PIPE] |74| 
        STR       A1, [A2, #0]          ; [DPU_3_PIPE] |74| 
	.dwpsn	file "../GPIO.c",line 75,column 5,is_stmt,isa 1
;----------------------------------------------------------------------
;  75 | delay  /*Wait Ready*/    =      SYSCTL_RCGC2_R;                        
;  77 | // GPIO Digital Control                                                
;----------------------------------------------------------------------
        LDR       A1, $C$CON6           ; [DPU_3_PIPE] |75| 
        LDR       A1, [A1, #0]          ; [DPU_3_PIPE] |75| 
        STR       A1, [SP, #0]          ; [DPU_3_PIPE] |75| 
	.dwpsn	file "../GPIO.c",line 78,column 5,is_stmt,isa 1
;----------------------------------------------------------------------
;  78 | GPIO_PORTF_DEN_R        |=      0x0E;                                  
;----------------------------------------------------------------------
        LDR       A2, $C$CON7           ; [DPU_3_PIPE] |78| 
        LDR       A1, [A2, #0]          ; [DPU_3_PIPE] |78| 
        ORR       A1, A1, #14           ; [DPU_3_PIPE] |78| 
        STR       A1, [A2, #0]          ; [DPU_3_PIPE] |78| 
	.dwpsn	file "../GPIO.c",line 79,column 5,is_stmt,isa 1
;----------------------------------------------------------------------
;  79 | GPIO_PORTF_DIR_R        |=      0x0E;                                  
;  81 | // GPIO Alternate function control                                     
;----------------------------------------------------------------------
        LDR       A2, $C$CON8           ; [DPU_3_PIPE] |79| 
        LDR       A1, [A2, #0]          ; [DPU_3_PIPE] |79| 
        ORR       A1, A1, #14           ; [DPU_3_PIPE] |79| 
        STR       A1, [A2, #0]          ; [DPU_3_PIPE] |79| 
	.dwpsn	file "../GPIO.c",line 82,column 5,is_stmt,isa 1
;----------------------------------------------------------------------
;  82 | GPIO_PORTF_AMSEL_R      &=      0;                                     
;----------------------------------------------------------------------
        LDR       A1, $C$CON9           ; [DPU_3_PIPE] |82| 
        MOVS      A2, #0                ; [DPU_3_PIPE] |82| 
        LDR       A3, [A1, #0]          ; [DPU_3_PIPE] |82| 
        STR       A2, [A1, #0]          ; [DPU_3_PIPE] |82| 
	.dwpsn	file "../GPIO.c",line 83,column 5,is_stmt,isa 1
;----------------------------------------------------------------------
;  83 | GPIO_PORTF_AFSEL_R      &=      ~0x0E;                                 
;----------------------------------------------------------------------
        LDR       A2, $C$CON10          ; [DPU_3_PIPE] |83| 
        LDR       A1, [A2, #0]          ; [DPU_3_PIPE] |83| 
        BIC       A1, A1, #14           ; [DPU_3_PIPE] |83| 
        STR       A1, [A2, #0]          ; [DPU_3_PIPE] |83| 
	.dwpsn	file "../GPIO.c",line 84,column 5,is_stmt,isa 1
;----------------------------------------------------------------------
;  84 | GPIO_PORTF_PCTL_R       &=      ~0x0000FFF0;                           
;----------------------------------------------------------------------
        LDR       A2, $C$CON11          ; [DPU_3_PIPE] |84| 
        LDR       A1, [A2, #0]          ; [DPU_3_PIPE] |84| 
        BFC       A1, #4, #12           ; [DPU_3_PIPE] |84| 
        STR       A1, [A2, #0]          ; [DPU_3_PIPE] |84| 
	.dwpsn	file "../GPIO.c",line 85,column 1,is_stmt,isa 1
        ADD       SP, SP, #8            ; [DPU_3_PIPE] 
	.dwcfi	cfa_offset, 0
$C$DW$16	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$16, DW_AT_low_pc(0x00)
	.dwattr $C$DW$16, DW_AT_TI_return

        BX        LR                    ; [DPU_3_PIPE] 
        ; BRANCH OCCURS                  ; [] 
	.dwattr $C$DW$14, DW_AT_TI_end_file("../GPIO.c")
	.dwattr $C$DW$14, DW_AT_TI_end_line(0x55)
	.dwattr $C$DW$14, DW_AT_TI_end_column(0x01)
	.dwendentry
	.dwendtag $C$DW$14

	.sect	".text"
	.clink
	.thumbfunc delay
	.thumb
	.global	delay

$C$DW$17	.dwtag  DW_TAG_subprogram
	.dwattr $C$DW$17, DW_AT_name("delay")
	.dwattr $C$DW$17, DW_AT_low_pc(delay)
	.dwattr $C$DW$17, DW_AT_high_pc(0x00)
	.dwattr $C$DW$17, DW_AT_TI_symbol_name("delay")
	.dwattr $C$DW$17, DW_AT_external
	.dwattr $C$DW$17, DW_AT_TI_begin_file("../GPIO.c")
	.dwattr $C$DW$17, DW_AT_TI_begin_line(0x58)
	.dwattr $C$DW$17, DW_AT_TI_begin_column(0x06)
	.dwattr $C$DW$17, DW_AT_decl_file("../GPIO.c")
	.dwattr $C$DW$17, DW_AT_decl_line(0x58)
	.dwattr $C$DW$17, DW_AT_decl_column(0x06)
	.dwattr $C$DW$17, DW_AT_TI_max_frame_size(0x10)
	.dwpsn	file "../GPIO.c",line 88,column 31,is_stmt,address delay,isa 1

	.dwfde $C$DW$CIE, delay
$C$DW$18	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$18, DW_AT_name("param")
	.dwattr $C$DW$18, DW_AT_TI_symbol_name("param")
	.dwattr $C$DW$18, DW_AT_type(*$C$DW$T$11)
	.dwattr $C$DW$18, DW_AT_location[DW_OP_reg0]


;*****************************************************************************
;* FUNCTION NAME: delay                                                      *
;*                                                                           *
;*   Regs Modified     : A1,A2,SP,SR                                         *
;*   Regs Used         : A1,A2,SP,LR,SR                                      *
;*   Local Frame Size  : 0 Args + 12 Auto + 0 Save = 12 byte                 *
;*****************************************************************************
delay:
;* --------------------------------------------------------------------------*
	.dwcfi	cfa_offset, 0
        SUB       SP, SP, #16           ; [DPU_3_PIPE] 
	.dwcfi	cfa_offset, 16
$C$DW$19	.dwtag  DW_TAG_variable
	.dwattr $C$DW$19, DW_AT_name("param")
	.dwattr $C$DW$19, DW_AT_TI_symbol_name("param")
	.dwattr $C$DW$19, DW_AT_type(*$C$DW$T$11)
	.dwattr $C$DW$19, DW_AT_location[DW_OP_breg13 0]

$C$DW$20	.dwtag  DW_TAG_variable
	.dwattr $C$DW$20, DW_AT_name("i")
	.dwattr $C$DW$20, DW_AT_TI_symbol_name("i")
	.dwattr $C$DW$20, DW_AT_type(*$C$DW$T$11)
	.dwattr $C$DW$20, DW_AT_location[DW_OP_breg13 4]

$C$DW$21	.dwtag  DW_TAG_variable
	.dwattr $C$DW$21, DW_AT_name("j")
	.dwattr $C$DW$21, DW_AT_TI_symbol_name("j")
	.dwattr $C$DW$21, DW_AT_type(*$C$DW$T$11)
	.dwattr $C$DW$21, DW_AT_location[DW_OP_breg13 8]

;----------------------------------------------------------------------
;  88 | void delay(unsigned int param){ unsigned int i, j;                     
;----------------------------------------------------------------------
        STR       A1, [SP, #0]          ; [DPU_3_PIPE] |88| 
	.dwpsn	file "../GPIO.c",line 90,column 9,is_stmt,isa 1
;----------------------------------------------------------------------
;  90 | for(j = 0; j < param; j++){                                            
;----------------------------------------------------------------------
        MOVS      A1, #0                ; [DPU_3_PIPE] |90| 
        STR       A1, [SP, #8]          ; [DPU_3_PIPE] |90| 
	.dwpsn	file "../GPIO.c",line 90,column 16,is_stmt,isa 1
        LDR       A2, [SP, #8]          ; [DPU_3_PIPE] |90| 
        LDR       A1, [SP, #0]          ; [DPU_3_PIPE] |90| 
        CMP       A1, A2                ; [DPU_3_PIPE] |90| 
        BLS       ||$C$L5||             ; [DPU_3_PIPE] |90| 
        ; BRANCHCC OCCURS {||$C$L5||}    ; [] |90| 
;* --------------------------------------------------------------------------*
;*   BEGIN LOOP ||$C$L2||
;*
;*   Loop source line                : 90
;*   Loop closing brace source line  : 94
;*   Known Minimum Trip Count        : 1
;*   Known Maximum Trip Count        : 4294967295
;*   Known Max Trip Count Factor     : 1
;* --------------------------------------------------------------------------*
||$C$L2||:    
	.dwpsn	file "../GPIO.c",line 91,column 13,is_stmt,isa 1
;----------------------------------------------------------------------
;  91 | for(i = 0; i < 800; i++){                                              
;----------------------------------------------------------------------
        MOVS      A1, #0                ; [DPU_3_PIPE] |91| 
        STR       A1, [SP, #4]          ; [DPU_3_PIPE] |91| 
	.dwpsn	file "../GPIO.c",line 91,column 20,is_stmt,isa 1
;----------------------------------------------------------------------
;  92 | // do nothing                                                          
;----------------------------------------------------------------------
        LDR       A1, [SP, #4]          ; [DPU_3_PIPE] |91| 
        CMP       A1, #800              ; [DPU_3_PIPE] |91| 
        BCS       ||$C$L4||             ; [DPU_3_PIPE] |91| 
        ; BRANCHCC OCCURS {||$C$L4||}    ; [] |91| 
;* --------------------------------------------------------------------------*
;*   BEGIN LOOP ||$C$L3||
;*
;*   Loop source line                : 91
;*   Loop closing brace source line  : 93
;*   Known Minimum Trip Count        : 1
;*   Known Maximum Trip Count        : 4294967295
;*   Known Max Trip Count Factor     : 1
;* --------------------------------------------------------------------------*
||$C$L3||:    
	.dwpsn	file "../GPIO.c",line 91,column 29,is_stmt,isa 1
        LDR       A1, [SP, #4]          ; [DPU_3_PIPE] |91| 
        ADDS      A1, A1, #1            ; [DPU_3_PIPE] |91| 
        STR       A1, [SP, #4]          ; [DPU_3_PIPE] |91| 
	.dwpsn	file "../GPIO.c",line 91,column 20,is_stmt,isa 1
        LDR       A1, [SP, #4]          ; [DPU_3_PIPE] |91| 
        CMP       A1, #800              ; [DPU_3_PIPE] |91| 
        BCC       ||$C$L3||             ; [DPU_3_PIPE] |91| 
        ; BRANCHCC OCCURS {||$C$L3||}    ; [] |91| 
;* --------------------------------------------------------------------------*
||$C$L4||:    
	.dwpsn	file "../GPIO.c",line 90,column 27,is_stmt,isa 1
        LDR       A1, [SP, #8]          ; [DPU_3_PIPE] |90| 
        ADDS      A1, A1, #1            ; [DPU_3_PIPE] |90| 
        STR       A1, [SP, #8]          ; [DPU_3_PIPE] |90| 
	.dwpsn	file "../GPIO.c",line 90,column 16,is_stmt,isa 1
        LDR       A1, [SP, #0]          ; [DPU_3_PIPE] |90| 
        LDR       A2, [SP, #8]          ; [DPU_3_PIPE] |90| 
        CMP       A1, A2                ; [DPU_3_PIPE] |90| 
        BHI       ||$C$L2||             ; [DPU_3_PIPE] |90| 
        ; BRANCHCC OCCURS {||$C$L2||}    ; [] |90| 
;* --------------------------------------------------------------------------*
	.dwpsn	file "../GPIO.c",line 95,column 1,is_stmt,isa 1
;* --------------------------------------------------------------------------*
||$C$L5||:    
        ADD       SP, SP, #16           ; [DPU_3_PIPE] 
	.dwcfi	cfa_offset, 0
$C$DW$22	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$22, DW_AT_low_pc(0x00)
	.dwattr $C$DW$22, DW_AT_TI_return

        BX        LR                    ; [DPU_3_PIPE] 
        ; BRANCH OCCURS                  ; [] 
	.dwattr $C$DW$17, DW_AT_TI_end_file("../GPIO.c")
	.dwattr $C$DW$17, DW_AT_TI_end_line(0x5f)
	.dwattr $C$DW$17, DW_AT_TI_end_column(0x01)
	.dwendentry
	.dwendtag $C$DW$17

;******************************************************************************
;* CONSTANT TABLE                                                             *
;******************************************************************************
	.sect	".text"
	.align	4
||$C$CON1||:	.bits	1073894396,32
	.align	4
||$C$CON2||:	.bits	-536813552,32
	.align	4
||$C$CON3||:	.bits	-536813548,32
	.align	4
||$C$CON4||:	.bits	-536813544,32
	.align	4
||$C$CON5||:	.bits	-536810208,32
	.align	4
||$C$CON6||:	.bits	1074782472,32
	.align	4
||$C$CON7||:	.bits	1073894684,32
	.align	4
||$C$CON8||:	.bits	1073894400,32
	.align	4
||$C$CON9||:	.bits	1073894696,32
	.align	4
||$C$CON10||:	.bits	1073894432,32
	.align	4
||$C$CON11||:	.bits	1073894700,32
;*****************************************************************************
;* UNDEFINED EXTERNAL REFERENCES                                             *
;*****************************************************************************
	.global	EnableInterrupts
	.global	WaitForInterrupt

;******************************************************************************
;* BUILD ATTRIBUTES                                                           *
;******************************************************************************
	.battr "aeabi", Tag_File, 1, Tag_ABI_PCS_wchar_t(2)
	.battr "aeabi", Tag_File, 1, Tag_ABI_FP_rounding(0)
	.battr "aeabi", Tag_File, 1, Tag_ABI_FP_denormal(0)
	.battr "aeabi", Tag_File, 1, Tag_ABI_FP_exceptions(0)
	.battr "aeabi", Tag_File, 1, Tag_ABI_FP_number_model(1)
	.battr "aeabi", Tag_File, 1, Tag_ABI_enum_size(0)
	.battr "aeabi", Tag_File, 1, Tag_ABI_optimization_goals(5)
	.battr "aeabi", Tag_File, 1, Tag_ABI_FP_optimization_goals(0)
	.battr "TI", Tag_File, 1, Tag_Bitfield_layout(2)
	.battr "aeabi", Tag_File, 1, Tag_ABI_VFP_args(3)
	.battr "TI", Tag_File, 1, Tag_FP_interface(1)

;******************************************************************************
;* TYPE INFORMATION                                                           *
;******************************************************************************
$C$DW$T$2	.dwtag  DW_TAG_unspecified_type
	.dwattr $C$DW$T$2, DW_AT_name("void")

$C$DW$T$4	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$4, DW_AT_encoding(DW_ATE_boolean)
	.dwattr $C$DW$T$4, DW_AT_name("bool")
	.dwattr $C$DW$T$4, DW_AT_byte_size(0x01)

$C$DW$T$5	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$5, DW_AT_encoding(DW_ATE_signed_char)
	.dwattr $C$DW$T$5, DW_AT_name("signed char")
	.dwattr $C$DW$T$5, DW_AT_byte_size(0x01)

$C$DW$T$6	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$6, DW_AT_encoding(DW_ATE_unsigned_char)
	.dwattr $C$DW$T$6, DW_AT_name("unsigned char")
	.dwattr $C$DW$T$6, DW_AT_byte_size(0x01)

$C$DW$T$7	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$7, DW_AT_encoding(DW_ATE_signed_char)
	.dwattr $C$DW$T$7, DW_AT_name("wchar_t")
	.dwattr $C$DW$T$7, DW_AT_byte_size(0x02)

$C$DW$T$8	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$8, DW_AT_encoding(DW_ATE_signed)
	.dwattr $C$DW$T$8, DW_AT_name("short")
	.dwattr $C$DW$T$8, DW_AT_byte_size(0x02)

$C$DW$T$9	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$9, DW_AT_encoding(DW_ATE_unsigned)
	.dwattr $C$DW$T$9, DW_AT_name("unsigned short")
	.dwattr $C$DW$T$9, DW_AT_byte_size(0x02)

$C$DW$T$10	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$10, DW_AT_encoding(DW_ATE_signed)
	.dwattr $C$DW$T$10, DW_AT_name("int")
	.dwattr $C$DW$T$10, DW_AT_byte_size(0x04)

$C$DW$T$11	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$11, DW_AT_encoding(DW_ATE_unsigned)
	.dwattr $C$DW$T$11, DW_AT_name("unsigned int")
	.dwattr $C$DW$T$11, DW_AT_byte_size(0x04)

$C$DW$T$12	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$12, DW_AT_encoding(DW_ATE_signed)
	.dwattr $C$DW$T$12, DW_AT_name("long")
	.dwattr $C$DW$T$12, DW_AT_byte_size(0x04)

$C$DW$T$13	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$13, DW_AT_encoding(DW_ATE_unsigned)
	.dwattr $C$DW$T$13, DW_AT_name("unsigned long")
	.dwattr $C$DW$T$13, DW_AT_byte_size(0x04)

$C$DW$T$24	.dwtag  DW_TAG_volatile_type
	.dwattr $C$DW$T$24, DW_AT_type(*$C$DW$T$13)

$C$DW$T$14	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$14, DW_AT_encoding(DW_ATE_signed)
	.dwattr $C$DW$T$14, DW_AT_name("long long")
	.dwattr $C$DW$T$14, DW_AT_byte_size(0x08)

$C$DW$T$15	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$15, DW_AT_encoding(DW_ATE_unsigned)
	.dwattr $C$DW$T$15, DW_AT_name("unsigned long long")
	.dwattr $C$DW$T$15, DW_AT_byte_size(0x08)

$C$DW$T$16	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$16, DW_AT_encoding(DW_ATE_float)
	.dwattr $C$DW$T$16, DW_AT_name("float")
	.dwattr $C$DW$T$16, DW_AT_byte_size(0x04)

$C$DW$T$17	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$17, DW_AT_encoding(DW_ATE_float)
	.dwattr $C$DW$T$17, DW_AT_name("double")
	.dwattr $C$DW$T$17, DW_AT_byte_size(0x08)

$C$DW$T$18	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$18, DW_AT_encoding(DW_ATE_float)
	.dwattr $C$DW$T$18, DW_AT_name("long double")
	.dwattr $C$DW$T$18, DW_AT_byte_size(0x08)

	.dwattr $C$DW$CU, DW_AT_language(DW_LANG_C)

;***************************************************************
;* DWARF CIE ENTRIES                                           *
;***************************************************************

$C$DW$CIE	.dwcie 14
	.dwcfi	cfa_register, 13
	.dwcfi	cfa_offset, 0
	.dwcfi	same_value, 4
	.dwcfi	same_value, 5
	.dwcfi	same_value, 6
	.dwcfi	same_value, 7
	.dwcfi	same_value, 8
	.dwcfi	same_value, 9
	.dwcfi	same_value, 10
	.dwcfi	same_value, 11
	.dwcfi	same_value, 80
	.dwcfi	same_value, 81
	.dwcfi	same_value, 82
	.dwcfi	same_value, 83
	.dwcfi	same_value, 84
	.dwcfi	same_value, 85
	.dwcfi	same_value, 86
	.dwcfi	same_value, 87
	.dwcfi	same_value, 88
	.dwcfi	same_value, 89
	.dwcfi	same_value, 90
	.dwcfi	same_value, 91
	.dwcfi	same_value, 92
	.dwcfi	same_value, 93
	.dwcfi	same_value, 94
	.dwcfi	same_value, 95
	.dwendentry
	.dwendtag $C$DW$CU

