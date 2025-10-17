module fulladder_32bit(
  input  logic [31:0] a_i,      
  input  logic [31:0] b_i,      
  input  logic        carry_i,  
  
  output logic [31:0] sum_o,    
  output logic        carry_o   
);

  logic [8:0] carry;
  assign carry[0] = carry_i;
  
  fulladder_4bit adder0 (
    .a_i(a_i[3:0]),
    .b_i(b_i[3:0]),
    .carry_i(carry[0]),
    .sum_o(sum_o[3:0]),
    .carry_o(carry[1])
  );
  
  fulladder_4bit adder1 (
    .a_i(a_i[7:4]),
    .b_i(b_i[7:4]),
    .carry_i(carry[1]),
    .sum_o(sum_o[7:4]),
    .carry_o(carry[2])
  );
  
  fulladder_4bit adder2 (
    .a_i(a_i[11:8]),
    .b_i(b_i[11:8]),
    .carry_i(carry[2]),
    .sum_o(sum_o[11:8]),
    .carry_o(carry[3])
  );
  
  fulladder_4bit adder3 (
    .a_i(a_i[15:12]),
    .b_i(b_i[15:12]),
    .carry_i(carry[3]),
    .sum_o(sum_o[15:12]),
    .carry_o(carry[4])
  );
  
  fulladder_4bit adder4 (
    .a_i(a_i[19:16]),
    .b_i(b_i[19:16]),
    .carry_i(carry[4]),
    .sum_o(sum_o[19:16]),
    .carry_o(carry[5])
  );
  
  fulladder_4bit adder5 (
    .a_i(a_i[23:20]),
    .b_i(b_i[23:20]),
    .carry_i(carry[5]),
    .sum_o(sum_o[23:20]),
    .carry_o(carry[6])
  );
  
  fulladder_4bit adder6 (
    .a_i(a_i[27:24]),
    .b_i(b_i[27:24]),
    .carry_i(carry[6]),
    .sum_o(sum_o[27:24]),
    .carry_o(carry[7])
  );
  
  fulladder_4bit adder7 (
    .a_i(a_i[31:28]),
    .b_i(b_i[31:28]),
    .carry_i(carry[7]),
    .sum_o(sum_o[31:28]),
    .carry_o(carry[8])
  );
  
  assign carry_o = carry[8];

endmodule