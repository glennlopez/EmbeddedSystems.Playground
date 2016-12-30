library ieee;
use ieee.std_logic_1164.all;

entity halfadder is
	port
		(
		A, B: IN std_logic; 					-- Input
		Sum, Carry_out: OUT std_logic		-- Output
		);
end halfadder;

architecture sig_con of halfadder is
begin
	Sum <= A xor B; 			-- Sum
	Carry_out <= A and B; 	-- Carry_out
end sig_con;