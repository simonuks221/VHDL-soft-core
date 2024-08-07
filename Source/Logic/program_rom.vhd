library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;
use STD.textio.all;
use ieee.std_logic_textio.all;

entity program_rom is
    PORT (
        CLK : IN STD_LOGIC;
        ADDR : IN STD_LOGIC_VECTOR(7 DOWNTO 0);
        DATA : OUT STD_LOGIC_VECTOR(7 DOWNTO 0) := (others => '0')
      );
end program_rom;

architecture Behavioral of program_rom is
	constant max_program_count : integer := 8;
	type program_array_type is array (0 to max_program_count) of std_logic_vector(7 downto 0);
	--Read from file hexadecimal data
	file file_voltages: text;
	impure function init return program_array_type is
		variable r : program_array_type := (others => (others => '0'));
		variable iline: line;
		variable temp_data : std_logic_vector(7 downto 0);
		begin
			file_open(file_voltages, "rom_preload.txt", read_mode);
			for i in 0 to max_program_count-1 loop
				readline(file_voltages, iline);
				HREAD(iline,temp_data);
				r(i) := temp_data;
			end loop;
		return r;
	end function init;

	signal program_array : program_array_type := init;
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
