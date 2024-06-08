--Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
--Copyright 2022-2024 Advanced Micro Devices, Inc. All Rights Reserved.
----------------------------------------------------------------------------------
--Tool Version: Vivado v.2024.1 (win64) Build 5076996 Wed May 22 18:37:14 MDT 2024
--Date        : Sat Jun  8 19:15:16 2024
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
  attribute CORE_GENERATION_INFO of main_design : entity is "main_design,IP_Integrator,{x_ipVendor=xilinx.com,x_ipLibrary=BlockDiagram,x_ipName=main_design,x_ipVersion=1.00.a,x_ipLanguage=VHDL,numBlks=1,numReposBlks=1,numNonXlnxBlks=0,numHierBlks=0,maxHierDepth=0,numSysgenBlks=0,numHlsBlks=0,numHdlrefBlks=1,numPkgbdBlks=0,bdsource=USER,synth_mode=Hierarchical}";
  attribute HW_HANDOFF : string;
  attribute HW_HANDOFF of main_design : entity is "main_design.hwdef";
end main_design;

architecture STRUCTURE of main_design is
  component main_design_main_0_0 is
  port (
    CLK_IN_12MHz : in STD_LOGIC;
    LED1 : out STD_LOGIC;
    LED2 : out STD_LOGIC;
    BTN1 : in STD_LOGIC;
    BTN2 : in STD_LOGIC;
    RGB_R : out STD_LOGIC;
    RGB_G : out STD_LOGIC;
    RGB_B : out STD_LOGIC
  );
  end component main_design_main_0_0;
  signal BTN1_0_1 : STD_LOGIC;
  signal BTN2_0_1 : STD_LOGIC;
  signal CLK_IN_12MHz_0_1 : STD_LOGIC;
  signal main_0_LED1 : STD_LOGIC;
  signal main_0_LED2 : STD_LOGIC;
  signal main_0_RGB_B : STD_LOGIC;
  signal main_0_RGB_G : STD_LOGIC;
  signal main_0_RGB_R : STD_LOGIC;
begin
  BTN1_0_1 <= BTN1;
  BTN2_0_1 <= BTN2;
  CLK_IN_12MHz_0_1 <= CLK_IN_12MHz;
  LED1 <= main_0_LED1;
  LED2 <= main_0_LED2;
  RGB_B <= main_0_RGB_B;
  RGB_G <= main_0_RGB_G;
  RGB_R <= main_0_RGB_R;
main_0: component main_design_main_0_0
     port map (
      BTN1 => BTN1_0_1,
      BTN2 => BTN2_0_1,
      CLK_IN_12MHz => CLK_IN_12MHz_0_1,
      LED1 => main_0_LED1,
      LED2 => main_0_LED2,
      RGB_B => main_0_RGB_B,
      RGB_G => main_0_RGB_G,
      RGB_R => main_0_RGB_R
    );
end STRUCTURE;
