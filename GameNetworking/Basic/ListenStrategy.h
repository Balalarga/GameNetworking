#pragma once

class TcpServer;
class TcpSocket;


class IListener
{
public:
	virtual ~IListener() = default;

	virtual void Listen(const std::shared_ptr<TcpSocket>& socket, const Endpoint& endpoint) = 0;
};
