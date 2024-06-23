library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity alu is
	Port (
		CLK : in STD_LOGIC;
		EN : in STD_LOGIC;
		OP_A : in STD_LOGIC_VECTOR(7 downto 0);
		OP_B : in STD_LOGIC_VECTOR(7 downto 0);
		CMD : in STD_LOGIC_VECTOR(7 downto 0);
		PASSTHROUGH : in STD_LOGIC;
		RESULT: out STD_LOGIC_VECTOR(7 downto 0)
	);
end alu;

architecture Behavioral of alu is

begin

process(CLK)
variable op_a_int : integer := 0;
variable op_b_int : integer := 0;
variable result_int : integer := 0;
begin
	if rising_edge(CLK) then
		if EN = '0' then
			RESULT <= (others => '0');
		else
			if PASSTHROUGH = '1' then
				RESULT <= CMD;
			else
				op_a_int := to_integer(unsigned(OP_A));
				op_b_int := to_integer(unsigned(OP_B));
				result_int := op_a_int + op_b_int;
				RESULT <= std_logic_vector(to_unsigned(result_int, RESULT'length));
			end if;
		end if;
	end if;
end process;

end architecture;
