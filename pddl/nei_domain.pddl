(define (domain nei)
(:requirements :strips :typing :negative-preconditions :adl :fluents :durative-actions)
(:types
  room corridor zone - location
  door elevator - connector
  robot object tool - item
)
(:predicates 
  (robotAt ?r - robot ?l - location)
  (zoneAt ?z ?l - location)

  (objectAt ?o - object ?l - location)
  (robotTool ?r - robot ?t - tool)
  (toolFree ?t - tool)
  (robotCarrying ?r - robot ?t - tool ?o - object)

)

(:durative-action move_location
    :parameters (?robot - robot ?prev_room - location ?next_room - location)
    :duration (= ?duration 5)
    :condition 
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


(:action enter_zone
    :parameters ( ?r - robot ?z ?l - location)
    :duration (= ?duration 3)
    :condition (and
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
    :duration (= ?duration 3)
    :condition (and
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
  :duration (= ?duration 3)
  :condition 
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
:duration (= ?duration 3)
:condition 
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



)
