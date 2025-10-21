/**
 * @file main.cpp
 * @author TODO Add your name
 * @brief TODO Add a description
 * @version 1.0
 * @date 09-30-2025
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "sensor_types.hpp"
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <array>

int main() {
  // Storage for all sensor data across timestamps
  std::vector<TimestampData> sensor_readings;

  // Quality tracking variables
  const std::unordered_map<std::string, int> initial_counts{{"LIDAR", 0},
                                                            {"Camera", 0}};
  // Used for printing sensor statuses                                                          
  const std::unordered_map<bool, std::string> status_str{{true, "GOOD"},
                                                         {false, "POOR"}};                                                          


  // Variables for calculating summary statistics
  double total_lidar_avg_distance{0.0};
  double total_camera_brightness{0.0};
  double average_camera_brightness{0.0};
  double average_imu_rotations{0.0};
  int total_obstacles_detected{0};
  int total_valid_readings{0};
  int lidar_valid_readings{0};
  int camera_valid_readings{0};
  int imu_valid_readings{0};
  int day_mode_count{0};
  int night_mode_count{0};
  int stable_counts{0};
  int unstable_counts{0};


  std::cout << "=== ROBOT MULTI-SENSOR SYSTEM ===\n\n";

  // ----
  //  Generate random data for sensors
  // ----
  

  // instantiate random number generators
  std::random_device rd;
  std::mt19937 gen{rd()};
  // instantiate distributions for each sensor bounded by limits in header file
  std::uniform_real_distribution<> lidar_dis{lidar_min_range, lidar_max_range};
  std::uniform_int_distribution<> cam_dis{rgb_min, rgb_max};
  std::uniform_real_distribution<> imu_dis{imu_min_rotation, imu_max_rotation};

  // preallocate memory for our lidar readings vector
  sensor_readings.reserve(sizeof(TimestampData) * num_timestamps);
  std::cout << "Generating sensor data for 5 timestamps...\n" << std::endl;

  // fill the timestamp sensor readings
  for(int i{0}; i<num_timestamps; i++){
    // lidar
    std::vector<double> vec_distance_readings;
    for(int ii{0}; ii<lidar_readings_count; ii++){
      vec_distance_readings.push_back(lidar_dis(gen));
    }
    // camera
    std::tuple<int, int, int> tup_cam_readings{
      cam_dis(gen),
      cam_dis(gen),
      cam_dis(gen)
    };
    // IMU
    std::tuple<double, double, double> tup_imu_readings{
      imu_dis(gen),
      imu_dis(gen),
      imu_dis(gen),
    };
    // struct TimestampData
    TimestampData timestamp_data{
      vec_distance_readings,
      tup_cam_readings,
      tup_imu_readings,
      i
    };
    // Add TimestampData to the end of the sensor_readings vector
    sensor_readings.push_back(timestamp_data);
  }
  

  // ----
  //  Process time stamped sensor data
  // ----

  for (const auto& data : sensor_readings) {

    // Calculate the average lidar distance for this iteration's TimestampData
    double lidar_avg_distance{ 
      std::accumulate( 
        data.lidar_readings.begin(),
        data.lidar_readings.end(),
        0.0f
       ) / data.lidar_readings.size()
    };
    
    // Add avg for timestamp to running total of averages.
    // Will be divided after loop completes
    total_lidar_avg_distance += lidar_avg_distance;
    bool lidar_status{true};
    int obstacles_detected{0};

    // check each lidar reading per Timestamp
    for(double obstacle_dist : data.lidar_readings){
      // if below obstacle threshold, increment obstacles detected count
      if(obstacle_dist < obstacle_threshold){
        obstacles_detected++;
      }
      // if below the minimum value, set status to poor
      if(obstacle_dist <= lidar_min_valid){
        lidar_status = false;
      }
    }
    // if status is good, increment tracking stats
    if(lidar_status){
      total_valid_readings++;
      lidar_valid_readings++;
    }

    total_obstacles_detected += obstacles_detected;


    const auto [r, g, b] {data.camera_readings};
    bool camera_status{true};
    // use a string for tracking camera mode
    std::string camera_mode_str{"NIGHT"};
    total_camera_brightness = (r+g+b) / 3.0;
    // add camera brightness to running count.  Will be averaged after loop
    average_camera_brightness += total_camera_brightness;
    // determine camera mode.  Update tracking stats
    if (total_camera_brightness > day_night_threshold){
      camera_mode_str = "DAY";
      day_mode_count++;
    } 
    else{
      night_mode_count++;
    }
    // determine if data is valid
    if (total_camera_brightness < brightness_threshold){
      camera_status = false;
    }
    if(camera_status){
      total_valid_readings++;
      camera_valid_readings++;
    }

    const auto [roll, pitch, yaw] = data.imu_readings;
    // use string for tracking imu mode
    std::string imu_mode_str{"STABLE"};
    // calculate RSS of angles
    double total_rotation_mag {sqrt( pow(roll, 2.0) + pow(pitch, 2.0) + pow(yaw, 2.0) )};
    // Add to running total. Will be averaged after loop
    average_imu_rotations += total_rotation_mag;
    // if any angle is outside threshold set mode to unstable. increment tracking variables
    if(
      abs(roll) > imu_stability_threshold or 
      abs(pitch) > imu_stability_threshold or
      abs(yaw) > imu_stability_threshold
    ){
      imu_mode_str = "UNSTABLE";
      unstable_counts++;
    }
    else{
      stable_counts++;
    }
    total_valid_readings++; //IMU data is always valid
    imu_valid_readings++;

    // set printing float precision to 2
    std::cout << std::fixed << std::setprecision(2);
    // print out LIDAR statistics for this timestamp
    std::cout << "Processing Timestamp: " << data.timestamp << std::endl;
    std::cout << " - LIDAR [";
    for (auto lidar_reading : data.lidar_readings){
      std::cout << lidar_reading << " ";
    }
    std::cout << "]" << std::endl;
    std::cout << "    Avg: " << lidar_avg_distance <<"m, Obstacles: " 
      << obstacles_detected << ", Status: " << status_str.at(lidar_status) << std::endl;
    
    // print out CAMERA statistics for this timestamp
    std::cout << " - Camera (" << r << " " << g << " " << b << ")\n";
    std::cout << "    Brightness: " << total_camera_brightness <<", Mode: " 
      << camera_mode_str << ", Status: " << status_str.at(camera_status) << std::endl;

    // print out IMU statistics for this timestamp
    std::cout << " - IMU ("  << roll << ", " << pitch << ", " << yaw << ")" << std::endl;
    std::cout << std::fixed << std::setprecision(1) 
      << "    Total rotation: " << total_rotation_mag <<" deg, Mode: " << imu_mode_str
      << ", Status: " << status_str.at(true) << std::endl;    

    std::cout << "\n";
  }

  // ----
  //  Calculate summary data for all timestamped data
  // ----

  total_lidar_avg_distance /= num_timestamps;
  average_camera_brightness /= num_timestamps;
  average_imu_rotations /= num_timestamps;
  double valid_percent{(double)total_valid_readings / ((double)num_timestamps * 3) * 100};
  double lidar_valid_percent{(double)lidar_valid_readings / ((double)num_timestamps) * 100};
  double camera_valid_percent{(double)camera_valid_readings / ((double)num_timestamps) * 100};
  double imu_valid_percent{(double)imu_valid_readings / ((double)num_timestamps) * 100};

  std::cout << "=== SUMMARY STATISTICS ===\n";

  std::cout << "Total Readings Processed: " << num_timestamps * 3 << std::endl;
  std::cout << std::fixed << std::setprecision(1) 
    << "Valid readings: " << total_valid_readings << "(" << valid_percent << "%)\n" << std::endl;
  

  std::cout << "Sensor Reliability Report:" << "\n";

  std::cout << std::fixed << std::setprecision(1)
    << " - LIDAR: " << lidar_valid_readings << "/" << num_timestamps << "(" << lidar_valid_percent << "%)" << std::endl;
  std::cout << std::fixed << std::setprecision(1)
    << " - Camera: " << camera_valid_readings << "/" << num_timestamps << "(" << camera_valid_percent << "%)" << std::endl;
  std::cout << std::fixed << std::setprecision(1)
    << " - IMU: " << imu_valid_readings << "/" << num_timestamps << "(" << imu_valid_percent << "%)" << std::endl;

  std::cout << "Operational Statistics: " << std::endl;
  std::cout << std::fixed << std::setprecision(2) << "  - Average LIDAR Distance: " << total_lidar_avg_distance << "m" << std::endl;
  std::cout << "    - Total Obstacles Detected: " << total_obstacles_detected << std::endl;
  std::cout << std::fixed << std::setprecision(2) << "  - Average Camera Brightness: " << average_camera_brightness << std::endl;
  std::cout << "    - Day Mode Detections: " << day_mode_count << std::endl;
  std::cout << "    - Night Mode Detections: " << night_mode_count << std::endl;
  std::cout << std::fixed << std::setprecision(2) << "  - Average IMU Total Rotation: " << average_imu_rotations << " deg" << std::endl;
  std::cout << "    - Stable Detections: " << stable_counts << std::endl;
  std::cout << "    - Unsatable Detections: " << unstable_counts << std:: endl;

}