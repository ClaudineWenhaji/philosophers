
<p align="center">
*This project has been created as part of the 42 curriculum by cwenhaj.*
</p>

# <h1 align="center">*PHILOSOPHERS*</h1>
### Description
The project is to illustrate common issues in **concurrent programming / multithreading**. It simulates the ***Dining Philosophers Problem*** demonstrating how to **manage shared resources, prevent deadlocks and handle concurrent processes or threads safely**.

### Overview
One or N philosophers sit at a round table. There is a large bowl of spaghetti in the middle of the table.
- The philosophers take turns eating, thinking, and sleeping. While they are eating, they are not thinking nor sleeping; while thinking, they are not eating nor sleeping; and, of course, while sleeping, they are not eating nor thinking.
- There are also forks on the table. There are **as many forks as philosophers**.
- Since eating spaghetti with just one fork is impractical, a philosopher must pick up
both the fork to their right and the fork to their left before eating.
- When a philosopher has finished eating, they put their forks back on the table and
start sleeping. Once awake, they start thinking again. **The simulation stops when a philosopher dies of starvation**.
- Every philosopher needs to eat and should never starve.
- Philosophers do not communicate with each other.
- Philosophers do not know if another philosopher is about to die.
- Philosophers should avoid dying

### Instructions

1. <u>**Compilation:**</u> 

The program must compile with 42 mandatory flags: -Wall -Werror -Wextra

Makefile usual commands:

```bash
make        # Compiles
make clean  # Deletes objs
make fclean # Deletes objs and executable
make re     # Cleans and recompiles
```

2. <u>**Execution:**</u> 

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
The last one is optional. If not given, it will run until a philosopher dies.

For example: ./philo 5 800 200 200 7
with **leaks** check: valgrind ./philo 5 800 200 200
with **data races** check: valgrind --tool=helgrind ./philo 200 800 200 200 3

3. <u>**Error management**</u>

The program must react properly to

- Wrong number of arguments
- A non-numeric argument
- A number being above INT_MAX or under INT_MIN

### Features

> - Simulates multiple philosophers thinking, eating, and sleeping concurrently.
> - Ensures proper synchronization using mutexes.
> - Avoids deadlocks and race conditions
> - Supports configurable number of philosophers and timing parameters.
> - Outputs philosopher actions with timestamps to the console.

### Technical Choices

1- *Concurrency*: **pthread** 
2- *Synchronization*: **Mutex**
- **pthread_mutex_t** for forks, writing, meals and dead checks
- Ensures safe access to shared variables

3- *Timing*: 
- **gettimeofday** or **usleep** for accurate simulation
- Fine-grained check to allow interruption or death

4- *Memory Management*
- Dynamic allocation for philosophers and forks
- Proper cleanup on errors or program end

5- *Edge Cases*
- Single philospher handle separately
- Optional number of meals per philosopher


### Resources

**Official documentation** to understand how to use:
- `gettimeofday`
- `pthread_create`
- `pthread_join`
- `pthread_mutex_init`
- `pthread_mutex_destroy`
- `pthread_mutex_lock`
- `pthread_mutex_unlock`

[Readme Syntax](https://markdownguide.offshoot.io/basic-syntax/) - to understand how to write a readme
[General Overview](https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2) - to understand the dining philosophers problem
[Process, Thread, and differences + Videos](https://42-cursus.gitbook.io/guide/3-rank-03/philosophers/understand-philosophers)
[Philo Visualizer](https://rom98759.github.io/Philosophers-visualizer/) - to visualize what's happening in a test

<u>**AI**</u> has been used to:
- debug
- Summarize and better understand new concepts introduced in this project.
- test all possible cases

### Summary of Concepts

1- <u>**A Thread:**</u> A **thread** is the smallest unit of execution within a process.
* Multiple threads within a process share memory and resources
* Threads allow concurrent operations within a single program.

Example: Each philosopher is a separate thread (pthread_create(&program->philos[i].thread, ...)) that independently executes philo_routine

2- <u>**A Process:**</u> A **process** is an independent program running in its own memory space
* Threads belong to processes, sharing memory.
* Communication between processes usually requires inter-process communication (IPC), unlike threads that share memory.

3- <u>**Mutex (Mutual Exclusion):**</u> A **mutex** is a synchronization tool used to protect shared resources from simultaneous access.
* Only one thread can lock a mutex at a time.
* Other threads attempting to lock it wait until it’s unlocked.

Example in my code:
pthread_mutex_t forks[i] ensures only one philosopher can pick up a fork at a time.
write_lock, meal_lock, dead_lock protect shared variables like printing to console, last meal time, and death flags

4- <u>**Deadlock:**</u> A **deadlock** occurs when two or more threads are waiting indefinitely for resources held by each other. In my code, Philosophers pick up forks in a specific order (**even IDs pick up right fork first, odd IDs pick up left first**). This breaks the circular wait condition, preventing deadlocks.

5- <u>**Data Race:**</u> A **data race** happens when two threads access the same variable simultaneously, and at least one of the accesses is a write, without proper synchronization. This can lead to unpredictable results or corrupted data.

Example in my code: Updating last_meal or meal_eaten without a mutex could cause incorrect counts. meal_lock and dead_lock are used to prevent data races.

6- <u>**Starvation:**</u> **Starvation** occurs when a thread never gets access to required resources, even if there is no deadlock. A philosopher may never eat if another philosopher constantly takes the forks before them.

Example in my code: Alternating fork pickup order (odd/even IDs) and careful monitoring ensures all philosophers get a chance to eat.
