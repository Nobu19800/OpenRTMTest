// -*-C++-*-
/*!
 * @file  OpenRTMSub.h
 * @brief 
 *
 */

#ifndef OpenRTMSub_H
#define OpenRTMSub_H

#include <rtm/PortBase.h>
#include <string>

bool port_connect(RTC::PortBase *port1_var, const std::string &recv_host, const int recv_port, const std::string &recv_name, const std::string &port_name);


#endif // OpenRTMSub_H


