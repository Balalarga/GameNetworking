#include <iostream>
#include "GameNetworking/TcpClient.h"



int main(int argc, char* argv[])
{
	Endpoint endpoint("127.0.0.1", 2545);
	setlocale(LC_ALL, "Russian");

	asio::io_context context;

	std::shared_ptr<TcpClient> client = std::make_shared<TcpClient>(context);

	class AsyncConnector: public IConnectionStrategy
	{
	public:
		void Connect(const Endpoint& endpoint, TcpSocket* socket) override
		{
			socket->Socket().async_connect(
				endpoint.AsioEndpoint(),
				[endpoint](asio::error_code error)
				{
					if (!error)
						std::cout << "Connected to " << endpoint << std::endl;
					else
						std::cout << "Connection error " << error.message() << std::endl;
				});
		}
	};

	client->Connect(endpoint, std::make_unique<AsyncConnector>());

	try
	{
		context.run();
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
		return -1;
	}
	return 0;
}
