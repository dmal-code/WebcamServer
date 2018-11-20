#include <VideoHardware/VideoSources/WebCamera.h>
#include <ImageProcessing/PNGReaderWriter.h>
#include <ImageProcessing/JPEGReaderWriter.h>
#include <pistache/http.h>
#include <pistache/endpoint.h>
#include <pistache/common.h>
#include <Encryption/Base64.h>

//fixme: make camera a singleton

Lazarus::WebCamera* cam = NULL;

class HelloHandler : public Pistache::Http::Handler {
public:

    HTTP_PROTOTYPE(HelloHandler)

	HelloHandler()
	{
	}

    virtual ~HelloHandler()
    {
    }


    void onRequest(const Pistache::Http::Request& request, Pistache::Http::ResponseWriter response) {
    	printf("cam %d\n",cam);
		auto capturedImage = cam->capture_image_buffer();

    	std::string body = Lazarus::Base64::encodeBase64((const char*)capturedImage.get_mp_data(),
    			capturedImage.get_m_length());
    	std::string body2 = "<div><p>Taken from wikpedia</p><img src='data:image/jpeg;base64," + body +"'></div>";

        response.send(Pistache::Http::Code::Ok, body2);
    }

};

void startServer()
{

	cam = new Lazarus::WebCamera();
	cam->openDevice("/dev/video0");

	cam->print_caps();
	cam->setImageFormat(1600,1200);
	cam->startStream();


	Pistache::Address addr(Pistache::Ipv4::any(), Pistache::Port(9080));

	auto opts = Pistache::Http::Endpoint::options().threads(1);
	Pistache::Http::Endpoint server(addr);
	server.init(opts);
	auto handler = std::make_shared<HelloHandler>();
	server.setHandler(handler);
	server.serve();


	cam->stopStream();
	cam->closeDevice();
}

int main(int argc, char *argv[])
{
	startServer();

	return 0;
}

