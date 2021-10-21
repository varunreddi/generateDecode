#include <vector>
#include <cassert>
#include <buffers.hpp>
#include <_5GS/decode.hpp>
#include <_5GS/NAS_generation.hpp>

using namespace _5GS;


int main(int argc, char *argv[])
{

    std::vector<uint8_t> data;

    NAS_generation ng;
	
    int i = std::stoi(argv[1]);

    switch(i)
    {
        case 1:
        {
            data = ng.generate_ul_nas_transport_1();
            break;
        }

    case 2:
        {
            data = ng.generate_pdu_session_establishment_request_2();
            break;
        }
        case 3:
        {
            data = ng.generate_pdu_session_establishment_request_3();
            break;
        }
        default:
            break;
    }

    std::cout<<"PDU session establishment request \n----------------------------------------------------- \n"<<dump_wireshark(data)<<"\n"<<std::endl;
    std::cout<<dump_wireshark_with_ngap_encapsulation(data)<<"\n"<<std::endl;
}
