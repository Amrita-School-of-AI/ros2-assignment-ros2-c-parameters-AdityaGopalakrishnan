[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/lgPfnhB6)
# Assignment: ROS2 C++ Parameters

**Course:** ROS2 Fundamentals  
**Build System:** ament_cmake

## Objective

The goal of this assignment is to verify your understanding of:

1. How to declare and use ROS2 Parameters.
2. How to set default parameter values.
3. How to read parameter values at runtime.

## Problem Statement

You must complete the provided skeleton code to create a ROS2 node that uses parameters to configure its behavior.

### Requirements

1. **Source Code (`src/param_node.cpp`)**:
   - Implement a class `ParamNode` that inherits from `rclcpp::Node`.
   - Initialize the node with the name `"param_node"`.
   - Declare the following parameters with their default values:
     - `robot_name` (string): default `"ROS2Bot"`
     - `max_speed` (double): default `1.5`
     - `enabled` (bool): default `true`
   - Create a timer that fires every **2000ms**.
   - In the timer callback:
     - Read all three parameters.
     - Log: `"Robot: <name>, Max Speed: <speed>, Enabled: <enabled>"`

2. **Build Configuration (`CMakeLists.txt`)**:
   - Add an executable target named `param_node`.
   - Link dependencies for `rclcpp`.

3. **Package Metadata (`package.xml`)**:
   - Add the missing dependency tags.

## How to Test Locally

```bash
# Build and run with default parameters
colcon build --packages-select ros2_parameters
source install/setup.bash
ros2 run ros2_parameters param_node

# Run with custom parameters
ros2 run ros2_parameters param_node --ros-args -p robot_name:=MyRobot -p max_speed:=2.5 -p enabled:=false
```

#### Expected Output (default parameters):

```shell
[INFO] [1700000000.123456789] [param_node]: Robot: ROS2Bot, Max Speed: 1.500000, Enabled: true
```

#### Expected Output (custom parameters):

```shell
[INFO] [1700000000.123456789] [param_node]: Robot: MyRobot, Max Speed: 2.500000, Enabled: false
```

#### Verify parameters with CLI:

```bash
ros2 param list /param_node
ros2 param get /param_node robot_name
```
