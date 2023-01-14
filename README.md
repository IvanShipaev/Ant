# Ant

- Generate MinGW Makefiles
```bash
mkdir cmake-build-debug
cd cmake-build-debug
# Command to generate MinGW Makefiles
cmake .. -G "MinGW Makefiles"
```
- Generate Unix Makefiles
```bash
mkdir cmake-build-debug
cd cmake-build-debug
# Command to generate Unix Makefiles
cmake .. -G "Unix Makefiles"
```
- Generate Ninja build
```bash
mkdir cmake-build-debug
cd cmake-build-debug
# Command to generate Ninja
cmake .. -G Ninja
```
- Additional options, only for test (debug only). Do not need to be used in a production release
```
