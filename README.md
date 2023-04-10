### MiniDbg setup

子模块自动获取，以及项目构建

```bash
cmake -B build
cmake --build build
```

使用方法：

```bash
$./bin/minidbg ./bin/hello
    Started debugging process 26931
    minidbg> c
    Hello world
    minidbg> 
```
