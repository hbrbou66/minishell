# Minishell Architecture Documentation

## Overview

This documentation provides a comprehensive analysis of the minishell project architecture, including detailed schemas of the parsing and execution processes.

## Documentation Files

### 1. [FULL_SYSTEM_SCHEMA.md](FULL_SYSTEM_SCHEMA.md)
Complete system overview with embedded visual schemas covering:
- **System Architecture**: High-level flow from input to output
- **Parsing Flow**: Detailed parsing process with visual diagram
- **Execution Flow**: Complete execution pipeline with visual diagram
- **Data Structures**: Key structures and their relationships
- **Error Handling**: Comprehensive error management system
- **Memory Management**: Custom allocation and cleanup system

### 2. [CODE_FLOW_ANALYSIS.md](CODE_FLOW_ANALYSIS.md)
Detailed code-level analysis with concrete examples:
- **Complete Command Trace**: Step-by-step execution of `echo "Hello $USER" > output.txt`
- **Pipeline Processing**: How `ls -la | grep .txt | wc -l` flows through the system
- **Memory Management**: Allocation tracking and cleanup mechanisms
- **Error Scenarios**: Handling of various error conditions
- **Signal Processing**: SIGINT and signal management

### 3. [DETAILED_STRUCT_FLOW.md](DETAILED_STRUCT_FLOW.md)
Complete linked list and struct content analysis:
- **Exact Structure Contents**: Shows real t_token and t_exec data at each stage
- **Linked List Connections**: Forward/backward pointers and relationships
- **Memory Layout**: Actual memory addresses and allocation tracking
- **File Descriptor States**: Detailed FD management through execution
- **Environment Variables**: t_env linked list structure and usage

### 4. [HEREDOC_VARIABLE_ANALYSIS.md](HEREDOC_VARIABLE_ANALYSIS.md)
Advanced command processing with complex features:
- **Heredoc Processing**: Complete `cat << EOF > $HOME/output.txt` analysis
- **Variable Expansion**: Multi-variable parsing and substitution
- **Temporary File Management**: Heredoc file creation and cleanup
- **Complex Data Structures**: Advanced t_var and t_heredoc_ctx usage

### 3. Visual Schemas

#### [parsing_schema.svg](parsing_schema.svg)
Visual representation of the parsing process showing:
- Input validation stages
- Tokenization process
- Variable expansion
- Token type assignments
- Final structure preparation

#### [execution_schema.svg](execution_schema.svg) 
Visual representation of the execution process showing:
- Token-to-exec conversion
- Builtin vs external command decision
- Fork/exec process flow
- File descriptor management
- Pipeline coordination

#### [detailed_struct_schema.svg](detailed_struct_schema.svg)
Comprehensive visualization showing:
- **Actual struct contents** at each processing stage
- **Linked list connections** with forward/backward pointers
- **Memory addresses** and allocation tracking
- **File descriptor flow** through the system
- **Process tree** with real PID values

## Key Architecture Features

### 1. **Modular Design**
- Clear separation between parsing and execution phases
- Independent validation, tokenization, and expansion stages
- Separate handling for builtins vs external commands

### 2. **Robust Error Handling**
- Comprehensive input validation
- Graceful error recovery
- Proper resource cleanup on errors
- Signal-safe operations

### 3. **Memory Safety**
- Custom memory allocator with tracking
- Automatic cleanup on exit or error
- No memory leaks in normal operation

### 4. **Process Management**
- Safe fork/exec for external commands
- Proper signal handling for interactive use
- Pipeline coordination with pipes
- File descriptor management

### 5. **Feature Completeness**
- Full shell parsing (quotes, variables, redirections)
- Built-in commands (cd, echo, env, export, unset, pwd, exit)
- I/O redirection (<, >, >>, <<)
- Environment variable expansion
- Command pipelines
- History support

## Data Flow Summary

```
User Input (readline)
    ↓
Syntax Validation (ft_parse_command)
    ↓
Tokenization (s_cmd, ft_split)
    ↓
Variable Expansion (ft_expand)
    ↓
Execution Structure (convert_token_to_exec)
    ↓
Command Execution (execution)
    ├── Builtins (direct function calls)
    └── External (fork/exec)
    ↓
Result Output & Status
```

## Usage

1. **For Understanding**: Start with `FULL_SYSTEM_SCHEMA.md` for the big picture
2. **For Implementation Details**: Refer to `CODE_FLOW_ANALYSIS.md` for specific code flows
3. **For Data Structure Details**: Use `DETAILED_STRUCT_FLOW.md` to see exact struct contents
4. **For Advanced Features**: Check `HEREDOC_VARIABLE_ANALYSIS.md` for complex scenarios
5. **For Visual Learning**: Use the SVG diagrams to understand process flows
6. **For Debugging**: Use the error handling sections to understand failure modes

## File Structure

```
minishell/
├── README.md                          # Main project README
├── minishell.c                        # Main entry point  
├── minishell.h                        # Header with all structures
├── parse/                             # Parsing implementation
├── exec/                              # Execution implementation
├── utils/                             # Utility functions
└── Minishell_Architecture_Documentation/
    ├── FULL_SYSTEM_SCHEMA.md          # Complete system documentation
    ├── CODE_FLOW_ANALYSIS.md          # Detailed code flow examples  
    ├── DETAILED_STRUCT_FLOW.md        # Linked list & struct content analysis
    ├── HEREDOC_VARIABLE_ANALYSIS.md   # Advanced command processing examples
    ├── README_DOCUMENTATION.md        # This overview file
    ├── parsing_schema.svg             # Parsing process diagram
    ├── execution_schema.svg           # Execution process diagram
    ├── detailed_struct_schema.svg     # Struct content visualization
    ├── parsing_schema.dot             # Graphviz source for parsing
    └── execution_schema.dot           # Graphviz source for execution
```

This documentation suite provides everything needed to understand, maintain, and extend the minishell implementation.
