avr
===

## Building and uploading AVR firmware
The commands for building and uploading firmware images are straight-forward CMake:

```
mkdir build
cd build
cmake ..
make
make ezeegame-upload # Assuming ezeegame is used in generate\_arduino\_firmware()
```
