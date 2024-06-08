library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity main is
    Port ( CLK_IN_12MHz : in STD_LOGIC;
           LED1 : out STD_LOGIC;
           LED2 : out STD_LOGIC;
           BTN1 : in STD_LOGIC;
           BTN2 : in STD_LOGIC;
           RGB_R : out STD_LOGIC;
           RGB_G : out STD_LOGIC;
           RGB_B : out STD_LOGIC
        );
end main;

architecture Behavioral of main is

begin

RGB_R <= '0';
RGB_G <= '0';
RGB_B <= '0';

process(CLK_IN_12MHz)
begin
    if rising_edge(CLK_IN_12MHz) then
        LED1 <= '1';
        LED2 <= '1';
    end if;
end process;

end Behavioral;