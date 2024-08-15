library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity decoder is
    Port (
        CLK : in STD_LOGIC;
        EN : in STD_LOGIC; --TODO: not used
        INSTRUCTION: in STD_LOGIC_VECTOR(7 downto 0);
        DATA_OUT: out STD_LOGIC_VECTOR(7 downto 0);
        ALU_OP: out STD_LOGIC_VECTOR(3 downto 0);
        STACK_PUSH: out STD_LOGIC;
        STACK_POP: out STD_LOGIC;
        STACK_AMOUNT: out STD_LOGIC_VECTOR(4 downto 0);
        STACK_SOURCE: out STD_LOGIC_VECTOR(1 downto 0);
        NEW_PC_EN: out STD_LOGIC;
        NEW_PC_IF_TRUE: out STD_LOGIC;
        MEMORY_WRITE: out STD_LOGIC
    );
end decoder;

architecture Behavioral of decoder is
    constant stack_source_immediate : STD_LOGIC_VECTOR(1 downto 0) := "00";
    constant stack_source_alu : STD_LOGIC_VECTOR(1 downto 0) := "01";
    constant stack_source_memory : STD_LOGIC_VECTOR(1 downto 0) := "10";
begin

process(CLK)
begin
    if rising_edge(CLK) then
        DATA_OUT <= (others => '0');
        STACK_SOURCE <= (others => '0');
        STACK_AMOUNT <= (others => '0');
        ALU_OP <= (others => '0');
        STACK_POP <= '0';
        STACK_PUSH <= '0';
        NEW_PC_EN <= '0';
        NEW_PC_IF_TRUE <= '0';
        MEMORY_WRITE <= '0';
        case INSTRUCTION(7 downto 5) is
            when "001" =>
                -- ALU operation
                STACK_SOURCE <= stack_source_alu;
                STACK_POP <= '1'; --Push 1 and pop 2, TODO:hacky
                STACK_PUSH <= '1';
                ALU_OP <= INSTRUCTION(3 downto 0);
                STACK_AMOUNT <= std_logic_vector(to_unsigned(2, STACK_AMOUNT'length));
            when "000" =>
                -- Pop amount
                STACK_POP <= '1';
                STACK_AMOUNT <= INSTRUCTION(4 downto 0);
            when "010" =>
                --Memory load/store
                --TODO
                if INSTRUCTION(0) = '1' then
                    --Load
                    STACK_POP <= '1';
                    STACK_PUSH <= '1';
                    STACK_AMOUNT <= std_logic_vector(to_unsigned(1, STACK_AMOUNT'length));
                else
                    --Store
                    STACK_POP <= '1';
                    STACK_AMOUNT <= std_logic_vector(to_unsigned(2, STACK_AMOUNT'length));
                end if;
                MEMORY_WRITE <= not INSTRUCTION(0);
                STACK_SOURCE <= stack_source_memory;
            when "011" =>
                --Jump
                NEW_PC_EN <= '1';
                STACK_POP <= '1';
                STACK_AMOUNT <= std_logic_vector(to_unsigned(2, STACK_AMOUNT'length));
                NEW_PC_IF_TRUE <= INSTRUCTION(0);
                --TODO
            when others =>
                --Push constant
                STACK_SOURCE <= stack_source_immediate;
                STACK_PUSH <= '1';
                DATA_OUT <= "0" & INSTRUCTION(6 downto 0);
                STACK_AMOUNT <= std_logic_vector(to_unsigned(1, STACK_AMOUNT'length));

        end case;
    end if;
end process;

end architecture;
