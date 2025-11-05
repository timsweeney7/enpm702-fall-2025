/**
 * @file main.cpp
 * @author Tim Sweeney (tsweene1@umd.edu)
 * @brief UMD Fall 2025 ENPM702 - Assignment 3 - Robot Kinematics and Control
 * @version 0.1
 * @date 2025-11-3
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "robot_types.hpp"
#include "robot_kinematics.hpp"
#include "robot_control.hpp"

#include <iostream>
#include <memory>
#include <vector>
#include <cmath>

int main() {
    std::cout << "=== Robot Kinematics & Control ===\n\n";

    // Define the start and goal positions
    const JointState start{0 , 0.0};               // radians, radians 
    const JointState goal{-M_PI , -M_PI / 6.0};    // radians, radians
    
    // print objective to terminal
    std::cout << "Start state: " << "\n";
    print_joint_state(start);
    std::cout << "Goal state: " << "\n";
    print_joint_state(goal);
    std::cout << '\n';

    // Create a container for storing joint states through trajetory
    auto traj = std::make_unique<std::vector<JointState>>();
    traj->reserve(k_num_samples);  // reserve necessary memory


    // Generate trajectory samples into *traj using interpolate_linear(...)
    for (int i{0}; i < k_num_samples; ++i) {
        const double alpha{static_cast<double>(i) * k_alpha_step};
        traj->push_back(interpolate_linear(start, goal, alpha));
    }
    std::cout << "Trajectory points: " << traj->size() << "\n";

    // Print sample of points
    std::cout <<"Before rate filter\n";
    print_decimated_joint_states(*traj, 5);

    
    // get a function pointer to the sign function to pass to the lambda function
    double (*fp_sign)(const double&) = sign<double>; 
    // Define a lambda function to clamp angular velocity to the maximuam value
    auto filter = [fp_sign](const JointState& js)->JointState{
        JointState out{};
        out.theta1 = js.theta1;
        out.theta2 = js.theta2;
        out.dtheta1 = sign(js.dtheta1) * std::min(std::abs(js.dtheta1), std::abs(k_vel_limit));
        out.dtheta2 = sign(js.dtheta2) * std::min(std::abs(js.dtheta2), std::abs(k_vel_limit));
        return out;
    };

    // Apply the filter across the saved states, print a sample
    apply_filter(*traj, filter); 
    std::cout << "After rate filter \n";
    print_decimated_joint_states(*traj, 5);

    // Define a container for end effector positions
    auto ee_poses = std::make_unique<std::vector<EndEffectorPose>>();
    // set the size to the same size to the same size as the trajectory container
    ee_poses->reserve(traj->size()); 

    // Compute the FK for each state in joint states
    for (JointState joint_state: *traj){
        ee_poses->push_back(forward_kinematics(joint_state));
    }

    // print all the joint states and end effector positions
    std::cout << "End-Effector Trajectory (all points)\n";
    for (size_t i{0}; i<ee_poses->size(); ++i){
        std::cout << "[" << i << "]  ";
        print_end_effector_pose((*ee_poses)[i]);
    }

}
