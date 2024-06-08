library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;


entity main_tb is

end main_tb;

architecture Behavioral of main_tb is
    signal CLK_IN_12MHz : STD_LOGIC := '0';
    signal LED1 : STD_LOGIC := '0';
    signal LED2 : STD_LOGIC := '0';
    signal BTN1 : STD_LOGIC := '0';
    signal BTN2 : STD_LOGIC := '0';
    signal RGB_R : STD_LOGIC := '0';
    signal RGB_G : STD_LOGIC := '0';
    signal RGB_B : STD_LOGIC := '0';

    component main_design is
        Port ( CLK_IN_12MHz : in STD_LOGIC;
               LED1 : out STD_LOGIC;
               LED2 : out STD_LOGIC;
               BTN1 : in STD_LOGIC;
               BTN2 : in STD_LOGIC;
               RGB_R : out STD_LOGIC;
               RGB_G : out STD_LOGIC;
               RGB_B : out STD_LOGIC
        );
    end component;
begin

main : main_design port map (CLK_IN_12MHz, LED1, LED2, BTN1, BTN2, RGB_R, RGB_G, RGB_B);

CLK_IN_12MHz <= not CLK_IN_12MHz after 41.666 ns;

end Behavioral;
