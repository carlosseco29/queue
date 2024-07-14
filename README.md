# Queue Documentation

Welcome to the documentation for the Queue project

## Overview

Queue is an exercise project
This project implements std::queue and std::forward_lists in order to have self-implemented queue that avoids using std library for storing elements

The queue supports Pushing, Popping and Popping with a timeout. It auto-resizes when maximum set size for the queue is reached.

## Getting Started
1. Install dependencies.
2. Clone the repository.
3. Run these commands inside the cloned repository
```bash
mkdir build
cd build
cmake ..
make
```

## Running the executable
1. cd into the build directory created above
2. Run the executable 
```bash
src/queue
```

## Running the tests 
1. cd into the build directory created above
2. Run the tests
```bash
test/tests
```

## Creating and opening the documention
1. Run this commands inside the cloned repository
```bash
doxygen Doxyfile
```
2. open docs/html/index.html with your favourite browser

## Dependencies
gtest (should be automatically fetched and installed by CMake)

Doxygen (to generate the documentation)
