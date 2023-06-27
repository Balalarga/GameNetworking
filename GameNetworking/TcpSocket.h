#pragma once
#include "Basic/AsioHandle.h"
#include "Basic/ConnectionStrategy.h"
#include "Basic/TransferStrategies.h"



class TcpSocket: public AsioHandle, public IReadable, public IWritable
{
public:
	TcpSocket(asio::io_context& context);

	void Read(std::unique_ptr<IReader>&& reader) override;
	void Write(std::unique_ptr<IWrite>&& writer) override;

	template<class TConnector, class... TArgs>
	requires std::is_base_of_v<IConnector, TConnector>
	void Connect(const Endpoint& endpoint, TArgs&&... constructorArgs)
	{
		_connector = std::make_unique<TConnector>(this, std::forward<TArgs>(constructorArgs)...);
		_connector->Connect(endpoint);
	}

	asio::ip::tcp::socket& AsioSocket()
	{
		return _socket;
	}


private:
	asio::ip::tcp::socket _socket;

	std::unique_ptr<IReader> _reader;
	std::unique_ptr<IWrite> _writer;
	std::unique_ptr<IConnector> _connector;
};
