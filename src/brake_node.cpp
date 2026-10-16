#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32.hpp"
#include "std_msgs/msg/bool.hpp"

class BrakeNode : public rclcpp::Node {
public:
  BrakeNode() : Node("brake_node") {
    subscription_ = this->create_subscription<std_msgs::msg::Float32>(
      "/distance", 10,
      std::bind(&BrakeNode::distance_callback, this, std::placeholders::_1));

    brake_pub_ = this->create_publisher<std_msgs::msg::Bool>("/emergency_brake", 10);

    RCLCPP_INFO(this->get_logger(), "Brake monitor node aktiv, figyeli a tavolsagot.");
  }

private:
  void distance_callback(const std_msgs::msg::Float32::SharedPtr msg) {
    auto brake_msg = std_msgs::msg::Bool();

    if (msg->data < 2.0f) {
      brake_msg.data = true;
      RCLCPP_WARN(this->get_logger(), 
                  "[VESZHELYZET] Tavolsag: %.2f m -> VESZFEK AKTIVALVA!", msg->data);
    } else {
      brake_msg.data = false;
      RCLCPP_INFO(this->get_logger(), "Tavolsag biztonsagos: %.2f m", msg->data);
    }

    brake_pub_->publish(brake_msg);
  }

  rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr subscription_;
  rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr brake_pub_;
};

int main(int argc, char * argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<BrakeNode>());
  rclcpp::shutdown();
  return 0;
}