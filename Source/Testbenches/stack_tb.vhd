library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity stack_tb is

end stack_tb;

architecture Behavioral of stack_tb is

	component stack is
		Port (
			CLK : in STD_LOGIC;
			WR_EN : in STD_LOGIC;
			DATA_IN : in STD_LOGIC_VECTOR (7 downto 0);
			TOP_DATA : out STD_LOGIC_VECTOR (7 downto 0);
			NEXT_DATA : out STD_LOGIC_VECTOR (7 downto 0);
			PUSH : in STD_LOGIC;
			POP : in STD_LOGIC;
			AMOUNT : in STD_LOGIC_VECTOR(4 downto 0);
			OVERFLOW : out STD_LOGIC := '0';
			UNDERFLOW : out STD_LOGIC := '0'
		);
	end component;

	signal CLK : STD_LOGIC := '0';
	signal WR_EN : STD_LOGIC := '0';
	signal DATA_IN : STD_LOGIC_VECTOR (7 downto 0) := (others => '0');
	signal TOP_DATA : STD_LOGIC_VECTOR (7 downto 0) := (others => '0');
	signal NEXT_DATA : STD_LOGIC_VECTOR (7 downto 0) := (others => '0');
	signal PUSH : STD_LOGIC := '0';
	signal POP : STD_LOGIC := '0';
	signal AMOUNT : STD_LOGIC_VECTOR(4 downto 0) := (others => '0');
	signal OVERFLOW : STD_LOGIC := '0';
    signal UNDERFLOW : STD_LOGIC := '0';
begin

dut : stack port map(CLK, WR_EN, DATA_IN, TOP_DATA, NEXT_DATA, PUSH, POP, AMOUNT, OVERFLOW, UNDERFLOW);

CLK <= not CLK after 10 ns;

process
begin
	wait for 11ns;
	-- Push several values
	wait until rising_edge(CLK);
	WR_EN <= '1';
	DATA_IN <= x"01";
	PUSH <= '1';
	AMOUNT <= std_logic_vector(to_unsigned(1, AMOUNT'length));
	wait until rising_edge(CLK);
	DATA_IN <= x"02";
	wait until rising_edge(CLK);
	DATA_IN <= x"03";
	--Pop value
	wait until rising_edge(CLK);
	PUSH <= '0';
	POP <= '1';
	AMOUNT <= std_logic_vector(to_unsigned(1, AMOUNT'length));
	--Pop two
	wait until rising_edge(CLK);
	AMOUNT <= std_logic_vector(to_unsigned(2, AMOUNT'length));
	PUSH <= '0';
	POP <= '1';
	wait until rising_edge(CLK);
	PUSH <= '0';
	POP <= '0';
	wait;
end process;

end architecture;
