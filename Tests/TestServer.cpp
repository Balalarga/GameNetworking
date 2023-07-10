#include <iostream>
#include "GameNetworking/TcpServer.h"
#include "GameNetworking/TcpSocket.h"


class Writer: public IAsyncWrite
{
public:
	WritingStatus AfterWrite(const std::shared_ptr<TcpSocket>& socket, size_t bytes, const asio::error_code& error) override
	{
		if (bytes == 0)
			return WritingStatus::RepeatWrite;

		std::cout << "[Server] Write " << bytes << " bytes\n";
		_totalWritten += bytes;
		if (_totalWritten == _buffer.size())
			return WritingStatus::StopWrite;

		return WritingStatus::RepeatWrite;
	}

	const TransferBuffer& Buffer() override
	{
		return _buffer;
	}


private:
	TransferBuffer _buffer;
	size_t _totalWritten = 0;
};


class Listener: public AsyncListener
{
public:
	using AsyncListener::AsyncListener;

	void ConnectionEstablished() override
	{
		std::cout << "[Server] Connection established\n";
		GetSharedSocket()->Write(std::make_unique<Writer>());
	}
	void ConnectionFailed(const asio::error_code& error) override
	{
		std::cout << "[Server] Connection failed with error: \"" << error.message() << "\"\n";
	}
};


int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");

	asio::io_context context;

	auto server = std::make_shared<TcpServer>(context, 2545);
	std::cout << "[Server] Started on "
		<< server->GetEndpoint().AsioEndpoint().address().to_string() << ":"
		<< server->GetEndpoint().AsioEndpoint().port() << std::endl;

	server->Listen(std::make_unique<Listener>(server.get()));

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
