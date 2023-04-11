### MiniDbg setup

支持对于寄存器，内存的访问读写，完善了 `continue` 指令。

1. 打印寄存器表

编译运行后，使用 `register dump` 即可打印寄存器表（也可使用简写的 `reg` 等）

```
minidbg> reg dump
r15              0x00007fb2fc7ee600             r14              0x00007fb2fc658057
r13              0x0000000000000001             r12              0x000055bf5c3470c0
rbp              0x000055bf5c3470c8             rbx              0x000055bf5c3470c0
r11              0x0000000000000003             r10              0x000055bf5c346978
r9               0x00007ffc0df5dae0             r8               0x00007fb2fcd2ebd4
rax              0x000055bf5c34012b             rcx              0x0000108000000008
rdx              0x00007ffc0df5daf0             rsi              0x000055bf5c338a0c
rdi              0x000000085c347501             orig_rax         0x000055bf5c3470e0
rip              0x00007ffc0df5db20             cs               0x000055bf5c338aab
eflags           0x000000080000004a             rsp              0x000055bf5c3470c8
ss               0x000055bf5c34012b             fs_base          0x000010885c3470c0
gs_base          0x0000000000000016             ds               0x000055bf5c347320
es               0x00007ffc0df5db50             fs               0x000055bf5c338dbd
gs               0x000000000000001a
minidbg> 
```

2. 断点功能与continue功能

```
$./bin/minidbg ./bin/hello
Started debugging process 90430
minidbg> b 0x555555555198
Set breakpoint at address 0x555555555198
minidbg> c
minidbg> c
Hello worldminidbg> 
```
