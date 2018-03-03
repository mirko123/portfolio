using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Security.Permissions;
using Microsoft.Win32;

using System.Management;
using System.Runtime.InteropServices;

namespace Optimizer
{
    class InstalledPrograms
    {
        const string registry_key2 = @"SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall";
        public static void GetInstalledProgramsFromRegistry(RegistryView registryView,
             out List<string> DisplayName, out List<string> Location)
        {
            DisplayName = new List<string>();
            Location = new List<string>();
            using (RegistryKey key = RegistryKey.OpenBaseKey(RegistryHive.LocalMachine, registryView).OpenSubKey(registry_key2))
            {
                foreach (string subkey_name in key.GetSubKeyNames())
                {
                    using (RegistryKey subkey = key.OpenSubKey(subkey_name))
                    {
                        if (IsProgramVisible(subkey))
                        {
                            DisplayName.Add((string)subkey.GetValue("DisplayName"));
                            Location.Add((string)subkey.GetValue("InstallLocation"));
                        }
                    }
                }
            }
        }
        private static bool IsProgramVisible(RegistryKey subkey)
        {
            var name = (string)subkey.GetValue("DisplayName");
            var releaseType = (string)subkey.GetValue("ReleaseType");
            //var unistallString = (string)subkey.GetValue("UninstallString");
            var systemComponent = subkey.GetValue("SystemComponent");
            var parentName = (string)subkey.GetValue("ParentDisplayName");

            return
                !string.IsNullOrEmpty(name)
                && string.IsNullOrEmpty(releaseType)
                && string.IsNullOrEmpty(parentName)
                && (systemComponent == null);
        }
    }
}
