# Operating Systems: Microkernel Implementation

![Unesp](https://img.shields.io/badge/BCC-UNESP-Bauru.svg)
![License](https://img.shields.io/badge/Code%20License-MIT-blue.svg)

## 📋 Overview

This repository contains a C language microkernel project developed to implement a multiprogramming environment for MS-DOS. By implementing the Round Robin scheduling algorithm, this project allows DOS (which is naturally single-programmed) to simulate multiprogramming with apparent parallelism.

## 🌟 Key Features

- **Multiprogramming Kernel**: Implements a scheduling mechanism that allows multiple processes to run in an apparently simultaneous manner
- **Round Robin Scheduling**: Uses time slices to rotate between active processes
- **Semaphore Implementation**: Provides synchronization mechanisms between processes
- **Process Management**: Includes process creation, termination, and context switching
- **Classic Synchronization Problems**: Implementation of "The Dining Savages" problem

## 🔍 Repository Structure

### TC Directory

Contains MS-DOS files with TurboC Compiler support.

### Núcleo (Kernel) Directory

- **nucleo.c** and **nucleo.h**: Core microkernel implementation
- **prco_ex.c** and related files: Implementation of "The Dining Savages" problem
- **teste.c** and related files: Test cases for the kernel

### Exercs (Exercises) Directory

- **esc_co.c**: Test case for the Scheduler Algorithm
- **tictac_m.c**: Test case for the transfer function with specific intervals
- **tictac.c**: Test case for the transfer function without interval limitations

## 💻 Technical Details

#### Key Functions

- `inicia_semaforo`: Initializes a semaphore with a given value
- `cria_processo`: Creates a new process with name and function pointer
- `termina_processo`: Terminates the current process
- `primitiva_p` and `primitiva_v`: Implements semaphore P (wait) and V (signal) operations
- `escalador`: The main scheduler function implementing Round Robin
- `inicia_sistema`: Initializes the system by creating the scheduler process

## 🔬 Case Study: The Dining Savages Problem

The project includes an implementation of "The Dining Savages" problem, a classic synchronization problem from concurrent programming:

> A tribe of savages dines together around a large pot containing M portions of missionary stew. When a savage wants to eat, they serve themselves a portion from the pot, unless the pot is empty. If the pot is empty, the savage wakes up the cook and then waits for the cook to refill the pot. After filling the pot, the cook returns to sleep.

This implementation demonstrates the use of semaphores for process synchronization with the producer-consumer pattern.

### Key Components:

- A cook (producer) that fills the pot when empty
- Multiple savages (consumers) that eat from the pot
- Semaphores to control access to the critical section (pot)

## 🚀 Getting Started

### Prerequisites

- DOSBox or similar DOS emulator
- Turbo C compiler

### Compilation and Execution

1. Mount your project directory in DOSBox
2. Navigate to the TC directory
3. Use the Turbo C compiler to compile the project files
4. Run the generated executable files

## 📚 References

- Tanenbaum, A. S. Operating Systems: Design and Implementation
- Gregory R. Andrews. Concurrent Programming: Principles and Practice. Addison-Wesley, 1991.

## 📄 License

This project is licensed under the MIT License - see the LICENSE file for details.

<h4 align="center" style="display:flex; flex-direction: row; justify-content: center; align-items: center">

<img src="https://socialify.git.ci/luisbernardinello/operating-systems/image?description=1&font=Rokkitt&language=1&name=1&owner=1&pattern=Floating%20Cogs&theme=Auto" alt="Operating Systems" width="498" height="270" />

</h4>
