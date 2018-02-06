using System;
using System.IO;
using Avalon.Common.Utilities.Watcher.Interfaces;

namespace Avalon.Common.Utilities.Watcher
{
    
    public class FileWatcher : IFileWatcher
    {
        
        private string _fileName;
        private string _folder;
        private FileSystemWatcher _watcher;
        private Action _callback;
        private bool _watching;
        private int _watchedCount;

        /// <inheritdoc />
        public bool AutoStart { get; set; }
        
        /// <inheritdoc />
        public int WatchCount { get; set; }
        
        /// <inheritdoc />
        public bool Continuous { get; set; }

        public FileWatcher(string folder, string fileName, Action callback)
        {
            Init(folder, fileName, callback);
        }
        
        public FileWatcher(string folder, string fileName, Action callback = null, bool autoStart = false, bool continuous = true, int minWatchCount = 1)
        {
            Init(folder, fileName, callback, autoStart, continuous, minWatchCount);
        }

        private void Init(string folder, string fileName, Action callback, bool autoStart = false, bool continuous = true, int minWatchCount = 1)
        {
            if (string.IsNullOrEmpty(folder) || (!Directory.Exists(folder)))
            {
                _folder = Directory.GetCurrentDirectory();
            }
            else
            {
                _folder = folder;
            }

            if (!File.Exists($"{_folder}/{fileName}"))
            {
                throw new ArgumentException("File not found!");
            }

            _watchedCount = 0;
            WatchCount = minWatchCount;
            Continuous = continuous;
            AutoStart = autoStart;
            _fileName = fileName;
            _callback = callback ?? throw new ArgumentNullException(nameof(callback));
            
            _watcher = new FileSystemWatcher
            {
                Path = _folder,
                NotifyFilter = NotifyFilters.LastWrite,
                Filter = $"{_fileName}",
                EnableRaisingEvents = true
            };
            

            if (AutoStart)
            {
                Watch();
            }
        }

        private void OnChanged(object sender, FileSystemEventArgs e)
        {
            _watchedCount++;

            if (_watchedCount < WatchCount) return;
            
            if (Continuous)
            {
                _watchedCount = 0;
            }
            else
            {
                _watcher.EnableRaisingEvents = false;
            }
            
            //var modifiedObj = JsonConvert.DeserializeObject<T>("");
            
            _callback();
        }


        public void Dispose()
        {
            _watcher?.Dispose();
        }

        public void Watch()
        {
            InternalWatch(AutoStart);
        }

        private void InternalWatch(bool autoStart)
        {
            if (autoStart)
            {
                _watching = true;
                _watcher.Changed += OnChanged;
            }
            else
            {
                if (_watching)
                {
                    throw new InvalidOperationException("File is already being watched.");
                }
                _watching = true;
                _watcher.Changed += OnChanged;
            }
        }
    }
}