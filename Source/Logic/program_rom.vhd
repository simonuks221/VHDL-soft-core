library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity program_rom is
    PORT (
        CLK : IN STD_LOGIC;
        ADDR : IN STD_LOGIC_VECTOR(7 DOWNTO 0);
        DATA : OUT STD_LOGIC_VECTOR(7 DOWNTO 0) := (others => '0')
      );
end program_rom;

architecture Behavioral of program_rom is
	constant max_program_count : integer := 6;
	type program_array_type is array (0 to max_program_count) of std_logic_vector(7 downto 0);
	signal program_array : program_array_type := (x"11", x"21", x"05", x"00", x"00", x"00", x"00");
begin

process(CLK)
variable addr_int : integer := 0;
begin
	if rising_edge(CLK) then
		addr_int := to_integer(unsigned(ADDR));
		if addr_int > max_program_count - 1 then
			DATA <= (others => '0');
		else
			DATA <= program_array(addr_int);
		end if;
	end if;
end process;

end Behavioral;
