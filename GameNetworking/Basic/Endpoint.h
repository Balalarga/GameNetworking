#pragma once
#include <string>
#include "asio/ip/tcp.hpp"


struct Endpoint
{
	static Endpoint LocalHost(uint16_t port = 0)
	{
		return Endpoint("127.0.0.1", port);
	}
	
	Endpoint(std::string host, uint16_t port): host(std::move(host)), port(port) { }

	asio::ip::tcp::endpoint AsioEndpoint() const
	{
		return {asio::ip::address_v4::from_string(host), port};
	}

	std::string host;
	uint16_t port;

	friend std::ostream& operator<<(std::ostream& os, const Endpoint& endpoint);
};

inline std::ostream& operator<<(std::ostream& os, const Endpoint& endpoint)
{
	os << endpoint.host << ":" << endpoint.port;
	return os;
}
