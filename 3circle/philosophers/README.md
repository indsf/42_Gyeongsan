*This project has been created as part of the 42 curriculum by inhlee.*

# philosophers
`philosophers` is a concurrency project that implements the classic **Dining Philosophers** problem using **threads** and **mutexes**.  
The core objective is to build a simulation where multiple threads compete for shared resources (forks) **without data races**, **without deadlocks**, and with **correct timing constraints**.

---

## Description

### Goal
- Create and manage multiple threads and their lifecycles
- Protect shared state (forks, timing data, stop flag, etc.) with mutexes to **eliminate data races**
- Apply a design that **prevents deadlocks**
- Ensure accurate timing behavior based on `time_to_die`, `time_to_eat`, and `time_to_sleep`
- Produce consistent timestamped event logs (with synchronized printing)

### Overview
Philosophers sit around a table and repeatedly cycle through **eating → sleeping → thinking**.  
To eat, each philosopher needs **two forks** (one on each side). Forks are shared resources, so access must be protected with mutexes.

The simulation must satisfy:
- A fork cannot be used by two philosophers at the same time
- If any philosopher exceeds `time_to_die`, print `died` and terminate the simulation
- Logs include a timestamp (ms) and philosopher ID, and output must be synchronized so lines do not interleave

---

## Features
- Thread-based simulation (one thread per philosopher)
- Mutex-protected access to forks and shared data
- Timestamped event logging
- Input validation and error handling (reject invalid arguments)

---

## Instructions

### Requirements
- OS: Linux or macOS
- Compiler: `cc` (clang or gcc)
- Build tool: `make`

### Build
If the project is located in the `Philosophers/` directory (current structure):

```bash
cd Philosophers
make
```

### Run
Executable path: **`Philosophers/./philo`**

#### Parameters
- `number_of_philosophers`: number of philosophers (= number of forks)
- `time_to_die` (ms): time after the last meal before a philosopher dies
- `time_to_eat` (ms): time spent eating
- `time_to_sleep` (ms): time spent sleeping
- `number_of_times_each_philosopher_must_eat` (optional): stop once each philosopher has eaten this many times

#### Examples
```bash
# 5 philosophers, die 800ms, eat 200ms, sleep 200ms
Philosophers/./philo 5 800 200 200

# Stop once each philosopher has eaten 7 times
Philosophers/./philo 5 800 200 200 7
```

---

## Output Format
Output generally follows this format:

```
[timestamp_in_ms] [philosopher_id] [event]
```

Event examples:
- `has taken a fork`
- `is eating`
- `is sleeping`
- `is thinking`
- `died`

Since multiple threads may print concurrently, it is common to protect logging with a **print mutex** to prevent mixed lines.

---

### Deadlock Avoidance — Common Strategy
Implementations typically use one (or a combination) of the following approaches.

1) **Odd/Even fork pickup order**
- Odd IDs: left → right
- Even IDs: right → left
- Pros: simple and effective
- Note: handle edge cases (especially when there is only 1 philosopher)

### Death Monitoring
- A monitor thread (or periodic loop) checks every philosopher’s `last_meal`
- If `(current_time - last_meal) > time_to_die`, print `died` and set a stop flag
- Prevent further logs after termination (or follow the project’s required output rules)

---

## Resources

### Classic References
- POSIX Threads (pthreads) overview  
  https://man7.org/linux/man-pages/man7/pthreads.7.html
- `pthread_mutex_*` reference  
  https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html
- Dining Philosophers problem overview  
  https://en.wikipedia.org/wiki/Dining_philosophers_problem
- Deadlock conditions (Coffman conditions)  
  https://en.wikipedia.org/wiki/Deadlock

### How AI Was Used
- Organizing the README structure (sections, wording, command examples)
- Summarizing concurrency concepts (deadlock avoidance strategies, monitoring loop design)
- Reviewing documentation for clarity (logging synchronization and shared-state protection checklist)

AI was used to support documentation, concept organization, and review—not to copy/paste a finished implementation.

---

## License
This project is developed as part of the 42 curriculum.