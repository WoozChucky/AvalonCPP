using System;
using System.IO;
using Avalon.Common.IO;
using Avalon.Common.Utilities.Watcher.Events;
using Avalon.Common.Utilities.Watcher.Interfaces;

namespace Avalon.Common.Utilities.Watcher
{
    public class JSONFileWatcher<T> : IFileWatcher
    {
        public int WatchCount { get; set; }
        public bool AutoStart { get; set; }
        public bool Continuous { get; set; }

        public event EventHandler<JSONWatcherEvents<T>> OnJSONChange;
        
        private string _fileName;
        private string _folder;
        private FileSystemWatcher _watcher;
        private bool _watching;
        private int _watchedCount;
        
        public JSONFileWatcher(string folder, string fileName)
        {
            Init(folder, fileName);
        }
        
        public JSONFileWatcher(string folder, string fileName, bool autoStart = false, bool continuous = true, int minWatchCount = 1)
        {
            Init(folder, fileName, autoStart, continuous, minWatchCount);
        }
        
        private void Init(string folder, string fileName, bool autoStart = false, bool continuous = true, int minWatchCount = 1)
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

            FireEvent();
        }

        private void FireEvent()
        {
            try
            {
                OnJSONChange?.Invoke(this, new JSONWatcherEvents<T>
                {
                    IsValid = true,
                    Result = IOHelper.ToJSON<T>(_fileName)
                });
            }
            catch (Exception)
            {
                OnJSONChange?.Invoke(this, new JSONWatcherEvents<T>
                {
                    IsValid = false,
                    Result = default(T)
                });
            }
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