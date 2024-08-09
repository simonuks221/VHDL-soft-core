library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity ram is
    generic (
        DATA_WIDTH : integer := 8;
        ADDR_WIDTH : integer := 8
    );
    port (
        CLK    : in  std_logic;
        WE     : in  std_logic;
        ADDR   : in  std_logic_vector(ADDR_WIDTH-1 downto 0);
        DATA_IN  : in  std_logic_vector(DATA_WIDTH-1 downto 0);
        DATA_OUT : out std_logic_vector(DATA_WIDTH-1 downto 0)
    );
end ram;

architecture Behavioral of ram is
    type ram_type is array (2**ADDR_WIDTH-1 downto 0) of std_logic_vector(DATA_WIDTH-1 downto 0);
    signal ram : ram_type := (others => (others => '0'));
    signal read_addr : std_logic_vector(ADDR_WIDTH-1 downto 0) := (others => '0');
begin

	DATA_OUT <= ram(to_integer(unsigned(read_addr)));
    process(clk)
    begin
        if rising_edge(clk) then
            if we = '1' then
                ram(to_integer(unsigned(addr))) <= DATA_IN;
            end if;
            read_addr <= ADDR;
        end if;
    end process;
end Behavioral;
