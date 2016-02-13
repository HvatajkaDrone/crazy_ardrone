#include "ros/ros.h"

#include "crazy_ardrone_macros.h"

// Во время работы отладочная инфа повалится в консоль, так что не боимси

int main(int argc, char *argv[])
{
        ros::init(argc, argv, "crazy_ardrone_example");

        CrazyARDroneControl drone;

        drone.arm(); // обязательно! иначе всё бессмысленно и коптер не полетит :(

        drone.takeoff(); // взлетаем. Функция потупит некоторое время, пока коптер не стабилизируется

        drone.forward(10); // летим вперёд, 10% наклона (10% от 45 градусов)
        ros_sleep(3); // летим 3 секунды

        drone.forward(0); // зависаем на месте
        ros_sleep(5); // тупим 5 секунд, чтобы зависнуть на месте

        drone.rotate(180); // поворачиваемся на 180 градусов против часовой

        drone.right(10); // летим вправо
        ros_sleep(3);

        drone.right(-10); // летим влево
        ros_sleep(5);

        drone.right(0); // тупим на месте
        ros_sleep(5);

        drone.land(); // садимся

        drone.disarm(); // дизармим, и всё будет хорошо

        return 0; // happy-end, я надеюсь
}
