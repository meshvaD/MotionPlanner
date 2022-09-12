# MotionPlanner

### IK Solver
* using CCD (Cyclic Coordinate Descent) align each link to the target, starting from the end effector to the start link
* continue this process until the end effector reaches the target position

* visualize this iterative process through an OpenGL window

### Path Solver
* upload an image of obstacles in the world, so that the origin of the simulated arm is in the center of the image
     * specify a scale between the obstacles in the image and the arm itself

  ##### Cartesian Spce
  * knowing the beginning and end cartesian positions of the end effector use the PathSolver class to solve for a path avoiding obstacles
  
  ##### Joint Space
  * knowing the beginning and end joint positions (by using the IK Solver), use the JointSpaceSolver class to solve for a path avoiding obstacles
  
* both scenarios use the A* path finding algorithm, using IK or FK at each position to determine if the position of the tip of end effector is valid (i.e. not touching any obstacles)
     * calculate the "weights" at each position by determining the Euclidean distance between the start and end
     
TO DO: ensure that no part of the link if touching any obstacles, not just the tip of the end effector
 
### Other
* visualize the Joint Space of any 2-joint system, given the Cartesian Space
