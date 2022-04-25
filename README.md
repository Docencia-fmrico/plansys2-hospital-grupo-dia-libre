[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-c66648af7eb3fe8bc4f294546bfd86ef473780cde1dea487d3c4ff354943c9ae.svg)](https://classroom.github.com/online_ide?assignment_repo_id=7551085&assignment_repo_type=AssignmentRepo)


# Problem solving in AWS Hospital using plansys2

In this assignment we were requested to generate a problem-solving behaviour in ROS2 using plansys2. The objective was to reuse the pddl domain that we created in the assignment before, adapt it to be able to use it with plansys2 and generate a series of problems that would run sequentially on a ROS2 controller node that uses a switch-case to create different goals for a problem solver.

## Problem PDDL

We used the pddl domain that we created in the assignment before. We needed to do some modifications. Before, we navigated between rooms, corridors and zones, that were either connected directly or with a door in between. To approach navigation in this problem, we decided to surpress doors, corridors, zones and connections. As the ROS2 navigation navigates between two stablished points, we were now navigating between points. In the domain, we created the following actions, that were going to be implemented in ROS2 nodes later on:

### Move location

Move location moves the robot from a point to another. The point does not necesarilly have to be in a room, we just left the typo that we have before.

```
(:durative-action move_location
    :parameters (?robot - robot ?prev_room - location ?next_room - location)
    :duration (= ?duration 5)
    :condition 
      (and
        (at start(robotat ?robot ?prev_room))
      )
    :effect 
      (and  
        (at end(robotat ?robot ?next_room))
        (at start(not(robotat ?robot ?prev_room)))
      )
)
```
### Pick

Pick remained the same as in the previous assignment. As we will not be able to use the robot's gripper whatsoever, the coding solution was emulating it. We will get deeper into it later on.

```
(:durative-action pick
  :parameters (?o - object ?l - location ?r - robot ?t - tool)
  :duration (= ?duration 5)
  :condition 
    (and
      (at start(robottool ?r ?t))
      (at start(objectat ?o ?l))
      (at start(robotat ?r ?l))
      (at start(toolfree ?t))
    )
:effect 
  (and 
    (at end(robotcarrying ?r ?t ?o))
    (at start(not (objectat ?o ?l)))
    (at start(not (toolfree ?t)))
  )
)
```

### Drop

Drop was also unchanged from the previous PDDL domain.

```
(:durative-action drop
:parameters (?o - object ?l - location ?r - robot ?t - tool)
:duration (= ?duration 5)
:condition 
  (and 
    (at start(robottool ?r ?t))
    (at start(robotat ?r ?l))
    (at start(robotcarrying ?r ?t ?o))
  )
:effect 
  (and 
    (at end(objectat ?o ?l))
    (at end(toolfree ?t))
    (at start(not (robotcarrying ?r ?t ?o)))
  )
)
```

## Mapping the hospital

The scenario requested on this assignment was the AWS Hospital. In order to execute problems that require navigation, mapping the place was a must. This was done with the same process we did in assignments before like the kobuki navigation. The resulting map was the following:

![image](https://user-images.githubusercontent.com/78983070/165061908-1ac7f1c9-7b10-4aff-bbcd-210da035c225.png)

With this map, we could now add navigation tasks in our problem.

## Action Nodes used by the controller

The plansys2 controller needs to know which nodes execute the actions indicated in the PDDL file. We needed to generate different .cpp files 
