# Description
Generic Finite State Machine


## Requirements
+ Explicit transition table
+ States could have multiple events
+ States could have multiple routes to another states
+ Event search should be optimized
+ States business logic should be implemented as function pointers
+ Each state must be attached to only one function


## Build
To bulid the project follow belowed steps. Script requires **cmake**, **make**.

1. Clone repository to workspace folder with --recursive flag,
2. Create build directory,
3. Enter build directory and run **cmake ..**,
4. After successful cmake configuration run **make all**.


