#include <chrono>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32.hpp"

using namespace std::chrono_literals;

class RadarNode : public rclcpp::Node {
public:
  RadarNode() : Node("radar_node"), current_distance_(10.0f) {
    publisher_ = this->create_publisher<std_msgs::msg::Float32>("/distance", 10);
    timer_ = this->create_wall_timer(
      500ms, std::bind(&RadarNode::timer_callback, this));
    RCLCPP_INFO(this->get_logger(), "Radar node elindult. Tavolsag szimulacio indul");
  }

private:
  void timer_callback() {
    auto message = std_msgs::msg::Float32();
    message.data = current_distance_;
    publisher_->publish(message);

    RCLCPP_INFO(this->get_logger(), "Mert tavolsag: %.2f m", message.data);

    current_distance_ -= 0.8f;
    if (current_distance_ <= 0.0f) {
      current_distance_ = 10.0f; 
      RCLCPP_INFO(this->get_logger(), "--- Akadaly elkerulve / uj ciklus indul ---");
    }
  }

  rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
  float current_distance_;
};

int main(int argc, char * argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<RadarNode>());
  rclcpp::shutdown();
  return 0;
}