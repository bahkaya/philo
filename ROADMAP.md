# Philosophers Project - Progress Roadmap

## ✅ COMPLETED

### Core Architecture
- [x] Data structures defined (`t_data` and `t_philo` structs in [philo.h](philo.h))
- [x] Linked list for philosophers
- [x] Mutex systems for forks and synchronization

### Input Validation & Setup
- [x] Argument count validation (5 or 6 arguments required)
- [x] Digit validation (`check_av()`)
- [x] Value range validation (`check_value()`)
- [x] Memory allocation for data structure (`allocate_data()`)
- [x] Memory allocation for philosophers (`allocate_philos()`)

### Synchronization Setup
- [x] Fork mutex creation (`ft_create_mutexes()`)
- [x] Fork assignment to philosophers (`assign_forks()`)
- [x] Print mutex defined and initialized
- [x] Death mutex defined and initialized
- [x] Meal mutex defined and initialized per philosopher

### Thread Management
- [x] Thread creation (`ft_create_thread()`)
- [x] Thread joining framework started (`ft_join_philos()`)
- [x] Philosopher routine with eat/sleep/think cycle (`routine()`)

### Utilities
- [x] Time management (`get_current_time()`, `ft_usleep()`)
- [x] Status printing with print_mutex (`printf_status()`)
- [x] Custom isdigit function (`ft_isdigit()`)

---

## � REMAINING ISSUES - NEED FIXING

### 1. **Incomplete Meal Counting Termination**
   - **Status**: Basic meal tracking exists, but termination on `must_eat_count` is missing
   - **Location**: [eat_simulation.c](eat_simulation.c) in `routine()` function
   - **Current State**:
     - ✅ Death detection logic exists (checks `time_to_die`)
     - ✅ Synchronization with mutexes is present
     - ✅ Meal counter increments are tracked
     - ❌ No check if all philosophers have eaten `must_eat_count` times
   - **Impact**: When 6th argument is provided, simulation doesn't end when all philosophers finish eating
   - **Fix**: After each meal, check if all philosophers reached `must_eat_count` and set `simulation_end = 1`

### 2. **Missing Memory Cleanup**
   - **Status**: No cleanup function exists
   - **Location**: Need new function in [utils.c](utils.c) or [eat_simulation.c](eat_simulation.c)
   - **Impact**: Memory leaks when program exits
   - **Functions Needed**:
     - `void free_data(t_data *data)` - free all allocations and destroy mutexes
     - Call this from `main()` after `ft_join_philos()`

---

## ⏭️ TODO - Priority Order

### Phase 1: Add Meal Counting Termination
- [ ] **Fix meal counting termination** in [eat_simulation.c](eat_simulation.c)
  - After philosopher eats (increments `meals_eaten`), check if ALL philosophers have eaten enough
  - Logic: Iterate through all philosophers, check if `meals_eaten >= must_eat_count`
  - If YES and `must_eat_count != -1`, set `simulation_end = 1`
  - Must protect this check with mutexes to avoid race conditions
  - Consider: May need a helper function to count philosophers who have eaten enough

### Phase 2: Memory Cleanup
- [ ] **Implement cleanup function** in [utils.c](utils.c)
  ```c
  void free_data(t_data *data)
  {
    t_philo *current = data->philos;
    t_philo *temp;
    
    // Destroy all mutexes
    for (int i = 0; i < data->nb_philos; i++)
      pthread_mutex_destroy(&data->forks[i]);
    pthread_mutex_destroy(&data->print_mutex);
    pthread_mutex_destroy(&data->death_mutex);
    
    // Free philosopher nodes and their mutexes
    while (current)
    {
      pthread_mutex_destroy(&current->meal_mutex);
      temp = current;
      current = current->next;
      free(temp);
    }
    
    // Free remaining data
    free(data->forks);
    free(data);
  }
  ```

- [ ] **Add declaration** to [philo.h](philo.h)
  - Add: `void free_data(t_data *data);`

- [ ] **Call cleanup from main**
  - After `ft_join_philos(data)` in [main.c](main.c), add `free_data(data);`

### Phase 3: Testing & Edge Cases
- [ ] **Test with 1 philosopher** - should die after `time_to_die`
- [ ] **Test with 2 philosophers** - check for deadlock
- [ ] **Test with >2 philosophers** - normal operation
- [ ] **Test with 6th parameter** - should stop when all eat enough times
- [ ] **Test without 6th parameter** - should stop on first death
- [ ] **Memory leak check** - run with valgrind
- [ ] **Check output format** - timestamps and philosopher IDs should be clean

---

## 📋 CHECKLIST - Quick Reference

| Task | File | Status |
|------|------|--------|
| Create threads | eat_simulation.c | ✅ DONE |
| Join threads | eat_simulation.c | ✅ DONE |
| Assign forks | eat_simulation.c | ✅ DONE |
| Fix meal termination | eat_simulation.c | ❌ TODO |
| Implement cleanup | utils.c | ❌ TODO |
| Add free_data() declaration | philo.h | ❌ TODO |
| Call free_data() in main | main.c | ❌ TODO |
| Test all scenarios | test/ | ❌ TODO |
- [ ] **Handle single philosopher case**
  - 1 philo with 2 forks won't work (deadlock)
  - May need special case logic
  
- [ ] **Add mutex destroy error checking**
  - Check `pthread_mutex_destroy()` return values

- [ ] **Improve error messages**
  - More descriptive error outputs
  - Use stderr for errors

### Phase 5: Testing & Verification
- [ ] Test with standard inputs (4 philosophers, etc.)
- [ ] Test with optional 6th parameter (meal count)
- [ ] Verify no output after philosopher dies
- [ ] Check for race conditions/garbled output
- [ ] Verify proper cleanup (no memory leaks)
- [ ] Test edge cases

---

## 📋 Key Functions Needing Work

| Function | Status | Issue |
|----------|--------|-------|
| `routine()` | ⚠️ Incomplete | No death detection, infinite loop, no mutex protection |
| `ft_join_philos()` | 🚧 Partial | Cut off, needs completion |
| Death Detection | ❌ Missing | Should track `last_meal`, update after eating |
| `free_data()` | ❌ Missing | Need to add cleanup function |
| Meal Counting | ❌ Missing | Optional feature for 6th parameter |

---

## 📊 Current Files

- `philo.h` - Header with structs and function declarations
- `main.c` - Entry point and initialization flow
- `utils.c` - Input validation, memory allocation, mutex setup
- `eat_simulation.c` - Philosopher routine and thread management
- `Makefile` - Build configuration (correct with pthread flag)

---

## 🎯 Success Criteria

When done, the program should:
1. ✅ Accept 5 or 6 command line arguments
2. ✅ Create N philosopher threads
3. ✅ Output timestamps and philosopher actions (thread-safe)
4. ✅ Stop output immediately when any philosopher dies
5. ✅ Exit cleanly without memory leaks
6. ✅ (Optional) Support meal counting when 6th arg provided
7. ✅ Handle all edge cases without deadlock/crashes
