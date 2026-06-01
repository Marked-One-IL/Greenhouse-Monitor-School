#include <General/Connection.hpp>
#include <stdexcept>
#include <string_view>
#include <string>

static General::Connection init;

SOCKET General::Connection::createSocket(void)
{
    SOCKET tempSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (INVALID_SOCKET == tempSocket)
    {
        throw std::runtime_error("Could not create socket. Error: " + std::to_string(WSAGetLastError()));
    }

    DWORD timeout = 10000;
    if (SOCKET_ERROR == setsockopt(tempSocket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<const char*>(&timeout), sizeof(timeout)))
    {
        closesocket(tempSocket);
        throw std::runtime_error("Failed to set socket timeout. Error: " + std::to_string(WSAGetLastError()));
    }

    return tempSocket;
}
void General::Connection::doBind(SOCKET self, unsigned short port)
{
    sockaddr_in sa{};
    sa.sin_port = htons(port);
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = INADDR_ANY;

    if (SOCKET_ERROR == bind(self, reinterpret_cast<sockaddr*>(&sa), sizeof(sa)))
    {
        throw std::runtime_error("Could not bind to port " + std::to_string(port) + ". Error: " + std::to_string(WSAGetLastError()));
    }
}
void General::Connection::doListen(SOCKET self)
{
    if (SOCKET_ERROR == listen(self, SOMAXCONN))
    {
        throw std::runtime_error("Could not listen. Error: " + std::to_string(WSAGetLastError()));
    }
}
SOCKET General::Connection::doAccept(SOCKET self)
{
    SOCKET tempSocket = accept(self, nullptr, nullptr);
    if (INVALID_SOCKET == tempSocket)
    {
        throw std::runtime_error("Could not accept connection. Error: " + std::to_string(WSAGetLastError()));
    }
    return tempSocket;
}
void General::Connection::closeSocket(SOCKET& self)
{
    if (INVALID_SOCKET != self)
    {
        shutdown(self, SD_BOTH);
        closesocket(self);
        self = INVALID_SOCKET;
    }
}

void General::Connection::receiveData(SOCKET self, void* buffer, int size)
{
    int received = 0;
    for (int totalReceived = 0; totalReceived < size; totalReceived += received)
    {
        received = recv(self, static_cast<char*>(buffer) + totalReceived, size - totalReceived, 0);
        if (SOCKET_ERROR == received || 0 == received)
        {
            throw std::runtime_error("Client disconnected during receiveData. Error: " + std::to_string(WSAGetLastError()));
        }
    }
}
void General::Connection::receiveHttp(SOCKET self, std::string& buffer, int maxSize)
{
    int received = 0;
    int totalReceived = 0;
    buffer.resize(maxSize);

    while (totalReceived < maxSize)
    {
        received = recv(self, buffer.data() + totalReceived, maxSize - totalReceived, 0);
        if (SOCKET_ERROR == received || 0 == received)
        {
            throw std::runtime_error("Client disconnected during receiveHttp. Error: " + std::to_string(WSAGetLastError()));
        }

        totalReceived += received;

        std::string_view currentData(buffer.data(), totalReceived);
        if (currentData.find("\r\n\r\n") != std::string_view::npos)
        {
            break;
        }
    }

    buffer.resize(totalReceived);
}
void General::Connection::sendData(SOCKET self, const void* buffer, int size)
{
    int sent = 0;
    for (int totalSent = 0; totalSent < size; totalSent += sent)
    {
        sent = send(self, static_cast<const char*>(buffer) + totalSent, size - totalSent, 0);
        if (SOCKET_ERROR == sent || 0 == sent)
        {
            throw std::runtime_error("Client disconnected during sendData. Error: " + std::to_string(WSAGetLastError()));
        }
    }
}

General::Connection::Connection(void)
{
    WSADATA wsa_data{};
    if (0 != WSAStartup(MAKEWORD(2, 2), &wsa_data))
    {
        throw std::runtime_error("WSAStartup Failed. Error: " + std::to_string(WSAGetLastError()));
    }
}
General::Connection::~Connection(void)
{
    WSACleanup();
}