library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity stack is
    Port (
        CLK : in STD_LOGIC;
        DATA_IN : in STD_LOGIC_VECTOR (7 downto 0);
        TOP_DATA : out STD_LOGIC_VECTOR (7 downto 0);
        NEXT_DATA : out STD_LOGIC_VECTOR (7 downto 0);
        PUSH : in STD_LOGIC;
        POP : in STD_LOGIC
    );
end stack;

architecture Behavioral of stack is
    type stack_array_type is array (0 to 255) of std_logic_vector(7 downto 0);
    signal stack_array : stack_array_type := (others => (others => '0'));

    signal stack_top_address : integer := 0;
    signal stack_next_address : integer := 0;
begin

--ram1 : stack_ram port map(CLK, ram_wr, std_logic_vector(to_unsigned(ram_addr_write, 8)), ram_wr_data, CLK, std_logic_vector(to_unsigned(ram_addr_write, 8)), ram_next_data);

TOP_DATA <= stack_array(stack_top_address);
NEXT_DATA <= stack_array(stack_next_address);

process(CLK)
begin
    if rising_edge(CLK) then
        --TODO:make into vector and make into decoder with when statements
        if PUSH = '1' and POP = '1' then
            stack_array(stack_top_address) <= DATA_IN;
        elsif PUSH = '1' then
            stack_array(stack_top_address + 1) <= DATA_IN;
            stack_top_address <= stack_top_address + 1;
            if stack_top_address /= 0 then
                stack_next_address <= stack_next_address + 1;
            end if;
        elsif POP = '1' then
            stack_top_address <= stack_top_address - 1;
            if stack_top_address /= 1 then
                stack_next_address <= stack_next_address - 1;
            end if;
        end if;
    end if;
end process;

end Behavioral;
