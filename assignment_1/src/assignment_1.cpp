#include <iostream>
#include <limits>
#include <cmath>


int main(){
    double robot_x_position{0.0};
    double robot_y_position{0.0};
    double robot_orientation_deg{0.0};
    constexpr float PI{3.14159};

    int user_input;

    std::cout << "Assignment 1 - Robot state control\n\n";


    while(true){
        std::cout << "1. Move Forward\n"; 
        std::cout << "2. Turn Left\n"; 
        std::cout << "3. Turn Right\n"; 
        std::cout << "4. Get Robot Status\n";
        std::cout << "5. Exit\n";

        std::cout << "Choose an option 1-5: ";
        std::cin >> user_input;
        
        // Check for non-integer characters
        if(std::cin.fail()) {
            std::cout << "Invalid input: Enter a number 1-5\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cout << "\n";
        }
        else if(user_input < 1 || user_input > 5){
            std::cout << "Invalid input: Enter a number 1-5\n\n";
        }
        
        

        double robot_orientation_rad = robot_orientation_deg * (PI / 180.0);
        double angle;

        switch(user_input){
            case 1:  // drive forward
                std::cout << "Enter distance to move forward: ";
                double dist;
                std::cin >> dist;
                if(std::cin.fail()) {
                    std::cout << "Invalid input: Enter a positive number.\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                    std::cout << "\n";
                }
                else if(dist < 0 ){
                    std::cout << "Invalid input: Enter a positive number.\n\n";
                }
                else{
                    robot_x_position += dist * std::cos(robot_orientation_rad);
                    robot_y_position += dist * std::sin(robot_orientation_rad);
                    std::cout << "Robot position:  X: " << robot_x_position << "   Y: " << robot_y_position << "\n\n";
                }
                break;

            case 2: // turn left
                std::cout << "Enter angle (degrees) to turn left: ";
                std::cin >> angle;
                if(std::cin.fail()) {
                    std::cout << "Invalid input: Enter a positive number.\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                    std::cout << "\n";
                }
                else if(angle < 0 ){
                    std::cout << "Invalid input: Enter a positive number.\n\n";
                }
                else{
                    robot_orientation_deg += angle; 
                    robot_orientation_deg = fmod(robot_orientation_deg, 360.0);
                    std::cout << "New orientation: " << robot_orientation_deg  << "\n\n";
                }
                break;

            case 3: // turn right
                std::cout << "Enter angle (degrees) to turn right: ";
                std::cin >> angle;
                if(std::cin.fail()) {
                    std::cout << "Invalid input: Enter a positive number.\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                    std::cout << "\n";
                }
                else if(angle < 0 ){
                    std::cout << "Invalid input: Enter a positive number.\n\n";
                }
                else{
                    robot_orientation_deg -= angle; 
                    while(robot_orientation_deg < 0){
                        robot_orientation_deg += 360;
                    }
                    robot_orientation_deg = fmod(robot_orientation_deg, 360.0);
                    std::cout << "New orientation: " << robot_orientation_deg << "\n\n";
                }
                break;

            case 4: // get robot status
                std::cout << "Robot position:  X: " << robot_x_position << "   Y: " << robot_y_position << "   Angle: " << robot_orientation_deg << "\n\n";
                break;
            case 5:
                std::cout << "Program complete\n\n";
                return 0;
        }

    }
}