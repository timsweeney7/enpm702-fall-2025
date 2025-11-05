/**
 * @file robot_control.cpp
 * @author Tim Sweeney (tsweene1@umd.edu)
 * @brief Implementation of robot control functions 
 * @version 0.1
 * @date 2025-11-3
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "robot_control.hpp"


void apply_filter(std::vector<JointState> &traj,
                  std::function<JointState(const JointState &)> filter)
{
    
    for (auto &s : traj)
    {
        s = filter(s);
    }
}
