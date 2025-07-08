# Philosophers

A C implementation of the classic **Dining Philosophers Problem** using pthreads. This project demonstrates concurrent programming concepts including thread synchronization, mutex locks, and deadlock prevention.

## 🍽️ The Dining Philosophers Problem

The dining philosophers problem is a classic synchronization problem that illustrates challenges in resource allocation and deadlock prevention. The scenario involves:

- **N philosophers** sitting around a circular table
- Each philosopher needs **two forks** to eat
- Philosophers alternate between **eating**, **sleeping**, and **thinking**
- The challenge is to prevent **deadlock** and **starvation**

## 📁 Project Structure

```
philosophers/
├── philo/
│   ├── philosophers.c      # Main entry point
│   ├── philo.h            # Header file with structures and function declarations
│   ├── Makefile           # Build configuration
│   ├── param_check.c      # Parameter validation
│   ├── initialise.c       # Data structure initialization
│   ├── initialise_helper.c # Helper functions for initialization
│   ├── simulation.c       # Core simulation logic
│   ├── monitoring.c       # Death monitoring thread
│   ├── helper.c           # Utility functions
│   ├── cleaning.c         # Memory cleanup
│   └── ft_atoi.c          # String to integer conversion
└── .gitignore
```

## 🛠️ Installation

### Prerequisites

- **GCC compiler** (GNU Compiler Collection)
- **Make** build system
- **pthread** library (usually included with GCC)

### Building the Project

1. **Clone the repository:**
   ```bash
   git clone https://github.com/Raainshe/philosophers.git
   cd philosophers
   ```

2. **Navigate to the source directory:**
   ```bash
   cd philo
   ```

3. **Build the project:**
   ```bash
   make
   ```

   This will create an executable named `philo`.

### Build Options

- `make` or `make all` - Build the project
- `make clean` - Remove object files
- `make fclean` - Remove object files and executable
- `make re` - Rebuild the project (clean + build)

## 🚀 Usage

### Command Line Format

```bash
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]
```

### Parameters

| Parameter | Description | Required |
|-----------|-------------|----------|
| `number_of_philosophers` | Number of philosophers (and forks) | Yes |
| `time_to_die` | Time in milliseconds before a philosopher dies of starvation | Yes |
| `time_to_eat` | Time in milliseconds it takes for a philosopher to eat | Yes |
| `time_to_sleep` | Time in milliseconds a philosopher spends sleeping | Yes |
| `number_of_times_each_philosopher_must_eat` | Optional: simulation stops when all philosophers eat this many times | No |

### Examples

**Basic simulation with 5 philosophers:**
```bash
./philo 5 800 200 200
```

**Simulation with eating limit:**
```bash
./philo 5 800 200 200 7
```

**Single philosopher (edge case):**
```bash
./philo 1 800 200 200
```

## 🎯 Features

### Core Functionality
- **Thread-based simulation** using pthreads
- **Mutex synchronization** for fork access
- **Death monitoring** to detect starvation
- **Configurable parameters** for timing and limits
- **Proper cleanup** of resources

### Deadlock Prevention
- **Ordered fork pickup** (lower index first)
- **Odd-even philosopher staggering** to reduce contention

### Error Handling
- **Parameter validation** (positive integers only)
- **Memory allocation checks**
- **Thread creation error handling**
- **Graceful cleanup on errors**

## 📊 Output Format

The program outputs philosopher actions with timestamps:

```
[timestamp] [philosopher_number] [action]
```

### Example Output:
```
0 1 has taken a fork
0 2 has taken a fork
0 2 is eating
200 2 is sleeping
200 1 has taken a fork
200 1 is eating
400 1 is sleeping
400 2 is thinking
```

### Actions:
- `has taken a fork` - Philosopher picked up a fork
- `is eating` - Philosopher is eating
- `is sleeping` - Philosopher is sleeping
- `is thinking` - Philosopher is thinking
- `died` - Philosopher died of starvation

## 🔧 Technical Details

### Data Structures

**Philosopher (`t_philo`):**
- Thread ID and state
- Fork assignments (left/right)
- Eating statistics
- Individual mutex for state protection

**Simulation Data (`t_data`):**
- Global parameters (timing, limits)
- Array of philosophers and forks
- Control mutexes for output and death monitoring
- Simulation state flags

### Threading Model
- **One thread per philosopher** for individual behavior
- **One monitoring thread** for death detection
- **Mutex-protected shared resources** (forks, output, death flag)

### Synchronization
- **Fork mutexes** prevent multiple philosophers from using the same fork
- **Write mutex** ensures atomic output
- **Death mutex** protects the death flag
- **State mutex** protects individual philosopher state

## 🧪 Testing

### Basic Tests
```bash
# Test with different numbers of philosophers
./philo 2 800 200 200
./philo 3 800 200 200
./philo 4 800 200 200
./philo 5 800 200 200

# Test with eating limits
./philo 5 800 200 200 3
./philo 5 800 200 200 7

# Test edge cases
./philo 1 800 200 200
./philo 200 800 200 200
```

### Performance Testing
```bash
# Test with many philosophers
./philo 50 800 200 200

# Test with different timing
./philo 5 1000 100 100
./philo 5 500 300 300
```

## 🐛 Troubleshooting

### Common Issues

**"You have entered the incorrect parameters!"**
- Ensure all parameters are positive integers
- Check that you have exactly 4 or 5 arguments
- Verify no parameters are zero

**Segmentation fault**
- Check for sufficient system resources
- Verify pthread library is available
- Ensure proper memory allocation

**Program hangs**
- May indicate deadlock (though the implementation prevents this)
- Check system load and available threads

### Debugging
- Use `valgrind` for memory leak detection:
  ```bash
  valgrind --leak-check=full ./philo 5 800 200 200
  ```

## 📝 License

This project is part of the 42 curriculum and follows the 42 coding standards.

## 👨‍💻 Author

**Raainshe** - [GitHub](https://github.com/Raainshe)

---

*This implementation demonstrates advanced concurrent programming concepts and provides a robust solution to the classic dining philosophers problem.* 