# trajectory-plan-with-rviz

## Usage
Build the package
```
cd ~/your workspace
catkin_make
source /devel/setup.bash
```

Run the node
```
rosrun trajectory_plan_with_rviz showpath
```

Visualize
```
cd ~/your workspace/src/trajectory_plan_with_rviz/rviz
rviz -d showpath.rviz
```
![image](https://github.com/ChengChengYang0416/trajectory-plan-with-rviz/figures/traj.png)

## Reference
[show trajectory in rviz](https://blog.csdn.net/ktigerhero3/article/details/70256437)
