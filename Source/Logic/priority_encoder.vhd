library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity priority_encoder is
	Port (
		CLK : in STD_LOGIC;
		DATA_IN : in STD_LOGIC_VECTOR(7 downto 0) := (others => '0');
		DATA_OUT : out STD_LOGIC_VECTOR(2 downto 0) := (others => '0');
		DATA_OUT_VALID : out STD_LOGIC := '0'
	);
end priority_encoder;

architecture Behavioral of priority_encoder is
begin

process(CLK)
variable data_out_int : integer := 0;
begin
	if rising_edge(CLK) then
		if DATA_IN = std_logic_vector(to_unsigned(0, DATA_IN'length)) then
			DATA_OUT_VALID <= '0';
		else
			DATA_OUT_VALID <= '1';
		end if;

		data_out_int := 0;
		if DATA_IN(0) = '1' then
			data_out_int := 0;
		elsif DATA_IN(1) = '1' then
			data_out_int := 1;
		elsif DATA_IN(2) = '1' then
			data_out_int := 2;
		elsif DATA_IN(3) = '1' then
			data_out_int := 3;
		elsif DATA_IN(4) = '1' then
			data_out_int := 4;
		elsif DATA_IN(5) = '1' then
			data_out_int := 5;
		elsif DATA_IN(6) = '1' then
			data_out_int := 6;
		elsif DATA_IN(7) = '1' then
			data_out_int := 7;
		end if;
		DATA_OUT <= std_logic_vector(to_unsigned(data_out_int, DATA_OUT'length));
	end if;
end process;

end architecture;
