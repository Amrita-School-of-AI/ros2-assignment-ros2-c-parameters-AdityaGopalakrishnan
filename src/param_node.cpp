#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"

using namespace std::chrono_literals;

/*
 * ALL: Create a Class named 'ParamNode' that inherits from rclcpp::Node.
 * Requirements:
 * 1. The constructor should name the node "param_node".
 * 2. Declare these parameters with default values:
 * - "robot_name" (string): default "ROS2Bot"
 * - "max_speed" (double): default 1.5
 * - "enabled" (bool): default true
 * 3. Create a timer that triggers every 2000ms.
 * 4. In timer callback, read parameters and log:
 * "Robot: <name>, Max Speed: <speed>, Enabled: <enabled>"
 */

class ParamNode : public rclcpp::Node
{
public:
    ParamNode()
        : Node("param_node")
    {
        // ALL: Declare parameters here
        // We declare parameters so they can be set via command line or launch files.
        // If not set externally, they fallback to these values.
        this->declare_parameter("robot_name", "ROS2Bot");
        this->declare_parameter("max_speed", 1.5);
        this->declare_parameter("enabled", true);

        // ALL: Create timer here
        // The timer triggers the 'timer_callback' function every 2000ms.
        timer_ = this->create_wall_timer(
            2000ms, 
            std::bind(&ParamNode::timer_callback, this));
    }

private:
    // ALL: Define timer_callback function here
    void timer_callback()
    {
        // Variables to store the current values
        std::string robot_name;
        double max_speed;
        bool enabled;

        // Fetch the CURRENT value of the parameters.
        // We do this inside the loop so that if you change a parameter
        // at runtime (e.g., via CLI), the log updates immediately.
        this->get_parameter("robot_name", robot_name);
        this->get_parameter("max_speed", max_speed);
        this->get_parameter("enabled", enabled);

        // Log the output
        // Note: We use a ternary operator (condition ? "true" : "false") 
        // to print the boolean as text instead of 1 or 0.
        RCLCPP_INFO(this->get_logger(), 
            "Robot: %s, Max Speed: %.2f, Enabled: %s",
            robot_name.c_str(),
            max_speed,
            enabled ? "true" : "false");
    }

    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ParamNode>());
    rclcpp::shutdown();
    return 0;
}
