library ieee;
use std_logic_1164.all;

entity truth_table is
	port
	(
	D: IN bit_vector (3 downto 0); 	-- bitvector inputs
	Y: OUT std_logic						-- outputs
	);
end truth_table;

architecture tLogic of truth_table is
begin
	-- truth table architecture
		-- 0111 = 1
		-- 1100 = 1
		-- 1110 = 1
		-- 1111 = 1
		-- everything else = 0
end tLogic;