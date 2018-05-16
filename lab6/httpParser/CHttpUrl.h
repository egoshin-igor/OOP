#pragma once
#include <string>
#include <regex>

enum Protocol
{
	HTTP,
	HTTPS
};

class CHttpUrl
{
public:
	CHttpUrl(std::string const& url);
	CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol = HTTP);
	CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol, unsigned short port);
	std::string GetURL() const;
	std::string GetDomain() const;
	std::string GetDocument() const;
	Protocol GetProtocol() const;
	std::string GetProtocolString() const;
	unsigned short GetPort() const;
private:
	std::smatch GetParseResult();
	void AddProtocol(std::string const& possibleProtocol);
	void AddDomain(std::string const& possibleDomain);
	void AddPort(std::string const& possiblePort = "");
	void AddDocument(std::string const& possibleDocument);
	void AddUrl();
	std::string GetLowerString(std::string const& str);

	std::string m_url = "";
	std::string m_domain = "";
	std::string m_document = "";
	Protocol m_protocol = HTTP;
	unsigned short m_port = 80;
};

