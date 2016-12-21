
//`#start header` -- edit after this line, do not edit this line
// ==============================================================
// Simple CY74 D-type flip-flop to demonstrate how to implement
// logic in UDBs with Verilog
//
// ==============================================================
`include "cypress.v"
//`#end` -- edit above this line, do not edit this line
// Generated on 02/25/2013 at 09:06
// Component: CYCC_CY74_v1_0
module CYCC_CY74_v1_0 (
	output  reg  Q,      // Ouput
	output  wire Qn,     // Complementary output
	input   wire clk,    // Clock input
	input   wire D,      // D flip-flop input
	input   wire Rn,     // Reset (active low)
	input   wire Sn      // Set (active low)
);

//`#start body` -- edit after this line, do not edit this line
    assign Qn = ~Q;                      // Qn is complementary to Q;
	always @(posedge clk or negedge Rn) 
	begin
		if (~Rn)
			Q <= 1'b0;                   // Rn has highest priority
		else if (~Sn)
		    Q <= 1'b1;                   // Followed by Sn
		else
			Q <= D;                      // Followed by D
	end
//`#end` -- edit above this line, do not edit this line
endmodule
//`#start footer` -- edit after this line, do not edit this line
//`#end` -- edit above this line, do not edit this line
