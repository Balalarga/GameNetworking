#pragma once

class TcpServer;
class TcpSocket;


class IListenStrategy
{
public:
	virtual ~IListenStrategy() = default;

	virtual void Listen(const std::shared_ptr<TcpSocket>& socket) = 0;
};
