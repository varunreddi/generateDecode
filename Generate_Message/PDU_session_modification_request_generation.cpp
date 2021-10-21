#include <vector>
#include <cassert>
#include <buffers.hpp>
#include <_5GS/decode.hpp>
#include<_5GS/ie/_5GSM_capability.hpp>
#include <_5GS/NAS_generation.hpp>
#include <algorithm>

using namespace _5GS;
logger *logger::instance = 0;



int main()
{

    std::vector<uint8_t> data;
    logger *logobj = logobj->getInstance();
    logobj->setloggingstyle();
    PDU_session_modification_request PSMR;
    PSMR.setPDUsessionidentityIE(IE::PDU_session_identity::Value::PDU_session_identity_value_3);
    PSMR.setProcedureTransactionIdentity(1);
    std::vector<uint8_t> dd{ 0x00, 0x0a, 0x00, 0x00, 0x0d, 0x00, 0x00, 0x03, 0x00,   0x00, 0x00, 0x03, 0x00};
    IE::_5GSM_capability::Values capability;
    PSMR.set5GSMCapabilities(capability,dd);
    PSMR.set5GSMCauseIE(IE::_5GSM_Cause::Cause_Value::Requested_service_option_not_subscribed);
    IE::ExtendedProtocolConfigurationOptions::configurationProtocol cp = IE::ExtendedProtocolConfigurationOptions::configurationProtocol::PPP1;
    IE::ExtendedProtocolConfigurationOptions::ext e = IE::ExtendedProtocolConfigurationOptions::ext::extpresent;
    std::vector<uint8_t> v{ 0x00, 0x0a, 0x00, 0x00, 0x0d, 0x00, 0x00, 0x03, 0x00};
    PSMR.setExtendedProtocolConfigOptionsIE(cp,e,v);
    PSMR.setMaximumNoofSupportedPackets(25);
    PSMR.setAlwaysOnPduSessionRequested(IE::Always_on_PDU_session_requested::APSR::Always_on_PDU_session_requested);
    PSMR.setIntegrityProtectionMaxBitRate(IE::Integrity_protection_maximum_data_rate::Value(IE::Maximum_data_rate_per_UE_for_user_plane(IE::Maximum_data_rate_per_UE_for_user_plane::Value::_64_kbps), IE::Maximum_data_rate_per_UE_for_user_plane(IE::Maximum_data_rate_per_UE_for_user_plane::Value::Full_data_rate)));
    
    uint8_t noOfFilters=0x01;
    uint8_t packetFilIdentifier = 0x01;
    uint8_t qosRulePrecedence = 0xff;

    IE::QoSRules::QoSRule qosRule1;
    
    qosRule1.qri = IE::QoSRules::QoS_rule_identifier::QRI1;
    qosRule1.noOfFilters=noOfFilters;
    qosRule1.roc = IE::QoSRules::Rule_operation_code::Modify_existing_QoS_rule_and_add_packet_filters;
    qosRule1.dqrbit = IE::QoSRules::DQR_bit::the_QoS_rule_is_the_default_QoS_rule;
    IE::QoSRules::packetFilterList p;
    p.filterDirection = IE::QoSRules::packet_filter_direction::uplink_only;
    p.filterIdentifier = packetFilIdentifier;
    p.length = 0x01;
    IE::QoSRules::PacketFilterContents pfcontents;
    pfcontents.pfcti=IE::QoSRules::Packet_filter_component_type_identifier::Match_all_type;
    qosRule1.qosRulePrecedency=qosRulePrecedence;
    qosRule1.qfi = static_cast<uint8_t>(IE::QoSRules::QFI::QFI9);
    p.pfc[0]=pfcontents;
    
    qosRule1.packetFilList[0] = p;
    qosRule1.len = 0x55;
    IE::QoSRules::QoSRule qosrules[100];
    qosrules[0]=qosRule1;
    uint8_t noOfRules = 0x01;
    PSMR.setQoSRules(qosrules,noOfRules);


    uint16_t maxcid = 0x14;
    std::vector<uint8_t> conData{0x01,0x02,0x03,0x06};
    PSMR.setHeaderCompressioncinfiuguration(IE::HeaderCompresionConfiguration::P0x0002::RoHC_profile_0x0002_supported,IE::HeaderCompresionConfiguration::P0x0003::RoHC_profile_0x0003_supported,
    IE::HeaderCompresionConfiguration::P0x0004::RoHC_profile_0x0004_supported,IE::HeaderCompresionConfiguration::P0x0006::RoHC_profile_0x0006_supported,
    IE::HeaderCompresionConfiguration::P0x0102::RoHC_profile_0x0102_supported,IE::HeaderCompresionConfiguration::P0x0103::RoHC_profile_0x0103_supported,
    IE::HeaderCompresionConfiguration::P0x0104::RoHC_profile_0x0104_supported,IE::HeaderCompresionConfiguration::IPHeaderCompressionContextParametersType::IP_0x0004,maxcid,conData);
    PSMR.setEthernetHeaderConfiguration(IE::EthernetHeaderConfiguration::CIDLength::EthernetHeaderCompressionNotUsed);
    
    IE::QosFlowDiscriptors::qosFlowDescriptor qfd;
    qfd.qfi = IE::QosFlowDiscriptors::QosFlowIdentifier::qosFlowIdentifier9;
    qfd.operationcode = IE::QosFlowDiscriptors::OperationCode::create_new_QoS_flow_description;
    qfd.noOfParameters = 0x01;
    if(qfd.operationcode ==  IE::QosFlowDiscriptors::OperationCode::create_new_QoS_flow_description){
         qfd.E = static_cast<uint8_t>(IE::QosFlowDiscriptors::EBitCreate::parameters_list_is_included);
    }
    if(qfd.operationcode ==  IE::QosFlowDiscriptors::OperationCode::delete_existing_QoS_flow_description){
         qfd.E = static_cast<uint8_t>(IE::QosFlowDiscriptors::EBitDelete::parameters_list_is_included);
    }
    if(qfd.operationcode ==  IE::QosFlowDiscriptors::OperationCode::modify_existing_QoS_flow_description){
         qfd.E = static_cast<uint8_t>(IE::QosFlowDiscriptors::EBitModify::extension_of_previously_provided_parameters);
    }
   // qfd.parameterLists[0].parameterIdentifier = IE::QosFlowDiscriptors::ParameterIdentifier::_5QI1;
  //  qfd.parameterLists[0].lengthOfParameterContents= 0x02;
    IE::QosFlowDiscriptors::parameterList para;
    para.parameterIdentifier = IE::QosFlowDiscriptors::ParameterIdentifier::_5QI1 ;
    para.lengthOfParameterContents = 0x02 ;
    para.contents[0] = 0x02 ;
    para.contents[1] = 0x03 ;
    qfd.parameterLists[0] = para;
    //qfd.parameterLists[0].contents[1] = 0x12;
    IE::QosFlowDiscriptors::qosFlowDescriptor qfds[100];
    qfds[0] = qfd;
    uint8_t noOfqfd = 0x01;
    PSMR.setQosFlowDescriptors(qfds,noOfqfd);

    PSMR.encode(data);



    std::cout<<"PDU session modification request \n----------------------------------------------------- \n"<<dump_wireshark(data)<<"\n"<<std::endl;
    std::cout<<dump_wireshark_with_ngap_encapsulation(data)<<"\n"<<std::endl;



}