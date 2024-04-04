// -*-C++-*-
/*!
 * @file  CORBASVC_impl.h
 * @brief 
 *
 */

#ifndef CORBASVC_IMPL_H
#define CORBASVC_IMPL_H


#include <rtm/config_rtc.h>
#if RTM_MAJOR_VERSION == 2
#include <rtm/idl/DataPort_OpenRTMSkel.h>
#else
#define USE_stub_in_nt_dll
#include <rtm/idl/DataPortSkel.h>
#endif

#include <vector>
#include <mutex>
#include <fstream>

/*
 * 
 */
class InPortCdrSVC
  : public virtual POA_OpenRTM::InPortCdr
{
 public:
   InPortCdrSVC();
   ~InPortCdrSVC() override;
   OpenRTM::PortStatus put(const ::OpenRTM::CdrData& data) override;
   void save(CORBA::ULong newsize);

private:
    std::ofstream m_file;
    std::vector<double> m_data;
    CORBA::ULong m_datasize;
    std::mutex m_mu;

#ifdef ORB_IS_ORBEXPRESS
    CORBA::Stream m_cdr;
#elif defined(ORB_IS_TAO)
    TAO_OutputCDR m_cdr;
#else
    cdrMemoryStream m_cdr;
#endif
};



#endif // MYSERVICESVC_IMPL_H


