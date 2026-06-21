*This project has been created as part of the 42 curriculum by bahkaya.*

# Philosophers

## Description

**Philosophers** is a multithreading project from the 42 curriculum. It is a classic implementation of the **Dining Philosophers Problem**, a well-known synchronization problem in computer science used to illustrate the challenges of concurrent resource access, deadlocks, and race conditions.

A number of philosophers sit around a round table. Each philosopher alternates between three states: **eating**, **sleeping**, and **thinking**. There is one fork between each pair of adjacent philosophers, and a philosopher needs **both** the fork on their left and the fork on their right to eat. Since the forks are shared resources, philosophers must compete for them without ever miscounting or duplicating a fork.

The goal of this project is to simulate this scenario using **threads** and **mutexes**, ensuring that:
- No philosopher starves (a philosopher dies if they don't start eating before `time_to_die` ms have passed since their last meal, or since the start of the simulation).
- No data races occur on shared resources (forks, simulation state, etc.).
- State-change messages (taking a fork, eating, sleeping, thinking, dying) are logged with an accurate timestamp and never overlap with one another.
- A death is reported within 10 ms of it actually happening.

This repository contains the **mandatory part**, where each philosopher is represented by a separate **thread**, and forks are protected by **mutexes**.

## Instructions

### Compilation

```bash
make
```

This builds the `philo` executable using `cc` with the `-Wall -Wextra -Werror -pthread` flags.

Other available Makefile rules:

```bash
make clean   # remove object files
make fclean  # remove object files and the executable
make re      # fclean + all
```

### Execution

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

| Argument | Description |
|---|---|
| `number_of_philosophers` | Number of philosophers (and number of forks) sitting at the table. |
| `time_to_die` | Time in milliseconds before a philosopher dies if they haven't started eating. |
| `time_to_eat` | Time in milliseconds a philosopher spends eating. |
| `time_to_sleep` | Time in milliseconds a philosopher spends sleeping. |
| `number_of_times_each_philosopher_must_eat` *(optional)* | If specified, the simulation stops once every philosopher has eaten at least this many times. |

#### Examples

```bash
# 5 philosophers, dies after 800ms without eating, eats for 200ms, sleeps for 200ms
./philo 5 800 200 200

# Same as above, but simulation stops once everyone has eaten 7 times
./philo 5 800 200 200 7

# A single philosopher: they have only one fork and will die, since they can never eat
./philo 1 800 200 200
```

#### Sample output format

```
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
400 1 is thinking
...
```

## Resources

- [The Dining Philosophers Problem (Wikipedia)](https://en.wikipedia.org/wiki/Dining_philosophers_problem) — original formulation of the problem by Edsger Dijkstra.
- [POSIX Threads Programming (LLNL Tutorial)](https://hpc-tutorials.llnl.gov/posix/) — reference for `pthread_create`, `pthread_join`, `pthread_detach`.
- `man pthread_mutex_init`, `man pthread_mutex_lock`, `man pthread_mutex_unlock`, `man pthread_mutex_destroy` — manual pages for mutex usage.
- `man gettimeofday`, `man usleep` — manual pages for timing functions used to track and respect simulation delays.
- 42 Network internal subject and resources for the *Philosophers* project.

### AI usage

AI assistance (Claude) was used during this project in the following ways:

- **Understanding the subject**: clarifying ambiguous points of the dining philosophers problem (e.g. fork assignment order, death-detection timing constraints) before writing any code.
- **Debugging support**: discussing potential race conditions and deadlock scenarios (e.g. all philosophers picking up their left fork simultaneously) and reviewing whether the mutex locking strategy avoided them.
- **Documentation**: drafting and refining this README file.

All core logic — thread creation, mutex management, the eating/sleeping/thinking routine, and the death-detection ("waiter") thread — was written and is fully understood by the author. AI-generated suggestions were reviewed, tested, and discussed with peers before being considered final, in line with the project's AI usage guidelines.
