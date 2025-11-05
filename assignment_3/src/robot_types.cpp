/**
 * @file robot_types.cpp
 * @author Tim Sweeney (tsweene1@umd.edu)
 * @brief Implementation of printing functions for robot types 
 * @version 0.1
 * @date 2025-11-3
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "robot_types.hpp"
#include <iomanip>


void print_decimated_joint_states(
    const std::vector<JointState>& traj,
    const int& decimator
){
    // loop over 
    for(size_t i{0}; i<traj.size(); i+=decimator){
        std::cout << "[" << i << "] ";
        print_joint_state(traj[i]);
    }
    std::cout << "\n";
}

void print_joint_state(const JointState& js) {
    std::cout << std::fixed << std::setprecision(4)
              << "θ1 = " << js.theta1 << " rad | "
              << "θ2 = " << js.theta2 << " rad | "
              << "dθ1 = " << js.dtheta1 << " rad/s | "
              << "dθ2 = " << js.dtheta2 << " rad/s\n";
}

void print_end_effector_pose(const EndEffectorPose& pose){
    std::cout << std::fixed << std::setprecision(4)
              << "x = " << pose.x << " m | "
              << "y = " << pose.y << " m\n";
}