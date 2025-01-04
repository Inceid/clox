#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"

int main(int argc, const char* argv[]) {
    initVM();

    Chunk chunk;
    initChunk(&chunk);

    int constant = addConstant(&chunk, 1.2);
    int l = 123;

    writeChunk(&chunk, OP_CONSTANT, l);
    writeChunk(&chunk, constant, l);

    constant = addConstant(&chunk, 3.4);
    writeChunk(&chunk, OP_CONSTANT, l);
    writeChunk(&chunk, constant, l);

    writeChunk(&chunk, OP_ADD, l);

    constant = addConstant(&chunk, 5.6); 
    writeChunk(&chunk, OP_CONSTANT, l);
    writeChunk(&chunk, constant, l);
    writeChunk(&chunk, OP_DIVIDE, l);

    writeChunk(&chunk, OP_NEGATE, l);

    writeChunk(&chunk, OP_RETURN, l);
    disassembleChunk(&chunk, "test chunk");
    interpret(&chunk);

    freeVM();

    freeChunk(&chunk);
    return 0;
}