using System;

namespace Avalon.Common.Utilities.Watcher.Interfaces
{
    public interface IFileWatcher : IDisposable
    {
           
        void Watch();
        
        /// <summary>
        /// Number of times that the ´watch´ has to occur before the <see cref="Action"/> callback fires.
        /// </summary>
        int WatchCount { get; set; }
        
        /// <summary>
        /// Sets/gets if the watcher starts automatically upon initialization
        /// </summary>
        bool AutoStart { get; set; }
        
        /// <summary>
        /// Set/gets if the watcher should continue runing after hitting the <see cref="WatchCount"/>
        /// </summary>
        bool Continuous { get; set; }
    }
}