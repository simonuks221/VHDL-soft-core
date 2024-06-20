library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity processor_core is
	Port (
		CLK : in STD_LOGIC;
		PROGRAM_MEMORY_D : in STD_LOGIC_VECTOR(7 downto 0);
		PROGRAM_MEMORY_A : out STD_LOGIC_VECTOR(7 downto 0)
	);
end processor_core;

architecture Behavioral of processor_core is

	component pc is
		Port (
		  CLK: in STD_LOGIC;
		  P_COUNTER: out STD_LOGIC_VECTOR(7 downto 0)
		);
	end component;

begin

pc_1 : pc port map(CLK, PROGRAM_MEMORY_A);

end architecture;
