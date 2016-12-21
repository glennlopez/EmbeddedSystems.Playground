// ======================================================================
// TestBench.v generated from TopDesign.cysch
// 10/10/2012 at 15:06
// This file is auto generated. ANY EDITS YOU MAKE MAY BE LOST WHEN THIS FILE IS REGENERATED!!!
// ======================================================================

/* -- WARNING: The following section of defines are deprecated and will be removed in a future release -- */
`define CYDEV_CHIP_DIE_LEOPARD 1
`define CYDEV_CHIP_REV_LEOPARD_PRODUCTION 3
`define CYDEV_CHIP_REV_LEOPARD_ES3 3
`define CYDEV_CHIP_REV_LEOPARD_ES2 1
`define CYDEV_CHIP_REV_LEOPARD_ES1 0
`define CYDEV_CHIP_DIE_PANTHER 2
`define CYDEV_CHIP_REV_PANTHER_PRODUCTION 1
`define CYDEV_CHIP_REV_PANTHER_ES1 1
`define CYDEV_CHIP_REV_PANTHER_ES0 0
`define CYDEV_CHIP_DIE_PSOC5LP 3
`define CYDEV_CHIP_REV_PSOC5LP_PRODUCTION 0
`define CYDEV_CHIP_REV_PSOC5LP_ES 0
`define CYDEV_CHIP_DIE_EXPECT 1
`define CYDEV_CHIP_REV_EXPECT 3
`define CYDEV_CHIP_DIE_ACTUAL 1
/* -- WARNING: The previous section of defines are deprecated and will be removed in a future release -- */
`define CYDEV_CHIP_FAMILY_UNKNOWN 0
`define CYDEV_CHIP_MEMBER_UNKNOWN 0
`define CYDEV_CHIP_FAMILY_PSOC3 1
`define CYDEV_CHIP_MEMBER_3A 1
`define CYDEV_CHIP_REVISION_3A_PRODUCTION 3
`define CYDEV_CHIP_REVISION_3A_ES3 3
`define CYDEV_CHIP_REVISION_3A_ES2 1
`define CYDEV_CHIP_REVISION_3A_ES1 0
`define CYDEV_CHIP_FAMILY_PSOC5 2
`define CYDEV_CHIP_MEMBER_5A 2
`define CYDEV_CHIP_REVISION_5A_PRODUCTION 1
`define CYDEV_CHIP_REVISION_5A_ES1 1
`define CYDEV_CHIP_REVISION_5A_ES0 0
`define CYDEV_CHIP_MEMBER_5B 3
`define CYDEV_CHIP_REVISION_5B_PRODUCTION 0
`define CYDEV_CHIP_REVISION_5B_ES 0
`define CYDEV_CHIP_FAMILY_USED 1
`define CYDEV_CHIP_MEMBER_USED 1
`define CYDEV_CHIP_REVISION_USED 3
// Component: CyControlReg_v1_60
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\CyControlReg_v1_60"
`include "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\CyControlReg_v1_60\CyControlReg_v1_60.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\2.1\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\CyControlReg_v1_60"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\2.1\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\CyControlReg_v1_60\CyControlReg_v1_60.v"
`endif

// Component: cy_virtualmux_v1_0
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\cy_virtualmux_v1_0"
`include "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\cy_virtualmux_v1_0\cy_virtualmux_v1_0.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\2.1\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\cy_virtualmux_v1_0"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\2.1\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\cy_virtualmux_v1_0\cy_virtualmux_v1_0.v"
`endif

// Component: and_v1_0
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\and_v1_0"
`include "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\and_v1_0\and_v1_0.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\2.1\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\and_v1_0"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\2.1\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\and_v1_0\and_v1_0.v"
`endif

// Component: OneTerminal
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\OneTerminal"
`include "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\OneTerminal\OneTerminal.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\2.1\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\OneTerminal"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\2.1\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\OneTerminal\OneTerminal.v"
`endif

// Component: xor_v1_0
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\xor_v1_0"
`include "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\xor_v1_0\xor_v1_0.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\2.1\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\xor_v1_0"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\2.1\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\xor_v1_0\xor_v1_0.v"
`endif

// Component: B_PWM_v2_10
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\B_PWM_v2_10"
`include "$CYPRESS_DIR\..\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\B_PWM_v2_10\B_PWM_v2_10.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\2.1\PSoC Creator\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\B_PWM_v2_10"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\2.1\PSoC Creator\psoc\content\cycomponentlibrary\CyComponentLibrary.cylib\B_PWM_v2_10\B_PWM_v2_10.v"
`endif

// Component: ZeroTerminal
`ifdef CY_BLK_DIR
`undef CY_BLK_DIR
`endif

`ifdef WARP
`define CY_BLK_DIR "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\ZeroTerminal"
`include "$CYPRESS_DIR\..\psoc\content\cyprimitives\CyPrimitives.cylib\ZeroTerminal\ZeroTerminal.v"
`else
`define CY_BLK_DIR "C:\Program Files (x86)\Cypress\PSoC Creator\2.1\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\ZeroTerminal"
`include "C:\Program Files (x86)\Cypress\PSoC Creator\2.1\PSoC Creator\psoc\content\cyprimitives\CyPrimitives.cylib\ZeroTerminal\ZeroTerminal.v"
`endif

// PWM_v2_10(CaptureMode=0, CompareStatusEdgeSense=true, CompareType1=1, CompareType1Software=0, CompareType2=1, CompareType2Software=0, CompareValue1=127, CompareValue2=63, CtlModeReplacementString=SyncCtl, CyGetRegReplacementString=CY_GET_REG8, CySetRegReplacementString=CY_SET_REG8, DeadBand=0, DeadBand2_4=0, DeadBandUsed=0, DeadTime=1, DitherOffset=0, EnableMode=0, FixedFunction=false, FixedFunctionUsed=0, InterruptOnCMP1=false, InterruptOnCMP2=false, InterruptOnKill=false, InterruptOnTC=false, IntOnCMP1=0, IntOnCMP2=0, IntOnKill=0, IntOnTC=0, KillMode=0, KillModeMinTime=0, MinimumKillTime=1, OneCompare=true, Period=255, PWMMode=0, PWMModeCenterAligned=0, RegDefReplacementString=reg8, RegSizeReplacementString=uint8, Resolution=8, RstStatusReplacementString=sSTSReg_rstSts, RunMode=0, TriggerMode=0, UseControl=true, UseInterrupt=true, UseStatus=true, VerilogSectionReplacementString=sP8, CY_COMPONENT_NAME=PWM_v2_10, CY_CONTROL_FILE=<:default:>, CY_FITTER_NAME=COM_PWM, CY_INSTANCE_SHORT_NAME=COM_PWM, CY_MAJOR_VERSION=2, CY_MINOR_VERSION=10, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=cydsfit No Version Information Found, INSTANCE_NAME=LED_COM_PWM, )
module PWM_v2_10_0 (
    pwm2,
    tc,
    clock,
    reset,
    pwm1,
    interrupt,
    capture,
    kill,
    enable,
    trigger,
    cmp_sel,
    pwm,
    ph1,
    ph2);
    output      pwm2;
    output      tc;
    input       clock;
    input       reset;
    output      pwm1;
    output      interrupt;
    input       capture;
    input       kill;
    input       enable;
    input       trigger;
    input       cmp_sel;
    output      pwm;
    output      ph1;
    output      ph2;

    parameter Resolution = 8;

          wire  Net_113;
          wire  Net_114;
          wire  Net_107;
          wire  Net_96;
          wire  Net_55;
          wire  Net_57;
          wire  Net_101;
          wire  Net_54;
          wire  Net_63;

    B_PWM_v2_10 PWMUDB (
        .reset(reset),
        .clock(clock),
        .tc(Net_101),
        .pwm1(pwm1),
        .pwm2(pwm2),
        .interrupt(Net_55),
        .kill(kill),
        .capture(capture),
        .enable(enable),
        .cmp_sel(cmp_sel),
        .trigger(trigger),
        .pwm(Net_96),
        .ph1(ph1),
        .ph2(ph2));
    defparam PWMUDB.CaptureMode = 0;
    defparam PWMUDB.CompareStatusEdgeSense = 1;
    defparam PWMUDB.CompareType1 = 1;
    defparam PWMUDB.CompareType2 = 1;
    defparam PWMUDB.DeadBand = 0;
    defparam PWMUDB.DitherOffset = 0;
    defparam PWMUDB.EnableMode = 0;
    defparam PWMUDB.KillMode = 0;
    defparam PWMUDB.PWMMode = 0;
    defparam PWMUDB.Resolution = 8;
    defparam PWMUDB.RunMode = 0;
    defparam PWMUDB.TriggerMode = 0;
    defparam PWMUDB.UseStatus = 1;

	// vmCompare (cy_virtualmux_v1_0)
	assign pwm = Net_96;

	// vmIRQ (cy_virtualmux_v1_0)
	assign interrupt = Net_55;

	// vmTC (cy_virtualmux_v1_0)
	assign tc = Net_101;

    OneTerminal OneTerminal_1 (
        .o(Net_113));

	// FFKillMux (cy_virtualmux_v1_0)
	assign Net_107 = Net_114;

    ZeroTerminal ZeroTerminal_1 (
        .z(Net_114));



endmodule

// KEES_LED_SegDriver_v1_0(Com_Drive=0, External_PWM_Clk=false, External_Refresh_Clk=false, Num_Commons=4, PWM_Enable=true, Seg_Drive=1, Seg7_Support=true, CY_COMPONENT_NAME=KEES_LED_SegDriver_v1_0, CY_CONTROL_FILE=<:default:>, CY_FITTER_NAME=LED, CY_INSTANCE_SHORT_NAME=LED, CY_MAJOR_VERSION=1, CY_MINOR_VERSION=0, CY_REMOVE=false, CY_SUPPRESS_API_GEN=false, CY_VERSION=cydsfit No Version Information Found, INSTANCE_NAME=LED, )
module KEES_LED_SegDriver_v1_0_1 (
    Seg,
    Com,
    Refresh_Clk,
    PWM_Clk);
    output     [0:7] Seg;
    output     [0:7] Com;
    input       Refresh_Clk;
    input       PWM_Clk;


          wire  Net_1826;
          wire  Seg_1;
          wire  Seg_2;
          wire  Seg_3;
          wire  Seg_4;
          wire  Seg_5;
          wire  Seg_6;
          wire  Seg_7;
          wire  Net_1827;
          wire  Net_1828;
          wire  Net_1829;
          wire  Net_1830;
          wire  Net_1831;
          wire  Net_1832;
          wire  Net_1833;
          wire  Com_Invert;
          wire  Net_1834;
          wire  Net_1835;
          wire  Net_1836;
          wire  Net_1837;
          wire  Net_1838;
          wire  Seg_0;
          wire  Net_1839;
          wire  Net_1840;
          wire  Net_1841;
          wire  Net_1842;
          wire  Net_1843;
          wire  Net_1844;
          wire  Net_1845;
          wire  Com_6;
          wire  Com_5;
          wire  Com_4;
          wire  Com_3;
          wire  Com_2;
          wire  Seg_Invert;
          wire  Com_1;
          wire  Com_0;
          wire  Net_1846;
          wire  Net_1847;
          wire  Com_7;
          wire  Net_1848;
          wire  Net_1849;
          wire  Net_1850;
          wire  Net_1857;
          wire  Net_1851;
          wire  Net_1852;
          wire  Net_1853;
          wire  Net_1854;
          wire  Net_1855;
          wire  Net_130;
          wire [0:7] Segment;
          wire  Net_97;
          wire [0:7] Common;
          wire  Net_1730;
          wire  Net_768;
          wire  Net_218;
          wire  Brightness;
          wire  Net_214;
          wire  Net_213;
          wire  Net_212;
          wire  Net_211;
          wire  Net_210;
          wire  Net_209;
          wire  Net_208;
          wire  Net_181;

    CyControlReg_v1_60 RAM_1 (
        .control_1(Seg_1),
        .control_2(Seg_2),
        .control_3(Seg_3),
        .control_0(Seg_0),
        .control_4(Seg_4),
        .control_5(Seg_5),
        .control_6(Seg_6),
        .control_7(Seg_7),
        .clock(Net_1826),
        .reset(1'b0));
    defparam RAM_1.Bit0Mode = 1;
    defparam RAM_1.Bit1Mode = 1;
    defparam RAM_1.Bit2Mode = 1;
    defparam RAM_1.Bit3Mode = 1;
    defparam RAM_1.Bit4Mode = 1;
    defparam RAM_1.Bit5Mode = 1;
    defparam RAM_1.Bit6Mode = 1;
    defparam RAM_1.Bit7Mode = 1;
    defparam RAM_1.BitValue = 0;
    defparam RAM_1.DeviceFamily = "PSoC3";
    defparam RAM_1.ExtrReset = 1;
    defparam RAM_1.NumOutputs = 8;
    defparam RAM_1.SiliconRevision = "3  ";

    CyControlReg_v1_60 RAM_2 (
        .control_1(Com_1),
        .control_2(Com_2),
        .control_3(Com_3),
        .control_0(Com_0),
        .control_4(Com_4),
        .control_5(Com_5),
        .control_6(Com_6),
        .control_7(Com_7),
        .clock(Net_1828),
        .reset(1'b0));
    defparam RAM_2.Bit0Mode = 1;
    defparam RAM_2.Bit1Mode = 1;
    defparam RAM_2.Bit2Mode = 1;
    defparam RAM_2.Bit3Mode = 1;
    defparam RAM_2.Bit4Mode = 1;
    defparam RAM_2.Bit5Mode = 1;
    defparam RAM_2.Bit6Mode = 1;
    defparam RAM_2.Bit7Mode = 1;
    defparam RAM_2.BitValue = 0;
    defparam RAM_2.DeviceFamily = "PSoC3";
    defparam RAM_2.ExtrReset = 1;
    defparam RAM_2.NumOutputs = 8;
    defparam RAM_2.SiliconRevision = "3  ";


	cy_clock_v1_0
		#(.id("1b6327a9-80a6-42a8-9dd7-233dbf05bd62/d05d066f-4294-4c15-bc55-057f915630ec"),
		  .source_clock_id("75C2148C-3656-4d8a-846D-0CAE99AB6FF7"),
		  .divisor(0),
		  .period("0"),
		  .is_direct(1),
		  .is_digital(1))
		Clock_1
		 (.clock_out(Net_1826));



	cy_clock_v1_0
		#(.id("1b6327a9-80a6-42a8-9dd7-233dbf05bd62/69673522-d71a-4108-84da-86616070decb"),
		  .source_clock_id("75C2148C-3656-4d8a-846D-0CAE99AB6FF7"),
		  .divisor(0),
		  .period("0"),
		  .is_direct(1),
		  .is_digital(1))
		Clock_2
		 (.clock_out(Net_1828));


	// VirtualMux_5 (cy_virtualmux_v1_0)
	assign Net_97 = Net_1832;

	// VirtualMux_4 (cy_virtualmux_v1_0)
	assign Net_768 = Net_1730;


	cy_clock_v1_0
		#(.id("1b6327a9-80a6-42a8-9dd7-233dbf05bd62/58dba220-3d20-44d3-9337-36aaa0ec5509"),
		  .source_clock_id(""),
		  .divisor(0),
		  .period("4000000000"),
		  .is_direct(0),
		  .is_digital(1))
		PWM_Clock
		 (.clock_out(Net_1730));



    assign Net_218 = Brightness & Com_7;


    assign Net_214 = Brightness & Com_6;


    assign Net_213 = Brightness & Com_5;


    assign Net_212 = Brightness & Com_4;


    assign Net_211 = Brightness & Com_3;


    assign Net_210 = Brightness & Com_2;


    assign Net_209 = Brightness & Com_1;


    assign Net_208 = Brightness & Com_0;

    OneTerminal OneTerminal_3 (
        .o(Net_1834));

	// VirtualMux_3 (cy_virtualmux_v1_0)
	assign Brightness = Net_181;


    assign Common[7] = Net_218 ^ Com_Invert;


    assign Common[6] = Net_214 ^ Com_Invert;


	cy_clock_v1_0
		#(.id("1b6327a9-80a6-42a8-9dd7-233dbf05bd62/061962bc-7dc6-4d5b-8913-497220c8c5cb"),
		  .source_clock_id(""),
		  .divisor(0),
		  .period("2000000000000"),
		  .is_direct(0),
		  .is_digital(1))
		Refresh_Clock
		 (.clock_out(Net_1832));



    assign Segment[0] = Seg_0 ^ Seg_Invert;


    assign Segment[5] = Seg_5 ^ Seg_Invert;


    assign Segment[4] = Seg_4 ^ Seg_Invert;


    assign Segment[3] = Seg_3 ^ Seg_Invert;


    assign Segment[2] = Seg_2 ^ Seg_Invert;


    assign Segment[1] = Seg_1 ^ Seg_Invert;

    PWM_v2_10_0 COM_PWM (
        .reset(1'b0),
        .clock(Net_768),
        .tc(Net_1837),
        .pwm1(Net_1838),
        .pwm2(Net_1839),
        .interrupt(Net_1840),
        .capture(1'b0),
        .kill(1'b1),
        .enable(1'b1),
        .trigger(1'b0),
        .cmp_sel(1'b0),
        .pwm(Net_181),
        .ph1(Net_1846),
        .ph2(Net_1847));
    defparam COM_PWM.Resolution = 8;


	cy_dma_v1_0
		#(.drq_type(2'b00))
		Brightness_DMA
		 (.drq(Net_97),
		  .trq(1'b0),
		  .nrq(Net_1849));



    assign Common[5] = Net_213 ^ Com_Invert;


    assign Common[4] = Net_212 ^ Com_Invert;


    assign Common[3] = Net_211 ^ Com_Invert;


    assign Common[2] = Net_210 ^ Com_Invert;


    assign Common[1] = Net_209 ^ Com_Invert;


    assign Common[0] = Net_208 ^ Com_Invert;


    assign Segment[7] = Seg_7 ^ Seg_Invert;


    assign Segment[6] = Seg_6 ^ Seg_Invert;


	cy_dma_v1_0
		#(.drq_type(2'b00))
		Common_DMA
		 (.drq(Net_97),
		  .trq(1'b0),
		  .nrq(Net_1857));


	// VirtualMux_2 (cy_virtualmux_v1_0)
	assign Com_Invert = Net_1852;

    ZeroTerminal ZeroTerminal_2 (
        .z(Net_1851));

    OneTerminal OneTerminal_2 (
        .o(Net_1852));

    OneTerminal OneTerminal_1 (
        .o(Net_1853));

    ZeroTerminal ZeroTerminal_1 (
        .z(Net_1854));

	// VirtualMux_1 (cy_virtualmux_v1_0)
	assign Seg_Invert = Net_1854;


	cy_dma_v1_0
		#(.drq_type(2'b00))
		Segment_DMA
		 (.drq(Net_97),
		  .trq(1'b0),
		  .nrq(Net_130));



    assign Seg = Segment[0:7];

    assign Com = Common[0:7];


endmodule

// top
module top ;

          wire  Net_48;
          wire  Net_47;
          wire [0:7] Segment;
          wire [0:7] Common;

	wire [0:0] tmpOE__Common_3_net;
	wire [0:0] tmpFB_0__Common_3_net;
	wire [0:0] tmpIO_0__Common_3_net;
	wire [0:0] tmpINTERRUPT_0__Common_3_net;
	electrical [0:0] tmpSIOVREF__Common_3_net;

	cy_psoc3_pins_v1_10
		#(.id("7cd5a0b7-4744-4ca8-89e4-c0f11eb2c75f"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_sync(1'b1),
		  .intr_mode(2'b00),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .output_conn(1'b1),
		  .output_sync(1'b0),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .use_annotation(1'b0),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b10),
		  .width(1))
		Common_3
		 (.oe(tmpOE__Common_3_net),
		  .y({Common[3]}),
		  .fb({tmpFB_0__Common_3_net[0:0]}),
		  .io({tmpIO_0__Common_3_net[0:0]}),
		  .siovref(tmpSIOVREF__Common_3_net),
		  .interrupt({tmpINTERRUPT_0__Common_3_net[0:0]}));

	assign tmpOE__Common_3_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__Common_2_net;
	wire [0:0] tmpFB_0__Common_2_net;
	wire [0:0] tmpIO_0__Common_2_net;
	wire [0:0] tmpINTERRUPT_0__Common_2_net;
	electrical [0:0] tmpSIOVREF__Common_2_net;

	cy_psoc3_pins_v1_10
		#(.id("3588e73b-9bb2-4c9d-a26a-e6ffebb0ab58"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_sync(1'b1),
		  .intr_mode(2'b00),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .output_conn(1'b1),
		  .output_sync(1'b0),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .use_annotation(1'b0),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b10),
		  .width(1))
		Common_2
		 (.oe(tmpOE__Common_2_net),
		  .y({Common[2]}),
		  .fb({tmpFB_0__Common_2_net[0:0]}),
		  .io({tmpIO_0__Common_2_net[0:0]}),
		  .siovref(tmpSIOVREF__Common_2_net),
		  .interrupt({tmpINTERRUPT_0__Common_2_net[0:0]}));

	assign tmpOE__Common_2_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__Common_1_net;
	wire [0:0] tmpFB_0__Common_1_net;
	wire [0:0] tmpIO_0__Common_1_net;
	wire [0:0] tmpINTERRUPT_0__Common_1_net;
	electrical [0:0] tmpSIOVREF__Common_1_net;

	cy_psoc3_pins_v1_10
		#(.id("85e25368-bb39-4a1b-9777-f4ace4e85187"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_sync(1'b1),
		  .intr_mode(2'b00),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .output_conn(1'b1),
		  .output_sync(1'b0),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .use_annotation(1'b0),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b10),
		  .width(1))
		Common_1
		 (.oe(tmpOE__Common_1_net),
		  .y({Common[1]}),
		  .fb({tmpFB_0__Common_1_net[0:0]}),
		  .io({tmpIO_0__Common_1_net[0:0]}),
		  .siovref(tmpSIOVREF__Common_1_net),
		  .interrupt({tmpINTERRUPT_0__Common_1_net[0:0]}));

	assign tmpOE__Common_1_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__Segment_7_net;
	wire [0:0] tmpFB_0__Segment_7_net;
	wire [0:0] tmpIO_0__Segment_7_net;
	wire [0:0] tmpINTERRUPT_0__Segment_7_net;
	electrical [0:0] tmpSIOVREF__Segment_7_net;

	cy_psoc3_pins_v1_10
		#(.id("fbdfe0c6-539f-4373-a1b1-3519e951e549"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_sync(1'b1),
		  .intr_mode(2'b00),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .output_conn(1'b1),
		  .output_sync(1'b0),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .use_annotation(1'b0),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b10),
		  .width(1))
		Segment_7
		 (.oe(tmpOE__Segment_7_net),
		  .y({Segment[7]}),
		  .fb({tmpFB_0__Segment_7_net[0:0]}),
		  .io({tmpIO_0__Segment_7_net[0:0]}),
		  .siovref(tmpSIOVREF__Segment_7_net),
		  .interrupt({tmpINTERRUPT_0__Segment_7_net[0:0]}));

	assign tmpOE__Segment_7_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__Segment_6_net;
	wire [0:0] tmpFB_0__Segment_6_net;
	wire [0:0] tmpIO_0__Segment_6_net;
	wire [0:0] tmpINTERRUPT_0__Segment_6_net;
	electrical [0:0] tmpSIOVREF__Segment_6_net;

	cy_psoc3_pins_v1_10
		#(.id("c87f25d9-da60-4d90-9600-cbc323ea2dee"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_sync(1'b1),
		  .intr_mode(2'b00),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .output_conn(1'b1),
		  .output_sync(1'b0),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .use_annotation(1'b0),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b10),
		  .width(1))
		Segment_6
		 (.oe(tmpOE__Segment_6_net),
		  .y({Segment[6]}),
		  .fb({tmpFB_0__Segment_6_net[0:0]}),
		  .io({tmpIO_0__Segment_6_net[0:0]}),
		  .siovref(tmpSIOVREF__Segment_6_net),
		  .interrupt({tmpINTERRUPT_0__Segment_6_net[0:0]}));

	assign tmpOE__Segment_6_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__Segment_5_net;
	wire [0:0] tmpFB_0__Segment_5_net;
	wire [0:0] tmpIO_0__Segment_5_net;
	wire [0:0] tmpINTERRUPT_0__Segment_5_net;
	electrical [0:0] tmpSIOVREF__Segment_5_net;

	cy_psoc3_pins_v1_10
		#(.id("472e9d28-0ee2-4685-8bd9-e90185ce3b7e"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_sync(1'b1),
		  .intr_mode(2'b00),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .output_conn(1'b1),
		  .output_sync(1'b0),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .use_annotation(1'b0),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b10),
		  .width(1))
		Segment_5
		 (.oe(tmpOE__Segment_5_net),
		  .y({Segment[5]}),
		  .fb({tmpFB_0__Segment_5_net[0:0]}),
		  .io({tmpIO_0__Segment_5_net[0:0]}),
		  .siovref(tmpSIOVREF__Segment_5_net),
		  .interrupt({tmpINTERRUPT_0__Segment_5_net[0:0]}));

	assign tmpOE__Segment_5_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__Segment_4_net;
	wire [0:0] tmpFB_0__Segment_4_net;
	wire [0:0] tmpIO_0__Segment_4_net;
	wire [0:0] tmpINTERRUPT_0__Segment_4_net;
	electrical [0:0] tmpSIOVREF__Segment_4_net;

	cy_psoc3_pins_v1_10
		#(.id("738e970f-e4d8-4660-8607-33b3188dcd63"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_sync(1'b1),
		  .intr_mode(2'b00),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .output_conn(1'b1),
		  .output_sync(1'b0),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .use_annotation(1'b0),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b10),
		  .width(1))
		Segment_4
		 (.oe(tmpOE__Segment_4_net),
		  .y({Segment[4]}),
		  .fb({tmpFB_0__Segment_4_net[0:0]}),
		  .io({tmpIO_0__Segment_4_net[0:0]}),
		  .siovref(tmpSIOVREF__Segment_4_net),
		  .interrupt({tmpINTERRUPT_0__Segment_4_net[0:0]}));

	assign tmpOE__Segment_4_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__Segment_3_net;
	wire [0:0] tmpFB_0__Segment_3_net;
	wire [0:0] tmpIO_0__Segment_3_net;
	wire [0:0] tmpINTERRUPT_0__Segment_3_net;
	electrical [0:0] tmpSIOVREF__Segment_3_net;

	cy_psoc3_pins_v1_10
		#(.id("38701248-80a0-497a-8d6a-6f2c07a4bbd0"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_sync(1'b1),
		  .intr_mode(2'b00),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .output_conn(1'b1),
		  .output_sync(1'b0),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .use_annotation(1'b0),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b10),
		  .width(1))
		Segment_3
		 (.oe(tmpOE__Segment_3_net),
		  .y({Segment[3]}),
		  .fb({tmpFB_0__Segment_3_net[0:0]}),
		  .io({tmpIO_0__Segment_3_net[0:0]}),
		  .siovref(tmpSIOVREF__Segment_3_net),
		  .interrupt({tmpINTERRUPT_0__Segment_3_net[0:0]}));

	assign tmpOE__Segment_3_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__Segment_2_net;
	wire [0:0] tmpFB_0__Segment_2_net;
	wire [0:0] tmpIO_0__Segment_2_net;
	wire [0:0] tmpINTERRUPT_0__Segment_2_net;
	electrical [0:0] tmpSIOVREF__Segment_2_net;

	cy_psoc3_pins_v1_10
		#(.id("245c649f-70c8-4456-8045-ded609f1a66d"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_sync(1'b1),
		  .intr_mode(2'b00),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .output_conn(1'b1),
		  .output_sync(1'b0),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .use_annotation(1'b0),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b10),
		  .width(1))
		Segment_2
		 (.oe(tmpOE__Segment_2_net),
		  .y({Segment[2]}),
		  .fb({tmpFB_0__Segment_2_net[0:0]}),
		  .io({tmpIO_0__Segment_2_net[0:0]}),
		  .siovref(tmpSIOVREF__Segment_2_net),
		  .interrupt({tmpINTERRUPT_0__Segment_2_net[0:0]}));

	assign tmpOE__Segment_2_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__Segment_1_net;
	wire [0:0] tmpFB_0__Segment_1_net;
	wire [0:0] tmpIO_0__Segment_1_net;
	wire [0:0] tmpINTERRUPT_0__Segment_1_net;
	electrical [0:0] tmpSIOVREF__Segment_1_net;

	cy_psoc3_pins_v1_10
		#(.id("5dc59184-f194-4e7b-8cad-3b0e68f7cee1"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_sync(1'b1),
		  .intr_mode(2'b00),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .output_conn(1'b1),
		  .output_sync(1'b0),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .use_annotation(1'b0),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b10),
		  .width(1))
		Segment_1
		 (.oe(tmpOE__Segment_1_net),
		  .y({Segment[1]}),
		  .fb({tmpFB_0__Segment_1_net[0:0]}),
		  .io({tmpIO_0__Segment_1_net[0:0]}),
		  .siovref(tmpSIOVREF__Segment_1_net),
		  .interrupt({tmpINTERRUPT_0__Segment_1_net[0:0]}));

	assign tmpOE__Segment_1_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__Common_0_net;
	wire [0:0] tmpFB_0__Common_0_net;
	wire [0:0] tmpIO_0__Common_0_net;
	wire [0:0] tmpINTERRUPT_0__Common_0_net;
	electrical [0:0] tmpSIOVREF__Common_0_net;

	cy_psoc3_pins_v1_10
		#(.id("bd05a1d4-6ea6-48f7-a50c-62bf057fc540"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_sync(1'b1),
		  .intr_mode(2'b00),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .output_conn(1'b1),
		  .output_sync(1'b0),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .use_annotation(1'b0),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b10),
		  .width(1))
		Common_0
		 (.oe(tmpOE__Common_0_net),
		  .y({Common[0]}),
		  .fb({tmpFB_0__Common_0_net[0:0]}),
		  .io({tmpIO_0__Common_0_net[0:0]}),
		  .siovref(tmpSIOVREF__Common_0_net),
		  .interrupt({tmpINTERRUPT_0__Common_0_net[0:0]}));

	assign tmpOE__Common_0_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

	wire [0:0] tmpOE__Segment_0_net;
	wire [0:0] tmpFB_0__Segment_0_net;
	wire [0:0] tmpIO_0__Segment_0_net;
	wire [0:0] tmpINTERRUPT_0__Segment_0_net;
	electrical [0:0] tmpSIOVREF__Segment_0_net;

	cy_psoc3_pins_v1_10
		#(.id("ed092b9b-d398-4703-be89-cebf998501f6"),
		  .drive_mode(3'b110),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b0),
		  .input_sync(1'b1),
		  .intr_mode(2'b00),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .output_conn(1'b1),
		  .output_sync(1'b0),
		  .pin_aliases(""),
		  .pin_mode("O"),
		  .por_state(4),
		  .use_annotation(1'b0),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b10),
		  .width(1))
		Segment_0
		 (.oe(tmpOE__Segment_0_net),
		  .y({Segment[0]}),
		  .fb({tmpFB_0__Segment_0_net[0:0]}),
		  .io({tmpIO_0__Segment_0_net[0:0]}),
		  .siovref(tmpSIOVREF__Segment_0_net),
		  .interrupt({tmpINTERRUPT_0__Segment_0_net[0:0]}));

	assign tmpOE__Segment_0_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};

    KEES_LED_SegDriver_v1_0_1 LED (
        .Seg(Segment[0:7]),
        .Com(Common[0:7]),
        .Refresh_Clk(1'b0),
        .PWM_Clk(1'b0));

	wire [0:0] tmpOE__Button_net;
	wire [0:0] tmpFB_0__Button_net;
	wire [0:0] tmpIO_0__Button_net;
	wire [0:0] tmpINTERRUPT_0__Button_net;
	electrical [0:0] tmpSIOVREF__Button_net;

	cy_psoc3_pins_v1_10
		#(.id("1425177d-0d0e-4468-8bcc-e638e5509a9b"),
		  .drive_mode(3'b111),
		  .ibuf_enabled(1'b1),
		  .init_dr_st(1'b1),
		  .input_sync(1'b1),
		  .intr_mode(2'b00),
		  .io_voltage(""),
		  .layout_mode("CONTIGUOUS"),
		  .oe_conn(1'b0),
		  .output_conn(1'b0),
		  .output_sync(1'b0),
		  .pin_aliases(""),
		  .pin_mode("I"),
		  .por_state(4),
		  .use_annotation(1'b0),
		  .sio_group_cnt(0),
		  .sio_hyst(1'b0),
		  .sio_ibuf(""),
		  .sio_info(2'b00),
		  .sio_obuf(""),
		  .sio_refsel(""),
		  .sio_vtrip(""),
		  .slew_rate(1'b0),
		  .spanning(0),
		  .vtrip(2'b00),
		  .width(1))
		Button
		 (.oe(tmpOE__Button_net),
		  .y({1'b0}),
		  .fb({tmpFB_0__Button_net[0:0]}),
		  .io({tmpIO_0__Button_net[0:0]}),
		  .siovref(tmpSIOVREF__Button_net),
		  .interrupt({tmpINTERRUPT_0__Button_net[0:0]}));

	assign tmpOE__Button_net = (`CYDEV_CHIP_MEMBER_USED == `CYDEV_CHIP_MEMBER_3A && `CYDEV_CHIP_REVISION_USED < `CYDEV_CHIP_REVISION_3A_ES3) ? ~{1'b1} : {1'b1};



endmodule

