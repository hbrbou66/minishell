# Minishell Code Flow Analysis

## Command Processing Example: `echo "Hello $USER" > output.txt`

Let's trace how this command flows through the minishell system:

### 1. Input Reception (minishell.c:56-66)
```c
shell_ctx.input = readline("minishell-> ");  // Gets: echo "Hello $USER" > output.txt
if (*shell_ctx.input)
    add_history(shell_ctx.input);
```

### 2. Parsing Phase

#### 2.1 Syntax Validation (ft_parse_command.c)
```c
if (ft_parse_command(shell_ctx.input))  // Returns 0 (valid)
    continue;
```
- Checks quotes: `"Hello $USER"` - valid pairing
- Checks operators: `>` - valid redirection
- Checks brackets: none present - valid

#### 2.2 Command Splitting (utils/ft_split.c)
Input: `"echo "Hello $USER" > output.txt"`
Output: `["echo", "\"Hello $USER\"", ">", "output.txt"]`

#### 2.3 Token List Creation (parse/ft_split_command.c:88-109)
```c
shell_ctx.lst = s_cmd(ft_split(shell_ctx.input), shell_ctx.envp);
```

Tokens created:
1. `{type: WORD, value: "echo"}`
2. `{type: DOUBLE_Q, value: "\"Hello $USER\""}`
3. `{type: R_OUT, value: ">"}`
4. `{type: RED_FILE, value: "output.txt"}`

#### 2.4 Variable Expansion (parse/ft_expend.c:116-134)
```c
if (!shell_ctx.lst || ft_expand(shell_ctx.lst, shell_ctx.envp))
    continue;
```

Token 2 becomes: `{type: WORD, value: "Hello john"}` (assuming USER=john)

### 3. Conversion to Execution Structure

#### 3.1 Token to Exec Conversion (exec/parse_to_exec.c:73-97)
```c
shell_ctx.exec = convert_token_to_exec(shell_ctx.lst, shell_ctx.envp);
```

Creates execution node:
```c
t_exec {
    fd_in: 0,              // stdin
    fd_out: [fd to output.txt],  // opened file descriptor
    cmd: "echo",
    cmd_args: ["echo", "Hello john", NULL],
    next: NULL,
    flag: 0
}
```

#### 3.2 File Descriptor Setup (exec/parse_to_exec_more.c:108-127)
```c
// For "> output.txt"
node->fd_out = open("output.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
```

### 4. Execution Phase

#### 4.1 Execution Decision (exec/exec_main.c:105-120)
```c
int execution(t_exec *exec, t_env **env) {
    if (ft_lstsize(exec) == 1 && is_builtin(exec->cmd))  // echo is builtin
        return (execute_builtin(exec, env, false), 1);
    // ... fork path not taken
}
```

#### 4.2 Builtin Execution (exec/builtins.c)
```c
void execute_builtin(t_exec *exec, t_env **env, bool forked) {
    if (!ft_strcmp(exec->cmd, "echo"))
        ft_echo(exec->cmd_args, exec->fd_out);  // Writes to output.txt
}
```

#### 4.3 Echo Implementation (exec/echo.c:33-52)
```c
int ft_echo(char **cmd, int fd) {
    // cmd = ["echo", "Hello john", NULL]
    // fd = file descriptor for output.txt
    i = 1;  // Skip "echo"
    while (cmd[i]) {
        ft_putstr_fd(cmd[i], fd);  // Write "Hello john" to output.txt
        if (cmd[i + 1])
            write(fd, " ", 1);
        i++;
    }
    write(fd, "\n", 1);  // Add newline
}
```

## Pipeline Example: `ls -la | grep .txt | wc -l`

### Token List After Parsing:
1. `{type: WORD, value: "ls"}`
2. `{type: WORD, value: "-la"}`
3. `{type: PIPE, value: "|"}`
4. `{type: WORD, value: "grep"}`
5. `{type: WORD, value: ".txt"}`
6. `{type: PIPE, value: "|"}`
7. `{type: WORD, value: "wc"}`
8. `{type: WORD, value: "-l"}`

### Execution Nodes Created:
```c
// Node 1: ls -la
t_exec {
    cmd: "/bin/ls",
    cmd_args: ["ls", "-la", NULL],
    fd_in: 0,      // stdin
    fd_out: pipe1[1],  // write end of first pipe
    next: node2
}

// Node 2: grep .txt
t_exec {
    cmd: "/bin/grep",
    cmd_args: ["grep", ".txt", NULL],
    fd_in: pipe1[0],   // read end of first pipe
    fd_out: pipe2[1],  // write end of second pipe
    next: node3
}

// Node 3: wc -l
t_exec {
    cmd: "/usr/bin/wc",
    cmd_args: ["wc", "-l", NULL],
    fd_in: pipe2[0],   // read end of second pipe
    fd_out: 1,         // stdout
    next: NULL
}
```

### Fork-Based Execution:
```c
// For each node:
1. pipe(fd) creates communication channel
2. fork() creates child process
3. Child: setup_child() configures file descriptors
4. Child: execve() replaces process with command
5. Parent: closes unused pipe ends, continues to next command
6. Parent: wait() for all children to complete
```

## Memory Management Flow

### Allocation Tracking (memory.c)
```c
void *ft_malloc(size_t size, int flag) {
    if (flag == ALLOC) {
        // Allocate and add to tracking list
        t_memory *new_node = malloc(sizeof(t_memory));
        new_node->address = malloc(size);
        // Add to global list for cleanup
    } else if (flag == CLEAR_DATA) {
        // Free all tracked allocations
        free_all_tracked_memory();
    }
}
```

### Cleanup Points:
1. After each command execution
2. On error conditions
3. On shell exit
4. On signal interruption (Ctrl+C)

## Error Handling Examples

### Syntax Error Flow:
```bash
minishell-> echo "unclosed quote
```
1. `ft_check_quots()` detects unclosed quote
2. `ft_parse_command()` returns 1 (error)
3. Main loop continues to next prompt
4. No execution phase reached

### Command Not Found:
```bash
minishell-> nonexistent_command
```
1. Parsing succeeds, creates exec node
2. `get_cmd_path()` fails to find command
3. `cmd_not_found()` prints error message
4. Child process exits with status 127
5. Parent receives exit status and sets `e_status(127, 1)`

### Permission Denied:
```bash
minishell-> ./no_execute_permission
```
1. File exists but lacks execute permission
2. `execve()` fails with EACCES
3. `call_execve()` handles error, prints message
4. Child exits with status 126

## Signal Handling Flow

### SIGINT (Ctrl+C) During Command:
```c
// In parent process:
void handler(int sig) {
    if (!recevied_from_input(0, 0))  // Not in heredoc
        ft_putstr_fd("\n", 1);
    rl_replace_line("", 1);        // Clear current line
    rl_on_new_line();              // Move to new line
    if (!recevied_from_input(0, 0))
        rl_redisplay();            // Redisplay prompt
    e_status(130, 1);              // Set interrupted status
}
```

### SIGINT During Heredoc:
```c
void heredoc_signal(int sig) {
    g_check = 1;  // Global flag to terminate heredoc
    close(STDIN_FILENO);  // Break readline loop
}
```

This comprehensive analysis shows how minishell handles the complete flow from user input to command execution, with proper error handling and resource management throughout the process.
