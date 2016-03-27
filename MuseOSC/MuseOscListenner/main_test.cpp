#include "MuseOscListenner.h"
#include <windows.h>
#pragma comment(lib, "ws2_32.lib")
using namespace Muse;

int main(int argc, char**argv) {
    
    (void) argc; // suppress unused parameter warnings
    (void) argv; // suppress unused parameter warnings

	IpEndpointName(MY_IP, PORT);
	MuseOscListenner<float, float, float, float> * listener = new MuseRaw();
	UdpListeningReceiveSocket s(
		IpEndpointName(MY_IP, PORT),
		listener);

	s.RunUntilSigInt();
	delete listener;
	std::cout << "finishing.\n";
    Sleep(200000); // observe results 
}