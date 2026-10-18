# `mes_ob9_fekrendszer` package

ROS 2 C++ package. ![Static Badge](https://img.shields.io/badge/ROS_2-Humble-34aec5)

A package két node-ból áll. A `/radar_node` folyamatosan csökkenő távolságadatokat szimulál egy akadály felé közeledve, amit a `/distance` nevű `std_msgs/msg/Float32` topicban hirdet. A `/brake_node` feliratkozik erre a topicra, és amennyiben a távolság 2.0 méter alá esik, vészfékezési jelzést hirdet az `/emergency_brake` nevű `std_msgs/msg/Bool` topicban, valamint figyelmeztetést jelenít meg a terminálban. Megvalósítás `ROS 2 Humble` alatt.

## Packages and build

It is assumed that the workspace is `~/ros2_ws/`.

### Clone the packages

```bash
cd ~/ros2_ws/src
```

```bash
git clone [https://github.com/markoo0120/mes_ob9_fekrendszer](https://github.com/markoo0120/mes_ob9_fekrendszer)
```

### Build ROS 2 packages

```bash
cd ~/ros2_ws
```

```bash
colcon build --packages-select mes_ob9_fekrendszer --symlink-install
```

<details>
<summary>Don't forget to source before ROS commands.</summary>

```bash
source ~/ros2_ws/install/local_setup.bash
```
</details>

```bash
ros2 launch mes_ob9_fekrendszer fekrendszer.launch.py
```

```bash
ros2 run mes_ob9_fekrendszer radar_node
```

```bash
ros2 run mes_ob9_fekrendszer brake_node
```

## Graph

```mermaid
graph LR;
    radar_node(["/radar_node"]):::red --> distance["/distance<br/>std_msgs/msg/Float32"]:::blue
    distance --> brake_node(["/brake_node"]):::red
    brake_node --> emergency_brake["/emergency_brake<br/>std_msgs/msg/Bool"]:::blue

    classDef red fill:#ea4335,stroke:#222,stroke-width:2px,color:#fff;
    classDef blue fill:#25a2b8,stroke:#222,stroke-width:2px,color:#111;
```