# cpp-ds

从零手写的 C++ 数据结构与系统组件库。

不使用 STL 容器——每一块内存的分配、每个对象的生命周期、每一次并发访问的位置，
都由自己决定。把「课程级 C++」练成「工程级 C++」。

## 组件

| 目录 | 组件 | 关键点 |
|---|---|---|
| `myvector/` | 动态数组 | Rule of Five、容量翻倍扩容（均摊 O(1)） |
| `smartptr/` | `unique_ptr` / `shared_ptr` | 所有权唯一（`= delete`）、引用计数放在堆上共享 |
| `pool/` | 定长内存池 | 空闲链表 + 头插法，分配/释放 O(1)，全程不碰 `malloc` |
| `queue/` | 线程安全队列 | `mutex` + 两个条件变量、背压、打烊信号关闭 |
| `threadpool/` | 线程池 | 复用 `BlockingQueue` 调度任务、异常兜底、析构顺序 `close → join` |

`experiments/` 里是学习过程的实验（编译链接、RAII、移动语义、lambda、并发对照实验等），
不属于交付物。

## 构建

需要 CMake ≥ 3.16 和 C++17 编译器。

    cmake -B build -DENABLE_SANITIZERS=ON
    cmake --build build -j

`-DENABLE_SANITIZERS=ON` 会开启 AddressSanitizer + UndefinedBehaviorSanitizer。

## 测试

    ./build/myvector_test
    ./build/smartptr_test
    ./build/pool_test
    ./build/queue_test
    ./build/threadpool_test

断言失败时打印 `[FAIL] 文件:行号 表达式`，并以非 0 退出码结束。
GitHub Actions 在每次 push 时自动构建并运行全部测试（含 ASan/UBSan）。

## 实测数字

- **内存池**：块大小 32 时，相邻块地址间隔恒为 32 字节；取完全部块后再分配返回 `nullptr`，
  还回去的块原样回来
- **`malloc` 的账本开销**：申请 4 字节，实际切给 24 字节
- **减少共享的收益**：同样 2000 万次自增，每圈碰共享原子变量 258ms，
  改成线程本地累加再合并 12ms，**差 21 倍**
- **不忙等**：同样等 1 秒，忙等烧掉 1001ms CPU，条件变量只烧 8ms，**差 125 倍**
- **智能指针零开销**：`sizeof(unique_ptr)` = 8（与裸指针相同），
  `sizeof(shared_ptr)` = 16（多出的 8 是指向引用计数的指针）

## 已知不足

- `MyVector::pop_back()` / `clear()` 不调用元素析构函数——被「删掉」的元素仍然存活，
  析构时机不对（对 `std::string` 这类非 POD 类型有影响）
- `MyVector` 用 `new T[n]` 分配，要求 `T` 可默认构造，且会多构造 `capacity - size` 个元素
- `MySharedPtr` 缺少拷贝赋值运算符（隐式生成的那个不会给计数 +1）；
  引用计数也不是原子的，**多线程下不安全**
- `BlockingQueue` 只有一把粗粒度锁；`FixedPool` 不是线程安全的

## 设计原则

- **内存与对象分开**：用 `operator new` 拿裸内存 + placement new 构造，代替 `new T[n]`
- **减少共享优先于优化锁**：并发代码的第一原则是让线程各用各的数据，最后归并
- **边界写清楚**：宁可在 README 里承认不足，也不假装完整