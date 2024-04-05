#include <fstream>
#include <iostream>
#include <iomanip>

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

// Service implementation headers
// <rtc-template block="service_impl_h">

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="consumer_stub_h">
#include "BasicDataTypeStub.h"

// </rtc-template>

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>
#include <rtm/ConnectorListener.h>
#include <rtm/CORBA_RTCUtil.h>

#include "OpenRTMTransportBase.h"

// <rtc-template block="component_description">
/*!
 * @class OpenRTMTestOut
 * @brief OpenRTM Test Out
 *
 * OpenRTM-aistの様々な種別のデータ送信の計測用コンポーネント
 *
 */
// </rtc-template>
class OpenRTMTestOut
    : public RTC::DataFlowComponentBase
{
public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  OpenRTMTestOut(RTC::Manager *manager);

  /*!
   * @brief destructor
   */
  ~OpenRTMTestOut() override;

  // <rtc-template block="public_attribute">

  // </rtc-template>

  // <rtc-template block="public_operation">

  // </rtc-template>

  // <rtc-template block="activity">
  /***
   *
   * The initialize action (on CREATED->ALIVE transition)
   *
   * @return RTC::ReturnCode_t
   *
   *
   */
  RTC::ReturnCode_t onInitialize() override;

  /***
   *
   * The finalize action (on ALIVE->END transition)
   *
   * @return RTC::ReturnCode_t
   *
   *
   */
  // RTC::ReturnCode_t onFinalize() override;

  /***
   *
   * The startup action when ExecutionContext startup
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   *
   *
   */
  // RTC::ReturnCode_t onStartup(RTC::UniqueId ec_id) override;

  /***
   *
   * The shutdown action when ExecutionContext stop
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   *
   *
   */
  // RTC::ReturnCode_t onShutdown(RTC::UniqueId ec_id) override;

  /***
   *
   * The activated action (Active state entry action)
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   *
   *
   */
  // RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id) override;

  /***
   *
   * The deactivated action (Active state exit action)
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   *
   *
   */
  // RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id) override;

  /***
   *
   * The execution action that is invoked periodically
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   *
   *
   */
  // RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id) override;

  /***
   *
   * The aborting action when main logic error occurred.
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   *
   *
   */
  // RTC::ReturnCode_t onAborting(RTC::UniqueId ec_id) override;

  /***
   *
   * The error action in ERROR state
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   *
   *
   */
  // RTC::ReturnCode_t onError(RTC::UniqueId ec_id) override;

  /***
   *
   * The reset action that is invoked resetting
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   *
   *
   */
  // RTC::ReturnCode_t onReset(RTC::UniqueId ec_id) override;

  /***
   *
   * The state update action that is invoked after onExecute() action
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   *
   *
   */
  // RTC::ReturnCode_t onStateUpdate(RTC::UniqueId ec_id) override;

  /***
   *
   * The action that is invoked when execution context's rate is changed
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   *
   *
   */
  // RTC::ReturnCode_t onRateChanged(RTC::UniqueId ec_id) override;
  // </rtc-template>

  RTC::TimedOctetSeq *getInData();
  RTC::InPort<RTC::TimedOctetSeq> *getInPort();
  RTC::TimedOctetSeq *getOutData();
  RTC::OutPort<RTC::TimedOctetSeq> *getOutPort();

protected:
  // <rtc-template block="protected_attribute">

  // </rtc-template>

  // <rtc-template block="protected_operation">

  // </rtc-template>

  // Configuration variable declaration
  // <rtc-template block="config_declare">

  // </rtc-template>

  // DataInPort declaration
  // <rtc-template block="inport_declare">
  RTC::TimedOctetSeq m_in;
  /*!
   * データ転送速度計測用ポート
   * - Type: RTC::TimedOctetSeq
   * - Semantics: outのポートからデータ送信後、返信を受信してコネク
   *              タコールバック関数で受信時間を計測する。
   *              buffer.length(バッファ長さ)を1、buffer.write.ful
   *              l_policy(バッファ書き込みポリシー)をoverwriteにす
   *              ることを前提としている。
   */
  RTC::InPort<RTC::TimedOctetSeq> m_inIn;

  // </rtc-template>

  // DataOutPort declaration
  // <rtc-template block="outport_declare">
  RTC::TimedOctetSeq m_out;
  /*!
   * データ転送速度計測用ポート
   * - Type: RTC::TimedOctetSeq
   * - Semantics: RTCのインスタンスの外部でデータポートのオブジェク
   *              トを取得して送信処理を実行する。
   *              基本的にonExecute関数でデータ送信処理を実行しない
   *              。
   */
  RTC::OutPort<RTC::TimedOctetSeq> m_outOut;

  // </rtc-template>

  // CORBA Port declaration
  // <rtc-template block="corbaport_declare">

  // </rtc-template>

  // Service declaration
  // <rtc-template block="service_declare">

  // </rtc-template>

  // Consumer declaration
  // <rtc-template block="consumer_declare">

  // </rtc-template>

private:
  // <rtc-template block="private_attribute">

  // </rtc-template>

  // <rtc-template block="private_operation">

  // </rtc-template>
};

#if RTM_MAJOR_VERSION >= 2
static const char *const openrtmtestout_spec[] =
#else
static const char *openrtmtestout_spec[] =
#endif
    {
        "implementation_id", "OpenRTMTestOut",
        "type_name", "OpenRTMTestOut",
        "description", "OpenRTM Test Out",
        "version", "1.0.0",
        "vendor", "AIST",
        "category", "Test",
        "activity_type", "PERIODIC",
        "kind", "DataFlowComponent",
        "max_instance", "1",
        "language", "C++",
        "lang_type", "compile",
        ""};

class SendData
{
public:
  SendData(unsigned int id_, double send_time_, double recv_time_, double ret_time_)
      : id(id_), send_time(send_time_), recv_time(recv_time_), ret_time(ret_time_)
  {
  }
  ~SendData(){};
  unsigned int id;
  double send_time;
  double recv_time;
  double ret_time;
};

class OutDataListener
    : public RTC::ConnectorDataListenerT<RTC::TimedOctetSeq>
{
  USE_CONNLISTENER_STATUS;

public:
  OutDataListener();
  ~OutDataListener() override;

  ReturnCode operator()(RTC::ConnectorInfo &info,
                             RTC::TimedOctetSeq &data) override;

  std::vector<SendData> &get_result();

private:
  std::vector<SendData> m_result;
};

OutDataListener::OutDataListener()
{
}

OutDataListener::~OutDataListener()
{
}

OutDataListener::ReturnCode OutDataListener::operator()(RTC::ConnectorInfo &info,
                                            RTC::TimedOctetSeq &data)
{
  const char *payload = (const char *)&data.data[0];
  struct DataHdr *hdr = (struct DataHdr *)payload;

  auto now = std::chrono::high_resolution_clock::now().time_since_epoch();
  auto pub2_sec = std::chrono::duration_cast<std::chrono::seconds>(now);
  auto pub2_nsec = std::chrono::duration_cast<std::chrono::nanoseconds>(now - pub2_sec);
  uint64_t pub2_sec_count = static_cast<uint64_t>(pub2_sec.count());
  uint64_t pub2_nsec_count = static_cast<uint64_t>(pub2_nsec.count());

  uint64_t pub2_count = pub2_nsec_count + pub2_sec_count * 1.0e+9;

  /*
  unsigned int id = 0;
  uint64_t pub_sec_count = 0;
  uint64_t pub_nsec_count = 0;
  uint64_t sub_sec_count = 0;
  uint64_t sub_nsec_count = 0;



  int pos = 0;

  memcpy(&id, &payload[pos], sizeof(id));
  pos += sizeof(id);
  memcpy(&pub_sec_count, &payload[pos], sizeof(pub_sec_count));
  pos += sizeof(pub_sec_count);
  memcpy(&pub_nsec_count, &payload[pos], sizeof(pub_nsec_count));
  pos += sizeof(pub_nsec_count);
  memcpy(&sub_sec_count, &payload[pos], sizeof(sub_sec_count));
  pos += sizeof(sub_sec_count);
  memcpy(&sub_nsec_count, &payload[pos], sizeof(sub_nsec_count));
  pos += sizeof(sub_nsec_count);
  */

  uint64_t pub_count = hdr->out.pub_nsec_count + hdr->out.pub_sec_count * 1.0e+9;
  uint64_t sub_count = hdr->sub_nsec_count + hdr->sub_sec_count * 1.0e+9;

  double send_time = static_cast<double>(hdr->out.pub_sec_count) + static_cast<double>(hdr->out.pub_nsec_count) * 1.0e-9;
  double recv_time = static_cast<double>(hdr->sub_sec_count) + static_cast<double>(hdr->sub_nsec_count) * 1.0e-9;
  double ret_time = static_cast<double>(pub2_sec_count) + static_cast<double>(pub2_nsec_count) * 1.0e-9;
  m_result.push_back(SendData(hdr->out.id, send_time, recv_time, ret_time));

  //

  if (hdr->out.id % 100 == 0)
  {
    std::cout << "receive: " << hdr->out.id << "\t" << static_cast<double>(pub2_count - pub_count) * 1.0e-9
              << "\t" << static_cast<double>(pub2_count - sub_count) * 1.0e-9 << std::endl;
  }

  return NO_CHANGE;
}

std::vector<SendData> &OutDataListener::get_result()
{
  return m_result;
}

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
OpenRTMTestOut::OpenRTMTestOut(RTC::Manager *manager)
    // <rtc-template block="initializer">
    : RTC::DataFlowComponentBase(manager),
      m_inIn("in", m_in),
      m_outOut("out", m_out)
// </rtc-template>
{
}

/*!
 * @brief destructor
 */
OpenRTMTestOut::~OpenRTMTestOut()
{
}

RTC::ReturnCode_t OpenRTMTestOut::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("in", m_inIn);

  // Set OutPort buffer
  addOutPort("out", m_outOut);

  // Set service provider to Ports

  // Set service consumers to Ports

  // Set CORBA Service Ports

  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t OpenRTMTestOut::onFinalize()
{
  return RTC::RTC_OK;
}
*/

// RTC::ReturnCode_t OpenRTMTestOut::onStartup(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t OpenRTMTestOut::onShutdown(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t OpenRTMTestOut::onActivated(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t OpenRTMTestOut::onDeactivated(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t OpenRTMTestOut::onExecute(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t OpenRTMTestOut::onAborting(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t OpenRTMTestOut::onError(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t OpenRTMTestOut::onReset(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t OpenRTMTestOut::onStateUpdate(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }

// RTC::ReturnCode_t OpenRTMTestOut::onRateChanged(RTC::UniqueId /*ec_id*/)
//{
//   return RTC::RTC_OK;
// }


RTC::TimedOctetSeq* OpenRTMTestOut::getInData()
{
  return &m_in;
}

RTC::InPort<RTC::TimedOctetSeq>* OpenRTMTestOut::getInPort()
{
  return &m_inIn;
}

RTC::TimedOctetSeq* OpenRTMTestOut::getOutData()
{
  return &m_out;
}

RTC::OutPort<RTC::TimedOctetSeq>* OpenRTMTestOut::getOutPort()
{
  return &m_outOut;
}

bool connect(RTC::PortBase *port1_var, const std::string &recv_host, const int recv_port, const std::string &recv_name, const std::string &port_name)
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

int main(int argc, char *argv[])
{
  unsigned short recv_port = 2809;
  std::string recv_host("127.0.0.1");
  std::string recv_name("OpenRTMTestIn0");
  std::string conffile("rtc.conf");

  uint32_t max_count = 1000;
  uint64_t data_size = 40;
  uint64_t rate = 1000000;
  std::string output_file("result_openrtm_in.txt");
  unsigned int wait_time = 1000000000;
  bool shutdown = false;

  unsigned long server_sleep_time = 5000000000;

  std::ifstream ifs;
  std::string filename;
  if (argc > 1)
  {
    if (std::string(argv[1]) == "shutdown")
    {
      shutdown = true;
      if (argc > 2)
      {

        filename = argv[2];
      }
      else
      {
        filename = "configOpenRTM.txt";
      }
    }
    else
    {
      filename = argv[1];
    }
  }
  else
  {
    filename = "configOpenRTM.txt";
  }

  std::string command = "--";
  if (filename.size() > command.size() && filename.compare(0, command.size(), command) == 0)
  {
    filename = "configOpenRTM.txt";
  }

  std::cout << "open config file: " << filename << std::endl;
  ifs.open(filename);

  std::string str;
  if (ifs.fail())
  {
    std::cerr << "load error:" << filename << std::endl;
    return -1;
  }
  std::vector<std::vector<std::string>> v_list;
  while (std::getline(ifs, str))
  {
    std::vector<std::string> v;
    std::stringstream ss{str};
    std::string buf;
    while (std::getline(ss, buf, ' '))
    {
      v.push_back(buf);
    }
    v_list.push_back(v);
  }

  for (int i = 1; i < argc; i++)
  {
    std::string arg(argv[i]);
    if (arg.size() > command.size() &&
        arg.compare(0, command.size(), command) == 0)
    {
      std::vector<std::string> v;
      std::stringstream ss{arg.substr(command.size())};
      std::string buf;
      while (std::getline(ss, buf, '='))
      {
        v.push_back(buf);
      }
      v_list.push_back(v);
    }
  }

  for (auto &v : v_list)
  {
    if (v.size() >= 2)
    {
      if (v[0] == "recv_port")
      {
        std::istringstream sv(v[1]);
        sv >> recv_port;
      }
      else if (v[0] == "recv_host")
      {
        recv_host = v[1];
      }
      else if (v[0] == "recv_name")
      {
        recv_name = v[1];
      }
      else if (v[0] == "max_count")
      {
        std::istringstream sv(v[1]);
        sv >> max_count;
      }
      else if (v[0] == "data_size")
      {
        std::istringstream sv(v[1]);
        sv >> data_size;
      }
      else if (v[0] == "rate")
      {
        std::istringstream sv(v[1]);
        sv >> rate;
      }
      else if (v[0] == "server_sleep_time")
      {
        std::istringstream sv(v[1]);
        sv >> server_sleep_time;
      }
      else if (v[0] == "wait_time")
      {
        std::istringstream sv(v[1]);
        sv >> wait_time;
      }
      else if (v[0] == "output_file_out")
      {
        output_file = v[1];
      }
      else if (v[0] == "rtc_conf_file")
      {
        conffile = v[1];
      }
    }
  }

  std::cout << "start RTComponent and Manager" << std::endl;

  RTC::Manager *manager;
  coil::vstring v_{ std::string("OpenRTMTestOut"), std::string("-f"), conffile };
  coil::Argv argv_(v_);
  manager = RTC::Manager::init(argv_.size(), argv_.get());
  manager->activateManager();
  manager->runManager(true);

  coil::Properties profile(openrtmtestout_spec);
  manager->registerFactory(profile,
                           RTC::Create<OpenRTMTestOut>,
                           RTC::Delete<OpenRTMTestOut>);

  RTC::RtcBase *comp;
  comp = manager->createComponent("OpenRTMTestOut");

  if (comp == nullptr)
  {
    std::cerr << "Component create failed." << std::endl;
    abort();
  }

  OpenRTMTestOut *rtc = dynamic_cast<OpenRTMTestOut *>(comp);

  if (rtc == nullptr)
  {
    std::cerr << "Component create failed." << std::endl;
    abort();
  }

  RTC::OutPort<RTC::TimedOctetSeq> *outOut = rtc->getOutPort();
  RTC::TimedOctetSeq *out = rtc->getOutData();
  RTC::InPort<RTC::TimedOctetSeq> *inIn = rtc->getInPort();

  OutDataListener *datalistener = new OutDataListener();

  inIn->addConnectorDataListener(RTC::ConnectorDataListenerType::ON_BUFFER_WRITE,
                                datalistener);

  if (!connect(outOut, recv_host, recv_port, recv_name, std::string("in")))
  {
    std::cout << "connect error" << std::endl;
    manager->terminate();
    manager->join();
    return 1;
  }

  if (!connect(inIn, recv_host, recv_port, recv_name, std::string("out")))
  {
    std::cout << "connect error" << std::endl;
    manager->terminate();
    manager->join();
    return 1;
  }

  if (!shutdown)
  {
    std::this_thread::sleep_for(std::chrono::nanoseconds(server_sleep_time));

    std::cout << "send data(data size: " << data_size << ", number: " << max_count << ", rate: " << static_cast<double>(rate) * 1.0e-9 << ")" << std::endl;
    out->data.length(data_size);

    for (uint32_t i = 0; i < max_count; i++)
    {
      struct InDataHdr *hdr = (struct InDataHdr *)&out->data[0];
      auto now = std::chrono::high_resolution_clock::now();
      auto now_time = now.time_since_epoch();
      auto sec = std::chrono::duration_cast<std::chrono::seconds>(now_time);
      auto nsec = std::chrono::duration_cast<std::chrono::nanoseconds>(now_time - sec);
      // uint64_t pub_sec_count = static_cast<uint64_t>(sec.count());
      // uint64_t pub_nsec_count = static_cast<uint64_t>(nsec.count());
      hdr->id = i;
      hdr->pub_sec_count = static_cast<uint64_t>(sec.count());
      hdr->pub_nsec_count = static_cast<uint64_t>(nsec.count());

      /*
      int pos = 0;

      memcpy(&data.data[pos], (void*)&i, sizeof(i));
      pos += sizeof(i);

      memcpy(&data.data[pos], (void*)&pub_sec_count, sizeof(pub_sec_count));
      pos += sizeof(pub_sec_count);

      memcpy(&data.data[pos], (void*)&pub_nsec_count, sizeof(pub_nsec_count));
      pos += sizeof(pub_nsec_count);
      */

      outOut->write();

      if (i % 100 == 0)
      {
        std::cout << "write data: " << i << std::endl;
      }

      auto last = std::chrono::high_resolution_clock::now();

      auto time = std::chrono::duration_cast<std::chrono::nanoseconds>(last - now);

      if (time.count() < static_cast<unsigned int>(rate))
      {
        std::this_thread::sleep_for(std::chrono::nanoseconds(rate - time.count()));
      }
      // std::this_thread::sleep_for(std::chrono::milliseconds(10));
      // std::cout << i << std::endl;
    }
  }
  else
  {
    std::cout << "send shutdown message" << std::endl;
    out->data.length(0);
    outOut->write();
  }
  // setTimestamp(data);

  std::this_thread::sleep_for(std::chrono::nanoseconds(wait_time));

  std::cout << "shutdown Manager" << std::endl;

  manager->terminate();
  manager->join();

  if (!shutdown)
  {
    std::cout << "save file" << std::endl;
    std::ofstream writing_file;
    writing_file.open(output_file, std::ios::out);

    std::vector<SendData> &result = datalistener->get_result();

    for (auto &data : result)
    {
      writing_file << data.id << "\t" << std::fixed << std::setprecision(9) << data.send_time << "\t" << data.recv_time << "\t" << data.ret_time << std::endl;
    }

    writing_file.close();
  }

  std::cout << "finish" << std::endl;

  // delete out;

  return 0;
}