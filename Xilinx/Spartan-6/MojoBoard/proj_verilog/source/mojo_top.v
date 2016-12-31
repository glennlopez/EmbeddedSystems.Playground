module mojo_top(
    input clk,
    input rst_n,
    input cclk,
    output [7:0] led,
    output spi_miso,
    input spi_ss,
    input spi_mosi,
    input spi_sck,
    output [3:0] spi_channel,
    input avr_tx,
    output avr_rx,
    input avr_rx_busy
  );
  
  wire rst = ~rst_n;
  
  assign spi_miso = 1'bz;
  assign avr_rx = 1'bz;
  assign spi_channel = 4'bzzzz;
  
  assign led = 8'b0;
  
endmodule