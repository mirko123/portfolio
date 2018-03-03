using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.ServiceProcess;
using System.Management;
using System.Security.Permissions;
using System.Diagnostics;
using System.Globalization;
using System.Resources;
using Microsoft.Win32;


namespace Optimizer
{
    public partial class Form1 : Form
    {
        ResourceManager res_man;    // declare Resource manager to access to specific cultureinfo
        CultureInfo cul;            //declare culture info
        Dictionary<string, bool> dict = new Dictionary<string, bool>();
        List<string> AllLocation;
        List<string> AllDisplayName;
        string[,] ExcelMatrix;
        OpenFileDialog ofd = new OpenFileDialog();
        RegistryKey startupKey;
        CreateExcelDoc newDoc;
        string[,] SProcess;
        GetProcess process;
        ManagementEventWatcher startWatch;
        ManagementEventWatcher stopWatch;
        const string runKey = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";

        public Form1()
        {
            InitializeComponent();
        }
        private void Form1_Load(object sender, EventArgs e)
        {
            startWatch = new ManagementEventWatcher(
              new WqlEventQuery("SELECT * FROM Win32_ProcessStartTrace"));
            startWatch.EventArrived += new EventArrivedEventHandler(startWatch_EventArrived);
            startWatch.Start();
            stopWatch = new ManagementEventWatcher(
              new WqlEventQuery("SELECT * FROM Win32_ProcessStopTrace"));
            stopWatch.EventArrived += new EventArrivedEventHandler(stopWatch_EventArrived);
            stopWatch.Start();

            MenuStripLanguageBulgarian.Enabled = false;//default language is BG
            MenuStripLanguageEnglish.Enabled = true; 

            res_man = new ResourceManager("Optimizer.Resource.Res", typeof(Form1).Assembly);
            switch_language();

            string Today = DateTime.Now.ToShortDateString();
            List<string> DisplayName;
            List<string> DisplayName64;
            List<string> Location;
            List<string> Location64;
            InstalledPrograms.GetInstalledProgramsFromRegistry(RegistryView.Registry32, out DisplayName, out Location);
            InstalledPrograms.GetInstalledProgramsFromRegistry(RegistryView.Registry64, out DisplayName64, out Location64);
            DisplayName.AddRange(DisplayName64);
            AllDisplayName = DisplayName;
            Location.AddRange(Location64);
            AllLocation = Location;

            newDoc = new CreateExcelDoc("Table.xls");//Create excel doc
            ExcelMatrix = newDoc.ReadMatrix();
            if (ExcelMatrix.GetLength(0) <= 1)
            {
                newDoc.AddArrayInCol(0, 1, DisplayName.ToArray());
                newDoc.NewDate(Today, DisplayName.Count + 1);
                ExcelMatrix = newDoc.ReadMatrix();
            }
            else
            {
                if (ExcelMatrix.GetLength(0) == DisplayName.Count + 1)
                {
                    newDoc.NewDate(Today, DisplayName.Count + 1);
                }
            }


            string[,] newExcelMatrix = new string[AllDisplayName.Count() + 1, 8];
            Array.Copy(ExcelMatrix, newExcelMatrix, 8);
            for (int i = 0; i < AllDisplayName.Count(); i++)
            {
                newExcelMatrix[i + 1, 0] = AllDisplayName[i];

                for (int p = 0; p < ExcelMatrix.GetLength(0); p++)
                {
                    if (newExcelMatrix[i + 1, 0] == ExcelMatrix[p, 0])
                    {
                        newExcelMatrix[i + 1, 1] = ExcelMatrix[p, 1];
                        newExcelMatrix[i + 1, 2] = ExcelMatrix[p, 2];
                        newExcelMatrix[i + 1, 3] = ExcelMatrix[p, 3];
                        newExcelMatrix[i + 1, 4] = ExcelMatrix[p, 4];
                        newExcelMatrix[i + 1, 5] = ExcelMatrix[p, 5];
                        newExcelMatrix[i + 1, 6] = ExcelMatrix[p, 6];
                        newExcelMatrix[i + 1, 7] = ExcelMatrix[p, 7];
                        break;
                    }
                    else if (p == (ExcelMatrix.GetLength(0) - 1))
                    {
                        newExcelMatrix[i + 1, 1] = "0";
                        newExcelMatrix[i + 1, 2] = "0";
                        newExcelMatrix[i + 1, 3] = "0";
                        newExcelMatrix[i + 1, 4] = "0";
                        newExcelMatrix[i + 1, 5] = "0";
                        newExcelMatrix[i + 1, 6] = "0";
                        newExcelMatrix[i + 1, 7] = "0";
                    }
                }
            }
            ExcelMatrix = newExcelMatrix;

            process = new GetProcess();
            int ProcesCount = process.GetAllProcesses().GetLength(0);
            SProcess = process.GetAllProcesses();
            ListView1();
            ListView2();
            ListView3(ExcelMatrix);
            ListView4();
        }

        public string[] GetStartupType()
        {
            string wmiClass = "Win32_Service";
            string condition = "";
            string[] queryProperties = new string[] { "StartMode" };
            SelectQuery wmiQuery = new SelectQuery(wmiClass, condition, queryProperties);
            ManagementScope scope = new System.Management.ManagementScope(@"\\.\root\CIMV2");
            
            ManagementObjectSearcher searcher = new ManagementObjectSearcher(scope, wmiQuery);
            ManagementObjectCollection runningProcesses = searcher.Get();

            int i = 0;
            string[] str = new string[runningProcesses.Count];
            foreach (ManagementObject obj in runningProcesses)
            {
                if (obj["StartMode"] != null)
                {
                    str[i] = obj["StartMode"].ToString();
                }
                else str[i] = "---";
                i++;
            }
            return str;
        }
        private void ListView1()
        {

       /*     ManagementClass mc = new ManagementClass("Win32_Service");
            List<string> SPath = new List<string>();
            foreach (ManagementObject mo in mc.GetInstances())
            {
                SPath.Add(mo.GetPropertyValue("PathName").ToString());
            }*/

            string[] StartUpType = new string[GetStartupType().Length];
            StartUpType = GetStartupType();
            listViewSer.Items.Clear();
            ServiceController[] services = ServiceController.GetServices();
            for (int i = 0; i < services.Length; i++)
            {
                if (services[i].DisplayName != null)
                {
                    ListViewItem newItem = new ListViewItem(services[i].ServiceName);
                    newItem.SubItems.Add(services[i].Status.ToString());
                    newItem.SubItems.Add(services[i].DisplayName.ToString());
                    newItem.SubItems.Add(StartUpType[i]);
                 //   if (i < SPath.Count) newItem.SubItems.Add(SPath[i]);
                  //  else newItem.SubItems.Add("---");
                    listViewSer.Items.Add(newItem);
                }
            }
        //    MessageBox.Show(SPath.Count.ToString());
         //   MessageBox.Show(services.Length.ToString());


            int col1 = 2, col2 = 1, col3 = 2, col4 = 1, col5 = 2;
            float coef = listViewSer.Width / (col1 + col2 + col3 + col4 + col5);
            double scroll = ((double)100 / 693) * 16 / 5;
            int width = Convert.ToInt32(scroll / 100 * listViewSer.Width);
            listViewSer.Columns[0].Width = Convert.ToInt32(col1 * coef) - width;
            listViewSer.Columns[1].Width = Convert.ToInt32(col2 * coef) - width;
            listViewSer.Columns[2].Width = Convert.ToInt32(col3 * coef) - width;
            listViewSer.Columns[3].Width = Convert.ToInt32(col4 * coef) - width;
            listViewSer.Columns[4].Width = Convert.ToInt32(col5 * coef) - width - 2;

        }

        private void ListView2()
        {
            listViewProc.Items.Clear();
            GetProcess processes = new GetProcess();
            string[,] SProcess = processes.GetAllProcesses();
            for (int row = 0; row < SProcess.GetLength(0); row++)
            {
                ListViewItem newItem = new ListViewItem(SProcess[row, 0]);
                newItem.SubItems.Add(SProcess[row, 1]);
                newItem.SubItems.Add(SProcess[row, 2]);
                for (int p = 0; p < SProcess.GetLength(0); p++)
                {
                    if (SProcess[row, 3] == SProcess[p, 2])
                    {
                        newItem.SubItems.Add(SProcess[p, 0]);
                        break;
                    }
                    else if (p == SProcess.GetLength(0) - 1)
                        newItem.SubItems.Add(SProcess[row, 3]);
                }
                newItem.SubItems.Add(SProcess[row, 4]);
                listViewProc.Items.Add(newItem);
            }/*
            int i = 0;
            foreach (Process process in Process.GetProcesses())
            {
                ListViewItem newItem = new ListViewItem(process.ProcessName.ToString());
                newItem.SubItems.Add(process.Id.ToString());
              //  newItem.SubItems.Add(SProcess[i, 3]);
                newItem.SubItems.Add(i.ToString());
             //   MessageBox.Show(GetProcess.GetParentProcess(process.Id).ToString());
              //  newItem.SubItems.Add(
              //      GetProcess.GetProcessOwner(process.ProcessName.ToString()));
                listViewProc.Items.Add(newItem);
                i++;
            }*/
            int col1 = 2, col2 = 3, col3 = 2, col4 = 2, col5 = 2;
            double scroll = ((double)100 / 693) * 16 / 5;
            float coef = listViewProc.Width / (col1 + col2 + col3 + col4 + col5);
            int width = Convert.ToInt32(scroll / 100 * listViewProc.Width) + 1;
            listViewProc.Columns[0].Width = Convert.ToInt32(col1 * coef) - width;
            listViewProc.Columns[1].Width = Convert.ToInt32(col2 * coef) - width;
            listViewProc.Columns[2].Width = Convert.ToInt32(col3 * coef) - width;
            listViewProc.Columns[3].Width = Convert.ToInt32(col4 * coef) - width;
            listViewProc.Columns[4].Width = Convert.ToInt32(col5 * coef) - width - 1;
        }

        private void ListView3(string[,] Matrix)
        {
            listViewTable.Items.Clear();
            for (int i = 1; i < 8; i++)
            {
                if (Matrix[0, i] != "0") listViewTable.Columns[i].Text = Matrix[0, i];
                else listViewTable.Columns[i].Text = 
                    res_man.GetString("day", cul)+" "+(8-i).ToString();
            }
            for (int i = 1; i < Matrix.GetLength(0); i++)
            {
                ListViewItem newItem = new ListViewItem(Matrix[i, 0]);
                newItem.SubItems.Add(Matrix[i, 1]);
                newItem.SubItems.Add(Matrix[i, 2]);
                newItem.SubItems.Add(Matrix[i, 3]);
                newItem.SubItems.Add(Matrix[i, 4]);
                newItem.SubItems.Add(Matrix[i, 5]);
                newItem.SubItems.Add(Matrix[i, 6]);
                newItem.SubItems.Add(Matrix[i, 7]);
                double average = (double)(Convert.ToInt32(Matrix[i, 1])+Convert.ToInt32(Matrix[i, 2])
                    + Convert.ToInt32(Matrix[i, 3]) + Convert.ToInt32(Matrix[i, 4])
                    + Convert.ToInt32(Matrix[i, 5]) + Convert.ToInt32(Matrix[i, 6])
                    + Convert.ToInt32(Matrix[i, 7])) / 7;
                newItem.SubItems.Add(Math.Round(average, 2).ToString());
                listViewTable.Items.Add(newItem);
            }
            int col1 = 3, col2 = 2, col3 = 2, col4 = 2,
                col5 = 2, col6 = 2, col7 = 2, col8 = 2, col9 = 2;
            double scroll = ((double)100 / 693) * 16 / 4;
            float coef = listViewTable.Width / (col1 + col2
                + col3 + col4 + col5 + col6 + col7 + col8 + col9);
            int width = Convert.ToInt32(scroll / 100 * listViewTable.Width / 8);
            listViewTable.Columns[0].Width = Convert.ToInt32(col1 * coef) - width;
            listViewTable.Columns[1].Width = Convert.ToInt32(col2 * coef) - width;
            listViewTable.Columns[2].Width = Convert.ToInt32(col3 * coef) - width;
            listViewTable.Columns[3].Width = Convert.ToInt32(col4 * coef) - width;
            listViewTable.Columns[4].Width = Convert.ToInt32(col5 * coef) - width;
            listViewTable.Columns[5].Width = Convert.ToInt32(col6 * coef) - width;
            listViewTable.Columns[6].Width = Convert.ToInt32(col7 * coef) - width;
            listViewTable.Columns[7].Width = Convert.ToInt32(col8 * coef) - width;
            listViewTable.Columns[7].Width = Convert.ToInt32(col9 * coef) - width;
        }

        private void ListView4()
        {
            listViewSUP.Items.Clear();

            ManagementClass cls = new ManagementClass("Win32_StartupCommand");
            ManagementObjectCollection coll = cls.GetInstances();
            List<string> items = new List<string>();

            foreach (ManagementObject obj in coll)
            {
                String Name = obj["Name"].ToString();
                String Command = obj["Command"].ToString();
                String Description = obj["Description"].ToString();
                String Location = obj["Location"].ToString();
                String User = obj["User"].ToString();

                ListViewItem newItem = new ListViewItem(Name);
                newItem.SubItems.Add(Command);
                newItem.SubItems.Add(Description);
                newItem.SubItems.Add(Location);
                newItem.SubItems.Add(User);
                listViewSUP.Items.Add(newItem);
            }
            int col1 = 1, col2 = 1, col3 = 1, col4 = 1, col5 = 1;
            double scroll = ((double)100 / 693) * 16 / 4;
            float coef = listViewSUP.Width / (col1 + col2 + col3 + col4 + col5);
            int width = Convert.ToInt32(scroll / 100 * listViewSUP.Width);
            listViewSUP.Columns[0].Width = Convert.ToInt32(col1 * coef);
            listViewSUP.Columns[1].Width = Convert.ToInt32(col2 * coef);
            listViewSUP.Columns[2].Width = Convert.ToInt32(col5 * coef);
            listViewSUP.Columns[3].Width = Convert.ToInt32(col3 * coef) - 2;
            listViewSUP.Columns[4].Width = Convert.ToInt32(col4 * coef) - 2;
        }

        private void notifyIcon1_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            this.Show();
        }

        private void NotifyMenuShow_Click(object sender, EventArgs e)
        {
            this.Show();
        }

        private void NotifyMenuClose_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }
        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            newDoc.AddMatrix(ExcelMatrix);
            if (MessageBox.Show(res_man.GetString("exit_text_string", cul), "Close Application",
                MessageBoxButtons.YesNo) == DialogResult.Yes)
            {
                //  MessageBox.Show("", "Application Closed!", MessageBoxButtons.OK);
            }
            else
            {
                e.Cancel = true;
                this.Hide();
            }
            startWatch.Stop();
            stopWatch.Stop();
        }

        private void ServicesMenuStart_Click(object sender, EventArgs e)
        {
            ServiceController sc = new ServiceController(
                listViewSer.SelectedItems[0].SubItems[0].Text);
            sc.Start();
            sc.Refresh();
            ListView1();
        }

        private void ServicesMenuStop_Click(object sender, EventArgs e)
        {
            ServiceController sc = new ServiceController(
                listViewSer.SelectedItems[0].SubItems[0].Text);
            sc.Stop();
            sc.Refresh();
            ListView1();
        }

        private void ServicesMenu_Opening(object sender, CancelEventArgs e)
        {
            if (listViewSer.SelectedItems.Count != 0)
            {
                int index = listViewSer.SelectedItems[0].Index;
                ServiceController[] services = ServiceController.GetServices();
                if (services[index].Status == ServiceControllerStatus.Running)
                {
                    ServicesContextMenu.Items[0].Enabled = false;
                    ServicesContextMenu.Items[1].Enabled = true;
                }
                else if (services[index].Status == ServiceControllerStatus.Stopped)
                {
                    ServicesContextMenu.Items[0].Enabled = true;
                    ServicesContextMenu.Items[1].Enabled = false;
                }
                if (listViewSer.Items[index].SubItems[3].Text == "Auto")
                {
                    Automatic.Enabled = false;
                    Manual.Enabled = true;
                    Disable.Enabled = true;
                }
                else if (listViewSer.Items[index].SubItems[3].Text == "Manual")
                {
                    Automatic.Enabled = true;
                    Manual.Enabled = false;
                    Disable.Enabled = true;
                }
                else if (listViewSer.Items[index].SubItems[3].Text == "Disabled")
                {
                    Automatic.Enabled = true;
                    Manual.Enabled = true;
                    Disable.Enabled = false;
                }
            }
            else e.Cancel = true;
        }

        private void ServicesMenuStartModeAuto_Click(object sender, EventArgs e)
        {
            ServiceStartModeUpdate(listViewSer.SelectedItems[0].SubItems[0].Text, "Automatic");
            ListView1();
        }

        private void ServicesMenuStartModeManual_Click(object sender, EventArgs e)
        {
            ServiceStartModeUpdate(listViewSer.SelectedItems[0].SubItems[0].Text, "Manual");
            ListView1();
        }

        private void ServicesMenuStartModeDisable_Click(object sender, EventArgs e)
        {
            ServiceStartModeUpdate(listViewSer.SelectedItems[0].SubItems[0].Text, "Disabled");
            ListView1();
        }
        public void ServiceStartModeUpdate(string serviceName, string startMode)
        {
            string filter =
                String.Format("SELECT * FROM Win32_Service WHERE Name = '{0}'", serviceName);
            ManagementObjectSearcher query = new ManagementObjectSearcher(filter);
            if (query != null)
            {
                ManagementObjectCollection services = query.Get();

                foreach (ManagementObject service in services)
                {
                    ManagementBaseObject inParams =
                        service.GetMethodParameters("ChangeStartMode");
                    inParams["startmode"] = startMode;

                    ManagementBaseObject outParams =
                        service.InvokeMethod("ChangeStartMode", inParams, null);
                }
            }
        }

        private void ProcessesContextMenu_Opening(object sender, CancelEventArgs e)
        {
            if (listViewProc.SelectedItems.Count == 0)
                e.Cancel = true;
        }

        private void ProcessesMenuKillProcess_Click(object sender, EventArgs e)
        {
            string name = listViewProc.SelectedItems[0].SubItems[0].Text;
            GetProcess.KillProcess(name.Remove(name.Length - 4));
            ListView2();
        }

        private void switch_language()
        {
            if (MenuStripLanguageBulgarian.Enabled == false)          //in english
            {
                cul = CultureInfo.CreateSpecificCulture("bg");        //create culture for english
            }
            else
            {
                cul = CultureInfo.CreateSpecificCulture("en");        //create culture for bg
            }

            PageSName.Text = res_man.GetString("Name", cul);
            PageSStatus.Text = res_man.GetString("Status", cul);
            PageSDescription.Text = res_man.GetString("Description", cul);
            PageSStartMode.Text = res_man.GetString("Start Mode", cul);

            PagePName.Text = res_man.GetString("Name", cul);
            PagePLocation.Text = res_man.GetString("Location", cul);
            PagePProcessID.Text = res_man.GetString("Process ID", cul);
            PagePParentProcess.Text = res_man.GetString("Parent Process", cul);
            PagePTitle.Text = res_man.GetString("Title", cul);

            PageTProgram.Text = res_man.GetString("Program", cul);

            PageSTName.Text = res_man.GetString("Name", cul);
            PageSTCommand.Text = res_man.GetString("Command", cul);
            PageSTDescription.Text = res_man.GetString("Description", cul);
            PageSTLocation.Text = res_man.GetString("Location", cul);
            PageSTUser.Text = res_man.GetString("User", cul);

            languageToolStripMenuItem.Text = res_man.GetString("Language", cul);
            MenuStripLanguageEnglish.Text = res_man.GetString("English", cul);
            MenuStripLanguageBulgarian.Text = res_man.GetString("Bulgarian", cul);

            fileToolStripMenuItem.Text = res_man.GetString("File_menu", cul);
            MenuStripFileExit.Text = res_man.GetString("Exit_menu", cul);
            MenuStripFileHidden.Text = res_man.GetString("Hidden_menu", cul);
            
            tabPageServices.Text = res_man.GetString("Services", cul);
            tabPageProcess.Text = res_man.GetString("Process", cul);
            tabPageTable.Text = res_man.GetString("Table", cul);
            tabPageSTPrograms.Text = res_man.GetString("Start-up programs", cul);

            NotifyMenuShow.Text = res_man.GetString("Show", cul);
            NotifyMenuClose.Text = res_man.GetString("Close", cul);

            SMenuStart.Text = res_man.GetString("start", cul);
            SMenuStop.Text = res_man.GetString("stop", cul);
            SMenuStartUpMode.Text = res_man.GetString("StartUp Mode", cul);
            Automatic.Text = res_man.GetString("Automatic", cul);
            Manual.Text = res_man.GetString("Manual", cul);
            Disable.Text = res_man.GetString("Disable", cul);
            helpToolStripMenuItem.Text = res_man.GetString("Help", cul);
            MenuStripHelpAboutServices.Text = res_man.GetString("About Services", cul);
            MenuStripHelpAboutProcesses.Text = res_man.GetString("About Processes", cul);

            labelManual.Text = res_man.GetString("Manual_string", cul);
            labelAutomatic.Text = res_man.GetString("Automatic_string", cul);
            labelAutomaticD.Text = res_man.GetString("Automatic(dsp)_string", cul);
            labelDisable.Text = res_man.GetString("Disabled_string", cul);
            labelAddSTProgram.Text = res_man.GetString("Add startup program", cul);
            buttonAddST.Text = res_man.GetString("Browse", cul);
            StartupProgramsDisable.Text = res_man.GetString("Disable", cul);

            PMenuKillProcess.Text = res_man.GetString("Kill Process", cul);
            PMenuInfo.Text = res_man.GetString("Info", cul);

        }

        private void MenuStripLanguageEnglish_Click(object sender, EventArgs e)
        {
            MenuStripLanguageBulgarian.Enabled = true;
            MenuStripLanguageEnglish.Enabled = false;        
            switch_language();
        }

        private void MenuStripLanguageBulgarian_Click(object sender, EventArgs e)
        {
            MenuStripLanguageBulgarian.Enabled = false;
            MenuStripLanguageEnglish.Enabled = true;
            switch_language();
        }

        private void MenuStripFileHidden_Click(object sender, EventArgs e)
        {
            this.Hide();
        }

        private void MenuStripFileExit_Click(object sender, EventArgs e)
        {
            Application.Exit();
           // this.Dispose();
        }

        private void MenuStripHelpAboutServices_Click(object sender, EventArgs e)
        {
            System.Diagnostics.Process.
                Start("http://www.blackviper.com/windows-services/");
            System.Diagnostics.Process.
                Start("http://windows7bg.com/index.php?/topic/13-няколко-трика-за-оптимизация/");
            System.Diagnostics.Process.
                Start("http://www.blackviper.com/service-configurations/black-vipers-windows-7-service-pack-1-service-configurations/");
        }

        private void MenuStripHelpAboutProcesses_Click(object sender, EventArgs e)
        {
            System.Diagnostics.Process.Start(
            "http://flames.illusion-net.com/Drugi%20Programi/System%20Proces/Sys%20proces.htm");
        }
     /*   private void timer1_Tick(object sender, EventArgs e)
        {
            process = new GetProcess();
            SProcess = process.GetAllProcesses();
            int length = process.GetAllProcesses().GetLength(0);
            for (int i = 0; i < length; i++)
            {
                if (SProcess[i, 4] != null)
                {
                    if (dict.ContainsKey(SProcess[i, 0]))
                    {
                        if(dict[SProcess[i, 0]]==false)
                        {
                            for (int p = 0; p < AllLocation.Count; p++)
                            {
                                if (AllLocation[p] != null && AllLocation[p].Length > 0 &&
                                    SProcess[i, 1].Contains(AllLocation[p]))
                                {
                                    MessageBox.Show(SProcess[i, 0]);
                                    int value = Convert.ToInt32(ExcelMatrix[p + 1, 7]) + 1;
                                    ExcelMatrix[p + 1, 7] = value.ToString();
                                    break;
                                }
                            }
                            dict[SProcess[i, 0]] = true;
                        }
                    }
                    else
                    {
                        for (int p = 0; p < AllLocation.Count; p++)
                        {
                            if (AllLocation[p] != null && AllLocation[p].Length > 0 &&
                                SProcess[i, 1].Contains(AllLocation[p]))
                            {
                                MessageBox.Show(SProcess[i, 0]);
                                int value = Convert.ToInt32(ExcelMatrix[p + 1, 7]) + 1;
                                ExcelMatrix[p + 1, 7] = value.ToString();
                                break;
                            }
                        }
                        dict[SProcess[i, 0]] = true;
                    }
                }
                else dict[SProcess[i, 0]] = false;
            }
        }*/

        private void startWatch_EventArrived(object sender, EventArrivedEventArgs e)
        {
            SProcess = process.GetAllProcesses();
            int length = process.GetAllProcesses().GetLength(0);
            string STprocess = e.NewEvent.Properties["ProcessName"].Value.ToString();
            if (dict.ContainsKey(STprocess) == false || dict[STprocess] == false)
            {
                for (int i = 0; i < length; i++)
                {
                    if (SProcess[i, 0] == STprocess)
                    {
                        for (int p = 0; p < AllLocation.Count; p++)
                        {
                            if (AllLocation[p] != null && AllLocation[p].Length > 0 &&
                                SProcess[i, 1].Contains(AllLocation[p]))
                            {
                            /*    MessageBox.Show(SProcess[i, 1]);
                                MessageBox.Show(AllLocation[p]);
                                if (dict[STprocess]) MessageBox.Show("true");
                                else MessageBox.Show("false");
                                MessageBox.Show("seeeeeeeee");*/
                                ExcelMatrix[p + 1, 7] =
                                    (Convert.ToInt32(ExcelMatrix[p + 1, 7]) + 1).ToString();
                                dict[STprocess] = true;
                                break;
                            }
                        }
                    }
                }
            }
        }
        private void stopWatch_EventArrived(object sender, EventArrivedEventArgs e)
        {
            string STprocess = e.NewEvent.Properties["ProcessName"].Value.ToString();
            dict[STprocess] = false;
        }

        private void StartupProgramsContextMenu_Opening(object sender, CancelEventArgs e)
        {
            if (listViewSUP.SelectedItems.Count == 0)
                e.Cancel = true;
        }

        private void StartupProgramsMenuDisable_Click(object sender, EventArgs e)
        {
            // remove startup
            startupKey = Microsoft.Win32.Registry.LocalMachine.OpenSubKey(runKey, true);
            startupKey.DeleteValue(listViewSUP.SelectedItems[0].SubItems[0].Text, false);
            startupKey.Close();

            startupKey = Microsoft.Win32.Registry.CurrentUser.OpenSubKey(runKey, true);
            startupKey.DeleteValue(listViewSUP.SelectedItems[0].SubItems[0].Text, false);
            startupKey.Close();
            ListView4();
        }

        private void buttonAddST_Click(object sender, EventArgs e)
        {
            ofd.Filter = "EXE|*.exe";
            if (ofd.ShowDialog() == DialogResult.OK)
            {
                string path = ofd.FileName;
                string program = ofd.SafeFileName;
                startupKey = Microsoft.Win32.Registry.CurrentUser.OpenSubKey(runKey, true);
                // Add startup reg key
                startupKey.SetValue(program.Remove(program.Length - 4), path);
                startupKey.Close();
            }
            ListView4();
        }

        private void ProcessesMenuInfo_Click(object sender, EventArgs e)
        {
            string name = listViewProc.SelectedItems[0].SubItems[0].Text;
            System.Diagnostics.Process.Start(
            "http://www.processlibrary.com/en/search/?q="+name);
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            newDoc.AddMatrix(ExcelMatrix);
            string Today = DateTime.Now.ToShortDateString();
            newDoc.NewDate(Today, AllDisplayName.Count + 1);
            ExcelMatrix = newDoc.ReadMatrix();
        }
    }
}
