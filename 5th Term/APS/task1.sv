module mod1 (
    input logic a,
    input logic b,
    input logic c,
    input logic d,
    input logic e,
    
    output logic f,
    output logic g
);
    logic ab;
    logic cd;
    logic ed;
    
    assign ab = a & b;
    assign f = ab | (~b);
    assign cd = c ^ d;
    assign ed = d | e;
    assign g = cd & ed;    
    
endmodule

module mod2 (
    input logic A,
    input logic B,
    input logic C,
    input logic D,
    input logic E,
    
    output logic F,
    output logic G
);
    logic f_o;
    logic g_o;
    
    mod1 mod (
        .a(A),
        .b(B),
        .c(~C),
        .d(D),
        .e(E),
        
        .f(f_o),
        .g(g_o)
    );
    
    mod1 modmod (
        .a(f_o),
        .b(g_o),
        .c(~E),
        .d(E),
        .e(E),
        
        .f(F),
        .g(G)
    );

endmodule