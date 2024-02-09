# Philosophers [42 Project]
This 42 project challenges us to create a multi-threaded program in C.

## Table of Contents
1. [Overview](#overview)
2. [Threads vs Processes](#threads-vs-processes)
3. [Project Structure](#project-structure)
4. [Dependencies](#dependencies)
5. [How to Use](#how-to-use)
6. [Code Example](#code-example)
7. [Bonus](#bonus)
8. [Contributing](#contributing)

## Overview
The goal of this project is to create a simulation where each philosopher, alternatively, `eat`, `think` and `sleep`. The simulation stops when a philosopher `dies of starvation`.

### The Rules
- One or more philosophers sit at a round table. There is a large bowl of spaghetti in the middle of the table.
- The philosophers alternatively `eat`, `think` and `sleep`. The philosophers can only do one thing at a time.
- There are forks on the table. The `number of forks` is equal to the `number of philosophers`.
- A philosopher needs two forks to `eat`, one in each hand.
- When a philosopher has finished eating, they put their forks back on the table and start sleeping. Once awake, they start thinking.
- Every philosopher needs to `eat` and should never `die of starvation`.
- Each philosopher has a number ranging from `1` to `number_of_philosophers`.
-  Philosopher number `1` sits next to philosopher number `number_of_philosophers`. Any other philosopher number `N` sits between philosopher number `N - 1` and philosopher number `N + 1`.
- Philosophers don’t speak with each other.
- Philosophers don’t know if another philosopher is about to die.

The program requires 4 arguments, in these order:
1. `number_of_philosophers`: The number of philosophers and forks.
2. `time_to_die` (milliseconds): The time a philosopher can survive without eating. Eating refresh this timer.
3. `time_to_eat` (milliseconds): The time it takes for a philosopher to `eat`.
4. `time_to_sleep` (milliseconds): The time a philospher `sleeps` after `eating`.
5. `number_of_meals` (optional argument): The number of times a philosopher can `eat`. Once all philosophers have eaten at least `number_of_meals` the simulation stops.

The program, `philo`, must output the philosphers states, as follows:
- `timestamp_in_ms X has taken a fork`
- `timestamp_in_ms X is eating`
- `timestamp_in_ms X is sleeping`
- `timestamp_in_ms X is thinking`
- `timestamp_in_ms X died`

`X`: philospher number

`timestamp_in_ms`: Current timestamp in milliseconds since the begging of the simulation.

### Specific Rules
- Each philosopher should be a thread.
- There is one fork between each pair of philosophers. Therefore, if there are several philosophers, each philosopher has a fork on their left side and a fork on their right side. If there is only one philosopher, there should be only one fork on the table.
- To prevent philosophers from duplicating forks, you should protect the forks state
with a mutex for each of them.
- A displayed state message should not be mixed up with another message.
- A message announcing a philosopher died should be displayed no more than 10 ms after the actual death of the philosopher.
- Your program must not have any data races.

## Threads vs Processes

### What's a Thread?
A thread is the smallest unit of execution within a process. Threads within the same process share the same memory space and resources, allowing them to communicate more easily.

### What's a Process?
A process is an independent program or instance of a program that runs in its own memory space and has its own set of system resources. Processes are isolated from each other.

### Differences between Threads and Processes
Main differences:
1. Memory space
    - Threads within the same process share the same memory space, meaning a thread can modify the same data of another thread
    - Process have their own memory space, meaning that any change in one process doesn't affect another processes.
2. Isolation
    - Threads within the same process are not isolated from each other, meaning if one thread crashes it can affect all the threads.
    - Processes are isolated from each other, meaning if a process crashes it doesn't affect the others processes.
3. Communication
    - Threads can comunicate through shared memory. This requires careful synchronization to avoid race conditions.
    - Process can comunicate via pipes.

### Mutex and Semaphore
A [mutex](https://en.wikipedia.org/wiki/Mutual_exclusion) is a protection to the shared memory between threads to avoid race conditions. The `mutex` prevents multiple threads from accessing the same data simultaneously.

A [semaphore](https://en.wikipedia.org/wiki/Semaphore_(programming)) is the same as `mutex` but for processes instead.

## Project Structure
- `philo/`: Main directory contaning all the directories.
- `philo_bonus/`: Main directory contaning all the directories for the bonus part.

Inside the both directories:
- `src/`: Contains all the source code.
- `include/`: Contains the header file.
- `Makefile`: Build automation file.

## Dependencies
- None.

## How to Use
1. Clone the repository.
2. Navigate to the `philo` directory: `cd philo`.
3. Compile the program: `make`.
4. Run the `philo` binary: `./philo nbr_philosophers time_to_die time_to_eat time_to_sleep [nbr_of_meals]`.

## Code Example
In this example the program runs indefinitely
```bash
./philo 5 800 200 200
2 2 has taken a fork
3 2 has taken a fork
3 2 is eating
4 4 has taken a fork
4 4 has taken a fork
4 4 is eating
6 1 has taken a fork
203 2 is sleeping
203 3 has taken a fork
204 1 has taken a fork
204 1 is eating
205 4 is sleeping
205 3 has taken a fork
205 3 is eating
205 5 has taken a fork
405 2 is thinking
406 1 is sleeping
406 5 has taken a fork
406 5 is eating
406 4 is thinking
406 3 is sleeping
406 2 has taken a fork
406 2 has taken a fork
406 2 is eating
...
```

## Bonus
The bonus part for this project challenges us to make the same program but, now, the philosophers are processes instead of threads.

This means that we don't share memory anymore, because every process has its own memory, and instead of `mutex` we need to use `semaphore` functions. This functions do the same thing a mutex does but for processes instead. (About [semaphore.h](https://pubs.opengroup.org/onlinepubs/7908799/xsh/semaphore.h.html))

## Contributing
I welcome contributions. If you have any bug fix or improvement, feel free to submit a pull request on the repository.
