/**
 * @file robot_types.hpp
 * @author Tim Sweeney (tsweene1@umd.edu)
 * @brief Provides generic types useful to robot kinematics
 * @version 0.1
 * @date 2025-11-3
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#pragma once
#include <iostream>
#include <vector>


/**
 * @brief Determines the sign of a number
 * 
 * @tparam T Class type. Any number type
 * @param x Input
 * @return T Sign of input number. Return type T
 */
template <typename T>
T sign(const T& x){
    if(x < 0){
        return T{-1};
    }
    else{
        return T{1};
    }
}


/**
 * @brief Class for tracking the state of the robot arm
 * 
 */
struct JointState {
    double theta1;        // Joint 1 angle [rad]
    double theta2;        // Joint 2 angle [rad]
    // Default member initializers for velocities (Task 1 requirement)
    double dtheta1 = 0.0; // Joint 1 velocity [rad/s]
    double dtheta2 = 0.0; // Joint 2 velocity [rad/s]
};

/**
 * @brief Class for tracking the position of the end effector in world space 
 */
struct EndEffectorPose {
    double x; // [m]
    double y; // [m]
};

/**
 * @brief Prints the joint state with theta1, theta2, d_theta1, d_theta2
 * values displayed
 * 
 * @param js joint state object
 */
void print_joint_state(const JointState& js);

/**
 * @brief Prints all the joint states in a vector of joint states
 * 
 * @param traj Vector of joint states across a trajectory
 * @param decimator Optional parameter for decimating print outputs
 */
void print_decimated_joint_states(
    const std::vector<JointState>& traj,
    const int& decimator = 1
);

/**
 * @brief Prints the end effector position in the world frame
 * 
 * @param pose End effector position object
 */
void print_end_effector_pose(const EndEffectorPose& pose);



inline constexpr double k_link1{0.5};      // [m]
inline constexpr double k_link2{0.3};      // [m]
inline constexpr double k_vel_limit{1.0};   // [rad/s]
inline constexpr int    k_num_samples{21};  // includes endpoints
inline constexpr double k_alpha_step{1.0 / (k_num_samples - 1)};
