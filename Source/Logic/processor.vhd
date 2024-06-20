library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity processor is
	Port (
		CLK_12 : in STD_LOGIC
	);
end processor;

architecture Behavioral of processor is

    component processor_core is
        Port (
            CLK : in STD_LOGIC;
            PROGRAM_MEMORY_D : in STD_LOGIC_VECTOR(7 downto 0);
            PROGRAM_MEMORY_A : out STD_LOGIC_VECTOR(7 downto 0)
        );
    end component;

    component program_rom is
        PORT (
            CLK : IN STD_LOGIC;
            ADDR : IN STD_LOGIC_VECTOR(7 DOWNTO 0);
            DATA : OUT STD_LOGIC_VECTOR(7 DOWNTO 0)
          );
    end component;

    signal program_memory_d : STD_LOGIC_VECTOR(7 downto 0);
    signal program_memory_a : STD_LOGIC_VECTOR(7 downto 0);

begin

core_1 : processor_core port map(CLK_12, program_memory_d, program_memory_a);
program_rom_1 : program_rom port map(CLK_12, program_memory_a, program_memory_d);

end architecture;
