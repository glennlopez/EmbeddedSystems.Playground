;******************************************************************************
;* TI ARM C/C++ Codegen                                        PC v16.9.0.LTS *
;* Date/Time created: Thu Mar 09 23:32:21 2017                                *
;******************************************************************************
	.compiler_opts --abi=eabi --arm_vmrs_si_workaround=off --code_state=16 --diag_wrap=off --embedded_constants=on --endian=little --float_support=FPv4SPD16 --hll_source=on --object_format=elf --silicon_version=7M4 --symdebug:dwarf --symdebug:dwarf_version=3 --unaligned_access=on 
	.thumb

$C$DW$CU	.dwtag  DW_TAG_compile_unit
	.dwattr $C$DW$CU, DW_AT_name("../SysTick.c")
	.dwattr $C$DW$CU, DW_AT_producer("TI TI ARM C/C++ Codegen PC v16.9.0.LTS Copyright (c) 1996-2015 Texas Instruments Incorporated")
	.dwattr $C$DW$CU, DW_AT_TI_version(0x01)
	.dwattr $C$DW$CU, DW_AT_comp_dir("D:\Github Clones\EmbeddedSystems.Playground\Texas Instruments\TM4C123G\Sandbox\GPIO_4C123\Debug")
;	D:\EngineeringSoftware\CCS\ccsv7\tools\compiler\ti-cgt-arm_16.9.0.LTS\bin\armacpia.exe -@C:\\Users\\Glenn\\AppData\\Local\\Temp\\0939212 
	.sect	".text"
	.clink
	.thumbfunc SysTick_Init
	.thumb
	.global	SysTick_Init

$C$DW$1	.dwtag  DW_TAG_subprogram
	.dwattr $C$DW$1, DW_AT_name("SysTick_Init")
	.dwattr $C$DW$1, DW_AT_low_pc(SysTick_Init)
	.dwattr $C$DW$1, DW_AT_high_pc(0x00)
	.dwattr $C$DW$1, DW_AT_TI_symbol_name("SysTick_Init")
	.dwattr $C$DW$1, DW_AT_external
	.dwattr $C$DW$1, DW_AT_TI_begin_file("../SysTick.c")
	.dwattr $C$DW$1, DW_AT_TI_begin_line(0x2a)
	.dwattr $C$DW$1, DW_AT_TI_begin_column(0x06)
	.dwattr $C$DW$1, DW_AT_decl_file("../SysTick.c")
	.dwattr $C$DW$1, DW_AT_decl_line(0x2a)
	.dwattr $C$DW$1, DW_AT_decl_column(0x06)
	.dwattr $C$DW$1, DW_AT_TI_max_frame_size(0x00)
	.dwpsn	file "../SysTick.c",line 42,column 24,is_stmt,address SysTick_Init,isa 1

	.dwfde $C$DW$CIE, SysTick_Init
;----------------------------------------------------------------------
;  42 | void SysTick_Init(void){                                               
;----------------------------------------------------------------------

;*****************************************************************************
;* FUNCTION NAME: SysTick_Init                                               *
;*                                                                           *
;*   Regs Modified     : A1,A2,SR                                            *
;*   Regs Used         : A1,A2,LR,SR                                         *
;*   Local Frame Size  : 0 Args + 0 Auto + 0 Save = 0 byte                   *
;*****************************************************************************
SysTick_Init:
;* --------------------------------------------------------------------------*
	.dwcfi	cfa_offset, 0
	.dwpsn	file "../SysTick.c",line 43,column 3,is_stmt,isa 1
;----------------------------------------------------------------------
;  43 | NVIC_ST_CTRL_R = 0;                   // disable SysTick during setup  
;----------------------------------------------------------------------
        LDR       A2, $C$CON1           ; [DPU_3_PIPE] |43| 
        MOVS      A1, #0                ; [DPU_3_PIPE] |43| 
        STR       A1, [A2, #0]          ; [DPU_3_PIPE] |43| 
	.dwpsn	file "../SysTick.c",line 44,column 3,is_stmt,isa 1
;----------------------------------------------------------------------
;  44 | NVIC_ST_RELOAD_R = NVIC_ST_RELOAD_M;  // maximum reload value          
;----------------------------------------------------------------------
        LDR       A2, $C$CON2           ; [DPU_3_PIPE] |44| 
        MVN       A1, #-16777216        ; [DPU_3_PIPE] |44| 
        STR       A1, [A2, #0]          ; [DPU_3_PIPE] |44| 
	.dwpsn	file "../SysTick.c",line 45,column 3,is_stmt,isa 1
;----------------------------------------------------------------------
;  45 | NVIC_ST_CURRENT_R = 0;                // any write to current clears it
;  46 |                                       // enable SysTick with core clock
;----------------------------------------------------------------------
        LDR       A2, $C$CON3           ; [DPU_3_PIPE] |45| 
        MOVS      A1, #0                ; [DPU_3_PIPE] |45| 
        STR       A1, [A2, #0]          ; [DPU_3_PIPE] |45| 
	.dwpsn	file "../SysTick.c",line 47,column 3,is_stmt,isa 1
;----------------------------------------------------------------------
;  47 | NVIC_ST_CTRL_R = NVIC_ST_CTRL_ENABLE+NVIC_ST_CTRL_CLK_SRC;             
;----------------------------------------------------------------------
        LDR       A2, $C$CON1           ; [DPU_3_PIPE] |47| 
        MOVS      A1, #5                ; [DPU_3_PIPE] |47| 
        STR       A1, [A2, #0]          ; [DPU_3_PIPE] |47| 
	.dwpsn	file "../SysTick.c",line 48,column 1,is_stmt,isa 1
$C$DW$2	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$2, DW_AT_low_pc(0x00)
	.dwattr $C$DW$2, DW_AT_TI_return

        BX        LR                    ; [DPU_3_PIPE] 
        ; BRANCH OCCURS                  ; [] 
	.dwattr $C$DW$1, DW_AT_TI_end_file("../SysTick.c")
	.dwattr $C$DW$1, DW_AT_TI_end_line(0x30)
	.dwattr $C$DW$1, DW_AT_TI_end_column(0x01)
	.dwendentry
	.dwendtag $C$DW$1

	.sect	".text"
	.clink
	.thumbfunc SysTick_Wait
	.thumb
	.global	SysTick_Wait

$C$DW$3	.dwtag  DW_TAG_subprogram
	.dwattr $C$DW$3, DW_AT_name("SysTick_Wait")
	.dwattr $C$DW$3, DW_AT_low_pc(SysTick_Wait)
	.dwattr $C$DW$3, DW_AT_high_pc(0x00)
	.dwattr $C$DW$3, DW_AT_TI_symbol_name("SysTick_Wait")
	.dwattr $C$DW$3, DW_AT_external
	.dwattr $C$DW$3, DW_AT_TI_begin_file("../SysTick.c")
	.dwattr $C$DW$3, DW_AT_TI_begin_line(0x33)
	.dwattr $C$DW$3, DW_AT_TI_begin_column(0x06)
	.dwattr $C$DW$3, DW_AT_decl_file("../SysTick.c")
	.dwattr $C$DW$3, DW_AT_decl_line(0x33)
	.dwattr $C$DW$3, DW_AT_decl_column(0x06)
	.dwattr $C$DW$3, DW_AT_TI_max_frame_size(0x10)
	.dwpsn	file "../SysTick.c",line 51,column 34,is_stmt,address SysTick_Wait,isa 1

	.dwfde $C$DW$CIE, SysTick_Wait
$C$DW$4	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$4, DW_AT_name("delay")
	.dwattr $C$DW$4, DW_AT_TI_symbol_name("delay")
	.dwattr $C$DW$4, DW_AT_type(*$C$DW$T$20)
	.dwattr $C$DW$4, DW_AT_location[DW_OP_reg0]


;*****************************************************************************
;* FUNCTION NAME: SysTick_Wait                                               *
;*                                                                           *
;*   Regs Modified     : A1,A2,SP,SR                                         *
;*   Regs Used         : A1,A2,SP,LR,SR                                      *
;*   Local Frame Size  : 0 Args + 12 Auto + 0 Save = 12 byte                 *
;*****************************************************************************
SysTick_Wait:
;* --------------------------------------------------------------------------*
	.dwcfi	cfa_offset, 0
        SUB       SP, SP, #16           ; [DPU_3_PIPE] 
	.dwcfi	cfa_offset, 16
$C$DW$5	.dwtag  DW_TAG_variable
	.dwattr $C$DW$5, DW_AT_name("delay")
	.dwattr $C$DW$5, DW_AT_TI_symbol_name("delay")
	.dwattr $C$DW$5, DW_AT_type(*$C$DW$T$20)
	.dwattr $C$DW$5, DW_AT_location[DW_OP_breg13 0]

$C$DW$6	.dwtag  DW_TAG_variable
	.dwattr $C$DW$6, DW_AT_name("elapsedTime")
	.dwattr $C$DW$6, DW_AT_TI_symbol_name("elapsedTime")
	.dwattr $C$DW$6, DW_AT_type(*$C$DW$T$37)
	.dwattr $C$DW$6, DW_AT_location[DW_OP_breg13 4]

$C$DW$7	.dwtag  DW_TAG_variable
	.dwattr $C$DW$7, DW_AT_name("startTime")
	.dwattr $C$DW$7, DW_AT_TI_symbol_name("startTime")
	.dwattr $C$DW$7, DW_AT_type(*$C$DW$T$20)
	.dwattr $C$DW$7, DW_AT_location[DW_OP_breg13 8]

;----------------------------------------------------------------------
;  51 | void SysTick_Wait(uint32_t delay){                                     
;  52 | volatile uint32_t elapsedTime;                                         
;----------------------------------------------------------------------
        STR       A1, [SP, #0]          ; [DPU_3_PIPE] |51| 
	.dwpsn	file "../SysTick.c",line 53,column 22,is_stmt,isa 1
;----------------------------------------------------------------------
;  53 | uint32_t startTime = NVIC_ST_CURRENT_R;                                
;  54 | do{                                                                    
;----------------------------------------------------------------------
        LDR       A1, $C$CON3           ; [DPU_3_PIPE] |53| 
        LDR       A1, [A1, #0]          ; [DPU_3_PIPE] |53| 
        STR       A1, [SP, #8]          ; [DPU_3_PIPE] |53| 
;* --------------------------------------------------------------------------*
;*   BEGIN LOOP ||$C$L1||
;*
;*   Loop source line                : 54
;*   Loop closing brace source line  : 56
;*   Known Minimum Trip Count        : 1
;*   Known Maximum Trip Count        : 4294967295
;*   Known Max Trip Count Factor     : 1
;* --------------------------------------------------------------------------*
||$C$L1||:    
	.dwpsn	file "../SysTick.c",line 55,column 5,is_stmt,isa 1
;----------------------------------------------------------------------
;  55 | elapsedTime = (startTime-NVIC_ST_CURRENT_R)&0x00FFFFFF;                
;----------------------------------------------------------------------
        LDR       A2, $C$CON3           ; [DPU_3_PIPE] |55| 
        LDR       A1, [SP, #8]          ; [DPU_3_PIPE] |55| 
        LDR       A2, [A2, #0]          ; [DPU_3_PIPE] |55| 
        SUBS      A1, A1, A2            ; [DPU_3_PIPE] |55| 
        BIC       A1, A1, #-16777216    ; [DPU_3_PIPE] |55| 
        STR       A1, [SP, #4]          ; [DPU_3_PIPE] |55| 
	.dwpsn	file "../SysTick.c",line 57,column 9,is_stmt,isa 1
;----------------------------------------------------------------------
;  57 | while(elapsedTime <= delay);                                           
;----------------------------------------------------------------------
        LDR       A1, [SP, #0]          ; [DPU_3_PIPE] |57| 
        LDR       A2, [SP, #4]          ; [DPU_3_PIPE] |57| 
        CMP       A1, A2                ; [DPU_3_PIPE] |57| 
        BCS       ||$C$L1||             ; [DPU_3_PIPE] |57| 
        ; BRANCHCC OCCURS {||$C$L1||}    ; [] |57| 
;* --------------------------------------------------------------------------*
	.dwpsn	file "../SysTick.c",line 58,column 1,is_stmt,isa 1
        ADD       SP, SP, #16           ; [DPU_3_PIPE] 
	.dwcfi	cfa_offset, 0
$C$DW$8	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$8, DW_AT_low_pc(0x00)
	.dwattr $C$DW$8, DW_AT_TI_return

        BX        LR                    ; [DPU_3_PIPE] 
        ; BRANCH OCCURS                  ; [] 
	.dwattr $C$DW$3, DW_AT_TI_end_file("../SysTick.c")
	.dwattr $C$DW$3, DW_AT_TI_end_line(0x3a)
	.dwattr $C$DW$3, DW_AT_TI_end_column(0x01)
	.dwendentry
	.dwendtag $C$DW$3

	.sect	".text"
	.clink
	.thumbfunc SysTick_Wait10ms
	.thumb
	.global	SysTick_Wait10ms

$C$DW$9	.dwtag  DW_TAG_subprogram
	.dwattr $C$DW$9, DW_AT_name("SysTick_Wait10ms")
	.dwattr $C$DW$9, DW_AT_low_pc(SysTick_Wait10ms)
	.dwattr $C$DW$9, DW_AT_high_pc(0x00)
	.dwattr $C$DW$9, DW_AT_TI_symbol_name("SysTick_Wait10ms")
	.dwattr $C$DW$9, DW_AT_external
	.dwattr $C$DW$9, DW_AT_TI_begin_file("../SysTick.c")
	.dwattr $C$DW$9, DW_AT_TI_begin_line(0x3d)
	.dwattr $C$DW$9, DW_AT_TI_begin_column(0x06)
	.dwattr $C$DW$9, DW_AT_decl_file("../SysTick.c")
	.dwattr $C$DW$9, DW_AT_decl_line(0x3d)
	.dwattr $C$DW$9, DW_AT_decl_column(0x06)
	.dwattr $C$DW$9, DW_AT_TI_max_frame_size(0x10)
	.dwpsn	file "../SysTick.c",line 61,column 38,is_stmt,address SysTick_Wait10ms,isa 1

	.dwfde $C$DW$CIE, SysTick_Wait10ms
$C$DW$10	.dwtag  DW_TAG_formal_parameter
	.dwattr $C$DW$10, DW_AT_name("delay")
	.dwattr $C$DW$10, DW_AT_TI_symbol_name("delay")
	.dwattr $C$DW$10, DW_AT_type(*$C$DW$T$20)
	.dwattr $C$DW$10, DW_AT_location[DW_OP_reg0]


;*****************************************************************************
;* FUNCTION NAME: SysTick_Wait10ms                                           *
;*                                                                           *
;*   Regs Modified     : A1,A2,A3,A4,SP,LR,SR,FPEXC,FPSCR                    *
;*   Regs Used         : A1,A2,A3,A4,SP,LR,SR,FPEXC,FPSCR                    *
;*   Local Frame Size  : 0 Args + 8 Auto + 4 Save = 12 byte                  *
;*****************************************************************************
SysTick_Wait10ms:
;* --------------------------------------------------------------------------*
	.dwcfi	cfa_offset, 0
        PUSH      {A2, A3, A4, LR}      ; [DPU_3_PIPE] 
	.dwcfi	cfa_offset, 16
	.dwcfi	save_reg_to_mem, 14, -4
	.dwcfi	save_reg_to_mem, 3, -8
	.dwcfi	save_reg_to_mem, 2, -12
	.dwcfi	save_reg_to_mem, 1, -16
$C$DW$11	.dwtag  DW_TAG_variable
	.dwattr $C$DW$11, DW_AT_name("delay")
	.dwattr $C$DW$11, DW_AT_TI_symbol_name("delay")
	.dwattr $C$DW$11, DW_AT_type(*$C$DW$T$20)
	.dwattr $C$DW$11, DW_AT_location[DW_OP_breg13 0]

$C$DW$12	.dwtag  DW_TAG_variable
	.dwattr $C$DW$12, DW_AT_name("i")
	.dwattr $C$DW$12, DW_AT_TI_symbol_name("i")
	.dwattr $C$DW$12, DW_AT_type(*$C$DW$T$20)
	.dwattr $C$DW$12, DW_AT_location[DW_OP_breg13 4]

;----------------------------------------------------------------------
;  61 | void SysTick_Wait10ms(uint32_t delay){                                 
;  62 | uint32_t i;                                                            
;----------------------------------------------------------------------
        STR       A1, [SP, #0]          ; [DPU_3_PIPE] |61| 
	.dwpsn	file "../SysTick.c",line 63,column 7,is_stmt,isa 1
;----------------------------------------------------------------------
;  63 | for(i=0; i<delay; i++){                                                
;----------------------------------------------------------------------
        MOVS      A1, #0                ; [DPU_3_PIPE] |63| 
        STR       A1, [SP, #4]          ; [DPU_3_PIPE] |63| 
	.dwpsn	file "../SysTick.c",line 63,column 12,is_stmt,isa 1
        LDR       A2, [SP, #4]          ; [DPU_3_PIPE] |63| 
        LDR       A1, [SP, #0]          ; [DPU_3_PIPE] |63| 
        CMP       A1, A2                ; [DPU_3_PIPE] |63| 
        BLS       ||$C$L3||             ; [DPU_3_PIPE] |63| 
        ; BRANCHCC OCCURS {||$C$L3||}    ; [] |63| 
;* --------------------------------------------------------------------------*
;*   BEGIN LOOP ||$C$L2||
;*
;*   Loop source line                : 63
;*   Loop closing brace source line  : 65
;*   Known Minimum Trip Count        : 1
;*   Known Maximum Trip Count        : 4294967295
;*   Known Max Trip Count Factor     : 1
;* --------------------------------------------------------------------------*
||$C$L2||:    
	.dwpsn	file "../SysTick.c",line 64,column 5,is_stmt,isa 1
;----------------------------------------------------------------------
;  64 | SysTick_Wait(160000);  // wait 10ms (assumes 16 MHz clock)             
;----------------------------------------------------------------------
        LDR       A1, $C$CON4           ; [DPU_3_PIPE] |64| 
$C$DW$13	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$13, DW_AT_low_pc(0x00)
	.dwattr $C$DW$13, DW_AT_name("SysTick_Wait")
	.dwattr $C$DW$13, DW_AT_TI_call

        BL        SysTick_Wait          ; [DPU_3_PIPE] |64| 
        ; CALL OCCURS {SysTick_Wait }    ; [] |64| 
	.dwpsn	file "../SysTick.c",line 63,column 21,is_stmt,isa 1
        LDR       A1, [SP, #4]          ; [DPU_3_PIPE] |63| 
        ADDS      A1, A1, #1            ; [DPU_3_PIPE] |63| 
        STR       A1, [SP, #4]          ; [DPU_3_PIPE] |63| 
	.dwpsn	file "../SysTick.c",line 63,column 12,is_stmt,isa 1
        LDR       A1, [SP, #0]          ; [DPU_3_PIPE] |63| 
        LDR       A2, [SP, #4]          ; [DPU_3_PIPE] |63| 
        CMP       A1, A2                ; [DPU_3_PIPE] |63| 
        BHI       ||$C$L2||             ; [DPU_3_PIPE] |63| 
        ; BRANCHCC OCCURS {||$C$L2||}    ; [] |63| 
;* --------------------------------------------------------------------------*
	.dwpsn	file "../SysTick.c",line 66,column 1,is_stmt,isa 1
;* --------------------------------------------------------------------------*
||$C$L3||:    
$C$DW$14	.dwtag  DW_TAG_TI_branch
	.dwattr $C$DW$14, DW_AT_low_pc(0x00)
	.dwattr $C$DW$14, DW_AT_TI_return

        POP       {A2, A3, A4, PC}      ; [DPU_3_PIPE] 
	.dwcfi	cfa_offset, 0
        ; BRANCH OCCURS                  ; [] 
	.dwattr $C$DW$9, DW_AT_TI_end_file("../SysTick.c")
	.dwattr $C$DW$9, DW_AT_TI_end_line(0x42)
	.dwattr $C$DW$9, DW_AT_TI_end_column(0x01)
	.dwendentry
	.dwendtag $C$DW$9

;******************************************************************************
;* CONSTANT TABLE                                                             *
;******************************************************************************
	.sect	".text"
	.align	4
||$C$CON1||:	.bits	-536813552,32
	.align	4
||$C$CON2||:	.bits	-536813548,32
	.align	4
||$C$CON3||:	.bits	-536813544,32
	.align	4
||$C$CON4||:	.bits	160000,32

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

$C$DW$T$23	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$23, DW_AT_name("int8_t")
	.dwattr $C$DW$T$23, DW_AT_type(*$C$DW$T$5)
	.dwattr $C$DW$T$23, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$23, DW_AT_decl_file("D:/EngineeringSoftware/CCS/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include/stdint.h")
	.dwattr $C$DW$T$23, DW_AT_decl_line(0x2a)
	.dwattr $C$DW$T$23, DW_AT_decl_column(0x1d)

$C$DW$T$24	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$24, DW_AT_name("int_least8_t")
	.dwattr $C$DW$T$24, DW_AT_type(*$C$DW$T$23)
	.dwattr $C$DW$T$24, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$24, DW_AT_decl_file("D:/EngineeringSoftware/CCS/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include/stdint.h")
	.dwattr $C$DW$T$24, DW_AT_decl_line(0x37)
	.dwattr $C$DW$T$24, DW_AT_decl_column(0x17)

$C$DW$T$6	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$6, DW_AT_encoding(DW_ATE_unsigned_char)
	.dwattr $C$DW$T$6, DW_AT_name("unsigned char")
	.dwattr $C$DW$T$6, DW_AT_byte_size(0x01)

$C$DW$T$25	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$25, DW_AT_name("uint8_t")
	.dwattr $C$DW$T$25, DW_AT_type(*$C$DW$T$6)
	.dwattr $C$DW$T$25, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$25, DW_AT_decl_file("D:/EngineeringSoftware/CCS/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include/stdint.h")
	.dwattr $C$DW$T$25, DW_AT_decl_line(0x2b)
	.dwattr $C$DW$T$25, DW_AT_decl_column(0x1c)

$C$DW$T$26	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$26, DW_AT_name("uint_least8_t")
	.dwattr $C$DW$T$26, DW_AT_type(*$C$DW$T$25)
	.dwattr $C$DW$T$26, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$26, DW_AT_decl_file("D:/EngineeringSoftware/CCS/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include/stdint.h")
	.dwattr $C$DW$T$26, DW_AT_decl_line(0x38)
	.dwattr $C$DW$T$26, DW_AT_decl_column(0x16)

$C$DW$T$7	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$7, DW_AT_encoding(DW_ATE_signed_char)
	.dwattr $C$DW$T$7, DW_AT_name("wchar_t")
	.dwattr $C$DW$T$7, DW_AT_byte_size(0x02)

$C$DW$T$8	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$8, DW_AT_encoding(DW_ATE_signed)
	.dwattr $C$DW$T$8, DW_AT_name("short")
	.dwattr $C$DW$T$8, DW_AT_byte_size(0x02)

$C$DW$T$27	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$27, DW_AT_name("int16_t")
	.dwattr $C$DW$T$27, DW_AT_type(*$C$DW$T$8)
	.dwattr $C$DW$T$27, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$27, DW_AT_decl_file("D:/EngineeringSoftware/CCS/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include/stdint.h")
	.dwattr $C$DW$T$27, DW_AT_decl_line(0x2c)
	.dwattr $C$DW$T$27, DW_AT_decl_column(0x1d)

$C$DW$T$28	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$28, DW_AT_name("int_least16_t")
	.dwattr $C$DW$T$28, DW_AT_type(*$C$DW$T$27)
	.dwattr $C$DW$T$28, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$28, DW_AT_decl_file("D:/EngineeringSoftware/CCS/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include/stdint.h")
	.dwattr $C$DW$T$28, DW_AT_decl_line(0x3a)
	.dwattr $C$DW$T$28, DW_AT_decl_column(0x17)

$C$DW$T$9	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$9, DW_AT_encoding(DW_ATE_unsigned)
	.dwattr $C$DW$T$9, DW_AT_name("unsigned short")
	.dwattr $C$DW$T$9, DW_AT_byte_size(0x02)

$C$DW$T$29	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$29, DW_AT_name("uint16_t")
	.dwattr $C$DW$T$29, DW_AT_type(*$C$DW$T$9)
	.dwattr $C$DW$T$29, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$29, DW_AT_decl_file("D:/EngineeringSoftware/CCS/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include/stdint.h")
	.dwattr $C$DW$T$29, DW_AT_decl_line(0x2d)
	.dwattr $C$DW$T$29, DW_AT_decl_column(0x1c)

$C$DW$T$30	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$30, DW_AT_name("uint_least16_t")
	.dwattr $C$DW$T$30, DW_AT_type(*$C$DW$T$29)
	.dwattr $C$DW$T$30, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$30, DW_AT_decl_file("D:/EngineeringSoftware/CCS/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include/stdint.h")
	.dwattr $C$DW$T$30, DW_AT_decl_line(0x3b)
	.dwattr $C$DW$T$30, DW_AT_decl_column(0x16)

$C$DW$T$10	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$10, DW_AT_encoding(DW_ATE_signed)
	.dwattr $C$DW$T$10, DW_AT_name("int")
	.dwattr $C$DW$T$10, DW_AT_byte_size(0x04)

$C$DW$T$31	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$31, DW_AT_name("int32_t")
	.dwattr $C$DW$T$31, DW_AT_type(*$C$DW$T$10)
	.dwattr $C$DW$T$31, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$31, DW_AT_decl_file("D:/EngineeringSoftware/CCS/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include/stdint.h")
	.dwattr $C$DW$T$31, DW_AT_decl_line(0x2e)
	.dwattr $C$DW$T$31, DW_AT_decl_column(0x1d)

$C$DW$T$32	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$32, DW_AT_name("int_fast16_t")
	.dwattr $C$DW$T$32, DW_AT_type(*$C$DW$T$31)
	.dwattr $C$DW$T$32, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$32, DW_AT_decl_file("D:/EngineeringSoftware/CCS/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include/stdint.h")
	.dwattr $C$DW$T$32, DW_AT_decl_line(0x47)
	.dwattr $C$DW$T$32, DW_AT_decl_column(0x17)

$C$DW$T$33	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$33, DW_AT_name("int_fast32_t")
	.dwattr $C$DW$T$33, DW_AT_type(*$C$DW$T$31)
	.dwattr $C$DW$T$33, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$33, DW_AT_decl_file("D:/EngineeringSoftware/CCS/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include/stdint.h")
	.dwattr $C$DW$T$33, DW_AT_decl_line(0x4a)
	.dwattr $C$DW$T$33, DW_AT_decl_column(0x17)

$C$DW$T$34	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$34, DW_AT_name("int_fast8_t")
	.dwattr $C$DW$T$34, DW_AT_type(*$C$DW$T$31)
	.dwattr $C$DW$T$34, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$34, DW_AT_decl_file("D:/EngineeringSoftware/CCS/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include/stdint.h")
	.dwattr $C$DW$T$34, DW_AT_decl_line(0x45)
	.dwattr $C$DW$T$34, DW_AT_decl_column(0x17)

$C$DW$T$35	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$35, DW_AT_name("int_least32_t")
	.dwattr $C$DW$T$35, DW_AT_type(*$C$DW$T$31)
	.dwattr $C$DW$T$35, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$35, DW_AT_decl_file("D:/EngineeringSoftware/CCS/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include/stdint.h")
	.dwattr $C$DW$T$35, DW_AT_decl_line(0x3c)
	.dwattr $C$DW$T$35, DW_AT_decl_column(0x17)

$C$DW$T$36	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$36, DW_AT_name("intptr_t")
	.dwattr $C$DW$T$36, DW_AT_type(*$C$DW$T$10)
	.dwattr $C$DW$T$36, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$36, DW_AT_decl_file("D:/EngineeringSoftware/CCS/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include/stdint.h")
	.dwattr $C$DW$T$36, DW_AT_decl_line(0x52)
	.dwattr $C$DW$T$36, DW_AT_decl_column(0x1a)

$C$DW$T$11	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$11, DW_AT_encoding(DW_ATE_unsigned)
	.dwattr $C$DW$T$11, DW_AT_name("unsigned int")
	.dwattr $C$DW$T$11, DW_AT_byte_size(0x04)

$C$DW$T$20	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$20, DW_AT_name("uint32_t")
	.dwattr $C$DW$T$20, DW_AT_type(*$C$DW$T$11)
	.dwattr $C$DW$T$20, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$20, DW_AT_decl_file("D:/EngineeringSoftware/CCS/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include/stdint.h")
	.dwattr $C$DW$T$20, DW_AT_decl_line(0x2f)
	.dwattr $C$DW$T$20, DW_AT_decl_column(0x1c)

$C$DW$T$37	.dwtag  DW_TAG_volatile_type
	.dwattr $C$DW$T$37, DW_AT_type(*$C$DW$T$20)

$C$DW$T$39	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$39, DW_AT_name("uint_fast16_t")
	.dwattr $C$DW$T$39, DW_AT_type(*$C$DW$T$20)
	.dwattr $C$DW$T$39, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$39, DW_AT_decl_file("D:/EngineeringSoftware/CCS/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include/stdint.h")
	.dwattr $C$DW$T$39, DW_AT_decl_line(0x48)
	.dwattr $C$DW$T$39, DW_AT_decl_column(0x16)

$C$DW$T$40	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$40, DW_AT_name("uint_fast32_t")
	.dwattr $C$DW$T$40, DW_AT_type(*$C$DW$T$20)
	.dwattr $C$DW$T$40, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$40, DW_AT_decl_file("D:/EngineeringSoftware/CCS/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include/stdint.h")
	.dwattr $C$DW$T$40, DW_AT_decl_line(0x4b)
	.dwattr $C$DW$T$40, DW_AT_decl_column(0x16)

$C$DW$T$41	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$41, DW_AT_name("uint_fast8_t")
	.dwattr $C$DW$T$41, DW_AT_type(*$C$DW$T$20)
	.dwattr $C$DW$T$41, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$41, DW_AT_decl_file("D:/EngineeringSoftware/CCS/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include/stdint.h")
	.dwattr $C$DW$T$41, DW_AT_decl_line(0x46)
	.dwattr $C$DW$T$41, DW_AT_decl_column(0x16)

$C$DW$T$42	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$42, DW_AT_name("uint_least32_t")
	.dwattr $C$DW$T$42, DW_AT_type(*$C$DW$T$20)
	.dwattr $C$DW$T$42, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$42, DW_AT_decl_file("D:/EngineeringSoftware/CCS/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include/stdint.h")
	.dwattr $C$DW$T$42, DW_AT_decl_line(0x3d)
	.dwattr $C$DW$T$42, DW_AT_decl_column(0x16)

$C$DW$T$43	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$43, DW_AT_name("uintptr_t")
	.dwattr $C$DW$T$43, DW_AT_type(*$C$DW$T$11)
	.dwattr $C$DW$T$43, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$43, DW_AT_decl_file("D:/EngineeringSoftware/CCS/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include/stdint.h")
	.dwattr $C$DW$T$43, DW_AT_decl_line(0x53)
	.dwattr $C$DW$T$43, DW_AT_decl_column(0x1a)

$C$DW$T$12	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$12, DW_AT_encoding(DW_ATE_signed)
	.dwattr $C$DW$T$12, DW_AT_name("long")
	.dwattr $C$DW$T$12, DW_AT_byte_size(0x04)

$C$DW$T$13	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$13, DW_AT_encoding(DW_ATE_unsigned)
	.dwattr $C$DW$T$13, DW_AT_name("unsigned long")
	.dwattr $C$DW$T$13, DW_AT_byte_size(0x04)

$C$DW$T$14	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$14, DW_AT_encoding(DW_ATE_signed)
	.dwattr $C$DW$T$14, DW_AT_name("long long")
	.dwattr $C$DW$T$14, DW_AT_byte_size(0x08)

$C$DW$T$44	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$44, DW_AT_name("int64_t")
	.dwattr $C$DW$T$44, DW_AT_type(*$C$DW$T$14)
	.dwattr $C$DW$T$44, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$44, DW_AT_decl_file("D:/EngineeringSoftware/CCS/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include/stdint.h")
	.dwattr $C$DW$T$44, DW_AT_decl_line(0x32)
	.dwattr $C$DW$T$44, DW_AT_decl_column(0x21)

$C$DW$T$45	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$45, DW_AT_name("int_fast64_t")
	.dwattr $C$DW$T$45, DW_AT_type(*$C$DW$T$44)
	.dwattr $C$DW$T$45, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$45, DW_AT_decl_file("D:/EngineeringSoftware/CCS/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include/stdint.h")
	.dwattr $C$DW$T$45, DW_AT_decl_line(0x4e)
	.dwattr $C$DW$T$45, DW_AT_decl_column(0x17)

$C$DW$T$46	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$46, DW_AT_name("int_least64_t")
	.dwattr $C$DW$T$46, DW_AT_type(*$C$DW$T$44)
	.dwattr $C$DW$T$46, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$46, DW_AT_decl_file("D:/EngineeringSoftware/CCS/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include/stdint.h")
	.dwattr $C$DW$T$46, DW_AT_decl_line(0x40)
	.dwattr $C$DW$T$46, DW_AT_decl_column(0x17)

$C$DW$T$47	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$47, DW_AT_name("intmax_t")
	.dwattr $C$DW$T$47, DW_AT_type(*$C$DW$T$14)
	.dwattr $C$DW$T$47, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$47, DW_AT_decl_file("D:/EngineeringSoftware/CCS/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include/stdint.h")
	.dwattr $C$DW$T$47, DW_AT_decl_line(0x56)
	.dwattr $C$DW$T$47, DW_AT_decl_column(0x20)

$C$DW$T$15	.dwtag  DW_TAG_base_type
	.dwattr $C$DW$T$15, DW_AT_encoding(DW_ATE_unsigned)
	.dwattr $C$DW$T$15, DW_AT_name("unsigned long long")
	.dwattr $C$DW$T$15, DW_AT_byte_size(0x08)

$C$DW$T$48	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$48, DW_AT_name("uint64_t")
	.dwattr $C$DW$T$48, DW_AT_type(*$C$DW$T$15)
	.dwattr $C$DW$T$48, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$48, DW_AT_decl_file("D:/EngineeringSoftware/CCS/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include/stdint.h")
	.dwattr $C$DW$T$48, DW_AT_decl_line(0x33)
	.dwattr $C$DW$T$48, DW_AT_decl_column(0x20)

$C$DW$T$49	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$49, DW_AT_name("uint_fast64_t")
	.dwattr $C$DW$T$49, DW_AT_type(*$C$DW$T$48)
	.dwattr $C$DW$T$49, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$49, DW_AT_decl_file("D:/EngineeringSoftware/CCS/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include/stdint.h")
	.dwattr $C$DW$T$49, DW_AT_decl_line(0x4f)
	.dwattr $C$DW$T$49, DW_AT_decl_column(0x16)

$C$DW$T$50	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$50, DW_AT_name("uint_least64_t")
	.dwattr $C$DW$T$50, DW_AT_type(*$C$DW$T$48)
	.dwattr $C$DW$T$50, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$50, DW_AT_decl_file("D:/EngineeringSoftware/CCS/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include/stdint.h")
	.dwattr $C$DW$T$50, DW_AT_decl_line(0x41)
	.dwattr $C$DW$T$50, DW_AT_decl_column(0x16)

$C$DW$T$51	.dwtag  DW_TAG_typedef
	.dwattr $C$DW$T$51, DW_AT_name("uintmax_t")
	.dwattr $C$DW$T$51, DW_AT_type(*$C$DW$T$15)
	.dwattr $C$DW$T$51, DW_AT_language(DW_LANG_C)
	.dwattr $C$DW$T$51, DW_AT_decl_file("D:/EngineeringSoftware/CCS/ccsv7/tools/compiler/ti-cgt-arm_16.9.0.LTS/include/stdint.h")
	.dwattr $C$DW$T$51, DW_AT_decl_line(0x57)
	.dwattr $C$DW$T$51, DW_AT_decl_column(0x20)

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

