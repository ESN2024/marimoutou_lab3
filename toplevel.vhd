library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity toplevel is
	port (

		CLK                             : in    std_logic                    := '0'; --                      clk.clk
		SCL : inout std_logic                    := '0'; -- opencores_i2c_0_export_0.scl_pad_io
		SDA : inout std_logic                    := '0'; --  .sda_pad_io
		RESET                       : in    std_logic                    := '0'; --      reset.reset_n
		BTN                          : in    std_logic                    := '0'; -- btn.export
		SEG1     : out   std_logic_vector(7 downto 0);        -- seg1_external_connection.export
		SEG2     : out   std_logic_vector(7 downto 0);        -- seg2_external_connection.export
		SEG3     : out   std_logic_vector(7 downto 0);        -- seg3_external_connection.export
		SEG4     : out   std_logic_vector(7 downto 0);        -- seg4_external_connection.export
		SEG5     : out   std_logic_vector(7 downto 0)         -- seg5_external_connection.export
	);
end entity toplevel;

architecture rtl of toplevel is
	component lab3 is
		port (
			clk_clk                             : in    std_logic := 'X'; -- clk
			reset_reset_n                       : in    std_logic := 'X'; -- reset_n
			opencores_i2c_0_export_0_scl_pad_io : inout std_logic := 'X'; -- scl_pad_io
			opencores_i2c_0_export_0_sda_pad_io : inout std_logic := 'X';  -- sda_pad_io
			btn_export                          : in    std_logic := 'X'; -- export
			seg1_external_connection_export     : out   std_logic_vector(3 downto 0);        -- export
			seg2_external_connection_export     : out   std_logic_vector(3 downto 0);        -- export
			seg4_external_connection_export     : out   std_logic_vector(3 downto 0);        -- export
			seg5_external_connection_export     : out   std_logic_vector(3 downto 0);        -- export
			seg3_external_connection_export     : out   std_logic_vector(3 downto 0)         -- export
		);
	end component lab3;
	
	component BCD7SEG is
		port (
			input : in std_logic_vector(3 downto 0) := (others => 'X'); 
			output : out std_logic_vector(7 downto 0)
		);
	end component BCD7SEG;
	
signal segment1 : std_logic_vector(3 downto 0);
signal segment2 : std_logic_vector(3 downto 0);
signal segment3 : std_logic_vector(3 downto 0);
signal segment4 : std_logic_vector(3 downto 0);
signal segment5 : std_logic_vector(3 downto 0);
	
begin
 
	u0 : component lab3
		port map (
			clk_clk                             => CLK,      --clk.clk
			reset_reset_n                       => RESET,    -- reset.reset_n
			opencores_i2c_0_export_0_scl_pad_io => SCL, -- .scl_pad_io
			opencores_i2c_0_export_0_sda_pad_io => SDA,  -- .sda_pad_io
			btn_export                          => BTN,      -- btn.export
			seg1_external_connection_export     => segment1,     -- seg1_external_connection.export
			seg2_external_connection_export     => segment2,     -- seg2_external_connection.export
			seg4_external_connection_export     => segment4,     -- seg4_external_connection.export
			seg5_external_connection_export     => segment5,     -- seg5_external_connection.export
			seg3_external_connection_export     => segment3      -- seg3_external_connection.export
		);
		
	u1 : component BCD7SEG
		port map (
			input => segment1,
			output => SEG1
		);

	u2 : component BCD7SEG
		port map (
			input => segment2,
			output => SEG2
		);
		
	u3 : component BCD7SEG
		port map (
			input => segment3,
			output => SEG3
		);		
		
	u4 : component BCD7SEG
		port map (
			input => segment4,
			output => SEG4
		);
		
	u5 : component BCD7SEG
		port map (
			input => segment5,
			output => SEG5
		);	
		
end architecture;