# FlightSim

A tiny C++ flight-sensation demo using SFML.

## Features

- Plane rendered as a single horizontal line
- Left and right arrow keys move the plane
- Basic scrolling terrain made from simple shapes
- Cross-platform CMake build setup (Windows/Linux)

## Build

```bash
cmake -S . -B build
cmake --build build
```

If SFML is already installed, it will be used. Otherwise CMake fetches SFML automatically.

## Run

```bash
./build/flightsim
```

On Windows, run `build\\Debug\\flightsim.exe` (or the generated configuration output).
