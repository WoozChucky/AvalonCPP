namespace Avalon.Common.Model
{
    public sealed class AuthServerConfiguration
    {
        public string Address { get; set; }
        public int Port { get; set; }
        public int MaxThreads { get; set; }
        public int MaxQueuedConnections { get; set; }
        public int BufferSize { get; set; }
        public int ReadTimeout { get; set; }
    }
}