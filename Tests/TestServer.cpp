#include <iostream>
#include "GameNetworking/TcpServer.h"
#include "GameNetworking/TcpSocket.h"


class AsyncListener: public AsioHandle, public IListenStrategy
{
public:
	AsyncListener(TcpServer* server):
		AsioHandle(
			server->AsioContext()),
			_acceptor(server->AsioContext(), server->GetEndpoint().AsioEndpoint())
	{
	}

	void Listen(const std::shared_ptr<TcpSocket>& socket) override
	{
		_acceptor.async_accept(
			socket->Socket(),
			[socket](const asio::error_code& error)
			{
				Endpoint endpoint(socket->Socket().local_endpoint().address().to_string(),
					socket->Socket().local_endpoint().port());
				if (!error)
					std::cout << "Connected to " << endpoint << std::endl;
				else
					std::cout << "Connection error " << error.message() << std::endl;
			});
	}


private:
	asio::ip::tcp::acceptor _acceptor;
};


int main(int argc, char* argv[])
{
	Endpoint endpoint("127.0.0.1", 2545);
	std::cout << endpoint.AsioEndpoint().address().to_string() << ":" << endpoint.AsioEndpoint().port() << std::endl;

	setlocale(LC_ALL, "Russian");

	asio::io_context context;

	auto server = std::make_shared<TcpServer>(context, endpoint);

	server->Listen(std::make_unique<AsyncListener>(server.get()));

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
