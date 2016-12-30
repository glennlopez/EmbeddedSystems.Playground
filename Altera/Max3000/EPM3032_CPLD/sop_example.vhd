library ieee;
use ieee.std_logic_1164.all;

entity sop_example is
	port
	( 
	P, Q, R: IN std_logic; 		-- Inputs | using std_logic library
	X, Y: OUT std_logic		-- Outputs
	);
end sop_example;

architecture logic_cct of sop_example is
begin
	X <= (P AND (not Q)) OR (Q AND (not R));	 		-- X = PQ' + QR'
	Y <= ((not P) OR (Q AND (not R))); 				-- Y = P' + QR'
end logic_cct;
