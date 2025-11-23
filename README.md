# C++ ADAS Vehicle Simulator

**Language / 语言选择：**

- [简体中文](#1-项目结构)
- [English](#1-project-structure)

---

本仓库是一个 C++ 课程实验项目，围绕一个简化的“车辆 / ADAS 控制系统”展开。
核心是对车辆位置与朝向的建模（`Pose`）、执行器 `Executor`、命令系统 `Cmder`，以及多种车辆行为（普通车、公交车、跑车）。

项目同时配有 Google Test 单元测试，便于你通过测试来验证每一步实验结果。

---

## 1. 项目结构

仓库主要目录说明（以 `task_1` 目录为根）：

- `src/`
  - `core/`
    - `Direction.hpp / .cpp`：方向枚举与移动向量（E/S/W/N）。
    - `Point.hpp / .cpp`：平面坐标点 (x, y)。
    - `PoseHandler.hpp / .cpp`：封装 `Pose`，负责前进、后退、转向、加速等状态更新。
    - `Singleton.hpp`：通用单例模板，用于 `CmderFactory` 等。
  - `cmder/`
    - `Command.hpp`：命令接口 `ICommand` 以及 `MoveCommand` / `TurnLeftCommand` / `TurnRightCommand` / `FastCommand` 等具体命令。
    - `ActionGroup.hpp / .cpp`：把一系列基本动作打包成“动作组”并执行。
    - `CmderFactory.hpp / .cpp`：把命令字符串解析为一组可执行命令对象（命令工厂）。
    - `BusOrchestrator.hpp`、`NormalOrchestrator.hpp`、`SportsCarOrchestrator.hpp`：根据车辆类型组织命令执行的策略入口。
    - `CmderOrchestrator.hpp`、`Command.hpp` 等：命令调度相关抽象。
  - `ExecutorImpl.hpp / .cpp`：`Executor` 的具体实现，持有 `PoseHandler` 和 `CmderOrchestrator`，对外提供 `Execute` / `Query` 等接口。
- `include/`
  - `Executor.hpp`：对外暴露的执行器接口与 `Pose`、`ExecutorType` 等类型声明。
- `tests/`
  - 使用 Google Test 编写的单元测试，例如：
    - `ExecutorTest.cpp`
    - `ExecutorReverseTest.cpp`
    - `ExecutorFastTest.cpp`
    - `SportsCarTest.cpp`
    - `BusTest.cpp`
  - `googletest/`：GoogleTest 源码（作为子目录构建）。
- `CMakeLists.txt` & `src/CMakeLists.txt` & `tests/CMakeLists.txt`：CMake 构建脚本。
- `script/`
  - `build.bat`：构建脚本。
  - `run.bat`：运行脚本（一般执行主程序或测试）。
  - `clean.bat`：清理构建输出。

---

## 2. 功能概览

从整体上看，这个项目模拟了“车辆在平面网格上运动”的过程：

1. **位姿建模**：
   - 使用 `Point` 表示位置，`Direction` 表示朝向（E/S/W/N）。
   - `PoseHandler` 内部持有 `Pose`，对外提供 `Forward`、`Backward`、`TurnLeft`、`TurnRight`、`Fast`、`Reverse` 等方法来修改状态。

2. **命令系统**：
   - 每个命令字符（例如 `M`, `L`, `R`, `B`, `F` 等）对应一个具体的 `ICommand` 实现或一个 `std::function`，封装了一步操作。
   - `CmderFactory` / `ActionGroup` 把字符串解析为命令列表，然后逐个对 `PoseHandler` 执行。

3. **执行器 `Executor`**：
   - 对外暴露简洁接口：
     - `Executor::NewExecutor(const Pose &, ExecutorType)`：构造不同类型的执行器（公交车、跑车、普通车）。
     - `void Execute(const std::string &commands)`：执行命令串。
     - `Pose Query() const`：查询当前车辆位置与朝向。
   - `ExecutorImpl` 内部使用 `CmderOrchestrator` 来决定不同类型车辆的行为策略（例如跑车的加速规则与公交车不同）。

4. **多种车辆类型**：
   - `ExecutorType::BUS` / `SPORTS_CAR` / `NORMAL` 对应不同 Orchestrator。
   - 各自有不同的“命令解释方式”或动作组合方式，用以演示“面向对象+策略模式”的用法。

5. **测试驱动**：
   - 每个实验（lab）配套若干测试文件，例如 `ExecutorReverseTest` 针对后退逻辑，`ExecutorTurnRoundTest` 针对转向/掉头逻辑等。

---

## 3. 构建与运行

以下命令都在 `task_1` 目录下执行。

### 3.1 使用脚本（推荐）

Windows 下可以直接双击或在 PowerShell 中执行：

```powershell
cd C:\Users\Owner\code\project\C++Course\task_1

# 构建
script\build.bat

# 运行（通常是主程序或者测试入口）
script\run.bat

# 清理
script\clean.bat
```

### 3.2 使用 CMake 手动构建

项目已经提供了 CMake 配置，可以在 VS Code 或命令行直接调用：

```powershell
cd C:\Users\Owner\code\project\C++Course\task_1

# 配置（Debug，MinGW Makefiles）
cmake -DCMAKE_BUILD_TYPE=Debug -G "MinGW Makefiles" -S . -B build

# 编译
cmake --build build
```

如果你使用 VS Code 中的 `cmake configure` 任务，也会做类似的事情。

### 3.3 运行测试

构建完成后，可以在 `build/tests` 目录下找到测试可执行文件（通常是一个 `${PROJECT_NAME}-main`，运行时会执行所有 Google Test 用例）：

```powershell
cd C:\Users\Owner\code\project\C++Course\task_1\build\tests

# 直接运行测试 EXE
.\nC-Course-task_1-main.exe

# 或使用 ctest（需在 build 目录下）
cd ..
ctest
```

在 VS Code 中，如果安装了 C++ TestMate / Google Test 相关扩展，也可以在 Testing 面板中看到所有测试并单独调试某一个用例。

---

## 4. 分支说明

本仓库包含多个分支，对应不同实验阶段或重构版本。下面是每个分支的建议说明（名称即 Git 分支名）：

### 4.1 `main`

- 当前主线分支。
- 通常包含所有实验完成后的参考实现，代码结构已经相对完整：
  - `Executor` + `CmderOrchestrator` + 各类 `Command` + `ActionGroup` + 单例工厂等。
- 适合作为“总览代码架构”和“查阅最终实现”的入口。

### 4.2 `lab1-cleancode-base`

- 实验 1：**代码整洁基础**。
- 目标：
  - 从一个相对原始的实现出发，进行命名优化、函数拆分、去除重复代码等。
  - 强调“可读性”“单一职责”“小函数”等 Clean Code 概念。
- 特点：
  - 架构较简单，更多是对原始逻辑的整理与重构。

### 4.3 `lab2-oop-support-F`

- 实验 2（阶段一）：**面向对象扩展：支持 `F`（Fast）命令**。
- 目标：
  - 在命令系统中增加一个“加速/快速移动”相关的语义，通常是 `F` 命令。
  - 探索如何通过新增 `FastCommand` / 修改 `PoseHandler::Fast()` 等方式扩展行为，而尽量不破坏已有结构。
- 特点：
  - 在 `Command.hpp` / `PoseHandler.hpp` 附近可看到与 `Fast` 行为相关的改动。

### 4.4 `lab2-oop-three-features`

- 实验 2（阶段二）：**面向对象的三个特性综合运用**。
- 关注点：
  - 继承：例如 `ICommand` 接口与多个具体命令类。
  - 封装：`PoseHandler` 封装位姿细节、`ExecutorImpl` 封装执行流程。
  - 多态：通过基类指针/引用调用不同子类的 `DoOperate`。
- 特点：
  - 分支中会更多体现接口抽象、虚函数、多态分发的用法。

### 4.5 `lab3-fp`

- 实验 3（阶段一）：**函数式编程风格**。
- 目标：
  - 使用 `std::function`、lambda、`std::for_each` 等来实现命令调度。
  - 减少显式的 `if-else` / `switch`，改用“表驱动 + 函数对象”的方式。
- 示例：
  - `std::unordered_map<char, std::function<void(PoseHandler &)>>` 映射命令字符到操作。
  - `std::for_each` + lambda 执行命令序列。

### 4.6 `lab3-fp-support-B`

- 实验 3（阶段二）：**在函数式风格下支持 `B`（Backward / Reverse）命令**。
- 目标：
  - 在 FP 风格的架构上，平滑扩展一个新命令（例如后退或反向相关逻辑）。
  - 观察：仅增加映射表项 + 对应动作逻辑，即可扩展功能，验证 FP 在扩展性上的优势。
- 特点：
  - 在 `ActionGroup` / `CmderFactory` 之类的地方会看到针对 `B` 的处理。

### 4.7 `lab3-oop-recfactor-final`

- 实验 3（阶段三）：**面向对象与函数式的综合重构版本**。
- 目标：
  - 在实践 OOP + FP 的过程中，对项目进行再一次结构化重构。
  - 清晰划分：
    - “状态”由谁维护（`PoseHandler`）。
    - “动作”如何组织（`ActionGroup` / `Command` / `std::function`）。
    - “策略”如何注入（`CmderOrchestrator` + `ExecutorImpl`）。
- 特点：
  - 代码风格更统一，职责划分更清晰，便于阅读和扩展。

### 4.8 `lab4-comprehensive-actual-combat`

- 实验 4：**综合实战**。
- 目标：
  - 把前面各实验中的知识点（Clean Code、OOP、FP）综合运用在一个稍大型的场景中。
  - 增强对“从需求到设计再到实现”的完整流程的体验。
- 特点：
  - 可能包含更多的业务规则、边界情况处理。
  - 测试用例更加丰富和贴近“真实需求”。

---

## 5. 如何在不同分支间学习

建议的学习路线：

1. 从 `lab1-cleancode-base` 开始，关注命名与基本结构；
2. 切到 `lab2-oop-support-F`、`lab2-oop-three-features`，体会如何通过 OOP 扩展行为；
3. 再看 `lab3-fp`、`lab3-fp-support-B`，体会用 FP 风格来替代 if-else / switch 的好处；
4. 阅读 `lab3-oop-recfactor-final`，理解一个综合重构后的较优架构；
5. 最后看 `lab4-comprehensive-actual-combat` 和 `main`，把所有内容串联起来。

切换分支时的命令示例：

```powershell
# 查看所有分支
git branch

# 切换到某个实验分支
git checkout lab3-fp
```

---

## 6. 贡献与扩展建议

如果你想在此基础上继续扩展，可以尝试：

- 增加障碍物 / 地图边界检测；
- 增加更多车辆类型（如卡车、自行车），让 `ExecutorType` 与 Orchestrator 更加多样；
- 引入日志系统，对每一步动作记录日志；
- 使用 CI（如 GitHub Actions）自动构建并运行测试。

欢迎在 GitHub 上使用 Issue / Pull Request 记录你的想法和改动。希望这个项目能帮助你更好地理解 C++ 的面向对象、函数式编程以及整洁代码实践。

---

## 1. Project Structure

This repository is a C++ course project that builds a simplified "vehicle / ADAS control system".
It focuses on modeling vehicle pose (`Pose`), the executor (`Executor`), the command system (`Cmder`),
and different vehicle behaviors (normal car, bus, sports car).

Main directories (rooted at `task_1`):

- `src/`
  - `core/`
    - `Direction.hpp / .cpp`: Direction enum and motion vectors (E/S/W/N).
    - `Point.hpp / .cpp`: 2D point (x, y).
    - `PoseHandler.hpp / .cpp`: Wraps `Pose`, responsible for forward/backward/turn/fast/reverse operations.
    - `Singleton.hpp`: Generic singleton template, used by `CmderFactory` etc.
  - `cmder/`
    - `Command.hpp`: Command interface `ICommand` and concrete commands like `MoveCommand`,
      `TurnLeftCommand`, `TurnRightCommand`, `FastCommand`.
    - `ActionGroup.hpp / .cpp`: Packs a sequence of basic actions into an action group and executes them.
    - `CmderFactory.hpp / .cpp`: Parses command strings into executable command objects (command factory).
    - `BusOrchestrator.hpp`, `NormalOrchestrator.hpp`, `SportsCarOrchestrator.hpp`:
      orchestrators for different vehicle types.
    - `CmderOrchestrator.hpp`, `Command.hpp`: abstractions around command orchestration.
  - `ExecutorImpl.hpp / .cpp`: Concrete implementation of `Executor`, holding a `PoseHandler`
    and a `CmderOrchestrator`, exposing `Execute` and `Query`.
- `include/`
  - `Executor.hpp`: Public executor interface, and declarations of `Pose`, `ExecutorType`, etc.
- `tests/`
  - Google Test based unit tests, e.g.:
    - `ExecutorTest.cpp`
    - `ExecutorReverseTest.cpp`
    - `ExecutorFastTest.cpp`
    - `SportsCarTest.cpp`
    - `BusTest.cpp`
  - `googletest/`: GoogleTest source as a subdirectory.
- `CMakeLists.txt`, `src/CMakeLists.txt`, `tests/CMakeLists.txt`: CMake build scripts.
- `script/`
  - `build.bat`: Build script.
  - `run.bat`: Run script (main program or tests).
  - `clean.bat`: Clean build outputs.

---

## 2. Features Overview

Conceptually, this project simulates a vehicle moving on a 2D grid:

1. **Pose modeling**
   - `Point` represents position; `Direction` represents heading (E/S/W/N).
   - `PoseHandler` owns a `Pose` and provides operations like `Forward`, `Backward`,
     `TurnLeft`, `TurnRight`, `Fast`, `Reverse`.

2. **Command system**
   - Each command character (e.g. `M`, `L`, `R`, `B`, `F`) maps to a concrete `ICommand`
     implementation or a `std::function` that performs one atomic operation.
   - `CmderFactory` / `ActionGroup` converts a string into a list of commands and
     executes them one by one on `PoseHandler`.

3. **Executor**
   - A simple public API:
     - `Executor::NewExecutor(const Pose &, ExecutorType)`: construct executors for bus,
       sports car, or normal car.
     - `void Execute(const std::string &commands)`: execute a command sequence.
     - `Pose Query() const`: get current pose (position and heading).
   - Internally, `ExecutorImpl` uses a `CmderOrchestrator` to decide how different
     vehicle types interpret and organize commands.

4. **Multiple vehicle types**
   - `ExecutorType::BUS` / `SPORTS_CAR` / `NORMAL` correspond to different orchestrators,
     demonstrating the strategy pattern.

5. **Tests**
   - Each lab/step is backed by Google Test cases, e.g. reverse logic, turn-around logic,
     fast movement, sports car behavior, bus behavior, etc.

---

## 3. Build & Run

All commands below assume the working directory is `task_1`.

### 3.1 Using scripts (recommended on Windows)

```powershell
cd C:\Users\Owner\code\project\C++Course\task_1

# Build
script\build.bat

# Run (main program or test entry)
script\run.bat

# Clean
script\clean.bat
```

### 3.2 Using CMake manually

```powershell
cd C:\Users\Owner\code\project\C++Course\task_1

# Configure (Debug, MinGW Makefiles)
cmake -DCMAKE_BUILD_TYPE=Debug -G "MinGW Makefiles" -S . -B build

# Build
cmake --build build
```

### 3.3 Run tests

After building, you can run tests in `build/tests` (usually one `${PROJECT_NAME}-main`
executable that runs all Google Test cases):

```powershell
cd C:\Users\Owner\code\project\C++Course\task_1\build\tests

./C-Course-task_1-main.exe   # or the actual test executable name

cd ..
ctest
```

In VS Code, with a Google Test extension installed, you can also discover and run
individual test cases from the Testing panel.

---

## 4. Branches

This repository contains several branches, each representing a lab step or a refactoring stage.

- `main`: consolidated version with all features and refactorings.
- `lab1-cleancode-base`: focus on clean code basics (naming, small functions, SRP).
- `lab2-oop-support-F`: extend OOP design to support `F` (fast) command.
- `lab2-oop-three-features`: practice inheritance, encapsulation, and polymorphism.
- `lab3-fp`: introduce functional style (lambdas, `std::function`, table-driven dispatch).
- `lab3-fp-support-B`: extend the FP-style design to support `B` (backward / reverse).
- `lab3-oop-recfactor-final`: combined OOP + FP refactoring version.
- `lab4-comprehensive-actual-combat`: comprehensive lab, applying all previous techniques.

You can switch branches with:

```powershell
git branch      # list branches
git checkout lab3-fp
```

---

## 5. How to Study This Project

Suggested path:

1. Start from `lab1-cleancode-base` to understand the basic structure and clean code ideas.
2. Move to `lab2-oop-support-F` and `lab2-oop-three-features` to see how OOP extends behavior.
3. Then read `lab3-fp` and `lab3-fp-support-B` for functional-style command handling.
4. Look at `lab3-oop-recfactor-final` for a more polished architecture.
5. Finally, study `lab4-comprehensive-actual-combat` and `main` as comprehensive examples.

---

## 6. Contribution & Further Ideas

Ideas for further extension:

- Add obstacles or map boundaries.
- Add more vehicle types (truck, bike, etc.).
- Add logging for each action.
- Integrate CI (e.g., GitHub Actions) to build and run tests automatically.

Issues and pull requests are welcome if you use this project as a practice playground.