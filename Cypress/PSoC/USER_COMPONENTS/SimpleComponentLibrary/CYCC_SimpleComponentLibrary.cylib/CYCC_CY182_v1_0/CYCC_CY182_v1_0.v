
//`#start header` -- edit after this line, do not edit this line
// ==============================================================
// Simple CY182 Look-ahead carry generator to demonstrate how
// to implement combinatorial logic in UDBs with Verilog
//
// ==============================================================
`include "cypress.v"
//`#end` -- edit above this line, do not edit this line
// Generated on 02/25/2013 at 18:32
// Component: CYCC_CY182_v1_0
module CYCC_CY182_v1_0 (
	output  wire CNX,  // Function output
	output  wire CNY,  // Function output
	output  wire CNZ,  // Function output
	output  wire Gn,   // Carry generate output (active low)
	output  wire Pn,   // Carry propagate output (active low)
	input   wire CN,   // Carry Input
	input   wire G0n,  // Carry generate input (active low) 
	input   wire G1n,  // Carry generate input (active low)
	input   wire G2n,  // Carry generate input (active low)
	input   wire G3n,  // Carry generate input (active low)
	input   wire P0n,  // Carry propagate input (active low)
	input   wire P1n,  // Carry propagate input (active low)
	input   wire P2n,  // Carry propagate input (active low)
	input   wire P3n   // Carry propagate input (active low)
);

//`#start body` -- edit after this line, do not edit this line
	assign  CNX = ~((G0n & P0n)|(~CN & G0n));
	assign  CNY = ~((G1n & P1n)|(G0n & P0n & G1n)|(~CN & G0n & G1n));
	assign  CNZ = ~((G2n & P2n)|(G1n & P1n & G2n)
	              |(G0n & P0n & G1n & G2n)|(~CN & G0n & G1n & G2n));
	assign  Gn  = (G3n & P3n)
	             |(G2n & P2n & G3n)
				 |(G1n & P1n & G2n & G3n)
				 |(G0n & G1n & G2n & G3n);
	assign  Pn  = P0n | P1n | P2n | P3n;
//`#end` -- edit above this line, do not edit this line
endmodule
//`#start footer` -- edit after this line, do not edit this line
//`#end` -- edit above this line, do not edit this line
