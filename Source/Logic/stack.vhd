library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity stack is
    Port (
        CLK : in STD_LOGIC;
        WR_EN : in STD_LOGIC;
        DATA_IN : in STD_LOGIC_VECTOR (7 downto 0);
        TOP_DATA : out STD_LOGIC_VECTOR (7 downto 0);
        NEXT_DATA : out STD_LOGIC_VECTOR (7 downto 0);
        PUSH : in STD_LOGIC;
        POP : in STD_LOGIC;
        AMOUNT : in STD_LOGIC_VECTOR(4 downto 0);
        OVERFLOW : out STD_LOGIC := '0';
        UNDERFLOW : out STD_LOGIC := '0'
    );
end stack;

architecture Behavioral of stack is
    constant max_depth : integer := 256;
    type stack_array_type is array (0 to max_depth - 1) of std_logic_vector(7 downto 0);
    signal stack_array : stack_array_type := (others => (others => '0'));

    signal stack_top_address : integer := 0;
    signal stack_next_address : integer := 0;
begin

TOP_DATA <= stack_array(stack_top_address);
NEXT_DATA <= stack_array(stack_next_address);

process(CLK)
variable amount_int : integer := 0;
begin
    if rising_edge(CLK) then
        if WR_EN = '0' then

        else
            --TODO: make into vector and make into decoder with when statements, maybe will speed up
            amount_int := to_integer(unsigned(AMOUNT));
            if PUSH = '1' and POP = '1' then
                --Quick fix for ALU that pops 2 and pushes one --TODO: do not hardcode
                stack_array(stack_top_address - 1) <= DATA_IN;
                stack_top_address <= stack_top_address - 1;
                if stack_top_address /= 1 then
                    stack_next_address <= stack_next_address - amount_int;
                end if;
                if stack_top_address < 1 then
                    UNDERFLOW <= '1';
                end if;
            elsif PUSH = '1' then
                stack_array(stack_top_address + 1) <= DATA_IN;
                stack_top_address <= stack_top_address + 1;
                if stack_top_address /= 0 then
                    stack_next_address <= stack_next_address + 1;
                end if;
                if stack_top_address = max_depth - 1 then
                    OVERFLOW <= '1';
                end if;
            elsif POP = '1' then
                stack_top_address <= stack_top_address - amount_int;
                if stack_top_address /= amount_int then
                    stack_next_address <= stack_next_address - amount_int;
                end if;
                if stack_top_address < amount_int then
                    UNDERFLOW <= '1';
                end if;
            end if;
        end if;
    end if;
end process;

end Behavioral;
