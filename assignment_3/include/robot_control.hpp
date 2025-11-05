/**
 * @file robot_control.hpp
 * @author Tim Sweeney (tsweene1@umd.edu)
 * @brief Functions for trajectory planning
 * @version 0.1
 * @date 2025-11-3
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#pragma once
#include "robot_types.hpp"
#include <vector>
#include <functional>


/**
 * @brief Linearly interpolates the state of the robot arm between start
 * and goal positions.  
 * 
 * @tparam State - The class representing the robot arm position
 * Must have members theta1, theta2, d_theta1, d_theta2
 * @param start - Starting state of the robot arm
 * @param goal - Desired end state of the robot arm
 * @param alpha - Value between [0,1]. Used to calculate how far along 
 * trajectory robot arm is. 0 being start, 1 being goal
 * @return State - The linearly interpolated state
 */
template <typename State>
State interpolate_linear(const State& start, const State& goal, double alpha)
{
    // clamp alpha to [0, 1] just in case
    if (alpha < 0.0) alpha = 0.0;
    if (alpha > 1.0) alpha = 1.0;

    State out{};

    // calculate delta theta
    double d_theta1{goal.theta1 - start.theta1};
    double d_theta2{goal.theta2 - start.theta2};
    
    // calculate the joint angle based on alpha
    out.theta1 = start.theta1 + alpha * d_theta1;
    out.theta2 = start.theta2 + alpha * d_theta2;

    // Set the angular velocity to the angle that needs to be covered
    // This will be filtered to max angular velocity in a later step
    out.dtheta1 = d_theta1;
    out.dtheta2 = d_theta2; 
    return out;
}


/**
 * @brief Applies a filter to a series of robot states 
 * 
 * @param traj - The trajectory the robot arm follows
 * @param filter - The filter to apply to the trajectories
 */
void apply_filter(std::vector<JointState>& traj,
                  std::function<JointState(const JointState&)> filter);
