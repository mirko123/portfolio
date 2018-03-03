using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ServiceProcess;
using System.Diagnostics;
using System.Management;
using System.Threading;
using System.Reflection;
using System.Windows.Forms;

namespace Optimizer
{
    class GetProcess
    {
        public string[,] GetAllProcesses()
        {
            string wmiClass = "Win32_Process";
            string condition = "";
            string[] queryProperties = new string[] { "Name",
                "ProcessId", "Caption", "ExecutablePath", "CommandLine", "ParentProcessId"};
            SelectQuery wmiQuery = new SelectQuery(wmiClass, condition, queryProperties);
            ManagementScope scope = new System.Management.ManagementScope(@"\\.\root\CIMV2");

            ManagementObjectSearcher searcher = new ManagementObjectSearcher(scope, wmiQuery);
            ManagementObjectCollection runningProcesses = searcher.Get();

            Process[] prs = Process.GetProcesses();
            GetProcess processes = new GetProcess();

            int count = 0;
            string[,] str = new string[runningProcesses.Count, 5];
            foreach (ManagementObject obj in runningProcesses)
            {
                if (obj["Caption"] != null)
                {
                    str[count, 0] = obj["Name"].ToString();
                }
                else str[count, 0] = "---";
                if (obj["ExecutablePath"] != null)
                {
                    str[count, 1] = obj["ExecutablePath"].ToString();
                }
                else
                {
                    str[count, 1] = "---";
                }
                if (obj["ProcessId"] != null)
                {
                    str[count, 2] = obj["ProcessId"].ToString();
                }
                else
                {
                    str[count, 2] = "---";
                }
                str[count, 3] = obj["ParentProcessId"].ToString();
                for (int i = 0; i < prs.Length; i++)
                {
                    if (prs[i].MainWindowTitle.Length > 0 && 
                        obj["Name"].ToString() == prs[i].ProcessName.ToString() + ".exe")
                    {
                        str[count, 4] = prs[i].MainWindowTitle;
                        break;
                    }
                }
                count++;
            }
            return str;
        }
        public static void KillProcess(string name)
        {
            foreach(Process p in Process.GetProcesses())
            {
                if (name.ToLower() == p.ProcessName.ToLower())
                {
                    p.Kill();
                    break;
                }
            }
        }
    }
}
