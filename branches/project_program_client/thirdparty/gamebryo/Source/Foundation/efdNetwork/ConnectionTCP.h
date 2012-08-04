// EMERGENT GAME TECHNOLOGIES PROPRIETARY INFORMATION
//
// This software is supplied under the terms of a license agreement or
// nondisclosure agreement with Emergent Game Technologies and may not 
// be copied or disclosed except in accordance with the terms of that 
// agreement.
//
//      Copyright (c) 1996-2009 Emergent Game Technologies.
//      All Rights Reserved.
//
// Emergent Game Technologies, Calabasas, CA 91302
// http://www.emergent.net

#pragma once
#ifndef EE_CONNECTIONTCP_H
#define EE_CONNECTIONTCP_H

#include <efdNetwork/IConnection.h>
#include <efdNetwork/TCPSocket.h>

namespace efd
{
class EnvelopeMessage;

/**
A wrapper for data sent via the NetTransportTCP transport.
*/
class ConnectionTCP : public efd::IConnection
{
public:
    EE_DECLARE_CONCRETE_REFCOUNT;

    enum ConnectionState
    {
        EE_CONN_CONNECTION_FAILED = -1,
        EE_CONN_NOT_CONNECTED,
        EE_CONN_ACCEPTED,
        EE_CONN_SEND_VERSIONS,
        EE_CONN_RECEIVE_VERSIONS,
        EE_CONN_CONNECTED
    };

    /// @name Construction and Destruction
    //@{
public:
    ConnectionTCP(const ConnectionTCP& rhs, ConnectionID remoteConnectionID);
    ConnectionTCP(
        MessageFactory* pMessageFactory, 
        QualityOfService qos, 
        TCPSocket* pTCPSocket, 
        INetCallback* pMessageCallback, 
        bool incomingConnection);

    ConnectionTCP(
        MessageFactory* pMessageFactory, 
        QualityOfService qos, 
        INetCallback* pMessageCallback, 
        INetCallback* pConnectionCallback);

    /// Virtual destructor
    virtual ~ConnectionTCP();
    //@}

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual efd::QualityOfService GetTransportType() { return m_qos; }

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual bool IsValid();

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual efd::SInt32 ReceiveMessage(
        EnvelopeMessagePtr& spEnvelopeMessage,
        ConnectionID& remoteConnectionID);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual efd::SInt32 SendMessages();

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual efd::SInt32 CompleteConnection();

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual ConnectionID GetRemoteConnectionID() const;

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual bool Send(EnvelopeMessage *pMessage, const ConnectionID& cid);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void Close();

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void SetConnectionCallback(INetCallback* pConnectionCallback);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual INetCallback* GetConnectionCallback();

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void SetMessageCallback( INetCallback* pMessageCallback );

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual INetCallback* GetMessageCallback();

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual void RemoveCallback(
        INetCallback* pCallbackToRemove,
        INetCallback* pReplacementCallback);

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual NetMessagePtr GetStatusMessage();

    // Overridden virtual functions inherit base documentation and thus are not documented here.
    virtual IConnectionPtr Accept();

    /**
        Factory a ConnectionTCP, bind to a port and listen for incoming connections

        @param pMessageFactory Pointer to a MessageFactory.
        @param qos Quality of service to use.
        @param portListen port to bind and listen for incoming connections on
        @param pMessageCallback Callback object to deliver messages on.
        @param pConnectionCallback callback to receive connection notifications
    */ 
    static efd::SmartPointer< ConnectionTCP > Listen(
        MessageFactory* pMessageFactory,
        efd::QualityOfService qos,
        efd::UInt16 portListen, 
        INetCallback* pMessageCallback, 
        INetCallback* pConnectionCallback);

    /**
        Factory a ConnectionTCP, use it to attempt to connect to a server
        @param pMessageFactory Pointer to a MessageFactory.
        @param qos Quality of service to use.
        @param strServerAddress address of the server to connect to
        @param portServer port of the server to connect to
        @param pMessageCallback callback object to deliver messages to
        @param pConnectionCallback callback object to report connection status events to
    */
    static efd::SmartPointer< ConnectionTCP > Connect(
        MessageFactory* pMessageFactory,
        efd::QualityOfService qos,
        const efd::utf8string& strServerAddress,
        efd::UInt16 portServer,
        INetCallback* pMessageCallback,
        INetCallback* pConnectionCallback);

    /**
        Called when a message of type kMSGID_UnreliableVersion is received.  Validates the 
        version numbers and sends a response if required.  Completes the connection if pending.
        versionConnectionID contains the ConnectionID this version message was targeted at.
    */
    virtual efd::SInt32 ReceiveVersions(
        efd::EnvelopeMessage* pEnvelopeMessage, 
        ConnectionID& versionConnectionID);


    /**
        returns true if this is a listening connection
    */
    bool IsListening(){ return m_isListening; }

    /**
        returns true if this is an incoming connection
    */
    bool IsIncomingConnection() { return m_isIncomingConnection; }

protected:

    /// The version of the ConnectionTCP. Used to ensure compatibility at the transport layer.
    static const efd::UInt32 ms_numVersions;
    static const efd::utf8string ms_pVersionName;
    static const efd::utf8string ms_pVersionValue;

    /**
        Receive a DataStream from the network
        @param spStream stream to receive
        @param senderConnectionID Senders connection id.
    */
    virtual efd::SInt32 ReceiveStream(DataStreamPtr& spStream, ConnectionID& senderConnectionID);

    /// Returns true if the version has been checked for this data.
    virtual bool VersionChecked();

    /// Validate the data contained in the given stream is compatible with this TCP data.
    virtual bool ValidateVersions(efd::DataStream* pStream, ConnectionID& versionConnectionID);

    /**
        Sends a version packet to be validated at the receiving end.
        The version packet consists of an unsigned integer that specifies the number 
        of strings to follow.  After it the first utf8string for the version name and 
        then the first utf8string for the version value.  All the other version string 
        pairs follow in succession. Of course the underlying TCP code send the total 
        length of the version packet before any data.
    */
    virtual efd::SInt32 SendVersions(bool needResponse, const ConnectionID& responseConnectionID);

    /**
        Attempts to receive versions.  If a version stream has been received, it is returned in 
        the spStream parameter and a positive value is returned.  If no stream has yet been
        received, returns 0.  Returns a negative value if an error occurred.
    */
    virtual efd::SInt32 ReceiveVersions(ConnectionID& senderConnectionID);

    /// @cond EMERGENT_INTERNAL

    class MessageToSend
    {
    public:
        MessageToSend()
        {
        }
        MessageToSend(
            EnvelopeMessage* pMessageToSend,
            DataStream* pDataStreamToSend,
            const ConnectionID& destCid)
            : m_spMessageToSend(pMessageToSend)
            , m_spDataStreamToSend(pDataStreamToSend)
            , m_destCid(destCid)
        {
        }
        EnvelopeMessagePtr m_spMessageToSend;
        DataStreamPtr m_spDataStreamToSend;
        ConnectionID m_destCid;
    };

    virtual efd::SInt32 InternalSend(MessageToSend& messageToSend);

    // do not use default constructor
    ConnectionTCP(){};
    //! The TCPSocket
    efd::TCPSocketPtr m_spTCPSocket;
    //! True if the transport has passed its version check
    bool m_versionsValid;

    INetCallback* m_pMessageCallback;
    INetCallback* m_pConnectionCallback;

    typedef efd::list< MessageToSend > MessageList;
    MessageList m_messageQueue;

    /// Hold versions so that we can attempt to send versions over multiple ticks.
    DataStreamPtr m_spSendVersionStream;

    /// True if versions have been successfully sent.
    bool m_versionsSent;

    /// Keep track of the state of this connection.
    ConnectionState m_connectionState;

    /// True if this connection was created by Accept
    bool m_isIncomingConnection;

    /// The quality of service to report this connection as
    efd::QualityOfService m_qos;

    /// A factory that can be used to create messages of registered types
    MessageFactory* m_pMessageFactory;

    /// the ConnectionID of the other end of the connection.  If TCP, this is always set to 
    /// m_spTCPSocket->GetConnectionID. If UDP listening set to m_spTCPSocket->GetConnectionID
    /// If UDP incoming, set to the other end of the incoming connection and m_spTCPSocket is 
    /// the listening socket
    ConnectionID m_remoteConnectionID;

    /// True if this connection is listening for incoming connections
    bool m_isListening;

    /// @endcond
};

/// A smart pointer (reference counting, self deleting pointer) for the ConnectionTCP class.
typedef efd::SmartPointer<ConnectionTCP> ConnectionTCPPtr;
} //End namespace efd

#include <efdNetwork/ConnectionTCP.inl>

#endif //EE_CONNECTIONTCP_H
