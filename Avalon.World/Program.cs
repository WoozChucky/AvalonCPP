using System;
using System.Net.Sockets;
using System.Text;
using Avalon.Common.Utilities.Watcher;
using Avalon.Common.Utilities.Watcher.Events;

namespace Avalon.World
{
    class Program
    {
        private static bool keepRunning = true;
        private static DateTimeOffset lastBreak = DateTimeOffset.MinValue;
        
        static void Main(string[] args)
        {
           Console.CancelKeyPress += ConsoleOnCancelKeyPress;   

            var watcher = new FileWatcher(null, "settings.json", () => { Console.WriteLine("Callback"); }, continuous: false);
            watcher.Watch();

            while (keepRunning)
            {
                
            }
            
            
            var s = new Socket(SocketType.Stream, ProtocolType.Tcp);
            s.Connect("127.0.0.1", 27015);

            while (true)
            {
                var lineRead = Console.ReadLine();
                //var buffer = new byte[1024];
                var buffer = Encoding.Unicode.GetBytes(lineRead);
                s.Send(buffer);
            
                //s.Disconnect(false);
            
                
            }

        }

        private static void ConsoleOnCancelKeyPress(object sender, ConsoleCancelEventArgs e)
        {
            e.Cancel = true;
            Console.WriteLine("CTRL + C Pressed");
        }
    }
}
