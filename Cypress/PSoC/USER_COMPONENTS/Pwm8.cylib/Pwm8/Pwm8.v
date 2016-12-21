`include "cypress.v"

module Pwm8 (clk, din, dout);

input clk;
input [7:0] din;
output dout;

reg [8:0] temp;
always @(posedge clk) temp <= temp[7:0] + din;

assign dout = temp[8];

endmodule