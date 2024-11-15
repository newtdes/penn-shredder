# Newt KHN Nguyen's Project

## Overview

This repository contains the source files for a C program that manages command execution with a timeout mechanism. Below is a list of the submitted source files along with a brief description of their functionality.

## Submitted Source Files

1. **penn-shredder.c**: This is the main file of the project.
2. **handler.c**: This file handles all signal processing.
3. **setTimer.c**: This file manages the timing for alarm signals (SIGALRM) and outputs a specific message if the specified timeout is exceeded.

## Code Description and Structure

### 1. `penn-shredder.c`
- **Purpose**: This file begins by checking if a timeout has been specified by the user. If not, the timeout is set to `NULL`. If a timeout is provided, it is taken into account.
- **Functionality**:
  - Parses user commands to eliminate any leading or trailing whitespace.
  - Implements the skeleton code provided on the project website by invoking `fork()` to create a child process.
  - The parent process waits for the child process to complete.
  - For extra credit, an additional `int main()` function is included, which sets an alarm in the child process. The parent process then listens for SIGALRM to output a specified catchphrase.

### 2. `handler.c`
- **Purpose**: This file manages signal handling as indicated by its name.
- **Functionality**:
  - Handles `Ctrl + C` interruptions.
  - Addresses timeout issues, with one handler utilizing the `kill` function while the other does not.

### 3. `setTimer.c`
- **Purpose**: Handles the timing mechanism for the program.
- **Functionality**: Initiates an alarm to signal when the timeout condition is met.

## General Comments

- This is my first experience coding in C, so I acknowledge that my code may be messy and somewhat unstructured in places. 
- I have made an effort to ensure that the code is as clear and understandable as possible.
- I welcome any feedback or suggestions regarding my code!

## Acknowledgments

Thank you for reviewing my project! Your insights and recommendations are greatly appreciated.
