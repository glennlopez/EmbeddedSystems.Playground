library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity lesson_6 is 
	port
		(
			reset: 	IN		std_logic;	--44 (10k)
			clock:	IN		std_logic;	--37
			led:		OUT	std_logic_vector(3 downto 0)	--19 to 22
		);
end lesson_6;

architecture logic of lesson_6 is

	-- signal count is used to hold the value of the counter
	signal count: 	std_logic_vector(3 downto 0);
	
begin
	timer: process(reset, clock)
	begin
		if reset = '1' then
			count <= "0000";
		
		elsif rising_edge(clock) then
			count <= count + 1;
			
		end if;
	end process timer;
	
	-- it puts the count into led
	led <= count;
end logic;
	
	
	
	