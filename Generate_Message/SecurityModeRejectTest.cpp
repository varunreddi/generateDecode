#include <vector>
#include <cassert>
#include <buffers.hpp>
#include <_5GS/decode.hpp>
#include <_5GS/Notification.hpp>
#include <_5GS/NAS_generation.hpp>
#include<_5GS/SecurityModeReject.hpp>

using namespace _5GS;

logger *logger::instance = 0;

int main()
{
    logger *logobj = logobj->getInstance();
    logobj->setloggingstyle();
    std::vector<uint8_t> data;

    NAS_generation ng;
	
   // int i = std::stoi(argv[1]);

    /*switch(i)
    {
        case 1:
        {
            data = ng.generate_registration_complete_1();
            break;
        }

        case 2:
        {
            //data = ng.generate_registration_complete_2();
            break;
        }
        case 3:
        {
           //data =  ng.generate_registration_complete_3();
            break;
        }
        default:
            break;
    }*/
    SecurityModeReject smr;
    smr.set5GMMCauseIE(IE::_5GMM_Cause::Cause_Value::DNN_not_supported_or_not_subscribed_in_the_slice);

    smr.encode(data);

    std::cout<<"Security Mode Reject \n----------------------------------------------------- \n"<<dump_wireshark(data)<<"\n"<<std::endl;
    std::cout<<dump_wireshark_with_ngap_encapsulation(data)<<"\n"<<std::endl;
    
}