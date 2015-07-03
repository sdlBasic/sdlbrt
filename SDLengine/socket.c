/*
_________________________________________________________________________________________________________________________

    SDLengine core of sdlBasic



    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Library General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Library General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    __vroby__
    __vroby__@libero.it

_________________________________________________________________________________________________________________________

*/

#include "SDLengine.h"

#ifdef SOCKET_SUPPORT
//_________________________________________________________________________________________________________________________

// SOCKET
//_________________________________________________________________________________________________________________________

//isenabledsock()							: return 1 if sdlnet was enabled
int isenabledsock()
{
    return enabledsock;
}
//_________________________________________________________________________________________________________________________

// getfreesock								: return the first free sock in sdlSocket array
int getfreesock()
{
    int i;
    for (i=1;i<NUM_SOCKS;i++)
	if (SDLsock[i]==NULL)return i;
    return -1;
}
//_________________________________________________________________________________________________________________________

/*OpenSock (sock,port) 							: Server side socket sock is the stream. in sdlBasic \
									  there are 256 stream and sintax is very similar of \
									  file open close. */
int opensock(int port)
{
    int sock;
    IPaddress my_ip;

	// Resolve the argument into an IPaddress type
	if(SDLNet_ResolveHost(&my_ip,INADDR_ANY,port)==-1)
	{
	    error_description="SDLengine error - openSock: SDLNet_ResolveHost  ";
	    error_type=1;
		SDLerr(stderr,"SDLengine error - openSock: SDLNet_ResolveHost: %s\n", SDLNet_GetError());
		return -1;
	}

    sock=getfreesock();
    SDLsock[sock] = SDLNet_TCP_Open( &my_ip);

    if (SDLsock[sock]==NULL)return 0;
    return sock;
}
//_________________________________________________________________________________________________________________________

//AcceptSock(serversockk)							: Accept the client connection
int acceptsock(int serversock)
{
    int clientsock;
    clientsock=getfreesock();
    SDLsock[clientsock]=SDLNet_TCP_Accept(SDLsock[serversock]);
    if(SDLsock[clientsock]!=NULL)return clientsock;
    return 0;
}


//_________________________________________________________________________________________________________________________

//IsServerReady(Sock)							: True/False if server is sending data    

int isserverready(int sock)
{
    int ret;
    SDLNet_SocketSet set;
    set=SDLNet_AllocSocketSet(1);

    if (SDLNet_TCP_AddSocket(set, SDLsock[sock])==-1){
	closesock(sock);
	return -1;
    }

    if (SDLNet_CheckSockets(set, 1)==-1){
	closesock(sock);
	return -1;
    }
    ret= SDLNet_SocketReady(SDLsock[sock]);
    SDLNet_TCP_DelSocket(set, SDLsock[sock]);
    return ret;
}


//_________________________________________________________________________________________________________________________

//ConnectSock(sock,ServerName,port)					: client side socket connection
int connectsock(char *servername,int port)
{
    int sock;
    IPaddress my_ip;

	// Resolve the argument into an IPaddress type
	if(SDLNet_ResolveHost(&my_ip,servername,port)==-1)
	{
	    error_description="SDLengine error - connectSock: SDLNet_ResolveHost ";
	    error_type=1;
	    SDLerr(stderr,"SDLengine error - connectSock: SDLNet_ResolveHost: %s\n",SDLNet_GetError());
		return -1;
	}

    sock=getfreesock();
    SDLsock[sock] = SDLNet_TCP_Open( &my_ip);

    if (SDLsock[sock]==NULL)return 0;
    return sock;
}


//_________________________________________________________________________________________________________________________

//ConnectionReadySock(sock)						: the server have accepted the connection

//_________________________________________________________________________________________________________________________

//IsClientReady(Sock)							: True/False if client is sending data
int isclientready(int sock)
{
    int ret;
    SDLNet_SocketSet set;
    set=SDLNet_AllocSocketSet(1);

    if (SDLNet_TCP_AddSocket(set, SDLsock[sock])==-1){
	closesock(sock);
	return -1;
    }

    if (SDLNet_CheckSockets(set, 1)==-1){
	closesock(sock);
	return -1;
    }
    ret= SDLNet_SocketReady(SDLsock[sock]);
    SDLNet_TCP_DelSocket(set, SDLsock[sock]);
    return ret;
}

//_________________________________________________________________________________________________________________________

//CloseSock(sock)							: Close the socket connection. Works for client and server
int closesock(int sock)
{
    SDLNet_TCP_Close(SDLsock[sock]);
    SDLsock[sock]=NULL;
    return 0;
}
//_________________________________________________________________________________________________________________________

//PeekSock(Sock, NumBytes)						: Peek information coming from socket, but do not clear.

//_________________________________________________________________________________________________________________________

//ReadSock(Sock, NumBytes)						: Read NumBytes
char *readsock(int sock,int numbytes)
{
    int len;
    char *message;
    message=(char *)malloc(numbytes);
    len=SDLNet_TCP_Recv(SDLsock[sock],message,numbytes);
    if (len<0){
	closesock(sock);
	return NULL;
    }
    return message;
}
//_________________________________________________________________________________________________________________________

//ReadByteSock(Sock)							: Read a single byte      
//char readbytesock(int sock)
int readbytesock(int sock)
{
    int len;
    char byte;
    len=SDLNet_TCP_Recv(SDLsock[sock],&byte,1);
    if (len<0){
	closesock(sock);
	return -1;
    }
    return byte;
}
//_________________________________________________________________________________________________________________________

//ReadLineSock(Sock)							: Read complete line
char *readlinesock(int sock)
{
//    char c;
    char c2;
    int c = 0;
    char *message;
    message=(char *)malloc(1024);
    strcpy(message,"");
    while(c!='\13'){
	c=readbytesock(sock)&255;
	if (c<0){
	    closesock(sock);
	    return NULL;
	}
//	strncat(message,&c,1);
   c2 = c;
   strncat(message, &c2, 1);
	if(c==10)break;
	if(c==13)break;
    }
    strncat(message,"\0",1);
    return message;
}
//_________________________________________________________________________________________________________________________

//WriteSock(Sock, data,len)						: Sends NumBytes from Message
int writesock(int sock,char *data,int len)
{
    int result;
    result=SDLNet_TCP_Send(SDLsock[sock],data,len);
    if (result<0){
	closesock(sock);
	return -1;
    }
    return result;
}
//_________________________________________________________________________________________________________________________

//WriteByteSock(Sock, Byte)						: Sends a single byte
int writebytesock(int sock,char byte)
{
    int result;
    result=SDLNet_TCP_Send(SDLsock[sock],&byte,1);
    if (result<0){
	closesock(sock);
	return -1;
    }
    return result;
}
//_________________________________________________________________________________________________________________________

//WriteLineSock(Sock, Message)						: Send Message
int writelinesock(int sock,char *message)
{
    int result,len;
    len=strlen(message);
    result=SDLNet_TCP_Send(SDLsock[sock],message,len);
    if (result<0){
	closesock(sock);
	return -1;
    }
    writebytesock(sock,13);
    return result;
}
//_________________________________________________________________________________________________________________________

//getremoteip(sock)							: return the ip address of remote client connetted
char *getremoteip(sock)
{
    Uint32 ipaddr;
    IPaddress *remoteip;
    char *ret;

    ret=(char *)malloc(24);
    // get the clients IP and port number
    remoteip=SDLNet_TCP_GetPeerAddress(SDLsock[sock]);
    if(!remoteip)
    {
	error_description="SDLengine error - getRemoteIp: SDLNet_TCP_GetPeerAddress ";
	error_type=1;
	SDLerr(stderr,"SDLengine error - getRemoteIp: SDLNet_TCP_GetPeerAddress: %s\n",SDLNet_GetError());
	return NULL;
    }

    // print out the clients IP and port number
    ipaddr=SDL_SwapBE32(remoteip->host);
    sprintf(ret,"%d.%d.%d.%d\n",
			ipaddr>>24,
			(ipaddr>>16)&0xff,
			(ipaddr>>8)&0xff,
			ipaddr&0xff);
    return ret;
}
//_________________________________________________________________________________________________________________________

//getremoteport(sock)							: return the ip address of remote client connetted
int getremoteport(sock)
{
    Uint16 port;
    IPaddress *remoteip;

    // get the clients IP and port number
    remoteip=SDLNet_TCP_GetPeerAddress(SDLsock[sock]);
    if(!remoteip)
    {
	error_description="SDLengine error - getRemotePort: SDLNet_TCP_GetPeerAddress ";
	error_type=1;
	SDLerr(stderr,"SDLengine error - getRemotePort: SDLNet_TCP_GetPeerAddress: %s\n",SDLNet_GetError());
	return -1;
    }

    // print out the clients IP and port number
    port=SDL_SwapBE32(remoteip->port);
    return port;
}
//_________________________________________________________________________________________________________________________

//getlocalip()								: return the local ip
#ifndef WIN32 // has no gethostname that we can use here...
    int gethostname(char *name,int number);
#endif

char *getlocalip()
{
#ifndef WIN32 // has no gethostname that we can use here...

    IPaddress ip;
    Uint32 ipaddr;
    //Uint16 port;
    char *localhostname;
    char *ret;

    ret=(char *)malloc(24);
    localhostname=(char *)malloc(256);
    if((gethostname(localhostname, 256)>=0))
	{
	if(SDLNet_ResolveHost(&ip,localhostname,0)==-1)
	    {
		error_description="SDLengine error getLocalIp: Can't resolve host ";
		error_type=1;
		SDLerr(stderr,"SDLengine error getLocalIp: Can't resolve host \"%s\"\n%s\n", localhostname, SDLNet_GetError());
		return NULL;
	    }
	    else
	    {
		// use the IP as a Uint8[4]
		ipaddr= ip.host;

		// print out the clients IP
		sprintf(ret,"%d.%d.%d.%d\n",
			ipaddr>>24,
			(ipaddr>>16)&0xff,
			(ipaddr>>8)&0xff,
			ipaddr&0xff);

	    }
	}
    return ret;
#else
    return "localhost";
#endif
}

#endif
//_________________________________________________________________________________________________________________________
