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

#include "OpenRTMTransportBase.h"
#include "UDPData.h"
#include "OpenRTMSub.h"

#ifdef WIN32
#include <stdio.h>
#include <iostream>
#include <string>
#include <WinSock2.h> 
#include <Windows.h>
#else
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#endif




// <rtc-template block="component_description">
/*!
 * @class OpenRTMTestIn
 * @brief OpenRTM Test In
 *
 * OpenRTM-aistの様々な種別のデータ受信の計測用コンポーネント
 *
 */
// </rtc-template>
class OpenRTMTestIn
    : public RTC::DataFlowComponentBase
{
public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  OpenRTMTestIn(RTC::Manager *manager);

  /*!
   * @brief destructor
   */
  ~OpenRTMTestIn() override;

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
   * - Semantics: コネクタコールバック関数で受信時間を計測する。
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
   * - Semantics: inのポートでデータ受信時に、コールバック関数内で
   *              送信処理を実行する。
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

// Module specification
// <rtc-template block="module_spec">
#if RTM_MAJOR_VERSION >= 2
static const char *const openrtmtestin_spec[] =
#else
static const char *openrtmtestin_spec[] =
#endif
    {
        "implementation_id", "OpenRTMTestIn",
        "type_name", "OpenRTMTestIn",
        "description", "OpenRTM Test In",
        "version", "1.0.0",
        "vendor", "AIST",
        "category", "Test",
        "activity_type", "PERIODIC",
        "kind", "DataFlowComponent",
        "max_instance", "1",
        "language", "C++",
        "lang_type", "compile",
        ""};
// </rtc-template>

class RecvData
{
public:
  RecvData(unsigned int id_, double send_time_, double recv_time_)
      : id(id_), send_time(send_time_), recv_time(recv_time_)
  {
  }
  ~RecvData(){};
  unsigned int id;
  double send_time;
  double recv_time;
};

class InDataListener
    : public RTC::ConnectorDataListenerT<RTC::TimedOctetSeq>
{
  USE_CONNLISTENER_STATUS;
public:
  InDataListener(RTC::TimedOctetSeq *out, RTC::OutPort<RTC::TimedOctetSeq> *outOut, bool mode);
  ~InDataListener() override;

  ReturnCode operator()(RTC::ConnectorInfo &info,
                             RTC::TimedOctetSeq &data) override;

  void exit();
  std::vector<RecvData> &get_result();

private:
  std::vector<RecvData> m_result;
  std::thread m_thread;
  RTC::TimedOctetSeq *m_out;
  RTC::OutPort<RTC::TimedOctetSeq> *m_outOut;
  bool m_mode;
};

InDataListener::InDataListener(RTC::TimedOctetSeq *out, RTC::OutPort<RTC::TimedOctetSeq> *outOut, bool mode)
    : m_out(out), m_outOut(outOut), m_mode(mode)
{
}

InDataListener::~InDataListener()
{
}

void InDataListener::exit()
{
  RTC::Manager *manager = &RTC::Manager::instance();
  manager->terminate();
}

InDataListener::ReturnCode InDataListener::operator()(RTC::ConnectorInfo &info,
                                           RTC::TimedOctetSeq &data)
{

  if (data.data.length() == 0)
  {
		std::cout << "exit" << std::endl;
    m_thread = std::thread([this]
                           { exit(); });
    return NO_CHANGE;
  }

  // std::cout << octetdata.tm.sec << "\t" << octetdata.tm.nsec << std::endl;
  /*
  uint32_t id = 0;
  uint64_t pub_sec_count = 0;
  uint64_t pub_nsec_count = 0;
  */

  auto now = std::chrono::high_resolution_clock::now().time_since_epoch();

  const char *payload = (const char *)&data.data[0];
  struct InDataHdr *inhdr = (struct InDataHdr *)payload;


  /*
  int pos = 0;
  memcpy(&id, &payload[pos], sizeof(id));
  pos += sizeof(id);
  memcpy(&pub_sec_count, &payload[pos], sizeof(pub_sec_count));
  pos += sizeof(pub_sec_count);
  memcpy(&pub_nsec_count, &payload[pos], sizeof(pub_nsec_count));
  pos += sizeof(pub_nsec_count);
  */

  uint64_t pub_count = inhdr->pub_nsec_count + inhdr->pub_sec_count * 1.0e+9;

  auto sub_sec = std::chrono::duration_cast<std::chrono::seconds>(now);
  auto sub_nsec = std::chrono::duration_cast<std::chrono::nanoseconds>(now - sub_sec);
  // uint64_t sub_sec_count = static_cast<uint64_t>(sub_sec.count());
  // uint64_t sub_nsec_count = static_cast<uint64_t>(sub_nsec.count());

  // uint64_t sub_count = sub_nsec_count + sub_sec_count * 1.0e+9;

  uint64_t data_length = static_cast<uint64_t>(data.data.length());

  if (!m_mode)
  {
    data_length = sizeof(struct DataHdr);
  }

  m_out->data.length(data_length);
  memcpy(&m_out->data[0], inhdr, sizeof(struct InDataHdr));
  struct DataHdr *outhdr = (struct DataHdr *)&m_out->data[0];

  outhdr->sub_sec_count = static_cast<uint64_t>(sub_sec.count());
  outhdr->sub_nsec_count = static_cast<uint64_t>(sub_nsec.count());

  /*
  memcpy(&m_out.data[0], payload, pos);



  memcpy(&m_out.data[pos], (void*)&sub_sec_count, sizeof(sub_sec_count));
  pos += sizeof(sub_sec_count);

  memcpy(&m_out.data[pos], (void*)&sub_nsec_count, sizeof(sub_nsec_count));
  pos += sizeof(sub_nsec_count);
  */

  double send_time = static_cast<double>(inhdr->pub_sec_count) + static_cast<double>(inhdr->pub_nsec_count) * 1.0e-9;
  double recv_time = static_cast<double>(outhdr->sub_sec_count) + static_cast<double>(outhdr->sub_nsec_count) * 1.0e-9;

  m_result.push_back(RecvData(inhdr->id, send_time, recv_time));

  m_outOut->write();

  uint64_t sub_count = outhdr->sub_nsec_count + outhdr->sub_sec_count * 1.0e+9;

  if (inhdr->id % 100 == 0)
  {
    std::cout << "receive: " << inhdr->id << "\t" << static_cast<double>(sub_count - pub_count) * 1.0e-9 << std::endl;
  }

  return NO_CHANGE;
}

std::vector<RecvData> &InDataListener::get_result()
{
  return m_result;
}

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
OpenRTMTestIn::OpenRTMTestIn(RTC::Manager *manager)
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
OpenRTMTestIn::~OpenRTMTestIn()
{
}

RTC::ReturnCode_t OpenRTMTestIn::onInitialize()
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

RTC::TimedOctetSeq *OpenRTMTestIn::getInData()
{
  return &m_in;
}

RTC::InPort<RTC::TimedOctetSeq> * OpenRTMTestIn::getInPort()
{
  return &m_inIn;
}

RTC::TimedOctetSeq *OpenRTMTestIn::getOutData()
{
  return &m_out;
}

RTC::OutPort<RTC::TimedOctetSeq> *OpenRTMTestIn::getOutPort()
{
  return &m_outOut;
}

int connect(char* buf, RTC::Manager* manager, RTC::InPortBase* inIn, RTC::OutPortBase* outOut)
{
	std::cout << "connect" << std::endl;
	int pos = 0;
	struct UDPDataHeader* udph = (struct UDPDataHeader*)&buf[0];

	if (udph->address_length == 0 && udph->comp_length == 0)
	{
		return 2;
	}

	pos += sizeof(struct UDPDataHeader);
	char address[30];
	std::memset(address, 0, sizeof(address));
	std::memcpy(address, &buf[pos], udph->address_length);
	pos += udph->address_length;
	std::string address_str(address);
	char comp[30];
	std::memset(comp, 0, sizeof(address));
	std::memcpy(comp, &buf[pos], udph->comp_length);
	std::string comp_str(comp);


	/*
	if (!port_connect(inIn, address_str, udph->port, comp_str, std::string("out")))
	{
		std::cout << "connect error" << std::endl;
		manager->terminate();
		manager->join();
		return 1;
	}

	if (!port_connect(outOut, address_str, udph->port, comp_str, std::string("in")))
	{
		std::cout << "connect error" << std::endl;
		manager->terminate();
		manager->join();
		return 1;
	}
	*/
	if (!ports_connect(inIn, outOut, address_str, udph->port, comp_str, std::string("in"), std::string("out")))
	{
		std::cout << "connect error" << std::endl;
		manager->terminate();
		manager->join();
		return 1;
	}

	return 0;
}

int main(int argc, char *argv[])
{
  bool mode = true;
  std::string conffile("rtc.conf");

  std::string output_file("result_openrtm_in.txt");

  std::ifstream ifs;
  std::string filename;
	bool reverse_connect = false;
	int udp_port(50008);

  if (argc > 1)
  {
    filename = argv[1];
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

      if (v[0] == "output_file_in")
      {
        output_file = v[1];
      }
      else if (v[0] == "mode")
      {
        if (v[1] == "false")
        {
          mode = false;
        }
        else
        {
          mode = true;
        }
      }
      else if (v[0] == "rtc_conf_file")
      {
        conffile = v[1];
      }
			else if (v[0] == "reverse_connect")
			{
				reverse_connect = coil::toBool(v[1], "true", "false", false);
			}
			else if (v[0] == "udp_port")
			{
				std::istringstream sv(v[1]);
				sv >> udp_port;
			}
    }
  }

  std::cout << "start RTComponent and Manager" << std::endl;

  RTC::Manager *manager;
  coil::vstring v_{ std::string("OpenRTMTestIn"), std::string("-f"), conffile };
  coil::Argv argv_(v_);
  manager = RTC::Manager::init(argv_.size(), argv_.get());
  manager->activateManager();
  manager->runManager(true);

  coil::Properties profile(openrtmtestin_spec);
  manager->registerFactory(profile,
                           RTC::Create<OpenRTMTestIn>,
                           RTC::Delete<OpenRTMTestIn>);
  RTC::RtcBase *comp;
  comp = manager->createComponent("OpenRTMTestIn");

  if (comp == nullptr)
  {
    std::cerr << "Component create failed." << std::endl;
		manager->terminate();
		manager->join();
		return 1;
  }

  OpenRTMTestIn *rtc = dynamic_cast<OpenRTMTestIn *>(comp);

  if (rtc == nullptr)
  {
    std::cerr << "Component create failed." << std::endl;
		manager->terminate();
		manager->join();
		return 1;
  }

  RTC::OutPort<RTC::TimedOctetSeq> *outOut = rtc->getOutPort();
  RTC::TimedOctetSeq *out = rtc->getOutData();
  RTC::InPort<RTC::TimedOctetSeq> *inIn = rtc->getInPort();

  InDataListener *datalistener = new InDataListener(out, outOut, mode);

  inIn->addConnectorDataListener(RTC::ConnectorDataListenerType::ON_BUFFER_WRITE,
                                datalistener, false);


	if (reverse_connect)
	{
#ifdef WIN32
		//WSAData wsaData;
		//WSAStartup(MAKEWORD(2, 0), &wsaData);
		int sock = socket(AF_INET, SOCK_DGRAM, 0);

		struct sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_port = htons(udp_port);
		addr.sin_addr.S_un.S_addr = INADDR_ANY;
		bind(sock, (struct sockaddr *)&addr, sizeof(addr));
#else
		int sock = socket(AF_INET, SOCK_DGRAM, 0);

		struct sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = INADDR_ANY;
		addr.sin_port = htons(udp_port);
		bind(sock, (const struct sockaddr *)&addr, sizeof(addr));
#endif


		char buf[100];

		for (int i = 0; i < 500; i++)
		{
			memset(buf, 0, sizeof(buf));


			recv(sock, buf, sizeof(buf), 0);

			int ret = connect(&buf[0], manager, inIn, outOut);
			if (ret == 1)
			{
				std::cerr << "UDP connection create failed." << std::endl;
#ifdef WIN32
				closesocket(sock);
#else
				close(sock);
#endif
				manager->terminate();
				manager->join();
				return 1;
			}
			else if (ret == 2)
			{
				std::cerr << "shutdown" << std::endl;
#ifdef WIN32
				closesocket(sock);
#else
				close(sock);
#endif
				manager->terminate();
				manager->join();
				return 0;
			}
		}
#ifdef WIN32
		closesocket(sock);
		//WSACleanup();
#else
		close(sock);
#endif

	}

  std::cout << "wait" << std::endl;
  manager->join();
	

  // in->exit();
  /*
  std::ofstream writing_file;
  writing_file.open(output_file, std::ios::out);


  std::vector<RecvData>& result = in->get_result();

  for (auto& data : result)
  {
    writing_file << data.id << "\t" << std::fixed << std::setprecision(9) << data.recv_time << "\t" << data.send_time << std::endl;
  }

  writing_file.close();
  */

  //delete datalistener;
  std::cout << "finish" << std::endl;

  // delete in;
  return 0;
}