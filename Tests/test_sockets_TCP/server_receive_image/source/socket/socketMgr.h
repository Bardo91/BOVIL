////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Project: DMC Server
// Date:	2014/Aug/22
// Author:	Carmelo J. Fdez-Agüera Tortosa
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _IMG_RECEIVER_SOCKET_SOCKETMGR_H_
#define _IMG_RECEIVER_SOCKET_SOCKETMGR_H_

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#endif // _WIN32
#ifdef __linux__
	#include <unistd.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netdb.h>
	typedef int SOCKET;
#endif // __linux__

#include <map>
#include <mutex>
#include <string>
#include <thread>


class ServerSocket;

class SocketMgr {
public:
	SocketMgr		(unsigned _port);
	// Write a message to the specified client
	// Return true on exit, false on fail
	bool write		(unsigned _clientId, const std::string& _msg) const;
	// Return true if we read anything from anyone
	bool readAny	(unsigned& _client, std::string& _msg) const;
	bool readFrom	(unsigned _client, std::string& _msg) const;

	bool closeConnection(unsigned _client);

private:
	addrinfo*	buildAddresInfo	(unsigned _port);
	void		startListening	(const addrinfo* _socketAddress);
	void		createConnection(int _socketDesc);

private:
	unsigned							mPort;
	SOCKET								mListener;
	mutable std::mutex					mConMutex;
	std::thread							mListenThread;
	std::map<unsigned, ServerSocket*>	mActiveConnections;
};


#endif // _IMG_RECEIVER_SOCKET_SOCKETMGR_H_
