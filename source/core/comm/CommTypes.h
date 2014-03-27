/////////////////////////////////////////////////////////////////////////////////////////
//	BOVIL: main
//
//		Author: Pablo Ramón Soria
//		Date:	2014-03-27
//
/////////////////////////////////////////////////////////////////////////////////////////

#ifndef _BOVIL_CORE_COMM_COMMTYPES_H_
#define _BOVIL_CORE_COMM_COMMTYPES_H_

#include <cstdint>

#ifdef _WIN32
	#include <winsock.h>
	using namespace std;
#endif

#if defined(__linux__)
	#include <sys/types.h>
	#include <sys/socket.h>
#endif

namespace BOViL{
	namespace comm{
		//-------------------------------------------------------------------------------------
		struct AddrInfo{
			int					aiFlags;	// AI_PASSIVE, AI_CANNONNAME, etc.
			int					aiFamily;	// AF_INET, AF_AINET, AF_UNSPEC
			int					aiSocketType;	// SOCK_STREAM, SOCK_DGRAM
			int					aiProtocol;	// use 0 for "any"
			size_t				ai_addrlen;	// size of aiAddr
			struct SockAddr*	aiAddr;		// struct sockAddr_in or _in6
			char*				aiCanonName;// full canonical hostname

			struct Addrinfo*	aiNext;		// linked list, next node
		};

		//-------------------------------------------------------------------------------------
		struct SockAddr {
			unsigned short	saFamily;	// address famili, AF_xxx
			char			saData[14];	// 14 bytes of protocol address
		};

		//-------------------------------------------------------------------------------------
		struct SockAddrIn {	// Only for IPv4 --> for IPv6 SockAddrIn6
			short int		sinFamily;	// Addres famili, AF_INET
			unsigned short	intsinPort;	// Port number
			struct InAddr	sinAddr;	// Internet Addres
			unsigned char	sinZero[8];	// Same size as struct sockAddr;
		};

		//-------------------------------------------------------------------------------------
		struct SockAddrIn6 {
			uint16_t	sin6Family;	// Addres family, AD_INET6
			uint16_t	sin6Port;	// Port number, Network Byte Order
			uint32_t	sin6FlowInfo;	// IPv6 flow information
			struct In6Addr	In6Addr;	// IPv6 address
			uint32_t	sin6ScopeId;	// Scope ID
		};

		//-------------------------------------------------------------------------------------
		struct InAddr {		// Internet Addres. Only for IPv4 --> for IPv6 In6Addr
			uint32_t sAddr;	// 32 bits int
		};
		//-------------------------------------------------------------------------------------
		struct In6Addr {
			unsigned char s6Addr[16];	// IPv6 address
		};

		//-------------------------------------------------------------------------------------
		struct SockAddrStorage {
			sa_family_t ssFamily;	// address family

			char	ssPad1[_SS_PAD1SIZE];
			std::int64_t ssAlign;
			char	ssPad2[_SS_PAD2SIZE];

		}

		//-------------------------------------------------------------------------------------

		//-------------------------------------------------------------------------------------

		//-------------------------------------------------------------------------------------
	}	//	namespace comm
}	//	namespace BOViL


#endif	//	_BOVIL_CORE_COMM_COMMTYPES_H_