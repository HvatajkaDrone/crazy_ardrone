#include "crazy_ardrone_macros.h"
        
ardrone_autonomy::Navdata CrazyARDroneControl::_current_state;
void CrazyARDroneControl::navDataCallback(const ardrone_autonomy::Navdata::ConstPtr &msg)
{
        _current_state = *msg;
}
