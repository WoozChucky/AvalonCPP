using System.Net.Sockets;
using System.Threading;

namespace Avalon.Core.Network.Auth.Structs
{
    internal struct ThreadParams
    {
        public AutoResetEvent ThreadHandle;
        public Socket ClientSocket;
        public int ThreadIndex;
    }
}