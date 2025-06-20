# `clox` – A Bytecode Virtual Machine for Lox (in C)

## 📘 Overview

This is my implementation of **clox**, the compiler described in *Crafting Interpreters* by Robert Nystrom. **clox** compiles a made-up high-level language called Lox to bytecode and executes it on a stack-based virtual machine written in C.

My version closely follows the book and derives from its codebase, but includes original debugging, test scripts, structural commentary, and extended tooling.

## 🛠 Features
- ✅ Bytecode compiler for Lox language
- ✅ Stack-based VM with lexical scoping
- ✅ Closures and upvalue capture
- ✅ Mark-and-sweep garbage collection
- ✅ Native function interface
- ✅ String interning
- ✅ Tracing GC with allocation logging
- 🚧 Planned: full test suite
- 🚧 Planned: postmortem memory analyzer

## 📂 Project Structure
- `main.c`
- `scanner.c/h`: Tokenize user code 
- `compiler.c/h`: Parser and bytecode emitter
- `vm.c/h`: Stack machine, call frames, value stack, code execution
- `memory.c/h`: Dynamic memory allocation and mark/sweep garbage collection
- `object.c/h`: Objects including functions, closures, strings
- `chunk.c/h`: Bytecode instruction array
- `value.c/h`: Tagged union / NaN-boxing value system
- `debug.c/h`: Bytecode disassembly and tracing

## 🔧 Setup
```bash
git clone https://github.com/inceid/clox.git
cd clox
make
./lox
```

## 🚀 Usage
- Run a script: `./lox ./main path/to/script.lox`
- Interactive REPL: just run `./lox` without arguments

Debug flags: users can build `clox` with several optional flags to aid codetracing:
```bash
make DEBUG_FLAGS="-DDEBUG_TRACE_EXECUTION -DDEBUG_PRINT_CODE -DDEBUG_STRESS_GC -DDEBUG_LOG_GC
"
```

Current features:
- Expressions, variables, and control flow
- Functions and closures
- Classes (if implemented)
- Native functions like `clock()`

## 📝 Development Notes

This project includes several nontrivial debugging experiments:
- Implemented deeper tracking of `upvalue` and `closure` behavior to ensure correct capture across nested scopes
- Tuned compiler design to make lexical scoping and closures feel intuitive and clean
- Planning a dedicated test runner and profiler to assess runtime performance and memory usage

Next steps:
- Add unit tests for GC edge cases
- Build a profiler or logging VM mode
- Write documentation for internals and memory layout

## 🧠 Learn More
- 📘 [Crafting Interpreters](https://craftinginterpreters.com/)
- 🛠 Compiler theory: Appel, Aho-Ullman, Wirth

## 📄 License
MIT License

## 👤 Author
Suraj Joshi  
[GitHub](https://github.com/inceid) • [Website](#)
