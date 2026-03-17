# philosophers

A concurrent programming project based on the classic *Dining Philosophers Problem*, developed as part of the 42 Lisboa curriculum.

## Overview

The goal of this project is to simulate philosophers sitting at a table, where each philosopher alternates between eating, sleeping, and thinking while sharing limited resources (forks).

The challenge is to manage synchronization between threads in order to avoid:

- data races  
- deadlocks  
- starvation  

## Problem Description

- A number of philosophers sit around a table  
- Each philosopher needs two forks to eat  
- Forks are shared between neighbors  
- Philosophers must:
  - eat  
  - sleep  
  - think  

The simulation must ensure correct behavior under concurrent execution.

## Implementation

This project uses:

- threads (`pthread`) to represent philosophers  
- mutexes to protect shared resources (forks, printing, state)  
- a monitoring system to detect philosopher death  

Each philosopher runs in its own thread and follows a loop of actions while respecting synchronization rules.

## Key Concepts

- multithreading  
- mutex locks  
- race condition prevention  
- deadlock avoidance  
- time management (precise sleep and timing)  
- shared memory synchronization  

## Features

- Thread-safe implementation  
- Accurate death detection  
- Controlled output (no mixed prints)  
- Input validation  
- Efficient resource management  

## Project Structure

philosophers/
├── include/
├── src/
├── Makefile
└── README.md

## Usage

### Compilation

make

### Execution

./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

### Example

./philo 5 800 200 200

## Arguments

- number_of_philosophers → total philosophers (and forks)  
- time_to_die → time (ms) before a philosopher dies without eating  
- time_to_eat → time (ms) spent eating  
- time_to_sleep → time (ms) spent sleeping  
- number_of_times_each_philosopher_must_eat → optional limit  

## Notes

- The simulation stops when:
  - a philosopher dies  
  - or all philosophers have eaten enough times (if specified)  

- Special care is taken to:
  - prevent deadlocks  
  - ensure fair resource access  
  - maintain accurate timing  

## Development Notes

This project focuses on understanding low-level concurrency and synchronization in C, including:

- managing threads with pthread  
- protecting shared data using mutexes  
- designing a safe and deterministic simulation  

## Use of AI

AI tools were used as a support resource during the development of this project, mainly for:

- understanding concurrency concepts  
- improving documentation quality (README)  
- reviewing synchronization strategies  

All core implementation, synchronization logic, and debugging were developed independently as part of the learning process.

## Author

Jean Henrique Moreira  
42 Lisboa  

Learning low-level. Thinking long-term.