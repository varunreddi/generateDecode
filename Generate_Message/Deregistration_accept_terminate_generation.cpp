#include <vector>
#include <cassert>
#include <buffers.hpp>
#include <_5GS/decode.hpp>
#include <_5GS/Notification.hpp>
#include <_5GS/NAS_generation.hpp>

using namespace _5GS;

logger *logger::instance = 0;

int main(int argc, char *argv[])
{

    std::vector<uint8_t> data;
    logger *logobj = logobj->getInstance();
    logobj->setloggingstyle();

    NAS_generation ng;
	
    int i = std::stoi(argv[1]);

    switch(i)
    {
        case 1:
        {
            data = ng.generate_deregistration_accept_terminate_1();
            break;
        }

    case 2:
        {
            data = ng.generate_deregistration_accept_terminate_2();
            break;
        }
        case 3:
        {
            data = ng.generate_deregistration_accept_terminate_3();
            break;
        }
        default:
            break;
    }
    std::cout<<"De-registration accept (UE terminated de-registration)\n----------------------------------------------------- \n"<<dump_wireshark(data)<<"\n"<<std::endl;
    std::cout<<dump_wireshark_with_ngap_encapsulation(data)<<"\n"<<std::endl;

}