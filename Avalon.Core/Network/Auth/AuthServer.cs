using System;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using Avalon.Core.Network.Auth.Interfaces;

namespace Avalon.Core.Network.Auth
{

    internal struct ThreadParamStruct 
    {
        public AutoResetEvent ThreadHandle;
        public Socket ClientSocket;
        public int ThreadIndex;
    }

    public class AuthServer : IAuthServer
    {
        private const int Port = 27015;
        private const int MaxThreads = 20;//MAX number of threads, 2 for testing > threads connections
        private const int DataReadTimeout = 2000; //Miliseconds
        private const int MaxQueuedConnections = 20;
        private const int MaxBufferSize = 1024;

        private readonly WaitHandle[] _waitHandles;
        private readonly Socket _listenerSocket;
        private readonly Dictionary<IPEndPoint, Socket> _clientSockets;
        
        private bool _running;

        public AuthServer()
        {
            _waitHandles = new WaitHandle[MaxThreads];
            _clientSockets = new Dictionary<IPEndPoint, Socket>();

            for (var i = 0; i < MaxThreads; i++) {
                _waitHandles[i] = new AutoResetEvent(true); //Initialize threads initial state
            }

            _listenerSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            _listenerSocket.Bind(new IPEndPoint(0, Port));
            _listenerSocket.Listen(MaxQueuedConnections); // Maximum number of connections allowed to be in queue
            _running = true;
        }

        public bool IsRunning()
        {
            while (_running)
            {
                var clientSocket = _listenerSocket.Accept();
                var endpoint = clientSocket.RemoteEndPoint as IPEndPoint;
                
                _clientSockets.Add(endpoint, clientSocket);

                var availableThreadIndex = WaitHandle.WaitAny(_waitHandles);

                var threadParams = new ThreadParamStruct
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
        }

        public void ForceShutdown()
        {
            _clientSockets.Clear();
            _listenerSocket.Dispose();
            _running = false;
        }

        public void GracefullyShutdown()
        {
            ResetClients();
            _listenerSocket.Shutdown(SocketShutdown.Both);
            _listenerSocket.Dispose();
            _running = false;
        }

        private void HandleSocketConnection(object threadState)
        {
            var context = (ThreadParamStruct)threadState;

            var buffer = new byte[MaxBufferSize];

            var bytesReceived = context.ClientSocket.Receive(buffer);

            var dataReceived = Encoding.ASCII.GetString(buffer, 0, bytesReceived);
            
            Console.WriteLine($"Received -> {dataReceived}");
            
            Thread.Sleep(TimeSpan.FromSeconds(20));
            
            context.ThreadHandle.Set();
            
            Console.WriteLine("thread {0} finished", context.ThreadIndex);
        }
    }
}
