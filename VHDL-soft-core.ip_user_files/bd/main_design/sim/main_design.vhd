--Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
--Copyright 2022-2024 Advanced Micro Devices, Inc. All Rights Reserved.
----------------------------------------------------------------------------------
--Tool Version: Vivado v.2024.1 (win64) Build 5076996 Wed May 22 18:37:14 MDT 2024
--Date        : Tue Jun 18 17:54:21 2024
--Host        : DESKTOP-5JRNHLO running 64-bit major release  (build 9200)
--Command     : generate_target main_design.bd
--Design      : main_design
--Purpose     : IP block netlist
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity main_design is
  port (
    BTN1 : in STD_LOGIC;
    BTN2 : in STD_LOGIC;
    CLK_IN_12MHz : in STD_LOGIC;
    LED1 : out STD_LOGIC;
    LED2 : out STD_LOGIC;
    RGB_B : out STD_LOGIC;
    RGB_G : out STD_LOGIC;
    RGB_R : out STD_LOGIC
  );
  attribute CORE_GENERATION_INFO : string;
  attribute CORE_GENERATION_INFO of main_design : entity is "main_design,IP_Integrator,{x_ipVendor=xilinx.com,x_ipLibrary=BlockDiagram,x_ipName=main_design,x_ipVersion=1.00.a,x_ipLanguage=VHDL,numBlks=6,numReposBlks=6,numNonXlnxBlks=0,numHierBlks=0,maxHierDepth=0,numSysgenBlks=0,numHlsBlks=0,numHdlrefBlks=6,numPkgbdBlks=0,bdsource=USER,synth_mode=Hierarchical}";
  attribute HW_HANDOFF : string;
  attribute HW_HANDOFF of main_design : entity is "main_design.hwdef";
end main_design;

architecture STRUCTURE of main_design is
  component main_design_program_rom_impl_0_0 is
  port (
    CLK : in STD_LOGIC;
    ADDR : in STD_LOGIC_VECTOR ( 7 downto 0 );
    DATA : out STD_LOGIC_VECTOR ( 7 downto 0 )
  );
  end component main_design_program_rom_impl_0_0;
  component main_design_pc_0_0 is
  port (
    CLK : in STD_LOGIC;
    P_COUNTER : out STD_LOGIC_VECTOR ( 7 downto 0 )
  );
  end component main_design_pc_0_0;
  component main_design_alu_0_0 is
  port (
    CLK : in STD_LOGIC;
    EN : in STD_LOGIC;
    OP_A : in STD_LOGIC_VECTOR ( 7 downto 0 );
    OP_B : in STD_LOGIC_VECTOR ( 7 downto 0 );
    RESULT : out STD_LOGIC_VECTOR ( 7 downto 0 )
  );
  end component main_design_alu_0_0;
  component main_design_decoder_0_0 is
  port (
    CLK : in STD_LOGIC;
    INSTRUCTION : in STD_LOGIC_VECTOR ( 7 downto 0 );
    DATA_OUT : out STD_LOGIC_VECTOR ( 7 downto 0 );
    EN_ALU : out STD_LOGIC;
    PUSH : out STD_LOGIC;
    POP : out STD_LOGIC
  );
  end component main_design_decoder_0_0;
  component main_design_stack_ram_imp_1_0 is
  port (
    CLK : in STD_LOGIC;
    DATA_IN : in STD_LOGIC_VECTOR ( 7 downto 0 );
    TOP_DATA : out STD_LOGIC_VECTOR ( 7 downto 0 );
    NEXT_DATA : out STD_LOGIC_VECTOR ( 7 downto 0 );
    PUSH : in STD_LOGIC;
    POP : in STD_LOGIC;
    WRITE_TOP : in STD_LOGIC
  );
  end component main_design_stack_ram_imp_1_0;
  component main_design_stack_data_bus_0_0 is
  port (
    DATA_1 : in STD_LOGIC_VECTOR ( 7 downto 0 );
    DATA_2 : in STD_LOGIC_VECTOR ( 7 downto 0 );
    DATA_OUT : out STD_LOGIC_VECTOR ( 7 downto 0 )
  );
  end component main_design_stack_data_bus_0_0;
  signal CLK_IN_12MHz_1 : STD_LOGIC;
  signal alu_0_RESULT : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal decoder_0_DATA_OUT : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal decoder_0_EN_ALU : STD_LOGIC;
  signal decoder_0_POP : STD_LOGIC;
  signal decoder_0_PUSH : STD_LOGIC;
  signal pc_0_P_COUNTER : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal program_rom_impl_0_DATA : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal stack_data_bus_0_DATA_OUT : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal stack_ram_imp_1_NEXT_DATA : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal stack_ram_imp_1_TOP_DATA : STD_LOGIC_VECTOR ( 7 downto 0 );
begin
  CLK_IN_12MHz_1 <= CLK_IN_12MHz;
alu_0: component main_design_alu_0_0
     port map (
      CLK => CLK_IN_12MHz_1,
      EN => decoder_0_EN_ALU,
      OP_A(7 downto 0) => stack_ram_imp_1_TOP_DATA(7 downto 0),
      OP_B(7 downto 0) => stack_ram_imp_1_NEXT_DATA(7 downto 0),
      RESULT(7 downto 0) => alu_0_RESULT(7 downto 0)
    );
decoder_0: component main_design_decoder_0_0
     port map (
      CLK => CLK_IN_12MHz_1,
      DATA_OUT(7 downto 0) => decoder_0_DATA_OUT(7 downto 0),
      EN_ALU => decoder_0_EN_ALU,
      INSTRUCTION(7 downto 0) => program_rom_impl_0_DATA(7 downto 0),
      POP => decoder_0_POP,
      PUSH => decoder_0_PUSH
    );
pc_0: component main_design_pc_0_0
     port map (
      CLK => CLK_IN_12MHz_1,
      P_COUNTER(7 downto 0) => pc_0_P_COUNTER(7 downto 0)
    );
program_rom_impl_0: component main_design_program_rom_impl_0_0
     port map (
      ADDR(7 downto 0) => pc_0_P_COUNTER(7 downto 0),
      CLK => CLK_IN_12MHz_1,
      DATA(7 downto 0) => program_rom_impl_0_DATA(7 downto 0)
    );
stack_data_bus_0: component main_design_stack_data_bus_0_0
     port map (
      DATA_1(7 downto 0) => alu_0_RESULT(7 downto 0),
      DATA_2(7 downto 0) => decoder_0_DATA_OUT(7 downto 0),
      DATA_OUT(7 downto 0) => stack_data_bus_0_DATA_OUT(7 downto 0)
    );
stack_ram_imp_1: component main_design_stack_ram_imp_1_0
     port map (
      CLK => CLK_IN_12MHz_1,
      DATA_IN(7 downto 0) => stack_data_bus_0_DATA_OUT(7 downto 0),
      NEXT_DATA(7 downto 0) => stack_ram_imp_1_NEXT_DATA(7 downto 0),
      POP => decoder_0_POP,
      PUSH => decoder_0_PUSH,
      TOP_DATA(7 downto 0) => stack_ram_imp_1_TOP_DATA(7 downto 0),
      WRITE_TOP => decoder_0_EN_ALU
    );
end STRUCTURE;
