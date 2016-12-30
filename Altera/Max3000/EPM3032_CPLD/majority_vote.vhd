library ieee;				-- use ieee library
use ieee.std_logic_1164.all;		-- use all of std_logic_1164

entity majority_vote is 
	port
	(
		A, B, C: IN BIT;	-- (3x) input	| use pin 25,26,27
		Y: OUT BIT		-- (1x) output	| use pin 22
	);
end majority_vote;

architecture cct OF majority_vote is
begin
	y <= (A AND B) OR (B AND C) OR (A and C); 	-- Y = AB + BC + AC
end cct;
	
