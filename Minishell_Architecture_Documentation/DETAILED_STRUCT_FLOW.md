# Minishell Data Structure Flow Analysis

## Command Example: `ls -la | grep ".txt" > results.txt`

This document traces how the command `ls -la | grep ".txt" > results.txt` flows through the minishell system, showing the exact content of linked lists and structures at each stage.

---

## Stage 1: Input Reception

### Raw Input String
```c
char *input = "ls -la | grep \".txt\" > results.txt";
```

---

## Stage 2: Command Splitting (ft_split)

### Split Array
After `ft_split(input)`:
```c
char **cmd_array = {
    [0] = "ls",
    [1] = "-la", 
    [2] = "|",
    [3] = "grep",
    [4] = "\".txt\"",
    [5] = ">",
    [6] = "results.txt",
    [7] = NULL
};
```

---

## Stage 3: Token List Creation (s_cmd)

### t_token Linked List Structure
After tokenization and type assignment:

```c
// Token 1: "ls"
t_token *token1 = {
    .type = WORD,
    .value = "ls",
    .next = token2,
    .previous = NULL,
    .fd_reder = -1,
    .heredoc_expn = 0,
    .ambg = 0,
    .removed = 0
};

// Token 2: "-la"  
t_token *token2 = {
    .type = WORD,
    .value = "-la",
    .next = token3,
    .previous = token1,
    .fd_reder = -1,
    .heredoc_expn = 0,
    .ambg = 0,
    .removed = 0
};

// Token 3: "|"
t_token *token3 = {
    .type = PIPE,
    .value = "|",
    .next = token4,
    .previous = token2,
    .fd_reder = -1,
    .heredoc_expn = 0,
    .ambg = 0,
    .removed = 0
};

// Token 4: "grep"
t_token *token4 = {
    .type = WORD,
    .value = "grep",
    .next = token5,
    .previous = token3,
    .fd_reder = -1,
    .heredoc_expn = 0,
    .ambg = 0,
    .removed = 0
};

// Token 5: "\".txt\"" (before expansion)
t_token *token5 = {
    .type = DOUBLE_Q,  // Initially DOUBLE_Q, becomes WORD after expansion
    .value = "\".txt\"",
    .next = token6,
    .previous = token4,
    .fd_reder = -1,
    .heredoc_expn = 0,
    .ambg = 0,
    .removed = 0
};

// Token 6: ">"
t_token *token6 = {
    .type = R_OUT,
    .value = ">",
    .next = token7,
    .previous = token5,
    .fd_reder = -1,
    .heredoc_expn = 0,
    .ambg = 0,
    .removed = 0
};

// Token 7: "results.txt"
t_token *token7 = {
    .type = RED_FILE,  // Redirection target file
    .value = "results.txt",
    .next = NULL,
    .previous = token6,
    .fd_reder = -1,
    .heredoc_expn = 0,
    .ambg = 0,
    .removed = 0
};
```

### Token List Visualization
```
[WORD:"ls"] <-> [WORD:"-la"] <-> [PIPE:"|"] <-> [WORD:"grep"] <-> [DOUBLE_Q:"\".txt\""] <-> [R_OUT:">"] <-> [RED_FILE:"results.txt"]
```

---

## Stage 4: After Expansion (ft_expand)

### Updated Token List
After quote removal and type normalization:

```c
// Token 5 after expansion
t_token *token5_expanded = {
    .type = WORD,        // Changed from DOUBLE_Q to WORD
    .value = ".txt",     // Quotes removed
    .next = token6,
    .previous = token4,
    .fd_reder = -1,
    .heredoc_expn = 0,
    .ambg = 0,
    .removed = 1        // Marked as processed
};
```

### Final Token List Visualization
```
[WORD:"ls"] <-> [WORD:"-la"] <-> [PIPE:"|"] <-> [WORD:"grep"] <-> [WORD:".txt"] <-> [R_OUT:">"] <-> [RED_FILE:"results.txt"]
```

---

## Stage 5: Execution Node Creation (convert_token_to_exec)

### t_exec Linked List Structure

The token list is converted into execution nodes, split by pipes:

```c
// Execution Node 1: "ls -la"
t_exec *exec_node1 = {
    .fd_in = 0,                    // stdin
    .fd_out = 4,                   // pipe1[1] (write end of first pipe)
    .cmd = "/bin/ls",              // Full path resolved
    .cmd_args = {
        [0] = "ls",
        [1] = "-la", 
        [2] = NULL
    },
    .next = exec_node2,
    .flag = 0                      // No errors
};

// Execution Node 2: "grep .txt > results.txt"  
t_exec *exec_node2 = {
    .fd_in = 5,                    // pipe1[0] (read end of first pipe)
    .fd_out = 6,                   // File descriptor for results.txt
    .cmd = "/bin/grep",            // Full path resolved
    .cmd_args = {
        [0] = "grep",
        [1] = ".txt",
        [2] = NULL
    },
    .next = NULL,
    .flag = 0                      // No errors
};
```

### Execution List Visualization
```
[Node1: ls -la | fd_out=pipe] -> [Node2: grep .txt > results.txt | fd_in=pipe, fd_out=file] -> NULL
```

---

## Stage 6: File Descriptor Setup

### Pipe Creation
```c
int pipe1[2];
pipe(pipe1);  // Creates: pipe1[0] = 5 (read), pipe1[1] = 4 (write)
```

### File Opening
```c
int results_fd = open("results.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);  // Returns fd = 6
```

### Updated Execution Nodes with FDs
```c
exec_node1->fd_out = 4;  // Write to pipe
exec_node2->fd_in = 5;   // Read from pipe  
exec_node2->fd_out = 6;  // Write to results.txt
```

---

## Stage 7: Process Execution

### Fork Tree Structure
```
Parent Process (minishell)
    ├── Child 1 (PID: 1234)
    │   ├── Command: /bin/ls -la
    │   ├── fd_in: 0 (stdin)
    │   ├── fd_out: 4 (pipe1[1])
    │   └── execve("/bin/ls", ["ls", "-la", NULL], envp)
    │
    └── Child 2 (PID: 1235)  
        ├── Command: /bin/grep .txt
        ├── fd_in: 5 (pipe1[0])
        ├── fd_out: 6 (results.txt)
        └── execve("/bin/grep", ["grep", ".txt", NULL], envp)
```

### Process State During Execution
```c
// In parent process (minishell)
pid_t child1_pid = 1234;
pid_t child2_pid = 1235;
int pipe1[2] = {5, 4};  // {read_fd, write_fd}
int results_fd = 6;

// Parent closes unused pipe ends
close(pipe1[0]);  // Parent doesn't read from pipe
close(pipe1[1]);  // Parent doesn't write to pipe  
close(results_fd); // Parent doesn't write to file

// Wait for children
waitpid(child1_pid, &status1, 0);
waitpid(child2_pid, &status2, 0);
```

---

## Stage 8: Environment Structure During Execution

### t_env Linked List (Environment Variables)
```c
t_env *env_list = {
    // PATH variable
    {
        .key = "PATH",
        .value = "/usr/local/bin:/usr/bin:/bin",
        .next = env_node2
    },
    
    // USER variable  
    {
        .key = "USER", 
        .value = "hbou-dou",
        .next = env_node3
    },
    
    // HOME variable
    {
        .key = "HOME",
        .value = "/home/hbou-dou", 
        .next = env_node4
    },
    
    // PWD variable
    {
        .key = "PWD",
        .value = "/home/hbou-dou/Desktop/minishell",
        .next = NULL
    }
};
```

---

## Stage 9: Memory Allocation Tracking

### t_memory Linked List (Custom Allocator)
```c
// Memory tracking during execution
t_memory *memory_list = {
    // Token list allocation
    {
        .address = 0x7f8b4c000010,  // token1 address
        .next = mem_node2
    },
    
    // Command arguments allocation
    {
        .address = 0x7f8b4c000020,  // exec_node1->cmd_args address
        .next = mem_node3  
    },
    
    // Command path allocation
    {
        .address = 0x7f8b4c000030,  // "/bin/ls" string address
        .next = mem_node4
    },
    
    // Execution nodes allocation
    {
        .address = 0x7f8b4c000040,  // exec_node1 address
        .next = NULL
    }
};
```

---

## Stage 10: Signal Handling Context

### Signal State Structure
```c
// Signal handling during execution
struct signal_context {
    pid_t current_child = 1234;     // Currently executing child
    int pipe_fds[4] = {4, 5, 6, -1}; // Open file descriptors to close on signal
    bool in_heredoc = false;         // Not in heredoc for this command
    int saved_stdin = 0;            // Original stdin fd
};

// Signal handler setup
signal(SIGINT, handler);    // Ctrl+C handling
signal(SIGQUIT, SIG_IGN);   // Ignore Ctrl+\
```

---

## Stage 11: Execution Flow Summary

### Complete Data Flow Visualization
```
Input String: "ls -la | grep \".txt\" > results.txt"
    ↓ ft_split()
String Array: ["ls", "-la", "|", "grep", "\".txt\"", ">", "results.txt"]
    ↓ s_cmd()
Token List: [WORD:"ls"] -> [WORD:"-la"] -> [PIPE:"|"] -> [WORD:"grep"] -> [DOUBLE_Q:"\".txt\""] -> [R_OUT:">"] -> [RED_FILE:"results.txt"]
    ↓ ft_expand()  
Token List: [WORD:"ls"] -> [WORD:"-la"] -> [PIPE:"|"] -> [WORD:"grep"] -> [WORD:".txt"] -> [R_OUT:">"] -> [RED_FILE:"results.txt"]
    ↓ convert_token_to_exec()
Exec List: [Node1: ls -la | pipe_out] -> [Node2: grep .txt > file]
    ↓ execution()
Process Tree: Parent -> Child1(ls) + Child2(grep) -> Results in results.txt
```

This detailed analysis shows exactly how data structures evolve and link together as a command flows through the minishell system, from raw input to final execution.
