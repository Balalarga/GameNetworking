#pragma once
#include "Endpoint.h"

class TcpSocket;


class IConnectionStrategy
{
public:
	virtual ~IConnectionStrategy() = default;

	virtual void Connect(const Endpoint& endpoint, TcpSocket* socket) = 0;
};
