/**
 * @file robot_kinematics.hpp
 * @author Tim Sweeney (tsweene1@umd.edu)
 * @brief Functions for calculating the robot kinematics
 * @version 0.1
 * @date 2025-10-25
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#pragma once
#include "robot_types.hpp"
#include <cmath>


/**
 * @brief Calculates the position of the end effector in the operating 
 * space
 * 
 * @tparam Class or struct for state of robot arm
 * Must have members theta1, theta2,  
 * @param s Class or struct representing the state of the robot arm
 * @param L1 Length of arm link 1
 * @param L2 Length of arm link 2
 * @return EndEffectorPose struct with end effector x,y position
 */
template <typename State>
EndEffectorPose forward_kinematics(const State& s,
                                   double L1 = k_link1,
                                   double L2 = k_link2)
{
    // Implement the FK equations:
    double x{ L1*cos(s.theta1) + L2*cos(s.theta1 + s.theta2) };
    double y{ L1*sin(s.theta1) + L2*sin(s.theta1 + s.theta2) };

    EndEffectorPose pose{x, y};

    return pose;
}
