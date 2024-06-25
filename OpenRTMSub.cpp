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
      if (RTC::RTC_OK == CORBA_RTCUtil::connect("test_connector", prop, port1_var->getPortRef(), port2_var.in()))
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


bool ports_connect(RTC::InPortBase *inport1_var, RTC::OutPortBase *outport1_var, const std::string &recv_host, const int recv_port, const std::string &recv_name, const std::string &inport_name, const std::string &outport_name)
{
	std::string inport_address = "rtcname://" + recv_host + ":" + coil::otos(recv_port) + "/*/" + recv_name + "." + inport_name;
	std::string outport_address = "rtcname://" + recv_host + ":" + coil::otos(recv_port) + "/*/" + recv_name + "." + outport_name;


	int max_count = 1000;

	for (int i = 0; i < max_count; i++)
	{

		RTC::PortService_var inport2_var = CORBA_RTCUtil::get_port_by_url(inport_address);
		RTC::PortService_var outport2_var = CORBA_RTCUtil::get_port_by_url(outport_address);

		if (CORBA::is_nil(inport2_var) || CORBA::is_nil(outport2_var))
		{
			std::cout << "could not access " << inport_address << " or " << outport_address << std::endl;
		}
		else
		{
			coil::Properties prop;
			prop["dataport.dataflow_type"] = "push";
			prop["dataport.interface_type"] = "corba_cdr";
			prop["dataport.subscription_type"] = "flush";
			prop["dataport.buffer.length"] = "1";
			prop["write.full_policy"] = "overwrite";
			if (RTC::RTC_OK == CORBA_RTCUtil::connect("test1_connector", prop, inport1_var->getPortRef(), outport2_var.in()))
			{
				if (RTC::RTC_OK == CORBA_RTCUtil::connect("test2_connector", prop, outport1_var->getPortRef(), inport2_var.in()))
				{
					return true;
				}
				else
				{
					std::cout << "could not access " << inport_address << std::endl;
					return false;
				}
			}
			else
			{
				std::cout << "could not access " << outport_address << std::endl;
				return false;
			}

			
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	std::cout << "could not access " << inport_address << " or " << outport_address << std::endl;
	return false;
}