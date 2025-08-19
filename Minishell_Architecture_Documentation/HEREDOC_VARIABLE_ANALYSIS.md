# Advanced Command Analysis: Heredoc with Environment Variables

## Command Example: `cat << EOF > $HOME/output_$USER.txt`

This example demonstrates heredoc processing with environment variable expansion.

---

## Stage 1: Initial Input and Environment Context

### Input Command
```c
char *input = "cat << EOF > $HOME/output_$USER.txt";
```

### Environment Variables (t_env linked list)
```c
// Environment node 1: HOME
t_env *env_home = {
    .key = "HOME",
    .value = "/home/hbou-dou",
    .next = env_user
};

// Environment node 2: USER
t_env *env_user = {
    .key = "USER",
    .value = "hbou-dou",
    .next = env_path
};

// Environment node 3: PATH
t_env *env_path = {
    .key = "PATH",
    .value = "/usr/local/bin:/usr/bin:/bin",
    .next = NULL
};
```

---

## Stage 2: Token List Before Expansion

### Raw Token List Structure
```c
// Token 1: "cat"
t_token *token1 = {
    .type = WORD,
    .value = "cat",
    .next = token2,
    .previous = NULL,
    .fd_reder = -1,
    .heredoc_expn = 0,
    .ambg = 0,
    .removed = 0
};

// Token 2: "<<"
t_token *token2 = {
    .type = HERDOC,
    .value = "<<",
    .next = token3,
    .previous = token1,
    .fd_reder = -1,    // Will be set during processing
    .heredoc_expn = 0,
    .ambg = 0,
    .removed = 0
};

// Token 3: "EOF"
t_token *token3 = {
    .type = DELEMTER,
    .value = "EOF",
    .next = token4,
    .previous = token2,
    .fd_reder = -1,
    .heredoc_expn = 0, // No expansion in delimiter
    .ambg = 0,
    .removed = 0
};

// Token 4: ">"
t_token *token4 = {
    .type = R_OUT,
    .value = ">",
    .next = token5,
    .previous = token3,
    .fd_reder = -1,
    .heredoc_expn = 0,
    .ambg = 0,
    .removed = 0
};

// Token 5: "$HOME/output_$USER.txt" (before expansion)
t_token *token5 = {
    .type = EXPAN,     // Contains variables to expand
    .value = "$HOME/output_$USER.txt",
    .next = NULL,
    .previous = token4,
    .fd_reder = -1,
    .heredoc_expn = 0,
    .ambg = 0,
    .removed = 0
};
```

### Token List Visualization (Before Expansion)
```
[WORD:"cat"] <-> [HERDOC:"<<"] <-> [DELEMTER:"EOF"] <-> [R_OUT:">"] <-> [EXPAN:"$HOME/output_$USER.txt"]
```

---

## Stage 3: Variable Expansion Process

### Variable Parsing (utils/split_var.c)
For token5 value `"$HOME/output_$USER.txt"`:

```c
// Variable list created by s_var()
t_var *var_list = {
    // First variable: $HOME
    {
        .value = "$HOME",      // Will be expanded to "/home/hbou-dou"
        .type = VAR,
        .next = var2
    },

    // Literal text: "/output_"
    {
        .value = "/output_",
        .type = WORD_V,
        .next = var3
    },

    // Second variable: $USER
    {
        .value = "$USER",      // Will be expanded to "hbou-dou"
        .type = VAR,
        .next = var4
    },

    // Literal text: ".txt"
    {
        .value = ".txt",
        .type = WORD_V,
        .next = NULL
    }
};
```

### After Variable Expansion (exp_val)
```c
// Token 5 after expansion
t_token *token5_expanded = {
    .type = WORD,      // Changed from EXPAN to WORD
    .value = "/home/hbou-dou/output_hbou-dou.txt", // Fully expanded
    .next = NULL,
    .previous = token4,
    .fd_reder = -1,
    .heredoc_expn = 0,
    .ambg = 0,
    .removed = 1       // Marked as processed
};
```

---

## Stage 4: Heredoc Processing

### Heredoc Context Setup (t_heredoc_ctx)
```c
t_heredoc_ctx ctx = {
    .tmp_file = "/tmp/12345678",    // Temporary file path
    .fd_in = 7,                     // Read file descriptor
    .fd_out = 8,                    // Write file descriptor
    .status = 0                     // Success status
};
```

### Heredoc File Creation Process
```c
// 1. Create temporary file
ctx.fd_out = open("/tmp/12345678", O_TRUNC | O_WRONLY | O_CREAT, 0777);  // fd = 8

// 2. Open for reading
ctx.fd_in = open("/tmp/12345678", O_RDONLY);  // fd = 7

// 3. Immediately unlink (file deleted but fds remain open)
unlink("/tmp/12345678");
```

### User Input Collection (ft_heredoc_handle)
```bash
minishell> cat << EOF > /home/hbou-dou/output_hbou-dou.txt
> Hello World!
> This is line 2
> Variable expansion: hbou-dou
> EOF
```

### Heredoc Data Flow
```c
// User inputs collected:
char *inputs[] = {
    "Hello World!",
    "This is line 2",
    "Variable expansion: hbou-dou",
    "EOF"  // Delimiter - stops collection
};

// Written to temporary file (fd=8):
"Hello World!\n"
"This is line 2\n"
"Variable expansion: hbou-dou\n"
// EOF delimiter not written
```

### Updated Token After Heredoc Processing
```c
// Token 2 after heredoc processing
t_token *token2_processed = {
    .type = HERDOC,
    .value = "<<",
    .next = token3,
    .previous = token1,
    .fd_reder = 7,     // Set to read file descriptor
    .heredoc_expn = 0,
    .ambg = 0,
    .removed = 0
};
```

---

## Stage 5: Execution Node Creation

### Single Execution Node
```c
t_exec *exec_node = {
    .fd_in = 7,        // Heredoc file descriptor (replaces stdin)
    .fd_out = 9,       // Output file descriptor (/home/hbou-dou/output_hbou-dou.txt)
    .cmd = "/bin/cat", // Resolved command path
    .cmd_args = {
        [0] = "cat",
        [1] = NULL     // No additional arguments
    },
    .next = NULL,      // Single command
    .flag = 0          // No errors
};
```

### File Descriptor Setup Details
```c
// Output file opening
int output_fd = open("/home/hbou-dou/output_hbou-dou.txt",
                     O_RDWR | O_CREAT | O_TRUNC, 0644);  // fd = 9

// File descriptor state:
// fd 0: stdin (unused)
// fd 1: stdout (unused)
// fd 2: stderr (available for errors)
// fd 7: heredoc temporary file (input)
// fd 9: output file (output)
```

---

## Stage 6: Process Execution

### Single Process Execution (No Fork Needed for Builtin)
Since `cat` is not a builtin, fork/exec is used:

```c
// Fork process
pid_t pid = fork();  // Returns child PID (e.g., 2468)

if (pid == 0) {
    // In child process:

    // 1. Duplicate file descriptors
    dup2(7, 0);   // Redirect stdin to heredoc file
    dup2(9, 1);   // Redirect stdout to output file

    // 2. Close unused file descriptors
    close(7);     // Close original heredoc fd
    close(9);     // Close original output fd

    // 3. Execute cat command
    execve("/bin/cat", ["cat", NULL], envp);
}
```

### Parent Process Wait
```c
// In parent process:
close(7);         // Close heredoc fd (child owns it now)
close(9);         // Close output fd (child owns it now)

int status;
waitpid(2468, &status, 0);  // Wait for child to complete

// Check exit status
if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
    // Success: cat completed successfully
    e_status(0, 1);
} else {
    // Error occurred
    e_status(1, 1);
}
```

---

## Stage 7: Memory and Resource Management

### File Descriptor Tracking
```c
// File descriptors in use during execution:
struct fd_tracker {
    int heredoc_read;    // 7 - temporary heredoc file
    int output_write;    // 9 - final output file
    int stdin_backup;    // 10 - saved stdin for restoration
    int stdout_backup;   // 11 - saved stdout for restoration
};
```

### Memory Allocation Tracking
```c
// Memory allocated during processing:
t_memory *memory_chain = {
    // Token list
    {
        .address = 0x7f8b4c001000,  // token1
        .next = mem2
    },

    // Expanded filename
    {
        .address = 0x7f8b4c001100,  // "/home/hbou-dou/output_hbou-dou.txt"
        .next = mem3
    },

    // Execution node
    {
        .address = 0x7f8b4c001200,  // exec_node
        .next = mem4
    },

    // Heredoc temporary file path
    {
        .address = 0x7f8b4c001300,  // "/tmp/12345678"
        .next = NULL
    }
};
```

### Cleanup Process
```c
// 1. Close all file descriptors
if (exec_node->fd_in > 2) close(exec_node->fd_in);    // Close heredoc fd
if (exec_node->fd_out > 2) close(exec_node->fd_out);  // Close output fd

// 2. Free all tracked memory
ft_malloc(0, CLEAR_DATA);  // Triggers cleanup of entire memory chain

// 3. Reset shell state
shell_ctx->lst = NULL;
shell_ctx->exec = NULL;
```

---

## Stage 8: Final Result

### Output File Contents
File: `/home/hbou-dou/output_hbou-dou.txt`
```
Hello World!
This is line 2
Variable expansion: hbou-dou
```

### Shell State After Completion
```c
t_shell final_state = {
    .input = "cat << EOF > $HOME/output_$USER.txt",  // Original input preserved
    .expn = NULL,                                     // No longer needed
    .lst = NULL,                                      // Cleaned up
    .exec = NULL,                                     // Cleaned up
    .envp = env_home                                  // Environment preserved
};

// Exit status: 0 (success)
// Ready for next command
```

This detailed analysis shows how complex commands with heredocs and variable expansion are processed, maintaining proper resource management and data structure integrity throughout the entire flow.
