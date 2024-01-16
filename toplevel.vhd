library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity toplevel is
	port (
		CLK                             : in    std_logic := '0'; -- clk.clk
		SCL : inout std_logic := '0'; -- .scl_pad_io
		SDA : inout std_logic := '0'; --                         .sda_pad_io
		RESET                       : in    std_logic := '0'  -- reset.reset_n
	);
end entity toplevel;

architecture rtl of toplevel is
	component lab3 is
		port (
			clk_clk                             : in    std_logic := 'X'; -- clk
			reset_reset_n                       : in    std_logic := 'X'; -- reset_n
			opencores_i2c_0_export_0_scl_pad_io : inout std_logic := 'X'; -- scl_pad_io
			opencores_i2c_0_export_0_sda_pad_io : inout std_logic := 'X'  -- sda_pad_io
		);
	end component lab3;

begin
 
	u0 : component lab3
		port map (
			clk_clk                             => CLK,      --clk.clk
			reset_reset_n                       => RESET,    -- reset.reset_n
			opencores_i2c_0_export_0_scl_pad_io => SCL, -- .scl_pad_io
			opencores_i2c_0_export_0_sda_pad_io => SDA  -- .sda_pad_io
		);

end architecture;