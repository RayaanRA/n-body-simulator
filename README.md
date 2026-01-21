# n-body-simulator
A customizable N-body simulator built on top of the [cphys](https://github.com/RayaanRA/cphys) library. 
It supports configurable initial conditions, CSV output, and optional visualization with [raylib](https://github.com/raysan5/raylib).

## Installation

```bash
git clone git@github.com:RayaanRA/n-body-simulator.git
cd n-body-simulator
```

To compile without visualization:
```bash
make
```

To compile with raylib:
```bash
make USE_RAYLIB=1
```

## Dependencies
- [cphys](https://github.com/RayaanRA/cphys)
- Optional: [raylib](https://github.com/raysan5/raylib)

## Configuration File Format
The simulator reads a configuration file specifying initial conditions. It must follow this structure:  
```
N <int>
G <double>
softening <double>
<pos_x> <pos_y> <vel_x> <vel_y> <mass>

```

Example config file:  
```
N 3
G 1.0
softening 0.2
-0.6 0.2 0.3 -0.1 1.0
0.4 -0.5 -0.2 0.35 1.0
0.2 0.3 -0.1 -0.25 1.0

```

## Running the Simulator
```
./nbody_sim <config_file> <dt> <steps> [csv_file]
```

## CSV Output
Passing in a CSV file is optional. If passed, the following data will be appended:
```
step, energy, momentum_x, momentum_y, body0_pos_x, body0_pos_y, body0_vel_x, body0_vel_y, ..., bodyN_pos_x, bodyN_pos_y, bodyN_vel_x, bodyN_vel_y
```

## Visualization
If compiled with raylib:  
- Simulation runs indefinitely regardless of `<steps>`
- A certain number of steps (`PHYSICS_STEPS`) are run before drawing

## Notes
- Precompute initial acceleration before the first integration step

## Demonstration

[Three-body simulation demo](media/three_body.mp4)
[Twelve-body simulation demo](media/twelve_body.mp4)
[Example CSV output](media/csv_output.png)