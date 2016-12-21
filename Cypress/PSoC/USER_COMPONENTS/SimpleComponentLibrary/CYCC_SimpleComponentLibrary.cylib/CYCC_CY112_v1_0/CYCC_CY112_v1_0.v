
//`#start header` -- edit after this line, do not edit this line
// ==============================================================
// Simple CY112 JK-type flip-flop to demonstrate how to implement
// logic in UDBs with Verilog
//
// ==============================================================
`include "cypress.v"
//`#end` -- edit above this line, do not edit this line
// Generated on 02/25/2013 at 13:00
// Component: CY112_v1_0
module CYCC_CY112_v1_0 (
	output  reg  Q,          // Output
	output  wire Qn,         // Complementary Output
	input   wire clk,        // clock (active on neg edge)
	input   wire J,          // J input
	input   wire K,          // K input
	input   wire Rn,         // Reset (active low) async
	input   wire Sn          // Set (active low )
);

//`#start body` -- edit after this line, do not edit this line
    assign Qn = ~Q;                // Complementary ouput;
	always @(negedge clk or  negedge Rn) 
	  begin
		if (~Rn)                   // Rn has highest priority
		  Q <= 1'b0;
		else if (~Sn)              // Followed by Sn
		  Q <= 1'b1;
		else                       
		  begin
 		    case ({J,K})           // Case statement allows look up table simplicity 
			  2'b00 : Q <= Q;
			  2'b01 : Q <= 1'b0;
			  2'b10 : Q <= 1'b1;
			  2'b11 : Q <= ~Q;
			endcase
		  end
	  end
//`#end` -- edit above this line, do not edit this line
endmodule
//`#start footer` -- edit after this line, do not edit this line
//`#end` -- edit above this line, do not edit this line
