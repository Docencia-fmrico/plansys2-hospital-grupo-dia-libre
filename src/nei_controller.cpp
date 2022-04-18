// Copyright 2019 Intelligent Robotics Lab
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <plansys2_pddl_parser/Utils.h>

#include <memory>

#include "plansys2_msgs/msg/action_execution_info.hpp"
#include "plansys2_msgs/msg/plan.hpp"

#include "plansys2_domain_expert/DomainExpertClient.hpp"
#include "plansys2_executor/ExecutorClient.hpp"
#include "plansys2_planner/PlannerClient.hpp"
#include "plansys2_problem_expert/ProblemExpertClient.hpp"

#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"

class Nei : public rclcpp::Node
{
public:
  Nei()
  : rclcpp::Node("nei_controller")
  {
  }

  bool init()
  {
    domain_expert_ = std::make_shared<plansys2::DomainExpertClient>();
    planner_client_ = std::make_shared<plansys2::PlannerClient>();
    problem_expert_ = std::make_shared<plansys2::ProblemExpertClient>();
    executor_client_ = std::make_shared<plansys2::ExecutorClient>();

    init_knowledge();

    auto domain = domain_expert_->getDomain();
    auto problem = problem_expert_->getProblem();
    auto plan = planner_client_->getPlan(domain, problem);

    if (!plan.has_value()) {
      std::cout << "Could not find plan to reach goal " <<
        parser::pddl::toString(problem_expert_->getGoal()) << std::endl;
      return false;
    }

    if (!executor_client_->start_plan_execution(plan.value())) {
      RCLCPP_ERROR(get_logger(), "Error starting a new plan (first)");
    }

    return true;
  }

  void init_knowledge()
  {
    problem_expert_->addInstance(plansys2::Instance{"r2d2", "robot"});

    problem_expert_->addInstance(plansys2::Instance{"corridor1", "corridor"});
    problem_expert_->addInstance(plansys2::Instance{"corridor2", "corridor"});
    problem_expert_->addInstance(plansys2::Instance{"corridor3", "corridor"});

    problem_expert_->addInstance(plansys2::Instance{"room1", "room"});
    problem_expert_->addInstance(plansys2::Instance{"room2", "room"});
    problem_expert_->addInstance(plansys2::Instance{"room3", "room"});
    problem_expert_->addInstance(plansys2::Instance{"room4", "room"});
    problem_expert_->addInstance(plansys2::Instance{"room5", "room"});
    problem_expert_->addInstance(plansys2::Instance{"room6", "room"});
    problem_expert_->addInstance(plansys2::Instance{"room7", "room"});
    problem_expert_->addInstance(plansys2::Instance{"room8", "room"});
    problem_expert_->addInstance(plansys2::Instance{"room9", "room"});

    problem_expert_->addInstance(plansys2::Instance{"zone1", "zone"});
    problem_expert_->addInstance(plansys2::Instance{"zone2", "zone"});
    problem_expert_->addInstance(plansys2::Instance{"zone3", "zone"});
    problem_expert_->addInstance(plansys2::Instance{"zone4", "zone"});
    problem_expert_->addInstance(plansys2::Instance{"zone5", "zone"});

    problem_expert_->addInstance(plansys2::Instance{"elevator1", "elevator"});

    problem_expert_->addInstance(plansys2::Instance{"door1", "door"});
    problem_expert_->addInstance(plansys2::Instance{"door2", "door"});
    problem_expert_->addInstance(plansys2::Instance{"door3", "door"});
    problem_expert_->addInstance(plansys2::Instance{"door4", "door"});
    problem_expert_->addInstance(plansys2::Instance{"door5", "door"});
    problem_expert_->addInstance(plansys2::Instance{"door6", "door"});
    problem_expert_->addInstance(plansys2::Instance{"door7", "door"});

    problem_expert_->addInstance(plansys2::Instance{"ball", "object"});
    problem_expert_->addInstance(plansys2::Instance{"toy", "object"});

    problem_expert_->addInstance(plansys2::Instance{"gripper", "tool"});

    problem_expert_->addPredicate(plansys2::Predicate("(robotAt r2d2 room9)"));

    problem_expert_->addPredicate(plansys2::Predicate("(elevatorAt elevator1 corridor1)"));
    problem_expert_->addPredicate(plansys2::Predicate("(elevatorAt elevator1 corridor2)"));

    problem_expert_->addPredicate(plansys2::Predicate("(elevatorConnects elevator1 corridor1 corridor2)"));
    problem_expert_->addPredicate(plansys2::Predicate("(elevatorConnects elevator1 corridor2 corridor1)"));

    problem_expert_->addPredicate(plansys2::Predicate("(doorExists door1 room1 corridor1)"));
    problem_expert_->addPredicate(plansys2::Predicate("(doorExists door1 corridor1 room1)"));

    problem_expert_->addPredicate(plansys2::Predicate("(doorClosed door1)"));
    problem_expert_->addPredicate(plansys2::Predicate("(zoneAt zone1 room1)"));
    problem_expert_->addPredicate(plansys2::Predicate("(zoneAt zone2 room1)"));

    problem_expert_->addPredicate(plansys2::Predicate("(doorExists door2 room3 room1)"));
    problem_expert_->addPredicate(plansys2::Predicate("(doorExists door2 room1 room3)"));
    problem_expert_->addPredicate(plansys2::Predicate("(doorClosed door2)"));

    problem_expert_->addPredicate(plansys2::Predicate("(areConnected corridor1 room2)"));
    problem_expert_->addPredicate(plansys2::Predicate("(areConnected room2 corridor1)"));

    problem_expert_->addPredicate(plansys2::Predicate("(areConnected room2 room4)"));
    problem_expert_->addPredicate(plansys2::Predicate("(areConnected room4 room2)"));

    problem_expert_->addPredicate(plansys2::Predicate("(doorExists door3 corridor2 room6)"));
    problem_expert_->addPredicate(plansys2::Predicate("(doorExists door3 room6 corridor2)"));
    problem_expert_->addPredicate(plansys2::Predicate("(doorClosed door3)"));

    problem_expert_->addPredicate(plansys2::Predicate("(doorExists door5 corridor3 room7)"));
    problem_expert_->addPredicate(plansys2::Predicate("(doorExists door5 room7 corridor3)"));
    problem_expert_->addPredicate(plansys2::Predicate("(doorClosed door5)"));

    problem_expert_->addPredicate(plansys2::Predicate("(doorExists door7 room8 corridor3)"));
    problem_expert_->addPredicate(plansys2::Predicate("(doorExists door2 corridor3 room8)"));
    problem_expert_->addPredicate(plansys2::Predicate("(doorClosed door7)"));

    problem_expert_->addPredicate(plansys2::Predicate("(doorExists door6 room9 corridor3)"));
    problem_expert_->addPredicate(plansys2::Predicate("(doorExists door2 corridor3 room9)"));
    problem_expert_->addPredicate(plansys2::Predicate("(doorClosed door6)"));

    problem_expert_->addPredicate(plansys2::Predicate("(areConnected corridor2 corridor3)"));
    problem_expert_->addPredicate(plansys2::Predicate("(areConnected corridor3 corridor2)"));

    problem_expert_->addPredicate(plansys2::Predicate("(doorExists door4 corridor2 room5)"));
    problem_expert_->addPredicate(plansys2::Predicate("(doorClosed door4)"));

    problem_expert_->addPredicate(plansys2::Predicate("(objectAt ball room2)"));
    problem_expert_->addPredicate(plansys2::Predicate("(objectAt toy room2)"));

    problem_expert_->addPredicate(plansys2::Predicate("(robotTool r2d2 gripper)"));
    problem_expert_->addPredicate(plansys2::Predicate("(toolFree gripper)"));

    
    problem_expert_->setGoal(
      plansys2::Goal("(and (robotAt r2d2 room7) (objectAt toy room9) (objectAt ball corridor3))"));
  }

  void step()
  {
    if (!executor_client_->execute_and_check_plan()) {  // Plan finished
      auto result = executor_client_->getResult();

      if (result.value().success) {
        RCLCPP_INFO(get_logger(), "Plan succesfully finished");
      } else {
        RCLCPP_ERROR(get_logger(), "Plan finished with error");
      }
    }
  }

private:
  std::shared_ptr<plansys2::DomainExpertClient> domain_expert_;
  std::shared_ptr<plansys2::PlannerClient> planner_client_;
  std::shared_ptr<plansys2::ProblemExpertClient> problem_expert_;
  std::shared_ptr<plansys2::ExecutorClient> executor_client_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<Nei>();

  if (!node->init()) {
    return 0;
  }

  rclcpp::Rate rate(5);
  while (rclcpp::ok()) {
    node->step();

    rate.sleep();
    rclcpp::spin_some(node->get_node_base_interface());
  }

  rclcpp::shutdown();

  return 0;
}
