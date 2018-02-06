using System;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using Avalon.Common.Model;
using Avalon.Core.Network.Auth.Interfaces;
using Avalon.Core.Network.Auth.Structs;

namespace Avalon.Core.Network.Auth
{

    public class AuthServer : IAuthServer
    {
        private readonly WaitHandle[] _waitHandles;
        private readonly Socket _listenerSocket;
        private readonly Dictionary<IPEndPoint, Socket> _clientSockets;
        private readonly AuthServerConfiguration _configuration;
        
        private bool _running;

        public AuthServer(AuthServerConfiguration configuration)
        {
            _configuration = configuration;
            
            _waitHandles = new WaitHandle[_configuration.MaxThreads];
            _clientSockets = new Dictionary<IPEndPoint, Socket>();

            for (var i = 0; i < _configuration.MaxThreads; i++) {
                _waitHandles[i] = new AutoResetEvent(true); //Initialize threads initial state
            }

            _listenerSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            _listenerSocket.Bind(new IPEndPoint(IPAddress.Parse(_configuration.Address), _configuration.Port));
            _listenerSocket.Listen(_configuration.MaxQueuedConnections); // Maximum number of connections allowed to be in queue
            _running = true;
            Console.WriteLine($"[AUTH] -> Listening at {_listenerSocket.LocalEndPoint as IPEndPoint}");
        }

        public bool IsRunning()
        {
            while (_running)
            {
                var clientSocket = _listenerSocket.Accept();
                var endpoint = clientSocket.RemoteEndPoint as IPEndPoint;
                
                var availableThreadIndex = WaitHandle.WaitAny(_waitHandles);
                
                _clientSockets.Add(endpoint, clientSocket);

                var threadParams = new ThreadParams
                {
                    ThreadHandle = (AutoResetEvent)_waitHandles[availableThreadIndex],
                    ClientSocket = clientSocket,
                    ThreadIndex = availableThreadIndex
                };

                ThreadPool.QueueUserWorkItem(HandleSocketConnection, threadParams);
            }

            return _running;
        }

        public void ResetClients()
        {
            foreach (var clientSocket in _clientSockets)
            {
                clientSocket.Value.Disconnect(false);
            }
            _clientSockets.Clear();
        }

        public void ForceShutdown()
        {
            _clientSockets.Clear();
            _listenerSocket.Close(0);
            _listenerSocket.Dispose();
            _running = false;
        }

        public void GracefullyShutdown()
        {
            ResetClients();
            //_listenerSocket.Close(0);
            _listenerSocket.Dispose();
            _running = false;
        }

        public IAuthServer ProvideConfiguration(AuthServerConfiguration configuration)
        {
             return new AuthServer(configuration);
        }

        private void DisconnectClient(IPEndPoint endpoint)
        {
            _clientSockets[endpoint].Disconnect(false);
            _clientSockets.Remove(endpoint);
        }

        private void HandleSocketConnection(object threadState)
        {
            var context = (ThreadParams)threadState;

            while (true)
            {
                var buffer = new byte[_configuration.BufferSize];

                var bytesReceived = context.ClientSocket.Receive(buffer);

                var dataReceived = Encoding.Unicode.GetString(buffer, 0, bytesReceived);
            
                Console.WriteLine($"[{context.ClientSocket.RemoteEndPoint as IPEndPoint}] Received -> {dataReceived}");

                context.ClientSocket.Send(buffer);
            
                if (dataReceived == "bye") break;
            }
            
            DisconnectClient(context.ClientSocket.RemoteEndPoint as IPEndPoint);

            context.ThreadHandle.Set(); //Let the ThreadPool know that this thread is ready to accept new jobs
            
            Console.WriteLine($"Thread {context.ThreadIndex} finished");
        }
    }
}
