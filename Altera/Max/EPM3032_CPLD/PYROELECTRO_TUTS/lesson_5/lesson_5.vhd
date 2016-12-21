library ieee;
use ieee.std_logic_1164.all;

entity lesson_5 is
port
	(
		reset:		IN		 	std_logic; -- 44
		clock:		IN			std_logic; -- 37
		button:		IN			std_logic; -- 23
		
		led_0:		OUT		std_logic; -- 21
		led_1:		OUT		std_logic  -- 22
	);
end lesson_5;

architecture clock of lesson_5 is
	signal blink:		std_logic;
	signal data:		std_logic;
begin

data_register: process (reset, clock, button)
	begin
		if 	reset = '1' then
				data <= '0';
				blink <= '0';
				
		elsif rising_edge(clock) then
				data <= button;
				blink <= not blink;
		end if;
	end process data_register;
	
led_0 <= blink;
led_1 <= data; 

end clock;