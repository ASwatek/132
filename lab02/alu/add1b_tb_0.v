module add1b_add1b_sch_tb();

// Inputs
   reg b;
   reg ci;
   reg a;

// Output
   wire r;
   wire co;

// Bidirs

// Instantiate the UUT
   add1b UUT (
		.b(b), 
		.ci(ci), 
		.r(r), 
		.co(co), 
		.a(a)
   );
// Initialize Inputs
initial begin
  ci = 0;
  b = 0;
  a = 0;
  // Wait 100ns for the simulator to finish initializing
  #99;
  a = 1;
  #1;
  if ((r == 1) && (co == 0))
    $display("okay 1");
  else
    $display("fail 1");
  // Wait 100ns for the simulator to finish initializing
  #99;
  a = 1;
  b = 1;
  ci =0;
  #1;
  if ((r == 0) && (co == 1))
    $display("okay 2");
  else
    $display("fail 2");
  // Wait 100ns for the simulator to finish initializing
  #99;
  ci = 1;
  b = 0;
  a = 0;
  #1;
  if ((r == 1) && (co == 0))
    $display("okay 3");
  else
    $display("fail 3");
  // Wait 100ns for the simulator to finish initializing
  #99;
  a = 1; 
  b = 1;
  ci = 1;
  #1;
  if ((r == 1) && (co == 1))
    $display("okay 4");
  else
    $display("fail 4");
end
endmodule