using System;
using System.Net.Sockets;
using System.Text;

namespace Avalon.World
{
    class Program
    {
        static void Main(string[] args)
        {
            Socket s;
            s = new Socket(SocketType.Stream, ProtocolType.Tcp);
            s.Connect("127.0.0.1", 27015);

            //var buffer = new byte[1024];
            var buffer = Encoding.ASCII.GetBytes("Hi Nuno!");
            s.Send(buffer);
            
            s.Disconnect(false);
            
            Console.WriteLine("Hello World!");
        }
    }
}
