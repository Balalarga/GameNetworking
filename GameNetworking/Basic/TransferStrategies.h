#pragma once
#include <memory>
#include <asio/error_code.hpp>
#include "TransferBuffer.h"

class TcpSocket;


enum class WritingStatus
{
	RepeatWrite,
	StopWrite
};

class IAsyncWrite
{
public:
	virtual ~IAsyncWrite() = default;

	virtual void RequestWriting(const std::shared_ptr<TcpSocket>& socket);
	virtual WritingStatus AfterWrite(const std::shared_ptr<TcpSocket>& socket, size_t bytes, const asio::error_code& error) = 0;

	// Returns buffer with lifetime equals to IWriter
	virtual const TransferBuffer& Buffer() = 0;
};


enum class ReadingStatus
{
	RepeatRead,
	StopRead
};

class IAsyncReader
{
public:
	virtual ~IAsyncReader() = default;

	virtual void RequestReading(const std::shared_ptr<TcpSocket>& socket);
	virtual ReadingStatus AfterRead(const std::shared_ptr<TcpSocket>& socket, size_t bytes, const asio::error_code& error) = 0;

	// Returns buffer with lifetime equals to IWriter
	virtual TransferBuffer& Buffer() = 0;
};


class IAsyncReadable
{
public:
	virtual ~IAsyncReadable() = default;

	virtual void Read(std::unique_ptr<IAsyncReader>&& writer) = 0;
};


class IAsyncWritable
{
public:
	virtual ~IAsyncWritable() = default;

	virtual void Write(std::unique_ptr<IAsyncWrite>&& writer) = 0;
};
