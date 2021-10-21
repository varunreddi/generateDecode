#include <vector>
#include <cassert>
#include <buffers.hpp>
#include <_5GS/decode.hpp>
#include <_5GS/NAS_generation.hpp>
#include<syslog.h>

using namespace _5GS;


logger *logger::instance = 0;


int main()
{
/*    int tt = 16;
    std::cout<<"before syslog...."<<std::endl;
    setlogmask(LOG_UPTO(LOG_NOTICE));
    openlog ("exampleprog", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
    syslog (LOG_NOTICE, "Program started by User %d",tt );
    syslog (LOG_INFO, "A tree falls in a forest");

    closelog ();*/
    logger *logobj = logobj->getInstance();
    logobj->setloggingstyle();
    NAS_generation ng;
	
   // int i = std::stoi(argv[1]);
    std::vector<uint8_t> data;
  /*  switch(i)
    {
        case 1:
        {
            data = ng.generate_authentication_failure_1();
            break;
        }

    case 2:
        {
            data = ng.generate_authentication_failure_2();
            break;
        }
        case 3:
        {
            data = ng.generate_authentication_failure_3();
            break;
        }
        default:
            break;
    }*/




    IE::_5GMM_cause _5gmm_cause;
    IE::Auth_failure_param afp;
    
    afp.m_lvalue.m_u8length=0xE;
    afp.m_lvalue.m_u8AUTS[0]=0x13;    afp.m_lvalue.m_u8AUTS[1]=0x02;    afp.m_lvalue.m_u8AUTS[2]=0x07;
    afp.m_lvalue.m_u8AUTS[3]=0x01;    afp.m_lvalue.m_u8AUTS[4]=0x07;    afp.m_lvalue.m_u8AUTS[5]=0x03;
    afp.m_lvalue.m_u8AUTS[6]=0x11;    afp.m_lvalue.m_u8AUTS[7]=0x07;    afp.m_lvalue.m_u8AUTS[8]=0x02;
    afp.m_lvalue.m_u8AUTS[9]=0x02;    afp.m_lvalue.m_u8AUTS[10]=0x08;    afp.m_lvalue.m_u8AUTS[11]=0x17;
    afp.m_lvalue.m_u8AUTS[12]=0x05;    afp.m_lvalue.m_u8AUTS[13]=0x09;

    Authentication_failure af;
    af.set5GMMCause(IE::_5GMM_cause::Value::Redirection_to_EPC_required_);
    af.setAuthFailureParam(afp.m_lvalue);
    af.encode(data);
  //  std::vector<uint8_t> data = create_authentication_failure_1(_5gmm_cause,afp);
   // return data;



    std::cout<<"Authentication failure \n--------------------------------- \n"<<dump_wireshark(data)<<"\n"<<std::endl;
    std::cout<<dump_wireshark_with_ngap_encapsulation(data)<<"\n"<<std::endl;

}