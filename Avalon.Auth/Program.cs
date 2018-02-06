using System;
using Avalon.Common.IO;
using Avalon.Common.Model;
using Avalon.Common.Utilities.Watcher;
using Avalon.Core.Network.Auth;
using Avalon.Core.Network.Auth.Interfaces;

namespace Avalon.Auth
{
    class Program
    {
        private static AuthServerConfiguration _serverConfiguration = null;

        private static IAuthServer _server;
        
        static void Main(string[] args)
        {
            _serverConfiguration = IOHelper.ToJSON<AuthServerConfiguration>(args[0]);
            
           _server = new AuthServer(_serverConfiguration);

            var configWatcher = new JSONFileWatcher<AuthServerConfiguration>(null, args[0])
            {
                AutoStart = true,
                Continuous = true,
                WatchCount = 1
            };
            configWatcher.OnJSONChange += (sender, evt) =>
            {
                if (evt.IsValid)
                {
                    _serverConfiguration = evt.Result;
                    _server.GracefullyShutdown();
                    _server = _server.ProvideConfiguration(_serverConfiguration);
                }
            };
            configWatcher.Watch();

            while (_server.IsRunning())
            {
                
            }
        }
    }
}
