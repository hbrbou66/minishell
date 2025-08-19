# Minishell

A simplified shell implementation in C that provides basic shell functionality including command execution, pipes, redirections, and built-in commands.

## Documentation

For comprehensive documentation including system architecture, data flow analysis, and visual schemas, see:

**📁 [Minishell_Architecture_Documentation/](./Minishell_Architecture_Documentation/)**

### Quick Documentation Guide:

- **[README_DOCUMENTATION.md](./Minishell_Architecture_Documentation/README_DOCUMENTATION.md)** - Start here for an overview of all documentation
- **[FULL_SYSTEM_SCHEMA.md](./Minishell_Architecture_Documentation/FULL_SYSTEM_SCHEMA.md)** - Complete system architecture with visual diagrams
- **[DETAILED_STRUCT_FLOW.md](./Minishell_Architecture_Documentation/DETAILED_STRUCT_FLOW.md)** - Detailed linked list and struct analysis
- **Visual Schemas** - SVG diagrams showing parsing and execution flows

## Building and Running

```bash
make
./minishell
```

## Features

- Interactive command line with readline support
- Command execution with PATH resolution
- Built-in commands: `cd`, `echo`, `env`, `export`, `unset`, `pwd`, `exit`
- I/O redirection: `<`, `>`, `>>`
- Here documents: `<<`
- Pipes: `|`
- Environment variable expansion: `$VAR`
- Signal handling (Ctrl+C, Ctrl+\)
- Command history

## Project Structure

```
minishell/
├── minishell.c              # Main entry point
├── minishell.h              # Header file with all structures
├── Makefile                 # Build configuration
├── memory.c                 # Custom memory management
├── parse/                   # Parsing and tokenization
├── exec/                    # Command execution
├── utils/                   # Utility functions
└── Minishell_Architecture_Documentation/  # Complete documentation suite
```
