library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity processor_core is
	Port (
		CLK : in STD_LOGIC;
		PROGRAM_MEMORY_D : in STD_LOGIC_VECTOR(7 downto 0);
		PROGRAM_MEMORY_A : out STD_LOGIC_VECTOR(7 downto 0)
	);
end processor_core;

architecture Behavioral of processor_core is

	component pc is
		Port (
			CLK: in STD_LOGIC;
			P_COUNTER: out STD_LOGIC_VECTOR(7 downto 0);
			DECODE_EN: out STD_LOGIC;
			EXECUTE_EN: out STD_LOGIC;
			STORE_EN: out STD_LOGIC
		);
	end component;

	component stack is
		Port (
			CLK : in STD_LOGIC;
			WR_EN : in STD_LOGIC;
			DATA_IN : in STD_LOGIC_VECTOR (7 downto 0);
			TOP_DATA : out STD_LOGIC_VECTOR (7 downto 0);
			NEXT_DATA : out STD_LOGIC_VECTOR (7 downto 0);
			PUSH : in STD_LOGIC;
			POP : in STD_LOGIC;
			AMOUNT : STD_LOGIC_VECTOR(4 downto 0);
			OVERFLOW : out STD_LOGIC := '0';
        	UNDERFLOW : out STD_LOGIC := '0'
		);
	end component;

	component decoder is
		Port (
			CLK : in STD_LOGIC;
			EN : in STD_LOGIC;
			INSTRUCTION: in STD_LOGIC_VECTOR(7 downto 0);
			DATA_OUT: out STD_LOGIC_VECTOR(7 downto 0);
			ALU_OP: out STD_LOGIC_VECTOR(3 downto 0);
			STACK_PUSH: out STD_LOGIC;
			STACK_POP: out STD_LOGIC;
			STACK_AMOUNT: out STD_LOGIC_VECTOR(4 downto 0);
			STACK_SOURCE: out STD_LOGIC_VECTOR(1 downto 0)
		);
	end component;

	component alu is
		Port (
			CLK : in STD_LOGIC;
			EN : in STD_LOGIC;
			OP_A : in STD_LOGIC_VECTOR(7 downto 0);
			OP_B : in STD_LOGIC_VECTOR(7 downto 0);
			CMD : in STD_LOGIC_VECTOR(3 downto 0);
			RESULT : out STD_LOGIC_VECTOR(7 downto 0)
		);
	end component;

	constant stack_source_immediate : STD_LOGIC_VECTOR(1 downto 0) := "00";
    constant stack_source_alu : STD_LOGIC_VECTOR(1 downto 0) := "01";
    constant stack_source_memory : STD_LOGIC_VECTOR(1 downto 0) := "10";

	--Instruction
	signal DECODE_EN: STD_LOGIC := '0';
	signal EXECUTE_EN: STD_LOGIC := '0';
	signal STORE_EN: STD_LOGIC := '0';
	--Stack signals
	signal stack_data_in : STD_LOGIC_VECTOR(7 downto 0) := (others => '0');
	signal stack_top : STD_LOGIC_VECTOR(7 downto 0) := (others => '0');
	signal stack_next : STD_LOGIC_VECTOR(7 downto 0) := (others => '0');
	signal overflow : STD_LOGIC := '0';
	signal underflow : STD_LOGIC := '0';
	--Decoder signals
	signal stack_push : STD_LOGIC := '0';
	signal stack_pop : STD_LOGIC := '0';
	signal stack_amount : STD_LOGIC_VECTOR(4 downto 0);
	signal decoder_data : STD_LOGIC_VECTOR(7 downto 0) := (others => '0');
	signal stack_source: STD_LOGIC_VECTOR(1 downto 0) := (others => '0');
	signal alu_op: STD_LOGIC_VECTOR(3 downto 0) := (others => '0');
	--ALU
	signal alu_data : STD_LOGIC_VECTOR(7 downto 0) := (others => '0');

	--UNUSED
	signal memory_data : STD_LOGIC_VECTOR(7 downto 0) := (others => '0');
begin

stack_data_in <= decoder_data when stack_source = stack_source_immediate else
				alu_data when stack_source = stack_source_alu else
				memory_data when stack_source = stack_source_memory else
				(others => '0');

pc_1 : pc port map(CLK, PROGRAM_MEMORY_A, DECODE_EN, EXECUTE_EN, STORE_EN);

stack_1 : stack port map(CLK, STORE_EN, stack_data_in, stack_top, stack_next, stack_push, stack_pop, stack_amount,
						overflow, underflow);

decoder_1 : decoder port map (CLK, DECODE_EN, PROGRAM_MEMORY_D, decoder_data, alu_op, stack_push, stack_pop, stack_amount, stack_source);

alu_1 : alu port map (CLK, EXECUTE_EN, stack_top, stack_next, alu_op, alu_data);

end architecture;
