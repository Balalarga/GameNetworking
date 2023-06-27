#pragma once
#include "TransferBuffer.h"

class TcpSocket;


class IWrite
{
public:
	virtual ~IWrite() = default;

	virtual void Write(const std::shared_ptr<TcpSocket>& socket, const asio::error_code& error) = 0;
	virtual const TransferBuffer& Buffer() = 0;
};


class IReader
{
public:
	virtual ~IReader() = default;

	virtual void Read(const std::shared_ptr<TcpSocket>& socket, const asio::error_code& error) = 0;
	virtual TransferBuffer& Buffer() = 0;
};


class IReadable
{
public:
	virtual ~IReadable() = default;

	virtual void Read(std::unique_ptr<IReader>&& writer) = 0;
};


class IWritable
{
public:
	virtual ~IWritable() = default;

	virtual void Write(std::unique_ptr<IWrite>&& writer) = 0;
};
