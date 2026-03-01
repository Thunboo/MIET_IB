`timescale 1ns / 1ps

module CYBERcobra
  import memory_pkg::INSTR_MEM_SIZE_BYTES;
  import memory_pkg::INSTR_MEM_SIZE_WORDS;
 (
  input  logic         clk_i,
  input  logic         rst_i,
  input  logic [15:0]  sw_i,
  output logic [31:0]  out_o
);

logic [31:0] pr_cnt;//счетчик (PC)
logic [31:0] pc_adder_res;//рез-т сумматора счетчика
logic [31:0] max_pc; // Максимальный валидный адрес
assign max_pc = (INSTR_MEM_SIZE_WORDS - 1) * 4; 
logic [31:0] adder_ms_res;//рез-т мультиплексора сумматора
logic [31:0] current_inst;//текущая инструкция
logic alu_flag;

//Program counter
always_ff @(posedge clk_i) begin
 if (rst_i)
    pr_cnt <= '0;
 else 
    pr_cnt <= pc_adder_res;
end

//Сигнал управления мультиплексором, выбирающий слагаемое для программного счётчика
assign ms2_sw = current_inst[31] | ( current_inst[30] & alu_flag ); //30 бит инстр. - branch; 31 - безусл.перход(jump)

//Мультиплексор, выбирающий слагаемое для программного счётчика
always_comb begin
case(ms2_sw)
    0: adder_ms_res = 32'd4; //прибавляем 4 (если у нас не инструкция условного перехода) 
    1: adder_ms_res = { {22{current_inst[12]}},current_inst[12:5], 2'b00 }; //прибавляем знакорасшир.const*4
//(если сейчас инстр. условного перехода и условие перехода выполнилось) или (сейчас инструкция безусловного перехода)
endcase
end

//Сумматор PC
fulladder_32bit inst(
    .a_i(pr_cnt),
    .b_i(adder_ms_res),
    .carry_i(1'b0),
    //
    .sum_o(pc_adder_res)
 );
 
 instr_mem imem(
    .read_addr_i(pr_cnt),
    .read_data_o(current_inst)
 );
 
 alu inst2(
    .a_i(RD1),
    .b_i(RD2),
    .alu_op_i(current_inst[27:23]),
    .flag_o(alu_flag),
    .result_o(alu_res)
    );
 
 //Сигнал управления MS регистрового файла
 logic[1:0] ms4_sw;
 assign ms4_sw = current_inst[29:28];
 logic [31:0] WD;
 logic [31:0] alu_res;
 
 //Мультиплексор, выбирающий источник записи в регистровый файл.
 always_comb begin
    case(ms4_sw)
        0: WD = { {9{current_inst[27]}} ,current_inst[27:5] };//загрузка константы из инструкции 
        1: WD = alu_res; // рез-т АЛУ
        2: WD = { {16{sw_i[15]}}, sw_i };//загрузка константы с внешнего источника
        //
        default WD = 32'd0;
     endcase
 end
 //30 бит инстр. - branch; 31 - безусл.перход(jump)
 //Сигнал разрешения записи в регистровый файл
 //будет равен 0 если сейчас инструкция условного или безусловного перехода
 assign WE = ~( current_inst[30] | current_inst[31] );
 logic [31:0] RD1;
 logic [31:0] RD2;
 
 register_file inst3(
    .clk_i (clk_i),
    .write_enable_i(WE),
    .write_addr_i(current_inst[4:0]),
    .read_addr1_i(current_inst[22:18]),
    .read_addr2_i(current_inst[17:13]),
    .write_data_i(WD),
 
    .read_data1_o(RD1),
    .read_data2_o(RD2)


);
assign out_o = RD1;
  
endmodule