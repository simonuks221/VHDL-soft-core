library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity alu is
	Port (
		CLK : in STD_LOGIC;
		EN : in STD_LOGIC; --TODO: not used, delete
		OP_A : in STD_LOGIC_VECTOR(7 downto 0); --TOP of stack
		OP_B : in STD_LOGIC_VECTOR(7 downto 0); --NEXT of stack
		CMD : in STD_LOGIC_VECTOR(2 downto 0);
		RESULT: out STD_LOGIC_VECTOR(7 downto 0)
	);
end alu;

architecture Behavioral of alu is

begin

process(CLK)
variable op_a_int : integer := 0;
variable op_b_int : integer := 0;
variable result_int : integer := 0;
variable shifted_val : std_Logic_vector(7 downto 0) := (others => '0');
begin
	if rising_edge(CLK) then
		op_a_int := to_integer(unsigned(OP_A));
		op_b_int := to_integer(unsigned(OP_B));
		case CMD is
			when "000" =>
				result_int := op_a_int + op_b_int;
				RESULT <= std_logic_vector(to_unsigned(result_int, RESULT'length));
			when "001" =>
				result_int := op_a_int - op_b_int;
				RESULT <= std_logic_vector(to_unsigned(result_int, RESULT'length));
			when "010" =>
				result_int := op_a_int * op_b_int;
				RESULT <= std_logic_vector(to_unsigned(result_int, RESULT'length));
			when "011" =>
				--Shift right
				--DIY barrel shifter, could be a costly implementation TODO: check
				shifted_val := OP_B(7 downto 0);
				if OP_A(0) = '1' then
					shifted_val := '0' & shifted_val(7 downto 1);
				end if;
				if OP_A(1) = '1' then
					shifted_val := "00" & shifted_val(7 downto 2);
				end if;
				if OP_A(2) = '1' then
					shifted_val := "0000" & shifted_val(7 downto 4);
				end if;
				result_int := to_integer(unsigned(shifted_val));
				RESULT <= std_logic_vector(to_unsigned(result_int, RESULT'length));
			when "100" =>
				--Shift left
				shifted_val := OP_B(7 downto 0);
				if OP_A(0) = '1' then
					shifted_val := shifted_val(6 downto 0) & '0';
				end if;
				if OP_A(1) = '1' then
					shifted_val := shifted_val(5 downto 0) & "00";
				end if;
				if OP_A(2) = '1' then
					shifted_val := shifted_val(3 downto 0) & "0000";
				end if;
				result_int := to_integer(unsigned(shifted_val));
				RESULT <= std_logic_vector(to_unsigned(result_int, RESULT'length));
			when "101" =>
				RESULT <= OP_A or OP_B;
			when "110" =>
				RESULT <= OP_A and OP_B;
			when "111" =>
				RESULT <= OP_A xor OP_B;
			when others =>
				RESULT <= (others => '0');
		end case;
	end if;
end process;

end architecture;
