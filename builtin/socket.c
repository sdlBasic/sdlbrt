//_______________________________________________________________________________________________________________________
//
// SOCKET
//_________________________________________________________________________________________________________________________

//isenabledsock()				: return 1 if sdlnet was enabled
void basIsEnabledSock()
{
    int ret;
    ret=isenabledsock();
    if (ret==-1) ePrintf( Runtime, "SDLengine socket Error \n");
    pushNumber( ret);
}

//_______________________________________________________________________________________________________________________

//sock=getfreesock()			: return the first free sock in sdlSocket array
void basGetFreeSock()
{
    int ret;
    ret=getfreesock();
    if (ret==-1) ePrintf( Runtime, "SDLengine socket Error \n");
    pushNumber( ret);
}
//_______________________________________________________________________________________________________________________

/*sock=OpenSock(port) 			: Server side socket sock is the stream. in sdlBasic there are 256 stream and \
					  sintax is very similar of file open close.*/
void basOpenSock()
{
    int port;
    int ret;

    port= popNumber();
    ret=opensock(port);
    if (ret==-1) ePrintf( Runtime, "SDLengine socket Error \n");
    pushNumber( ret);
}
//_______________________________________________________________________________________________________________________

//clientsock=AcceptSock(serversock)	: Accept the client connection
void basAcceptSock()
{
    int serversock;
    int ret;

    serversock= popNumber();
    ret=acceptsock(serversock);
    if (ret==-1) ePrintf( Runtime, "SDLengine socket Error \n");
    pushNumber( ret);
}

//_______________________________________________________________________________________________________________________

//IsServerReady(Sock)			: True/False if server is sending data    
void basIsServerReady()
{
    int sock;
    int ret;

    sock= popNumber();
    ret=isserverready(sock);
    if (ret==-1) ePrintf( Runtime, "SDLengine socket Error \n");
    pushNumber( ret);
}

//_______________________________________________________________________________________________________________________

//sock=ConnectSock(ServerName,port)	: client side socket connection
void basConnectSock()
{
    int port;
    char *servername;
    int ret;

    port= popNumber();
    servername=popString();
    ret=connectsock(servername,port);
    //if (ret==-1) ePrintf( Runtime, "SDLengine socket Error \n");
    pushNumber( ret);
}

//_______________________________________________________________________________________________________________________

//*ConnectionReadySock(sock)		: the server have accepted the connection
/*
void ConnectionReadySock()
{
    int sock;
    int ret;

    sock= popNumber();
    ret=connectionready(sock);
    if (ret==-1) ePrintf( Runtime, "SDLengine socket Error \n");
    pushNumber( ret);
}
*/
//_______________________________________________________________________________________________________________________

//IsClientReady(Sock)			: True/False if client is sending data
void basIsClientReady()
{
    int sock;
    int ret;

    sock= popNumber();
    ret=isclientready(sock);
    if (ret==-1) ePrintf( Runtime, "SDLengine socket Error \n");
    pushNumber( ret);
}
//_______________________________________________________________________________________________________________________

//CloseSock(sock)				: Close the socket connection. Works for client and server
void basCloseSock()
{
    int sock;
    int ret;

    sock= popNumber();
    ret=closesock(sock);
    if (ret==-1) ePrintf( Runtime, "SDLengine socket Error \n");
    pushNumber( ret);
}

//_______________________________________________________________________________________________________________________

//*PeekSock(Sock, NumBytes)		: Peek information coming from socket, but do not clear.
/*
void basPeekSock(void)
{
    int sock,numbytes;

    char *ret;

    numbytes= popNumber();
    sock= popNumber();
    ret=peeksock(sock,numbytes);
    if (ret==NULL) ePrintf( Runtime, "SDLengine socket Error \n");
    pushString(ret);
}
*/
//_______________________________________________________________________________________________________________________

//ReadSock(Sock, NumBytes)		: Read NumBytes
void basReadSock()
{
    int sock,numbytes;

    numbytes= popNumber();
    sock= popNumber();
    pushString(readsock(sock,numbytes));
}

//_______________________________________________________________________________________________________________________

//ReadByteSock(Sock)			: Read a single byte      
void basReadByteSock()
{
    int sock;
    int ret;

    sock= popNumber();
    ret=readbytesock(sock);
    if (ret==-1) ePrintf( Runtime, "SDLengine socket Error \n");
    pushNumber( ret);
}
//_______________________________________________________________________________________________________________________

//ReadLineSock(Sock)			: Read complete line
void basReadLineSock()
{
    int sock;

    sock= popNumber();
    pushString(readlinesock(sock));
}
//_______________________________________________________________________________________________________________________

//WriteSock(Sock, Message, NumBytes)	: Sends NumBytes from Message
void basWriteSock()
{
    int sock,numbytes;
    char *message;
    int ret;

    numbytes= popNumber();
    message=popString();
    sock= popNumber();
    ret=writesock(sock,message,numbytes);
    if (ret==-1) ePrintf( Runtime, "SDLengine socket Error \n");
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

//WriteByteSock(Sock, Byte)		: Sends a single byte
void basWriteByteSock()
{
    int sock;
    char byte;
    int ret;

    byte=popNumber();
    sock= popNumber();
    ret=writebytesock(sock,byte);
    if (ret==-1) ePrintf( Runtime, "SDLengine socket Error \n");
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

//WriteLineSock(Sock, Message)		: Send Message
void basWriteLineSock()
{
    int sock;
    char *message;
    int ret;

    message=popString();
    sock= popNumber();
    ret=writelinesock(sock,message);
    if (ret==-1) ePrintf( Runtime, "SDLengine socket Error \n");
    pushNumber(ret);
}
//_______________________________________________________________________________________________________________________

//getremoteip(sock)			: return the ip address of remote client connetted
void basGetRemoteIp()
{
    int sock;

    sock= popNumber();
    pushString(getremoteip(sock));
}
//_______________________________________________________________________________________________________________________

//getremoteport(sock)			: return the port address of remote client connetted
void basGetRemotePort()
{
    int sock;
    int ret;

    sock= popNumber();
    ret=getremoteport(sock);
    if (ret==-1) ePrintf( Runtime, "SDLengine socket Error \n");
    pushNumber( ret);
}

//_______________________________________________________________________________________________________________________

//getlocalip()				: return the local ip
void basGetLocalIp()
{
    pushString(getlocalip());
}

//_______________________________________________________________________________________________________________________
