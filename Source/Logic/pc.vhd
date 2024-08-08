library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity pc is
	Port (
		CLK: in STD_LOGIC;
		P_COUNTER: out STD_LOGIC_VECTOR(7 downto 0) := (others => '0');
		DECODE_EN: out STD_LOGIC;
		EXECUTE_EN: out STD_LOGIC;
		STORE_EN: out STD_LOGIC;
		NEW_PC_EN: in STD_LOGIC;
		NEW_PC: in STD_LOGIC_VECTOR(7 downto 0) := (others => '0')
	);
end pc;

architecture Behavioral of pc is
	signal internal_counter : integer range 0 to 255 := 0;
	signal delay_counter : integer range 0 to 4 := 0;
begin

P_COUNTER <= std_logic_vector(to_unsigned(internal_counter, P_COUNTER'length));

process(CLK)
begin
	if rising_edge(CLK) then
		DECODE_EN <= '0';
		EXECUTE_EN <= '0';
		STORE_EN <= '0';
		delay_counter <= delay_counter + 1;
		case delay_counter is
			when 0 =>
				if NEW_PC_EN = '1' then
					internal_counter <= to_integer(unsigned(NEW_PC));
				else
					internal_counter <= internal_counter + 1; --TODO: could be a problem that PC is delayed by 1
				end if;
			when 1 =>
				DECODE_EN <= '1';
			when 2 =>
				EXECUTE_EN <= '1';
			when 3 =>
				STORE_EN <= '1';
				delay_counter <= 0;
			when others =>

		end case;
	end if;
end process;

end architecture;
