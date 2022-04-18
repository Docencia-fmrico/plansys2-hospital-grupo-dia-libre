(define (domain nei)
(:requirements :strips :typing :negative-preconditions)
(:types
  room corridor zone - location
  door elevator - connector
  robot object tool - item
)
(:predicates 
  (robotAt ?r - robot ?l - location)
  (doorExists ?d - door ?l1 ?l2 - location)
  (doorClosed ?d - door)
  (doorOpen ?d - door)
  (elevatorAt ?e - elevator ?c - corridor)
  (elevatorConnects ?e - elevator ?c1 ?c2 - corridor)
  (areConnected ?l1 ?l2 - location)
  (zoneAt ?z ?l - location)

  (objectAt ?o - object ?l - location)
  (robotTool ?r - robot ?t - tool)
  (toolFree ?t - tool)
  (robotCarrying ?r - robot ?t - tool ?o - object)

)

(:action move_location
    :parameters (?robot - robot ?prev_room - location ?next_room - location)
    :precondition 
      (and
        (robotAt ?robot ?prev_room)
        (areConnected ?prev_room ?next_room)
      )
    :effect 
      (and  
        (robotAt ?robot ?next_room)
        (not (robotAt ?robot ?prev_room))
      )
)
(:action open_door
    :parameters ( ?r - robot ?d - door ?lat ?lout - location)
    :precondition (and
      (doorExists ?d ?lat ?lout)
      (robotAt ?r ?lat)
      (doorClosed ?d)
     )
    :effect (and
      (doorOpen ?d)
      (not (doorClosed ?d))
      (areConnected ?lat ?lout)
      (areConnected ?lout ?lat)
     )
)

(:action close_door
    :parameters ( ?d - door ?r - robot ?lat ?lout - location)
    :precondition (and
      (doorExists ?d ?lat ?lout)
      (robotAt ?r ?lat)
      (doorOpen ?d)
     )
    :effect (and
      (doorClosed ?d)
      (not (doorOpen ?d))
      (not (areConnected ?lat ?lout))
      (not (areConnected ?lout ?lat))
     )
)

(:action enter_zone
    :parameters ( ?r - robot ?z ?l - location)
    :precondition (and
      (zoneAt ?z ?l)
      (robotAt ?r ?l)
     )
    :effect (and
      (not (robotAt ?r ?l))
      (robotAt ?r ?z)
     )
)

(:action leave_zone
    :parameters ( ?r - robot ?l ?z - location)
    :precondition (and
      (zoneAt ?z ?l)
      ;(not (robotAt ?r ?l))
      (robotAt ?r ?z)
     )
    :effect (and
      (robotAt ?r ?l)
      (not(robotAt ?r ?z))
     )
)

(:action pick
  :parameters (?o - object ?l - location ?r - robot ?t - tool)
  :precondition 
    (and
      (robotTool ?r ?t)
      (objectAt ?o ?l)
      (robotAt ?r ?l)
      (toolFree ?t)
    )
:effect 
  (and 
    (robotCarrying ?r ?t ?o)
    (not (objectAt ?o ?l))
    (not (toolFree ?t))
  )
)

(:action drop
:parameters (?o - object ?l - location ?r - robot ?t - tool)
:precondition 
  (and 
    (robotTool ?r ?t)
    (robotAt ?r ?l)
    (robotCarrying ?r ?t ?o)
  )
:effect 
  (and 
    (objectAt ?o ?l)
    (toolFree ?t)
    (not (robotCarrying ?r ?t ?o))
  )
)

(:action take_elevator
    :parameters (?e - elevator ?r - robot ?sc - corridor ?dc - corridor)
    :precondition (and
      (elevatorAt ?e ?sc)
      (robotAt ?r ?sc)
      (elevatorConnects ?e ?sc ?dc)
      )
    :effect (and 
      (robotAt ?r ?dc)
      (elevatorAt ?e ?dc)
      (not (robotAt ?r ?sc))
      (not (elevatorAt ?e ?sc))
    )
)


)