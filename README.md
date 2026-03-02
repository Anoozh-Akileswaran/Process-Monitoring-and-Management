
---

## 2) **Linux Process Monitoring & Management Tool (OS Project)**


# Linux Process Monitor and Manager

A lightweight process monitoring and management tool built on Ubuntu Linux to learn how user-space programs interact with the kernel via system calls. The tool inspects running processes and supports basic management operations.

## Features
- List processes and display key metadata (PID, state, CPU/memory usage where available)
- Inspect a specific process (basic details)
- Basic process management actions (e.g., send signals)
- Emphasis on understanding OS concepts: process lifecycle, scheduling, and syscalls

## Tech Stack
- C/C++ (POSIX)
- Linux (Ubuntu)
- Makefile/CMake (optional)

## Build and Run

### Requirements
- Linux (Ubuntu recommended)
- `gcc`/`g++`, `make`

### Build
```bash
make
