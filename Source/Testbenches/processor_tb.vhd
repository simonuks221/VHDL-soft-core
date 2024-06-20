library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity processor_core_tb is

end processor_core_tb;

architecture Behavioral of processor_core_tb is

	component processor is
		Port (
			CLK_12 : in STD_LOGIC
		);
	end component;

	signal CLK : STD_LOGIC := '0';

begin

dut : processor port map(CLK);

CLK <= not CLK after 10 ns;

end architecture;
