### MiniDbg setup

反汇编被测程序，决定断点地址。

构建了一个hello-world示例，对其进行了反汇编，寻找`main`的反汇编：

```
$objdump -d ./bin/hello

......

0000000000001189 <main>:
    1189:       f3 0f 1e fa             endbr64 
    118d:       55                      push   %rbp
    118e:       48 89 e5                mov    %rsp,%rbp
    1191:       48 8d 35 6c 0e 00 00    lea    0xe6c(%rip),%rsi        # 2004 <_IO_stdin_used+0x4>
    1198:       48 8d 3d 81 2e 00 00    lea    0x2e81(%rip),%rdi        # 4020 <_ZSt4cerr@@GLIBCXX_3.4>
    119f:       e8 dc fe ff ff          callq  1080 <_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@plt>
    11a4:       b8 00 00 00 00          mov    $0x0,%eax
    11a9:       5d                      pop    %rbp
    11aa:       c3                      retq   

......
```

1. 运行调试程序，并开始调试hello-world程序：

```
$./bin/minidbg ./bin/hello
Started debugging process 45000
minidbg> 
```

2. 查找子进程的映射地址

```
$cat /proc/45000/maps
555555554000-555555555000 r--p 00000000 103:04 1239017                   /media/ccz/code/Codefield/MiniDbg/bin/hello
555555555000-555555556000 r-xp 00001000 103:04 1239017                   /media/ccz/code/Codefield/MiniDbg/bin/hello
555555556000-555555557000 r--p 00002000 103:04 1239017                   /media/ccz/code/Codefield/MiniDbg/bin/hello
555555557000-555555559000 rw-p 00002000 103:04 1239017                   /media/ccz/code/Codefield/MiniDbg/bin/hello
7ffff7fbf000-7ffff7fc2000 r--p 00000000 00:00 0                          [vvar]
7ffff7fc2000-7ffff7fc3000 r-xp 00000000 00:00 0                          [vdso]
7ffff7fc3000-7ffff7fc5000 r--p 00000000 103:07 6304043                   /lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
7ffff7fc5000-7ffff7fef000 r-xp 00002000 103:07 6304043                   /lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
7ffff7fef000-7ffff7ffa000 r--p 0002c000 103:07 6304043                   /lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
7ffff7ffb000-7ffff7fff000 rw-p 00037000 103:07 6304043                   /lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
7ffffffdd000-7ffffffff000 rw-p 00000000 00:00 0                          [stack]
ffffffffff600000-ffffffffff601000 --xp 00000000 00:00 0                  [vsyscall]
```

3. 开始测试断点

将断点打在 程序地址 `1198` 处，程序将在打印输出前中断

```
minidbg> b 0x555555555198
Set breakpoint at address 0x555555555198
minidbg> c
minidbg> 
```

重新启动程序，将断点打在地址 `11a4` 处，程序在打印输出后中断，因此可以看到输出

```
minidbg> b 0x5555555551a4
Set breakpoint at address 0x5555555551a4
minidbg> c
Hello worldminidbg> 
