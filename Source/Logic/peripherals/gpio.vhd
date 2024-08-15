library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity gpio is
    generic (
        DATA_WIDTH : integer := 8;
        ADDR_WIDTH : integer := 8;
        ADDR_BASE : integer := 50
    );
	port (
		CLK : in STD_LOGIC;
        GPIO_0 : inout STD_LOGIC := 'Z';
        GPIO_1 : inout STD_LOGIC := 'Z';
        GPIO_2 : inout STD_LOGIC := 'Z';
        GPIO_3 : inout STD_LOGIC := 'Z';
        GPIO_4 : inout STD_LOGIC := 'Z';
        GPIO_5 : inout STD_LOGIC := 'Z';
        GPIO_6 : inout STD_LOGIC := 'Z';
        GPIO_7 : inout STD_LOGIC := 'Z';
        WR     : in  std_logic;
        ADDR   : in  std_logic_vector(ADDR_WIDTH-1 downto 0);
        DATA_IN  : in  std_logic_vector(DATA_WIDTH-1 downto 0);
        DATA_OUT : out std_logic_vector(DATA_WIDTH-1 downto 0) := (others => '0')
	);
end gpio;

architecture Behavioral of gpio is
    --Register offset   | 0                              | 1                | 2             |
    --Register meaning  | GPIO state 0 - in, 1 -out R/W  | Output state R/W | Input state R |
    constant REGISTER_AMOUNT : integer := 3;
    constant REGISTER_GPIO_STATE : integer := 0;
    constant REGISTER_OUTPUT_STATE : integer := 1;
    constant REGISTER_INPUT_STATE : integer := 2;

    type registers_type is array (REGISTER_AMOUNT - 1 downto 0) of std_logic_vector(DATA_WIDTH-1 downto 0);
    signal data_registers : registers_type := (others => (others => '0'));
    signal read_addr : std_logic_vector(ADDR_WIDTH-1 downto 0) := (others => '0');
    signal gpio_output_vector : std_logic_vector(7 downto 0) := (others => 'Z');
    signal gpio_input_vector : std_logic_vector(7 downto 0) := (others => 'Z');
begin
    --GPIO outputting
    GPIO_0 <= gpio_output_vector(0);
    GPIO_1 <= gpio_output_vector(1);
    GPIO_2 <= gpio_output_vector(2);
    GPIO_3 <= gpio_output_vector(3);
    GPIO_4 <= gpio_output_vector(4);
    GPIO_5 <= gpio_output_vector(5);
    GPIO_6 <= gpio_output_vector(6);
    GPIO_7 <= gpio_output_vector(7);
    gpio_input_vector(0) <= GPIO_0;
    gpio_input_vector(1) <= GPIO_1;
    gpio_input_vector(2) <= GPIO_2;
    gpio_input_vector(3) <= GPIO_3;
    gpio_input_vector(4) <= GPIO_4;
    gpio_input_vector(5) <= GPIO_5;
    gpio_input_vector(6) <= GPIO_6;
    gpio_input_vector(7) <= GPIO_7;
    --Process GPIO control
    process(CLK)
    begin
        if rising_edge(CLK) then
            for i in 0 to 7 loop
                if data_registers(REGISTER_GPIO_STATE)(i) = '0' then
                    data_registers(REGISTER_INPUT_STATE)(i) <= gpio_input_vector(i);
                else
                    data_registers(REGISTER_INPUT_STATE)(i) <= '0';
                end if;
            end loop;
        end if;
    end process;
    --Process writing to registers
    process(CLK)
    begin
        if rising_edge(CLK) then
            --Write to input state
            for i in 0 to 7 loop
                if data_registers(REGISTER_GPIO_STATE)(i) = '0' then
                    gpio_output_vector(i) <= 'Z';
                else
                    gpio_output_vector(i) <= data_registers(REGISTER_OUTPUT_STATE)(i);
                end if;
            end loop;
            --Write from memory bus
            if WR = '1' then
                case to_integer(unsigned(read_addr)) is
                    when ADDR_BASE + REGISTER_GPIO_STATE =>
                        data_registers(REGISTER_GPIO_STATE) <= DATA_IN;
                    when ADDR_BASE + REGISTER_OUTPUT_STATE =>
                        data_registers(REGISTER_OUTPUT_STATE) <= DATA_IN;
                    when others =>
                        --Do nothing as are read only
                end case;
            end if;
            read_addr <= ADDR;
        end if;
    end process;
    --Process reading register
    process(CLK)
    begin
        if rising_edge(CLK) then
            DATA_OUT <= (others => '0');
            if to_integer(unsigned(read_addr)) >= ADDR_BASE and to_integer(unsigned(read_addr)) <= ADDR_BASE + REGISTER_AMOUNT then
                DATA_OUT <= data_registers((to_integer(unsigned(read_addr)) - ADDR_BASE));
            end if;
        end if;
    end process;
end architecture;
