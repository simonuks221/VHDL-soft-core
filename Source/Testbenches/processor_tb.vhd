library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity processor_tb is

end processor_tb;

architecture Behavioral of processor_tb is

	component processor is
		Port (
			CLK_12 : in STD_LOGIC;
			LED_1 : inout STD_LOGIC;
			LED_2 : inout STD_LOGIC;
			RGB_R : inout STD_LOGIC;
			RGB_G : inout STD_LOGIC;
			RGB_B : inout STD_LOGIC;
			BTN_1 : inout STD_LOGIC;
			BTN_2 : inout STD_LOGIC
		);
	end component;

	signal CLK : STD_LOGIC := '0';
	signal LED_1 : STD_LOGIC := '0';
	signal LED_2 : STD_LOGIC := '0';
	signal RGB_R : STD_LOGIC := '0';
	signal RGB_G : STD_LOGIC := '0';
	signal RGB_B : STD_LOGIC := '0';
    signal BTN_1 : STD_LOGIC := '0';
    signal BTN_2 : STD_LOGIC := '0';

begin

dut : processor port map(CLK, LED_1, LED_2, RGB_R, RGB_G, RGB_B, BTN_1, BTN_2);

CLK <= not CLK after 10 ns;

process
begin
	BTN_1 <= '0';
	BTN_2 <= '0';
	RGB_R <= 'L';
	RGB_G <= 'L';
	RGB_B <= 'L';
	wait for 2 us;
	BTN_1 <= '1';
	wait for 1 us;
	BTN_1 <= '0';
	wait;
end process;

end architecture;
