#include "OpenRTMTransportBase.h"
#include <iostream>
#include <sstream>
#include <rtm/CORBA_RTCUtil.h>

DataListenerBase::DataListenerBase(RTC::TimedOctetSeq *out, RTC::OutPort<RTC::TimedOctetSeq> *outOut, const std::string &recv_host, const int recv_port, const std::string &recv_name,
								   const std::string &send_host, const int send_port, const std::string &send_name)
	: m_out(out), m_outOut(outOut), m_send_host(send_host), m_send_port(send_port), m_send_name(send_name)
{
}

DataListenerBase::~DataListenerBase()
{
}

void DataListenerBase::exit()
{
	m_out.data.length(0);
	m_outOut.write();

	RTC::Manager *manager = &RTC::Manager::instance();
	manager->shutdown();
}

bool CORBATransportBase::connect()
{
	return connect(m_send_host, m_send_port, m_send_name);
}

bool CORBATransportBase::connect(const std::string &send_host, const int send_port, const std::string &send_name)
{
	std::string address = "rtcname://" + send_host + ":" + send_port + "/*/" + send_name;

	int max_count = 1000;

	for (int i = 0; i < max_count; i++)
	{

		RTC::PortService_var port_in_var = CORBA_RTCUtil::get_port_by_url(address);

		if (CORBA::is_nil(port_in_var))
		{
			std::cout << "could not access " << address << std::endl;
		}
		else
		{
			coil::Properties prop;
			prop["dataport.dataflow_type"] = "push";
			prop["dataport.interface_type"] = "corba_cdr";
			prop["dataport.subscription_type"] = "flush";
			CORBA_RTCUtil::connect("test_connector", prop, port_in_var.in(), m_outOut.in());
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	std::cout << "could not access " << address << std::endl;
	return false;
}