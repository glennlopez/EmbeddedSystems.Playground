
//`#start header` -- edit after this line, do not edit this line
// ========================================
// Simple CY191 counter demostration to show Users a
// way to route signals into the ALU and out of A0/A1 and
// generate conbinatorial logic signals.
//
// Datapath States
//        PLn UnD CEn
//   Reg0  0   0   0    => Load counter from data input (A0 = pi)
//   Reg1  0   0   1    => Load counter from data input (A0 = pi)
//   Reg2  0   1   0    => Load counter from data input (A0 = pi)
//   Reg3  0   1   1    => Load counter from data input (A0 = pi)
//   Reg4  1   0   0    => Count Up (A0++)
//   Reg5  1   0   1    => Disable counter (do nothing)
//   Reg6  1   1   0    => Count Down (A0--)
//   Reg7  1   1   1    => Disable Counter  (do nothing)
//
// Registers
//   A0 => Counter register (Initialized to zero) 
//   A1 => not used
//   D0 => not used
//   D1 => not used
//   F0 => not used
//   F1 => not used
// ========================================
`include "cypress.v"
//`#end` -- edit above this line, do not edit this line
// Generated on 02/20/2013 at 15:58
// Component: CYCC_CY191_v1_0
module CYCC_CY191_v1_0 (
	output wire[7:0] Q,         // Counter Inputs
	output wire RCn,            // Ripple Carry Output (active low)
	output wire TC,             // Terminal Count Output
	input  wire CEn,            // Count Enable (active low)
	input  wire clk,            // Clock input
	input  wire [7:0] D,        // Data inputs
	input  wire PLn,            // Parallel Load (active load)
	input  wire UnD             // Count direction input
);

//`#start body` -- edit after this line, do not edit this line
    wire   AllZeros;                                 // Flag that A0 is 0x00
	wire   AllOnes;                                  // Flag that A0 is 0xff
	assign TC  = (AllZeros & UnD)|( AllOnes * ~UnD); // TC is set at 0x00 for down and 0xff for up
	assign RCn = ~(TC & ~CEn & ~clk);                // RCn is enabled for the last half of TC when CEn is valid
   
cy_psoc3_dp #(.cy_dpconfig(
{
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_ENBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM0: Load Counter (A0 = pi) (CFB inabled)*/
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_ENBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM1: Load Counter (A0 = pi) (CFB inabled)*/
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_ENBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM2: Load Counter (A0 = pi) (CFB inabled)*/
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_ENBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM3: Load Counter (A0 = pi) (CFB inabled)*/
    `CS_ALU_OP__INC, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM4: Count Up  (A0++)*/
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM5: Null*/
    `CS_ALU_OP__DEC, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM6: Count Down (A---)*/
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM7: Null*/
    8'hFF, 8'h00,  /*CFG9: */
    8'hFF, 8'hFF,  /*CFG11-10: */
    `SC_CMPB_A1_D1, `SC_CMPA_A1_D1, `SC_CI_B_ARITH,
    `SC_CI_A_ARITH, `SC_C1_MASK_DSBL, `SC_C0_MASK_DSBL,
    `SC_A_MASK_DSBL, `SC_DEF_SI_0, `SC_SI_B_DEFSI,
    `SC_SI_A_DEFSI, /*CFG13-12: */
    `SC_A0_SRC_ACC, `SC_SHIFT_SL, `SC_PI_DYN_EN,
    1'h0, `SC_FIFO1_BUS, `SC_FIFO0_BUS,
    `SC_MSB_DSBL, `SC_MSB_BIT0, `SC_MSB_NOCHN,
    `SC_FB_NOCHN, `SC_CMP1_NOCHN,
    `SC_CMP0_NOCHN, /*CFG15-14: */
    10'h00, `SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,
    `SC_FIFO_LEVEL,`SC_FIFO__SYNC,`SC_EXTCRC_DSBL,
    `SC_WRK16CAT_DSBL /*CFG17-16: */
}
)) counter(
        /*  input                   */  .reset(1'b0),
        /*  input                   */  .clk(clk),                 //Connect to clock
        /*  input   [02:00]         */  .cs_addr({PLn, UnD, CEn}), // Connect to control logic
        /*  input                   */  .route_si(1'b0),
        /*  input                   */  .route_ci(1'b0),
        /*  input                   */  .f0_load(1'b0),
        /*  input                   */  .f1_load(1'b0),
        /*  input                   */  .d0_load(1'b0),
        /*  input                   */  .d1_load(1'b0),
        /*  output                  */  .ce0(),
        /*  output                  */  .cl0(),
        /*  output                  */  .z0(AllZeros),     // Flag set when A0 == 0x00
        /*  output                  */  .ff0(AllOnes),     // Flag set when A0 == oxff
        /*  output                  */  .ce1(),
        /*  output                  */  .cl1(),
        /*  output                  */  .z1(),
        /*  output                  */  .ff1(),
        /*  output                  */  .ov_msb(),
        /*  output                  */  .co_msb(),
        /*  output                  */  .cmsb(),
        /*  output                  */  .so(),
        /*  output                  */  .f0_bus_stat(),
        /*  output                  */  .f0_blk_stat(),
        /*  output                  */  .f1_bus_stat(),
        /*  output                  */  .f1_blk_stat(),
        
        /* input                    */  .ci(1'b0),     // Carry in from previous stage
        /* output                   */  .co(),         // Carry out to next stage
        /* input                    */  .sir(1'b0),    // Shift in from right side
        /* output                   */  .sor(),        // Shift out to right side
        /* input                    */  .sil(1'b0),    // Shift in from left side
        /* output                   */  .sol(),        // Shift out to left side
        /* input                    */  .msbi(1'b0),   // MSB chain in
        /* output                   */  .msbo(),       // MSB chain out
        /* input [01:00]            */  .cei(2'b0),    // Compare equal in from prev stage
        /* output [01:00]           */  .ceo(),        // Compare equal out to next stage
        /* input [01:00]            */  .cli(2'b0),    // Compare less than in from prv stage
        /* output [01:00]           */  .clo(),        // Compare less than out to next stage
        /* input [01:00]            */  .zi(2'b0),     // Zero detect in from previous stage
        /* output [01:00]           */  .zo(),         // Zero detect out to next stage
        /* input [01:00]            */  .fi(2'b0),     // 0xFF detect in from previous stage
        /* output [01:00]           */  .fo(),         // 0xFF detect out to next stage
        /* input [01:00]            */  .capi(2'b0),   // Software capture from previous stage
        /* output [01:00]           */  .capo(),       // Software capture to next stage
        /* input                    */  .cfbi(1'b0),   // CRC Feedback in from previous stage
        /* output                   */  .cfbo(),       // CRC Feedback out to next stage
        /* input [07:00]            */  .pi(D[7:0]),   // Data connecte to PI
        /* output [07:00]           */  .po(Q[7:0])    // PO connected to output
);
//`#end` -- edit above this line, do not edit this line
endmodule
//`#start footer` -- edit after this line, do not edit this line
//`#end` -- edit above this line, do not edit this line

