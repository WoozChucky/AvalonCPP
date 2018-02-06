using System;

namespace Avalon.Common.Utilities.Watcher.Events
{
    public class JSONWatcherEvents<T> : EventArgs
    {
        public bool IsValid { get; set; }
        public T Result { get; set; }
    }
}