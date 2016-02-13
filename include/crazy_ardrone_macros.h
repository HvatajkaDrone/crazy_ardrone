#ifndef INCLUDE_CRAZY_ARDRONE_MACROS_H
#define INCLUDE_CRAZY_ARDRONE_MACROS_H

#include "ros/ros.h"
#include "std_msgs/Empty.h"
#include "geometry_msgs/Twist.h"

#include "ardrone_autonomy/Navdata.h"

// Тупить заданное количество секунд
#define ros_sleep(a) ros::Duration((a)).sleep()

class CrazyARDroneControl {

        ros::NodeHandle n;
        
        ros::Publisher pubControl;
        ros::Publisher pubReset;
        ros::Publisher pubTakeoff;
        ros::Publisher pubLand;
        
        ros::Subscriber subNavdata;

        // enum States {
                // STATE_EMERGENCY = 0,
                // STATE_INITED = 1,
                // STATE_LANDED = 2,
                // STATE_FLYING = 3,
                // STATE_HOVERING = 4,
                // STATE_TEST = 5,
                // STATE_TAKINGOFF = 6,
                // STATE_FLYING2 = 7,
                // STATE_LANDING = 8,
                // STATE_LOOPING = 9
        // };

        static ardrone_autonomy::Navdata _current_state;

        // Callback для чтения данных с коптера. Оставь здесь и не трогай ;)
        static void navDataCallback(const ardrone_autonomy::Navdata::ConstPtr &msg);

public:
        CrazyARDroneControl():
                pubControl(n.advertise<geometry_msgs::Twist>("/cmd_vel", 1000)),
                pubReset(n.advertise<std_msgs::Empty>("/ardrone/reset", 1000)),
                pubTakeoff(n.advertise<std_msgs::Empty>("/ardrone/takeoff", 1000)),
                pubLand(n.advertise<std_msgs::Empty>("/ardrone/land", 1000))
        {
                subNavdata = n.subscribe("/ardrone/navdata", 1000, navDataCallback);
        }

        ~CrazyARDroneControl()
        {}

        // Взлёт
        // Предварительно убедиться, что коптер активен!
        void takeoff()
        {
                ROS_INFO("Taking off");
                pubTakeoff.publish(std_msgs::Empty());
                ros_sleep(5);
        }

        // Посадка
        void land()
        {
                ROS_INFO("Landing");
                pubLand.publish(std_msgs::Empty());
                ros_sleep(5);
        }

        // Активировать коптер
        // После этого могут включаться движки!
        void arm()
        {
                if (!isArmed()) {
                        ROS_INFO("Arming");
                        pubReset.publish(std_msgs::Empty());
                }
        }

        // Деактивировать коптер
        // Движки выключатся как есть
        void disarm()
        {
                if (isArmed()) {
                        ROS_INFO("Disarming");
                        pubReset.publish(std_msgs::Empty());
                }
        }

        // Проверить, заармлен ли коптер
        bool isArmed()
        {
                return _current_state.state != 0;
        }

        // Получить текущую высоту
        double getAltitude()
        {
                return _current_state.altd;
        }

        // Получить текущую ориентацию
        double getAngle()
        {
                return _current_state.rotZ;
        }

        // Задать ориентацию
        void setAngle(double angle)
        {

        }

        // Повернуться на угол относительно текущего
        void rotate(double angle)
        {

        }

        // Задать высоту
        void setAltitude(double val)
        {

        }

        // Крен: летим влево-вправо
        // Процетаж: 0% - горизонт, 100% - 45 градусов направо, -100% - 45 градусов налево
        void right(double percent)
        {
                ROS_INFO("Moving right at %g", percent);
                geometry_msgs::Twist cmd;
                cmd.linear.x = 0;
                cmd.linear.y = percent / 100.0;
                cmd.linear.z = 0;
                cmd.angular.z = 0;
                pubControl.publish(cmd);        
        }

        // Тангаж: летим вперёд-назад
        // Процентаж: 0% - горизонт, 100% - 45 градусов вперёд, -100% - 45 градусов назад
        void forward(double percent)
        {
                ROS_INFO("Moving forward at %g", percent);
                geometry_msgs::Twist cmd;
                cmd.linear.x = percent / 100.0;
                cmd.linear.y = 0;
                cmd.linear.z = 0;
                cmd.angular.z = 0;
                pubControl.publish(cmd);        
                pubControl.publish(geometry_msgs::Twist());
        }


        /// Функции для настоящих профессионалов ;)
        
        // Задать вертикальную скорость
        void setVSpeed(double speed)
        {
                ROS_INFO("Moving up at %g", speed);
                geometry_msgs::Twist cmd;
                cmd.linear.x = 0;
                cmd.linear.y = 0;
                cmd.linear.z = 0;
                cmd.angular.z = speed;
                pubControl.publish(cmd);        

        }

        // Задать угловую скорость (тангаж)
        void setYawSpeed(double speed)
        {
                ROS_INFO("Yawing at %g", speed);
                geometry_msgs::Twist cmd;
                cmd.linear.x = 0;
                cmd.linear.y = 0;
                cmd.linear.z = 0;
                cmd.angular.z = speed;
                pubControl.publish(cmd);        
        }
};

#endif
