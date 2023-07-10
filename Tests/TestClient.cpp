#include <iostream>
#include "GameNetworking/TcpClient.h"


class Reader: public IAsyncReader
{
public:
	ReadingStatus AfterRead(const std::shared_ptr<TcpSocket>& socket, size_t bytes, const asio::error_code& error) override
	{
		return ReadingStatus::StopRead;
	}

	TransferBuffer& Buffer() override
	{
		return _buffer;
	}

private:
	TransferBuffer _buffer;
};


int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");

    asio::io_context context;

    std::shared_ptr<TcpClient> client = std::make_shared<TcpClient>(context);

    client->AsyncConnect(Endpoint::LocalHost(2545),
        std::make_unique<FunctionalAsyncConnector>(
            client,
            [](const std::shared_ptr<TcpSocket>& socket)
            {
                std::cout << "[Client] Connection established" << std::endl;
            },
            [](const std::shared_ptr<TcpSocket>& socket, const asio::error_code& ec)
            {
                std::cout << "[Client] Connection error: " << ec.message() << std::endl;
            }));

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
