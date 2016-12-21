-- library
library ieee;
use ieee.std_logic_1164.all;

-- entity
entity bitVector is
	port
	(
		A: IN bit_vector(3 downto 0);		-- input A
		B: IN bit_vector(3 downto 0);		-- input B
		Y: OUT bit_vector(3 downto 0)		-- output Y
	);
end bitVector;

-- architecture
architecture and_gate of bitVector is
begin
	Y <= A and B;		-- Y = A and B
end and_gate;