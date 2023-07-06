#include <iostream>
#include "GameNetworking/TcpClient.h"


int main(int argc, char* argv[])
{
    Endpoint endpoint("127.0.0.1", 2545);
    setlocale(LC_ALL, "Russian");

    asio::io_context context;

    std::shared_ptr<TcpClient> client = std::make_shared<TcpClient>(context);

    class AsyncConnectorLocal : public AsyncConnector
    {
    public:
        using AsyncConnector::AsyncConnector;

        void OnConnect(const std::shared_ptr<TcpSocket>& socket, const asio::error_code& ec) override
        {
            if (!ec)
                std::cout << "Connected to " << socket->GetEndpoint() << std::endl;
            else
                std::cout << "Connection error " << ec.message() << std::endl;
        }

        void Connect(const Endpoint& endpoint) override
        {
	        std::shared_ptr<TcpSocket> socket = GetSharedSocket();
            if (!socket)
                return;

            socket->AsioSocket().async_connect(
                endpoint.AsioEndpoint(),
                [endpoint](asio::error_code error)
                {
                });
        }
    };
    client->Connect(endpoint,
        std::make_unique<FunctionalAsyncConnector>(
            client,
            [](const std::shared_ptr<TcpSocket>& socket)
            {
                std::cout << "Connection established" << std::endl;
            },
            [](const std::shared_ptr<TcpSocket>& socket, const asio::error_code& ec)
            {
                std::cout << "Connection error: " << ec.message() << std::endl;
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
