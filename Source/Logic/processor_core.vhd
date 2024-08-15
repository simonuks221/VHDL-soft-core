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
			STORE_EN: out STD_LOGIC;
			NEW_PC_EN: in STD_LOGIC;
			NEW_PC: in STD_LOGIC_VECTOR(7 downto 0) := (others => '0')
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
			STACK_SOURCE: out STD_LOGIC_VECTOR(1 downto 0);
			NEW_PC_EN: out STD_LOGIC;
			NEW_PC_IF_TRUE: out STD_LOGIC;
			MEMORY_WRITE: out STD_LOGIC
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

	component ram is
		Port (
			CLK    : in  std_logic;
			WE     : in  std_logic;
			ADDR   : in  std_logic_vector(7 downto 0);
			DATA_IN  : in  std_logic_vector(7 downto 0);
			DATA_OUT : out std_logic_vector(7 downto 0)
		);
	end component;

	constant stack_source_immediate : STD_LOGIC_VECTOR(1 downto 0) := "00";
    constant stack_source_alu : STD_LOGIC_VECTOR(1 downto 0) := "01";
    constant stack_source_memory : STD_LOGIC_VECTOR(1 downto 0) := "10";

	--Instruction
	signal decode_en: STD_LOGIC := '0';
	signal execute_en: STD_LOGIC := '0';
	signal store_en: STD_LOGIC := '0';
	signal new_pc_en: STD_LOGIC := '0';
	signal new_pc_condition: STD_LOGIC := '0';
	signal new_pc : STD_LOGIC_VECTOR(7 downto 0) := (others => '0');
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
	signal decoder_new_pc: STD_LOGIC := '0';
	signal new_pc_if_true: STD_LOGIC := '0';
	signal decoder_memory_write: STD_LOGIC := '0';
	--ALU
	signal alu_data : STD_LOGIC_VECTOR(7 downto 0) := (others => '0');
	--RAM
	signal memory_data : STD_LOGIC_VECTOR(7 downto 0) := (others => '0');
	signal ram_memory_write: STD_LOGIC := '0';
begin

stack_data_in <= decoder_data when stack_source = stack_source_immediate else
				alu_data when stack_source = stack_source_alu else
				memory_data when stack_source = stack_source_memory else
				(others => '0');

new_pc_en <= new_pc_condition and decoder_new_pc;

process(CLK)
begin
	if rising_edge(CLK) then
		if EXECUTE_EN = '1' then
			if new_pc_if_true = '1' and stack_next = std_logic_vector(to_unsigned(1, stack_next'length)) then
				new_pc_condition <= '1';
			elsif new_pc_if_true = '0' and stack_next /= std_logic_vector(to_unsigned(1, stack_next'length)) then
				new_pc_condition <= '1';
			else
				new_pc_condition <= '0';
			end if;
		end if;
	end if;
end process;

new_pc <= stack_top;
ram_memory_write <= decoder_memory_write and STORE_EN;

pc_1 : pc port map(CLK, PROGRAM_MEMORY_A, decode_en, execute_en, store_en, new_pc_en, new_pc);

stack_1 : stack port map(CLK, STORE_EN, stack_data_in, stack_top, stack_next, stack_push, stack_pop, stack_amount,
						overflow, underflow);

decoder_1 : decoder port map (CLK, DECODE_EN, PROGRAM_MEMORY_D, decoder_data, alu_op, stack_push, stack_pop, stack_amount,
							stack_source, decoder_new_pc, new_pc_if_true, decoder_memory_write);

alu_1 : alu port map (CLK, EXECUTE_EN, stack_top, stack_next, alu_op, alu_data);

ram_1 : ram port map(CLK, ram_memory_write, stack_top, stack_next, memory_data);

end architecture;
