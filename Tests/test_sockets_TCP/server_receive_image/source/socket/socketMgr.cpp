////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Project: DMC Server
// Date:	2014/Aug/22
// Author:	Carmelo J. Fdez-Agüera Tortosa
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <iostream>
#include "serverSocket.h"
#include "socketMgr.h"
#include <sstream>


#ifdef __linux__
	#include <cstring>
	#define INVALID_SOCKET -1
	#define SOCKET_ERROR -1
	#define closesocket(SOCKET) close(SOCKET)
#endif // __linux__

void initSocketLib();

//------------------------------------------------------------------------------------------------------------------
SocketMgr::SocketMgr(unsigned _port)
	:mPort(_port)
{
	assert(0 != _port);	// Ensure data integrity
	initSocketLib();

	addrinfo * socketAddress = buildAddresInfo(_port);
	mListener = socket(socketAddress->ai_family, socketAddress->ai_socktype, socketAddress->ai_protocol);
	assert(mListener != INVALID_SOCKET);

	startListening(socketAddress);
}

//------------------------------------------------------------------------------------------------------------------
bool SocketMgr::write(unsigned _clientId, const std::string& _msg) const {
	// Is there such client between active connections?
	mConMutex.lock();
	auto connectionIter = mActiveConnections.find(_clientId);
	if(connectionIter == mActiveConnections.end()) {
		mConMutex.unlock();
		return false; // No client known by that id
	}

	bool ret = connectionIter->second->write(_msg);
	mConMutex.unlock();
	return ret;
}

//------------------------------------------------------------------------------------------------------------------
bool SocketMgr::readAny(unsigned& _clientId, std::string& _msg) const {
	mConMutex.lock();
	for(auto& connection : mActiveConnections) {
		if(connection.second->read(_msg)) { // Message received
			_clientId = connection.first;
			mConMutex.unlock();
			return true;
		}
	}
	// No message received
	mConMutex.unlock();
	return false;
}

//------------------------------------------------------------------------------------------------------------------
bool SocketMgr::readFrom(unsigned _clientId, std::string& _msg) const {
	mConMutex.lock();
	// Is there such client between active connections?
	auto connectionIter = mActiveConnections.find(_clientId);
	if(connectionIter == mActiveConnections.end()) {
		mConMutex.unlock();
		return false; // No client known by that id
	}

	bool ret = connectionIter->second->read(_msg);
	mConMutex.unlock();
	return ret;
}

//------------------------------------------------------------------------------------------------------------------
addrinfo* SocketMgr::buildAddresInfo(unsigned _port) {
	// Translate port into a string
	assert(0 != _port);
	std::stringstream portName;
	portName << _port;

	// Get address information
	struct addrinfo intendedAddress;
	memset(&intendedAddress, 0, sizeof(struct addrinfo));
	intendedAddress.ai_flags = AI_PASSIVE;	// Socket address will be used to call the bind function
	intendedAddress.ai_family = AF_INET;
	intendedAddress.ai_socktype = SOCK_STREAM;
	intendedAddress.ai_protocol = IPPROTO_TCP;

	struct addrinfo *socketAddress = nullptr;
	int res = getaddrinfo(nullptr, portName.str().c_str(), &intendedAddress, &socketAddress);
	assert(res == 0);
	assert(nullptr != socketAddress);

	return socketAddress;
}

//------------------------------------------------------------------------------------------------------------------
void SocketMgr::startListening(const addrinfo* _socketAddress) {
	// Setup the TCP listening socket
	int res = bind( mListener, _socketAddress->ai_addr, (int)_socketAddress->ai_addrlen);
	assert(res != SOCKET_ERROR);
	res = listen(mListener, SOMAXCONN);
	assert(res != SOCKET_ERROR);
	std::cout << "Server is listening\n";

	// Start listening thread
	mListenThread = std::thread([this](){
		for(;;) {
			SOCKET conn = accept(mListener, nullptr, nullptr);
			if (INVALID_SOCKET == conn) {
				closesocket(mListener);
				assert(false);
				return;
			} else {
				std::cout << "Accepting connection on socket " << conn << "\n";
				createConnection(conn);
			}
		}
	});
}

//------------------------------------------------------------------------------------------------------------------
void SocketMgr::createConnection(int _socketDesc) {
	// Ensure descriptor isn't already in use
	mConMutex.lock();
	assert(mActiveConnections.find(_socketDesc) == mActiveConnections.end());
	// Add new connection
	mActiveConnections[_socketDesc] = new ServerSocket(_socketDesc);
	mConMutex.unlock();
}

//------------------------------------------------------------------------------------------------------------------
bool SocketMgr::closeConnection(unsigned _clientId) {
	// Is there such client between active connections?
	mConMutex.lock();
	auto connectionIter = mActiveConnections.find(_clientId);
	if(connectionIter == mActiveConnections.end()) {
		mConMutex.unlock();
		return false; // No client known by that id
	}

	delete connectionIter->second;
	mActiveConnections.erase(connectionIter);
	mConMutex.unlock();
	return true;
}

//------------------------------------------------------------------------------------------------------------------
void initSocketLib() {
	#ifdef _WIN32
		WSADATA wsaData;

		// Initialize Winsock
		int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
		assert(!iResult);
	#endif // _WIN32
}
