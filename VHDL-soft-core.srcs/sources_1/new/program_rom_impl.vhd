library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;
--library UNISIM;
--use UNISIM.VComponents.all;

entity program_rom_impl is
    PORT (
        CLK : IN STD_LOGIC;
        ADDR : IN STD_LOGIC_VECTOR(7 DOWNTO 0);
        DATA : OUT STD_LOGIC_VECTOR(7 DOWNTO 0)
      );
end program_rom_impl;

architecture Behavioral of program_rom_impl is
    component program_rom IS
    PORT (
      clka : IN STD_LOGIC;
      ena : IN STD_LOGIC;
      addra : IN STD_LOGIC_VECTOR(7 DOWNTO 0);
      douta : OUT STD_LOGIC_VECTOR(7 DOWNTO 0)
    );
  END component;
begin

    rom_cell : program_rom port map (CLK, '1', ADDR, DATA);

end Behavioral;
