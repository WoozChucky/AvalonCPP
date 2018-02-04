using System;

namespace Avalon.Auth
{
    class Program
    {
        static void Main(string[] args)
        {
            var server = new Core.Network.Auth.AuthServer();

            while (server.IsRunning())
            {
                
            }
        }
    }
}
