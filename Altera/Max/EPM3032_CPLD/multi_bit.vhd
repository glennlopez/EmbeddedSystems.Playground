-- libraries are defined here
library ieee;
use ieee.std_logic_1164.all;

-- port entities are defined here
entity multi_bit is
	port(
		a, b, c: in std_logic;
		w, x, y, z: out std_logic);
end multi_bit;

-- architechture (or the port functions) are defined here
architecture logic of multi_bit is
	-- define input and output signals here
	signal inputs: std_logic_vector (2 downto 0);
	signal outputs: std_logic_vector (3 downto 0);
begin
	inputs <= a & b & c; -- concatinate the input ports into "input" variable
	with inputs select
		outputs <= 	"1000" when "000",
						"0100" when "001",
						"0110" when "010",
						"1001" when "011",
						"0110" when "100",
						"0001" when "101",
						"1001" when "110",
						"0010" when "111",
						"0000" when others;
		-- seperate the "outputs" signal into individual ports again
		w <= outputs (3);
		x <= outputs (2);
		y <= outputs (1);
		z <= outputs (0);
end logic;
