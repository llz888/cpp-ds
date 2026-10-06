# MyVector

从零手写的动态数组，对标 `std::vector` 的最小可用子集。cpp-ds 的第一个容器。

整个类不使用任何 STL 容器，堆内存自己申请、自己释放 —— 目的是把 **RAII / Rule of Five / 模板实例化 / 扩容策略** 从「知道」练到「写得出、讲得清」。

```
myvector/
├── myvector.hpp    # MyVector<T> 的完整定义
├── main.cpp        # 演示与自测
└── README.md
```

## 接口

| 成员 | 说明 | 复杂度 |
| --- | --- | --- |
| `MyVector()` | 空数组，不分配内存 | O(1) |
| `~MyVector()` | `delete[]` 释放缓冲区 | O(1) |
| `MyVector(const MyVector&)` | 拷贝构造（深拷贝） | O(n) |
| `operator=(const MyVector&)` | 拷贝赋值 | O(n) |
| `MyVector(MyVector&&) noexcept` | 移动构造（窃取指针） | O(1) |
| `operator=(MyVector&&) noexcept` | 移动赋值 | O(1) |
| `push_back(const T&)` | 尾部追加，满了就扩容 | 均摊 O(1) |
| `pop_back()` | 尾部删除（只减 `size_`，不还内存） | O(1) |
| `clear()` | 清空元素，保留容量 | O(1) |
| `operator[](int)` | 无边界检查访问 | O(1) |
| `front()` / `back()` | 首 / 尾元素的引用 | O(1) |
| `size()` / `capacity()` / `empty()` | 状态查询 | O(1) |
| `begin()` / `end()` | 只读迭代，支持范围 for | O(1) |

## 设计要点

### 1. 三个成员：`data_` / `size_` / `cap_`

`size_` 是**已构造元素个数**，`cap_` 是**已分配原始内存能装多少个**。两者分开，才谈得上「容量翻倍但元素数不变」。
`pop_back()` 和 `clear()` 只改 `size_`、不动 `cap_`，所以之后再 `push_back` 不会重新分配。

### 2. 为什么整个定义都放在 `.hpp` 里

类模板不是代码，是**生成代码的模板**。`MyVector<int>` 和 `MyVector<double>` 是两份互相独立的类，编译器要到你写下 `MyVector<int>` 的那一刻，才知道 `T` 就是 `int`，才能生成那份代码。

所以定义必须和它的使用者（`main.cpp`）在同一个编译单元里可见 —— 也就是头文件。如果挪进 `.cpp`，那个文件自己编译时看不到定义、无法实例化，链接阶段就会报：

```
undefined reference to `MyVector<int>::push_back(int const&)'
```

### 3. 扩容：容量翻倍

`size_ == cap_` 时触发 `grow()`：新容量取 `cap_ == 0 ? 1 : cap_ * 2`，把旧数据搬过去，再 `delete[]` 旧缓冲区。

- **为什么翻倍**：单次 `push_back` 最坏是 O(n)，但连续 n 次追加一共只搬 `n + n/2 + n/4 + … < 2n` 次，**均摊 O(1)**。若每次只加 1，均摊就退化成 O(n)。
- **为什么先建新的再删旧的**：顺序是「申请 → 搬运 → 释放」。中间任何一步失败，原对象都还是完整的。

### 4. Rule of Five：五个函数必须写全

类里持有裸指针，编译器默认生成的拷贝是**浅拷贝**（两个对象指向同一块内存）→ 析构时双重释放。所以析构、拷贝构造、拷贝赋值、移动构造、移动赋值五个都得自己写：

- **拷贝赋值先 `new` 再 `delete`**，而不是先 `delete` 再 `new` —— 这样自赋值安全，异常时也不会把自己搞成悬垂指针。
- **移动构造 / 移动赋值直接窃取指针**，然后把源对象置空（`data_ = nullptr, size_ = cap_ = 0`）。置空的必要性：源对象仍然会被析构，而 `delete[] nullptr` 是合法的空操作。
- **都标了 `noexcept`**：这是在给编译器一个承诺 —— 移动不会抛异常。`std::vector` 扩容搬运元素时会看这个标记，只有 `noexcept` 的移动构造才会被采用，否则为了异常安全会退回去用拷贝。

### 5. 迭代器就是裸指针

`T*` 天然满足迭代器的要求，范围 for 展开后就是 `for (auto it = v.begin(); it != v.end(); ++it)`。
目前只提供 `const T*` 版本，所以能遍历、不能通过迭代器改元素。

## 与 `std::vector` 的差距

当前实现是刻意保持最小的，以下是已知的缺口（下一步补）：

- **`pop_back()` / `clear()` 不调用元素的析构函数**。被「删掉」的元素其实还活着，要等整个数组析构时才一起销毁。这**不是内存泄漏**（`delete[]` 最终会析构全部 `cap_` 个元素），但**析构时机是错的**：如果 `T` 的析构带副作用（关闭文件、释放锁、归还连接），这个副作用会被无限期推迟。
- **`new T[n]` 要求 `T` 可默认构造**，而且一次构造满 `cap_` 个（比实际用到的 `size_` 多）。实测：当 `T` 只有带参构造函数时，这一行直接编译失败。
- **`grow()` 用拷贝赋值搬数据**，对可移动类型是浪费。
- **没有 `push_back(T&&)`**，所以 `v.push_back(MyVector<int>{})` 会走拷贝而不是移动。
- **没有 `reserve` / `resize` / `at` / `insert` / `erase` / `data()`**。
- **`size_` / `cap_` 用 `int`**：标准库用的是无符号的 `size_type`（`std::vector<T>::size_type`）。`int` 能表示的元素数上限只有约 21 亿，而且用有符号类型表示「个数」在语义上说不通。
- **没有 const 版 `operator[]`**，`const MyVector<T>` 无法下标访问。
- **`front()` / `back()` 不做检查**，空数组调用是 UB（这一点和 `std::vector` 一致）。

## 编译与运行

```bash
cd ~/cpp-lab/myvector
g++ -Wall -Wextra -g -fsanitize=address,undefined main.cpp -o main
./main
```

输出：

```
size=5 front=10 back=50
pop 之后: size=4 back=40
clear 之后: size=0 capacity=8 empty=1
```

`capacity=8` 是扩容轨迹的直接体现：5 次 `push_back` 依次把容量撑到 1 → 2 → 4 → 8。

## 验证状态

- `-Wall -Wextra`：**无警告**
- AddressSanitizer + UndefinedBehaviorSanitizer：**无报告**（无越界、无泄漏、无 UB）
- 编译器：g++ 15.2.0 (Ubuntu)
