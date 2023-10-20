module counter #(
    parameter WIDTH = 8
)(
    // interface signals
    input logic clk,
    input logic rst,
    input logic en,
    output logic [WIDTH-1:0] count 
);

always_ff @(posedge clk, negedge rst) begin
    if (rst) count <= {WIDTH{1'b0}}; 
    else 
        count <= (en) ? count + 1 : count -1;
end
endmodule
