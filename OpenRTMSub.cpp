#include "OpenRTMSub.h"
#include <rtm/CORBA_RTCUtil.h>


bool port_connect(RTC::PortBase *port1_var, const std::string &recv_host, const int recv_port, const std::string &recv_name, const std::string &port_name)
{
  
  std::string address = "rtcname://" + recv_host + ":" + coil::otos(recv_port) + "/*/" + recv_name + "." + port_name;

  int max_count = 1000;

  for (int i = 0; i < max_count; i++)
  {

    RTC::PortService_var port2_var = CORBA_RTCUtil::get_port_by_url(address);

    if (CORBA::is_nil(port2_var))
    {
      std::cout << "could not access " << address << std::endl;
    }
    else
    {
      coil::Properties prop;
      prop["dataport.dataflow_type"] = "push";
      prop["dataport.interface_type"] = "corba_cdr";
      prop["dataport.subscription_type"] = "flush";
      prop["dataport.buffer.length"] = "1";
      prop["write.full_policy"] = "overwrite";
      if (RTC::RTC_OK == CORBA_RTCUtil::connect("test_connector", prop, port2_var.in(), port1_var->getPortRef()))
      {
        return true;
      }
      else
      {
        std::cout << "could not access " << address << std::endl;
        return false;
      }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  std::cout << "could not access " << address << std::endl;
  return false;
}