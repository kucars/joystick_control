    #include <ros/ros.h>
    #include <geometry_msgs/Twist.h>
    #include <sensor_msgs/Joy.h>


     class Teleopseekur
     {
     public:
     Teleopseekur();

     private:
     void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);

     ros::NodeHandle nh_;

     int linear_, angular_;
     double l_scale_, a_scale_;

     ros::Publisher cmd_vel_pub_;
     ros::Subscriber joy_sub_;

   };


   Teleopseekur::Teleopseekur():
     linear_(1),
     angular_(2)
   {

     nh_.param("axis_linear", linear_, linear_);
     nh_.param("axis_angular", angular_, angular_);
     nh_.param("scale_angular", a_scale_, a_scale_);
     nh_.param("scale_linear", l_scale_, l_scale_);


     cmd_vel_pub_ = nh_.advertise<geometry_msgs::Twist>("RosAria/cmd_vel", 1);


     joy_sub_ = nh_.subscribe<sensor_msgs::Joy>("joy", 10, &Teleopseekur::joyCallback, this);

   }

   void Teleopseekur::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
   {
     geometry_msgs::Twist cmd_vel;
     cmd_vel.angular.z = a_scale_*joy->axes[angular_];
     cmd_vel.linear.x = l_scale_*joy->axes[linear_];
     cmd_vel_pub_.publish(cmd_vel);
   }


   int main(int argc, char** argv)
   {
     ros::init(argc, argv, "teleop_seekur");
     Teleopseekur teleop_seekur;

     ros::spin();
  }
