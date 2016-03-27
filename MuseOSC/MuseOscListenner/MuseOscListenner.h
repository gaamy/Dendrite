#include <iostream>
#include <cstring>
#include <memory>
#include <list>
#include <tuple>
#include <vector>
#if defined(__BORLANDC__) // workaround for BCB4 release build intrinsics bug
namespace std {
	using ::__strcmp__;  // avoid error: E2316 '__strcmp__' is not a member of 'std'.
}
#endif

#include "../../oscpack_1_1_0/osc/OscReceivedElements.h"

#include "../../oscpack_1_1_0/ip/UdpSocket.h"
#include "../../oscpack_1_1_0/osc/OscPacketListener.h"

#define PORT 5000
#define MY_IP "127.0.0.1" //0x7F000001
namespace Muse {
    
    
	template<class T = float, class... EEGDATATYPE>
	class MuseOscListenner : public osc::OscPacketListener {
	public: MuseOscListenner(const std::string adressPattern) : adressPattern_(adressPattern) {
		data_ = std::make_unique<std::list<std::tuple<T, EEGDATATYPE...>>>();
	};
			virtual void parseMessage(osc::ReceivedMessage::const_iterator arg,  osc::ReceivedMessage::const_iterator argsEnd) = 0;
	protected:
		virtual void ProcessMessage(const osc::ReceivedMessage& m, const IpEndpointName& remoteEndPoint) {
            (void) remoteEndPoint;//supress unused parameter warning
			parseMessage(m.ArgumentsBegin(), m.ArgumentsEnd());
		};
		std::unique_ptr<std::list<std::tuple<T, EEGDATATYPE... >>> data_;
		std::tuple<T, EEGDATATYPE... > next_;
	private:
		std::string adressPattern_;
	};



	class MuseRaw : public MuseOscListenner<float, float, float, float> {
	public: MuseRaw(std::string adressPattern = "/muse/eeg") : MuseOscListenner<float, float, float, float>(adressPattern) {};
			inline virtual void parseMessage(osc::ReceivedMessage::const_iterator arg, osc::ReceivedMessage::const_iterator argsEnd); //A implementer
	};



	void MuseRaw::parseMessage(osc::ReceivedMessage::const_iterator arg, osc::ReceivedMessage::const_iterator argsEnd) {
		std::vector<float> a;
		while (arg != argsEnd) {      
                a.emplace_back((arg++)->AsFloatUnchecked());          
		}
		next_ = std::tuple<float, float, float, float>(a[0], a[1], a[2], a[3]);
		data_->emplace_back(next_);
        std::vector<float>::iterator it;
        for( it = a.begin(); it  != a.end(); it++){
            std::cout << *it << std::endl;
        } 

	}
}

