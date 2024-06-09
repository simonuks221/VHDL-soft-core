library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

--LIBRARY blk_mem_gen_v8_4_8;
--USE blk_mem_gen_v8_4_8.blk_mem_gen_v8_4_8;

entity stack_ram_imp is
    Port (
        CLK : in STD_LOGIC;
        DATA_IN : in STD_LOGIC_VECTOR (7 downto 0);
        TOP_DATA : out STD_LOGIC_VECTOR (7 downto 0);
        NEXT_DATA : out STD_LOGIC_VECTOR (7 downto 0);
        PUSH : in STD_LOGIC;
        POP : in STD_LOGIC
    );
end stack_ram_imp;

architecture Behavioral of stack_ram_imp is
    --component stack_ram IS
    --    PORT (
    --        clka : IN STD_LOGIC;
    --        wea : IN STD_LOGIC_VECTOR(0 DOWNTO 0);
    --        addra : IN STD_LOGIC_VECTOR(7 DOWNTO 0);
    --        dina : IN STD_LOGIC_VECTOR(7 DOWNTO 0);
    --        clkb : IN STD_LOGIC;
    --        addrb : IN STD_LOGIC_VECTOR(7 DOWNTO 0);
    --        doutb : OUT STD_LOGIC_VECTOR(7 DOWNTO 0)
    --    );
    --END component;
    --TODO: figure out whats wrong with the Xilinx RAM
    type stack_array_type is array (0 to 255) of std_logic_vector(7 downto 0);
    signal stack_array : stack_array_type := (others => (others => '0'));

    --signal ram_wr : STD_LOGIC_VECTOR(0 DOWNTO 0) := "0";
    --signal ram_addr_write : integer := 0;
    --signal ram_addr_read : integer := 0;
    --signal ram_wr_data : STD_LOGIC_VECTOR(7 downto 0) := (others => '0');
    --signal ram_next_data : STD_LOGIC_VECTOR(7 downto 0) := (others => '0');

    --signal top_internal : STD_LOGIC_VECTOR(7 downto 0) := (others => '0');
    --signal next_internal : STD_LOGIC_VECTOR(7 downto 0) := (others => '0');

    signal stack_top_address : integer := 0;
    signal stack_next_address : integer := 0;
begin

--ram1 : stack_ram port map(CLK, ram_wr, std_logic_vector(to_unsigned(ram_addr_write, 8)), ram_wr_data, CLK, std_logic_vector(to_unsigned(ram_addr_write, 8)), ram_next_data);

TOP_DATA <= stack_array(stack_top_address);
NEXT_DATA <= stack_array(stack_next_address);

process(CLK)
begin
    if rising_edge(CLK) then
        if PUSH = '1' then
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
