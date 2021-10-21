#include <vector>
#include <cassert>
#include <buffers.hpp>
#include <header.hpp>
#include <_5GS/ie/Identity_type.hpp>
#include <_5GS/ie/Group.hpp>
#include<_5GS/ie/Message_type.hpp>
#include <_5GS/decode.hpp>
#include <_5GS/pdu_session_release_request.hpp>

using namespace _5GS;


int main(int argc, char *argv[])
{

    std::vector<uint8_t> data;
    std::vector<uint8_t> extdata;
	
    CPDU_session_release_request    PDUreleasereq;

    PDUreleasereq.setPDUsessionidentityIE(IE::PDU_session_identity::Value::PDU_session_identity_value_10);
    PDUreleasereq.setProceduretransactionIdyIE(0);
    PDUreleasereq.set5GSMCauseIE(IE::_5GSM_Cause::Cause_Value::Missing_or_unknown_DNN);

    extdata.push_back(3);
    extdata.push_back(10);
    PDUreleasereq.setExtendedProtocolConfigOptionsIE(IE::ExtendedProtocolConfigurationOptions::configurationProtocol::PPP2 , IE::ExtendedProtocolConfigurationOptions::ext::extpresent , extdata);


    PDUreleasereq.encode(data);


    std::cout<<"PDU session release request \n----------------------------------------------------- \n"<<dump_wireshark(data)<<"\n"<<std::endl;
    std::cout<<dump_wireshark_with_ngap_encapsulation(data)<<"\n"<<std::endl;
}