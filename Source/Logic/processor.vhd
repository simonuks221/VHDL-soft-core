library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity processor is
	Port (
		CLK_12 : in STD_LOGIC;
        LED_1 : inout STD_LOGIC;
        LED_2 : inout STD_LOGIC;
        RGB_R : inout STD_LOGIC;
        RGB_G : inout STD_LOGIC;
        RGB_B : inout STD_LOGIC;
        BTN_1 : inout STD_LOGIC;
        BTN_2 : inout STD_LOGIC
	);
end processor;

architecture Behavioral of processor is

    component processor_core is
        Port (
            CLK : in STD_LOGIC;
            PROGRAM_MEMORY_D : in STD_LOGIC_VECTOR(7 downto 0);
            PROGRAM_MEMORY_A : out STD_LOGIC_VECTOR(7 downto 0);
            DATA_BUS_CORE_D : out STD_LOGIC_VECTOR(7 downto 0);
		    DATA_BUS_MEMORY_D : in STD_LOGIC_VECTOR(7 downto 0);
		    DATA_BUS_A : out STD_LOGIC_VECTOR(7 downto 0);
            DATA_BUS_WR : out STD_LOGIC
        );
    end component;

    component program_rom is
        PORT (
            CLK : IN STD_LOGIC;
            ADDR : IN STD_LOGIC_VECTOR(7 DOWNTO 0);
            DATA : OUT STD_LOGIC_VECTOR(7 DOWNTO 0)
          );
    end component;

    component gpio is
        generic (
            DATA_WIDTH : integer := 8;
            ADDR_WIDTH : integer := 8;
            ADDR_BASE : integer := 50;
            GPIO_USED : integer := 8
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
            ADDR   : in  std_logic_vector(7 downto 0);
            DATA_IN  : in  std_logic_vector(7 downto 0);
            DATA_OUT : out std_logic_vector(7 downto 0) := (others => '0')
        );
    end component;

    signal program_memory_d : STD_LOGIC_VECTOR(7 downto 0);
    signal program_memory_a : STD_LOGIC_VECTOR(7 downto 0);
    -- Data bus
    signal data_bus_core_d : STD_LOGIC_VECTOR(7 downto 0);
    signal data_bus_memory_d : STD_LOGIC_VECTOR(7 downto 0);
    signal data_bus_a : STD_LOGIC_VECTOR(7 downto 0);
    signal data_bus_wr : STD_LOGIC;
    signal data_bus_memory_led1_d : STD_LOGIC_VECTOR(7 downto 0);
    --GPIO
    signal gpio_bank_1_7 : STD_LOGIC := '0';
begin

data_bus_memory_d <= data_bus_memory_led1_d;

core_1 : processor_core port map(CLK_12, program_memory_d, program_memory_a, data_bus_core_d, data_bus_memory_d, data_bus_a, data_bus_wr);
program_rom_1 : program_rom port map(CLK_12, program_memory_a, program_memory_d);
gpio_bank_1 : gpio generic map (8, 8, 50, 7) port map(CLK_12, LED_1, LED_2, RGB_R, RGB_G, RGB_B, BTN_1, BTN_2, gpio_bank_1_7, data_bus_wr, data_bus_a, data_bus_core_d, data_bus_memory_led1_d);

end architecture;
