library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity stack_tb is

end stack_tb;

architecture Behavioral of stack_tb is

	component stack is
		Port (
			CLK : in STD_LOGIC;
			DATA_IN : in STD_LOGIC_VECTOR (7 downto 0);
			TOP_DATA : out STD_LOGIC_VECTOR (7 downto 0);
			NEXT_DATA : out STD_LOGIC_VECTOR (7 downto 0);
			PUSH : in STD_LOGIC;
			POP : in STD_LOGIC
		);
	end component;

	signal CLK : STD_LOGIC := '0';
	signal DATA_IN : STD_LOGIC_VECTOR (7 downto 0) := (others => '0');
	signal TOP_DATA : STD_LOGIC_VECTOR (7 downto 0) := (others => '0');
	signal NEXT_DATA : STD_LOGIC_VECTOR (7 downto 0) := (others => '0');
	signal PUSH : STD_LOGIC := '0';
	signal POP : STD_LOGIC := '0';
begin

dut : stack port map(CLK, DATA_IN, TOP_DATA, NEXT_DATA, PUSH, POP);

CLK <= not CLK after 10 ns;

process
begin
	wait for 11ns;
	-- Push several values
	wait until rising_edge(CLK);
	DATA_IN <= x"11";
	PUSH <= '1';
	wait until rising_edge(CLK);
	DATA_IN <= x"22";
	wait until rising_edge(CLK);
	DATA_IN <= x"FF";
	--Pop value
	wait until rising_edge(CLK);
	PUSH <= '0';
	POP <= '1';
	DATA_IN <= x"00";
	--Write top value
	wait until rising_edge(CLK);
	PUSH <= '1';
	POP <= '1';
	DATA_IN <= x"FF";
	--Pop all
	wait until rising_edge(CLK);
	PUSH <= '0';
	POP <= '1';
	DATA_IN <= x"00";
	wait until rising_edge(CLK);
	PUSH <= '0';
	POP <= '1';
	DATA_IN <= x"00";

	wait until rising_edge(CLK);
	PUSH <= '0';
	POP <= '0';
	DATA_IN <= x"00";
	wait;
end process;

end architecture;
