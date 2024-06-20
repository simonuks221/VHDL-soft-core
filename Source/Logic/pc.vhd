library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity pc is
  Port (
    CLK: in STD_LOGIC;
    P_COUNTER: out STD_LOGIC_VECTOR(7 downto 0) := (others => '0')
  );
end pc;

architecture Behavioral of pc is
	signal internal_counter : integer range 0 to 255 := 0;
begin

process(CLK)
begin
	if rising_edge(CLK) then
		internal_counter <= internal_counter + 1; --TODO: could be a problem that PC is delayed by 1
		P_COUNTER <= std_logic_vector(to_unsigned(internal_counter, P_COUNTER'length));
	end if;
end process;

end architecture;
