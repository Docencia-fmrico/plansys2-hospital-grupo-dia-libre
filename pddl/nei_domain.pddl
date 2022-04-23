(define (domain nei)
(:requirements :strips :typing :negative-preconditions :adl :fluents :durative-actions)
(:types
  room - location
  door elevator - connector
  robot object tool - item
)
(:predicates 
  (robotat ?r - robot ?l - location)

  (objectat ?o - object ?l - location)
  (robottool ?r - robot ?t - tool)
  (robotfree ?t - tool)
  (robotcarrying ?r - robot ?t - tool ?o - object)

)

(:durative-action move_location
    :parameters (?robot - robot ?prev_room - location ?next_room - location)
    :duration (= ?duration 5)
    :condition 
      (and
      )
    :effect 
      (and  
        (at end(robotat ?robot ?next_room))
      )
)

(:durative-action pick
  :parameters (?o - object ?l - location ?r - robot ?t - tool)
  :duration (= ?duration 3)
  :condition 
    (and
      (at start(robottool ?r ?t))
      (at start(objectat ?o ?l))
      (at start(robotat ?r ?l))
      (at start(robotfree ?t))
    )
:effect 
  (and 
    (at end(robotcarrying ?r ?t ?o))
    (at start(not (objectat ?o ?l)))
    (at start(not (robotfree ?t)))
  )
)

(:durative-action drop
:parameters (?o - object ?l - location ?r - robot ?t - tool)
:duration (= ?duration 3)
:condition 
  (and 
    (at start(robottool ?r ?t))
    (at start(robotat ?r ?l))
    (at start(robotcarrying ?r ?t ?o))
  )
:effect 
  (and 
    (at end(objectat ?o ?l))
    (at end(robotfree ?t))
    (at start(not (robotcarrying ?r ?t ?o)))
  )
)



)

