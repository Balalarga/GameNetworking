#pragma once
#include "TransferBuffer.h"


class TcpSocket;
class IWriteStrategy
{
public:
	virtual ~IWriteStrategy() = default;

	virtual void Write(const std::shared_ptr<TcpSocket>& socket, const asio::error_code& error) = 0;
	virtual const TransferBuffer& Buffer() = 0;
};


class IReadStrategy
{
public:
	virtual ~IReadStrategy() = default;

	virtual void Read(const std::shared_ptr<TcpSocket>& socket, const asio::error_code& error) = 0;
	virtual TransferBuffer& Buffer() = 0;
};

