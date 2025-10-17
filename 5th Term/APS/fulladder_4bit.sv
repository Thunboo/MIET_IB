module fulladder_4bit(
  input  logic [3:0] a_i,      
  input  logic [3:0] b_i,      
  input  logic       carry_i,  
  
  output logic [3:0] sum_o,    
  output logic       carry_o   
);

  // temp 
  logic [4:0] carry;
  assign carry[0] = carry_i;
  
  fulladder_1bit adder0 (
    .a_i(a_i[0]),
    .b_i(b_i[0]),
    .carry_i(carry[0]),
    .sum_o(sum_o[0]),
    .carry_o(carry[1])
  );
  
  fulladder_1bit adder1 (
    .a_i(a_i[1]),
    .b_i(b_i[1]),
    .carry_i(carry[1]),
    .sum_o(sum_o[1]),
    .carry_o(carry[2])
  );
  
  fulladder_1bit adder2 (
    .a_i(a_i[2]),
    .b_i(b_i[2]),
    .carry_i(carry[2]),
    .sum_o(sum_o[2]),
    .carry_o(carry[3])
  );
  
  fulladder_1bit adder3 (
    .a_i(a_i[3]),
    .b_i(b_i[3]),
    .carry_i(carry[3]),
    .sum_o(sum_o[3]),
    .carry_o(carry[4])
  );
  
  assign carry_o = carry[4];

endmodule