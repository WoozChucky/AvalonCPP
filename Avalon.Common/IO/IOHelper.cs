using System.IO;
using System.Text;
using Newtonsoft.Json;

namespace Avalon.Common.IO
{
    public static class IOHelper
    {
        public static T ToJSON<T>(string fileLocation)
        {
            if (File.Exists(fileLocation))
            {
                var contents = File.ReadAllText(fileLocation, Encoding.Unicode);
                return JsonConvert.DeserializeObject<T>(contents);
            }
            
            if (File.Exists($"{Directory.GetCurrentDirectory()}/{fileLocation}"))
            {
                var contents = File.ReadAllText($"{Directory.GetCurrentDirectory()}/{fileLocation}", Encoding.Unicode);
                return JsonConvert.DeserializeObject<T>(contents);
            }

            throw new IOException("File not found");
            
        }
    }
}