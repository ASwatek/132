// Verilog test fixture created from schematic D:\CSSE\CSSE 132\1819a-csse132-jungs1\lab02\alu\alu1b.sch - Sun Sep 16 13:17:40 2018

`timescale 1ns / 1ps

module alu1b_alu1b_sch_tb();

// Inputs
   reg a;
   reg b;
   reg [2:0] op;
   reg Ci;
   reg less;
// Output
   wire set;
   wire Co;
   wire r;
// Bidirs

// Instantiate the UUT
   alu1b UUT (
		.set(set), 
		.Co(Co), 
		.a(a), 
		.b(b), 
		.op(op), 
		.Ci(Ci), 
		.less(less), 
		.r(r)
   );
// Initialize Inputs
initial begin
  Ci = 0;
  b = 0;
  a = 0;
  op=0;
  less=0;
  // Wait 100ns for the simulator to finish initializing
  #100;
  a = 1;
  b=1;
  op=3'b000;
  #1;
  if ((r == 1))
    $display("okay 1 and 1 = 1");
  else
    $display("fail 1 and 1");
  #100;
  a = 1;
  b=0;
  op=3'b001;
  #1;
  if ((r == 1))
    $display("okay 1 or 0 = 1");
  else
    $display("fail 1 ro 0");
  #100;
  a = 1;
  b= 1;
  op=3'b010;
  #1;
  if ((r == 0) && (Co == 1))
    $display("okay 1+1=10"); 
  else
    $display("fail 1 + 1");
	 
  #100;
  a = 1;
  b=  0;
  op=3'b110;
  #1;
  if ((r == 0) && (Co == 1))
    $display("okay 1- -1=10");
  else
    $display("fail 1 --1");
end
endmodule