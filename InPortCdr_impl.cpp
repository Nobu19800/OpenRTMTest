#include "InPortCdr_impl.h"
#include <rtm/idl/InterfaceDataTypesSkel.h>
#include <iostream>

InPortCdrSVC::InPortCdrSVC() : m_datasize(0)
{
    m_file.open("cameratestin.txt");
}

InPortCdrSVC::~InPortCdrSVC()
{
}

OpenRTM::PortStatus InPortCdrSVC::put(const ::OpenRTM::CdrData& data)
{

    std::lock_guard<std::mutex> guard(m_mu);

#ifdef ORB_IS_ORBEXPRESS
    m_cdr.rewind();
    m_cdr.is_little_endian(true);
#elif defined(ORB_IS_TAO)
    m_cdr.reset();
#else
    m_cdr.rewindPtrs();
    m_cdr.setByteSwapFlag(true);
#endif

#ifdef ORB_IS_ORBEXPRESS
    m_cdr.write_array_1(data.get_buffer(), data.length());
#elif defined(ORB_IS_TAO)
    m_cdr.write_octet_array((const unsigned char*)data.get_buffer(), data.length());
#else
    m_cdr.put_octet_array(data.get_buffer(), data.length());
#endif


    RTC::TimedOctetSeq octetdata;

#ifdef ORB_IS_ORBEXPRESS
    m_cdr >> octetdata;
#elif defined(ORB_IS_TAO)
    TAO_InputCDR tao_cdr = TAO_InputCDR(m_cdr);
    tao_cdr >> octetdata;
#else
    octetdata <<= m_cdr;
#endif



    
    if (!m_data.empty() && m_datasize != octetdata.data.length())
    {
        save(octetdata.data.length());
    }

    auto end = std::chrono::system_clock::now().time_since_epoch();
    auto start = std::chrono::seconds(octetdata.tm.sec) + std::chrono::nanoseconds(octetdata.tm.nsec);
    double diff = std::chrono::duration<double>(end - start).count();
    m_data.push_back(diff);
    m_datasize = octetdata.data.length();

    return OpenRTM::PortStatus::PORT_OK;
}

void InPortCdrSVC::save(CORBA::ULong newsize)
{
    if (m_data.size() == 0)
    {
        m_datasize = newsize;
        return;
    }
    double avg = 0;
    for (const auto &data : m_data)
    {
        avg += data;
    }
    avg /= m_data.size();
    std::cout << m_datasize << "\t" << avg << "\t" << m_data.size() << std::endl;
    m_file << m_datasize << "\t" << avg << "\t" << m_data.size() << std::endl;
    m_data.clear();
    m_datasize = newsize;
}