library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity alu is
	Port (
		CLK : in STD_LOGIC;
		EN : in STD_LOGIC; --TODO: not used, delete
		OP_A : in STD_LOGIC_VECTOR(7 downto 0);
		OP_B : in STD_LOGIC_VECTOR(7 downto 0);
		CMD : in STD_LOGIC_VECTOR(3 downto 0);
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
		op_a_int := to_integer(unsigned(OP_A));
		op_b_int := to_integer(unsigned(OP_B));
		case CMD is
			when "0000" =>
				result_int := 0;
				RESULT <= std_logic_vector(to_unsigned(result_int, RESULT'length));
			when "0001" =>
				result_int := op_a_int + op_b_int;
				RESULT <= std_logic_vector(to_unsigned(result_int, RESULT'length));
			when "0010" =>
				result_int := op_a_int - op_b_int;
				RESULT <= std_logic_vector(to_unsigned(result_int, RESULT'length));
			when "0011" =>
				result_int := op_a_int * op_b_int;
				RESULT <= std_logic_vector(to_unsigned(result_int, RESULT'length));
			when "0100" =>
				--Shift right
				--TODO
			when "0101" =>
				--Shift left
				--TODO
			when "0110" =>
				RESULT <= OP_A or OP_B;
			when "0111" =>
				RESULT <= OP_A and OP_B;
			when "1000" =>
				RESULT <= OP_A xor OP_B;
			when others =>
				RESULT <= (others => '0');
		end case;
	end if;
end process;

end architecture;
