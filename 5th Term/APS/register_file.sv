import memory_pkg::*;

module instr_mem
import memory_pkg::INSTR_MEM_SIZE_BYTES;
import memory_pkg::INSTR_MEM_SIZE_WORDS;
(
  input  logic [31:0] read_addr_i,
  output logic [31:0] read_data_o
);

  logic [31:0] ROM [INSTR_MEM_SIZE_WORDS];  // создать память с
                                            // <INSTR_MEM_SIZE_WORDS>
                                            // 32-битных ячеек

  initial begin
    $readmemh("program.mem", ROM);          // поместить в память ROM содержимое
  end                                       // файла program.mem

  // Реализация асинхронного порта на чтение, где на выход идёт ячейка памяти
  // инструкций, расположенная по адресу read_addr_i, в котором отброшены два
  // младших бита, а также биты, двоичный вес которых превышает размер памяти
  // данных в байтах.
  // Два младших бита отброшены, чтобы обеспечить выровненный доступ к памяти,
  // в то время как старшие биты отброшены, чтобы не дать обращаться в память
  // по адресам несуществующих ячеек (вместо этого будут выданы данные ячеек,
  // расположенных по младшим адресам).
  assign read_data_o = ROM[read_addr_i[$clog2(INSTR_MEM_SIZE_BYTES)-1:2]];
  // clog2 - выравнивание памяти, чтобы каждая ячейка была равна 4 байтам
  // 1 слово - 4 байта. 0.5 слова - 2 байта
  // слово = инструкция
endmodule

module register_file(
  input  logic        clk_i,
  input  logic        write_enable_i,

  input  logic [ 4:0] write_addr_i, //  синхронная
  input  logic [ 4:0] read_addr1_i, // асинхронная
  input  logic [ 4:0] read_addr2_i, // асинхронная

  input  logic [31:0] write_data_i,
  output logic [31:0] read_data1_o,
  output logic [31:0] read_data2_o
);

    logic [31:0] rf_mem [31:0];

    // Синхронная запись с защитой нулевого регистра
    // ff - flip-flops
    // posedge - по возрастающему фронту - с перехода 0->1
    // negedge - по    убывающему фронту - с перехода 1->0
    
    // Триггер (ff) смотрит (@) на возрастающий фронт (posedge) сигнала (clk_i)
    always_ff @(posedge clk_i) begin
        // Если записываем И адрес не 5b00000, то мы записываем 
        // НЕблокирующим присваиванием (потому что НЕ комбинационная схема, а
        // схема с синхроимпульсом clk_i)
        if (write_enable_i && (write_addr_i != 5'b0)) begin
            rf_mem[write_addr_i] <= write_data_i;
        end
    end

    // Асинхронное чтение порта 1
    assign read_data1_o = (read_addr1_i == 5'b0) ? 32'b0 : rf_mem[read_addr1_i];

    // Асинхронное чтение порта 2  
    assign read_data2_o = (read_addr2_i == 5'b0) ? 32'b0 : rf_mem[read_addr2_i];
endmodule

