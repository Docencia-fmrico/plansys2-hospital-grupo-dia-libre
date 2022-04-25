[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-c66648af7eb3fe8bc4f294546bfd86ef473780cde1dea487d3c4ff354943c9ae.svg)](https://classroom.github.com/online_ide?assignment_repo_id=7551085&assignment_repo_type=AssignmentRepo)


# Problem solving in AWS Hospital using plansys2

In this assignment we were requested to generate a problem-solving behaviour in ROS2 using plansys2. The objective was to reuse the pddl domain that we created in the assignment before, adapt it to be able to use it with plansys2 and generate a series of problems that would run sequentially on a ROS2 controller node that uses a switch-case to create different goals for a problem solver.

## Mapping the hospital

The scenario requested on this assignment was the AWS Hospital. In order to execute problems that require navigation, mapping the place was a must. This was done with the same process we did in assignments before like the kobuki navigation. The resulting map was the following:

![image](https://user-images.githubusercontent.com/78983070/165061908-1ac7f1c9-7b10-4aff-bbcd-210da035c225.png)

With this map, we could now add navigation tasks in our problem.

## Action Nodes used by the controller

The plansys2 controller needs to know which nodes execute the actions indicated in the PDDL file. 
