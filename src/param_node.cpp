#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"

using namespace std::chrono_literals;


class ParamNode : public rclcpp::Node
{
public:
    ParamNode()
        : Node("param_node")
    {
        this->declare_parameter("robot_name", "ROS2Bot");
        this->declare_parameter("max_speed", 1.5);
        this->declare_parameter("enabled", true);

        timer_ = this->create_wall_timer(
            2000ms, 
            std::bind(&ParamNode::timer_callback, this));
    }

private:
    void timer_callback()
    {
        std::string robot_name;
        double max_speed;
        bool enabled;

        this->get_parameter("robot_name", robot_name);
        this->get_parameter("max_speed", max_speed);
        this->get_parameter("enabled", enabled);
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
