# Ant Colony GAP
Usage of the Ant Colony Optimization to solve the Generalized Assignment Problem. 


## Requirements 
* G++ (GCC) >= 10.2.0
* Sqlite3 >= 3.33.0
* Meson >= 0.55.3

## How to compile

Build directory
```
meson release --buildtype=release
```

Compile
```
cd release
ninja
```

## Usage
```
Usage: ./gap <datatabase.db> <randomSeed> 
Arguments: 
    <database.db>      The sqlite3 file containing all the information.
    <randomSeed>       The seed for the RNG
```
