# Metro Mondego Management System
**Programação - DEIS/ISEC**

## Description

This project is a C-based management system for the "Metro Mondego" (Coimbra metro) network. It's a console application designed to load, manage, and query information about metro stops, lines, and routes.

The system loads initial data from text files (`paragens.txt`) and can save the current state of lines and stops to a binary data file (`metromondego.dat`). The core logic involves managing dynamic data structures (linked lists) to store stops, lines, and the routes (`percursos`) that connect them.

## Features

* **Load Data**: Reads stops and lines from text files at startup.
* **Save/Load State**: Saves the current network (stops and lines) to a binary file and can load it back.
* **Manage Stops**: Add new stops and list all existing stops.
* **Manage Lines**: Create new lines and list all lines.
* **Manage Routes**: Add stops to the beginning or end of a line's route.
* **Query Routes**: Calculate and display routes between two stops.
* **Data Model**: Uses linked lists to manage collections of stops (`pStop`), lines (`pLine`), and route segments (`pPercurso`).

## Technologies

* **C** (Main programming language)
* **Dynamic Memory Allocation** (`malloc`, `free`)
* **Linked Lists** (Custom implementations for data structures)
* **File I/O** (Text file parsing with `fgets`/`sscanf`, Binary file I/O with `fwrite`/`fread`)

## Directory Structure

* `main.c`: The main application entry point, handling user menus and high-level logic.
* `stops.h`, `stops.c`: Data structure and functions for managing metro stops (paragens).
* `lines.h`, `lines.c`: Data structure and functions for managing metro lines.
* `percursos.h`, `percursos.c`: Data structure and functions for managing the routes/paths (percursos) of each line.
* `paragens.txt`: Input data file containing the list of metro stops.
* `metromondego.dat`: Default binary file for saving and loading the system state.
* `RelatorioProg.pdf`: The final project report (in Portuguese).
* `metromondego.exe`: A pre-compiled executable for Windows.

## How to Compile and Run

### Prerequisites

* A C compiler (e.g., **GCC**).
* The `make` build tool (optional, but a `tasks.json` for VSCode is provided which uses `gcc`).

### Compilation (using GCC)

You can compile the project by linking all the `.c` files. A `tasks.json` file is provided for VSCode, which suggests the following build command:

```bash

gcc -fdiagnostics-color=always -g \*.c -o metromondego -Wall -lm

```

### Execution

Once compiled, you can run the executable:

```bash

./metromondego

```

The application will launch and present a text-based menu in the console.

## Commands (Menu Options)

The main application loop in `main.c` provides the following options:

1.  **Paragens (Stops)**
    * `Adicionar Paragem`: Add a new stop.
    * `Listar Paragens`: List all currently loaded stops.
2.  **Linhas (Lines)**
    * `Adicionar Linha`: Create a new metro line.
    * `Listar Linhas`: List all current lines.
    * `Adicionar Paragem (Inicio)`: Add a stop to the beginning of a line's route.
    * `Adicionar Paragem (Fim)`: Add a stop to the end of a line's route.
3.  **Percursos (Routes)**
    * `Calcular Percurso`: Calculate and display the route between two stops.
4.  **Guardar (Save)**
    * Saves the current lists of stops and lines to `metromondego.dat`.
5.  **Carregar (Load)**
    * Loads the system state from `metromondego.dat`.
6.  **Sair (Exit)**
    * Terminates the application.
