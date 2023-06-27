#include <iostream>
#include "GameNetworking/TcpClient.h"



int main(int argc, char* argv[])
{
	Endpoint endpoint("127.0.0.1", 2545);
	setlocale(LC_ALL, "Russian");

	asio::io_context context;

	std::shared_ptr<TcpClient> client = std::make_shared<TcpClient>(context);

	class AsyncConnectorLocal: public AsyncConnector
	{
	public:
		using IConnector::IConnector;

		virtual void OnConnect(const asio::error_code& ec)
		{
			if (!ec)
				std::cout << "Connected to " << GetEndpoint() << std::endl;
			else
				std::cout << "Connection error " << ec.message() << std::endl;
		}

		void Connect(const Endpoint& endpoint) override
		{
			std::shared_ptr<TcpSocket> socket = GetSocket().lock();
			if (!socket)
				return;

			socket->AsioSocket().async_connect(
				endpoint.AsioEndpoint(),
				[endpoint](asio::error_code error)
				{

				});
		}
	};

	client->Connect<AsyncConnector>(endpoint);

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
