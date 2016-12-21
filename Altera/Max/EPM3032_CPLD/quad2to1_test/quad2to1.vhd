----------------------------------------------------------------------
--			LAB4: quad2to1.vhd
--
--		Write a VHDL file that defines a multiplexer that switches 
--		two 4-bit inputs, x and y to a 4-bit output, z. Define x, y, 
--		and z as type BIT_VECTOR
----------------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;

--entity
entity quad2to1 is
  port (
  -- x=3 y=3 s=1 z=3
  x,y:   in    std_logic_vector(3 downto 0);
  s:     in    std_logic;
  z:     out   std_logic_vector(3 downto 0)
  );
end entity;asdasdas 

--architecture
--we will select x or y output depending on select (1 or 0)
architecture selector of quad2to1 is
begin
   with s select
   z <= 	x when '0',
			y when '1';
end selector;