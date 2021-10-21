#include <vector>
#include <cassert>
#include <buffers.hpp>
#include <_5GS/decode.hpp>
#include<_5GS/PDUSessionModificationCommandReject.hpp>
#include<_5GS/ie/_5GSM_capability.hpp>
#include <_5GS/NAS_generation.hpp>

using namespace _5GS;

logger *logger::instance = 0;

int main()
{
    logger *logobj = logobj->getInstance();
    logobj->setloggingstyle();

    std::vector<uint8_t> data;

    PDUSessionModificationCommandReject psmcr;
    psmcr.setPDUsessionidentityIE(IE::PDU_session_identity::Value::PDU_session_identity_value_3);
    psmcr.setProcedureTransactionIdentity(1);
    psmcr.set5GSMCauseIE(IE::_5GSM_Cause::Cause_Value::Requested_service_option_not_subscribed);
    IE::ExtendedProtocolConfigurationOptions::configurationProtocol cp = IE::ExtendedProtocolConfigurationOptions::configurationProtocol::PPP1;
    IE::ExtendedProtocolConfigurationOptions::ext e = IE::ExtendedProtocolConfigurationOptions::ext::extpresent;
    std::vector<uint8_t> v{ 0x00, 0x0a, 0x00, 0x00, 0x0d, 0x00, 0x00, 0x03, 0x00};
    psmcr.setExtendedProtocolConfigOptionsIE(cp,e,v);
  
    psmcr.encode(data);

    std::cout<<"PDU Session Modification Command Reject   \n----------------------------------------------------- \n"<<dump_wireshark(data)<<"\n"<<std::endl;
    std::cout<<dump_wireshark_with_ngap_encapsulation(data)<<"\n"<<std::endl;



}