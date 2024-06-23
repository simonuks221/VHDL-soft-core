library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity decoder is
    Port (
        CLK : in STD_LOGIC;
        EN : in STD_LOGIC;
        INSTRUCTION: in STD_LOGIC_VECTOR(7 downto 0);
        DATA_OUT: out STD_LOGIC_VECTOR(7 downto 0);
        PUSH: out STD_LOGIC;
        POP: out STD_LOGIC;
        PASSTHROUGH: out STD_LOGIC
    );
end decoder;

architecture Behavioral of decoder is
    signal push_delay : STD_LOGIC := '0';
    signal pop_delay : STD_LOGIC := '0';
begin

-- MSB

-- X
-- X
-- X
-- X

-- X
-- EN_ALU
-- POP
-- PUSH

-- LSB

process(CLK)
begin
    if rising_edge(CLK) then
        push_delay <= '0';
        pop_delay <= '0';
        if EN = '1' then
            push_delay <= INSTRUCTION(0);
            pop_delay <= INSTRUCTION(1);
            PASSTHROUGH <= not INSTRUCTION(2);
        end if;
        PUSH <= push_delay;
        POP <= pop_delay;
    end if;
end process;

DATA_OUT <= "0000" & INSTRUCTION( 7 downto 4);

end architecture;
