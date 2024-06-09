library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity decoder is
    Port (
        CLK : in STD_LOGIC;
        INSTRUCTION: in STD_LOGIC_VECTOR(7 downto 0);
        DATA_OUT: out STD_LOGIC_VECTOR(7 downto 0);
        EN_ALU: out STD_LOGIC;
        PUSH: out STD_LOGIC;
        POP: out STD_LOGIC
    );
end decoder;

architecture Behavioral of decoder is

begin

process(CLK)
begin
    if rising_edge(CLK) then
        PUSH <= '0';
        POP <= '0';
        case INSTRUCTION(1 downto 0) is
            when "00" =>
                --NOP
            when "01" =>
                --PUSH TO TOP
                PUSH <= '1';
                DATA_OUT <= "0000" & INSTRUCTION(7 downto 4);
            when "10" =>
                --POP
                POP <= '1';
            when "11" =>
                --ALU

            when others =>
                --INVALID
        end case;
    end if;
end process;

end Behavioral;
