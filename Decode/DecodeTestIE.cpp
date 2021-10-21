#include <vector>
#include <cassert>
#include <buffers.hpp>
#include <_5GS/decode.hpp>
#include<logger.hpp>
#include<_5GS/ie/QoSRules.hpp>
using namespace _5GS;

class DecodeExample : public Decode
{

    

    void onPduSessionEstablishmentAccept(const PDU_session_establishment_accept &pdu)
    {
       // std::cout << pdu.to_string();
    }

    void onPduSessionEstablishmentReject(const PDU_session_establishment_reject &pdu,const std::vector<uint8_t> &data)
    {
      //  std::cout << pdu.to_string();
    }

};

int decode_nas(std::vector<uint8_t> data){
    int size;
    std::vector<uint8_t> outdata;
    DecodeExample decoder;
    int status =  decoder.identify_ct(data);
    //LOG_INFO("Status : {}",status);
    //std::cout << "Decoded " << size << " bytes." << std::endl;
    return status;

}

/*
   QoSRules
   QoSRules
         0x7a, 0x00, 0x09, 0x01, 000, 0x06, 0x31, 
//       Len       qri,    len   ,   roc,dqr,no.ofpc
0x31,       0x01, 0x01,
//pdf,pfi   len   pfc
0xff,     0x09
//qosPre   qos flow iden





0x7a, 0x00, 0x12, 0x01, 000, 0x06, 0x31, 
//       Len       qri,    len   ,   roc,dqr,no.ofpc
0x31,       0x01, 0x01,
//pdf,pfi   len   pfc
0xff,     0x09
//qosPre   qos flow iden

,0x01, 000, 0x06, 0x31, 0x31,       0x01, 0x01, 0xff,     0x09

Qos Flow descriptions : 0x79,0x00,0x06,0x09,0x20,0x41,0x01,0x01,0x09



*/
int main()
{   
     const std::vector<uint8_t> data = {



0x7a, 0x00, 0x09, 0x01, 000, 0x06, 0x31, 0x31,0x01, 0x01,0xff,0x09,0x01, 000, 0x06, 0x31, 0x31,       0x01, 0x01, 0xff,     0x09

            
         };
        IE::QoSRules m_qosRules;
        uint8_t i= 0x7a ;
        m_qosRules.decode_TLV_E(data, i);
//       m_qosRules.decode_TLV_E(data);
  
    return 0;
}
