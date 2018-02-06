using Avalon.Common.Model;

namespace Avalon.Core.Network.Auth.Interfaces
{
    public interface IAuthServer
    {
        bool IsRunning();
        void ResetClients();
        void ForceShutdown();
        void GracefullyShutdown();
        IAuthServer ProvideConfiguration(AuthServerConfiguration configuration);
    }
}