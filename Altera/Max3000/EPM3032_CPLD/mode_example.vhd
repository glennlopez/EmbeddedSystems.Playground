library ieee;
use ieee.std_logic_1164.all;

entity mode_example is
	port
	(
		A, B, C: IN std_logic; 		-- input
		X: BUFFER std_logic; 		-- buffer
		Y: OUT std_logic				-- output
	);
end mode_example;

architecture cct_logic of mode_example is
begin
	X <= A or B;			-- X = A or B
	Y <= X and C;			-- Y = X and C
end cct_logic;