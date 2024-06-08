library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity alu is
  Port (
    CLK : in STD_LOGIC;
    OP_A: in STD_LOGIC_VECTOR(7 downto 0);
    OP_B: in STD_LOGIC_VECTOR(7 downto 0);
    RESULT: out STD_LOGIC_VECTOR(7 downto 0)
   );
end alu;

architecture Behavioral of alu is

begin


end Behavioral;
