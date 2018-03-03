namespace Optimizer
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.notifyIcon1 = new System.Windows.Forms.NotifyIcon(this.components);
            this.NotifyContextMenu = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.NotifyMenuShow = new System.Windows.Forms.ToolStripMenuItem();
            this.NotifyMenuClose = new System.Windows.Forms.ToolStripMenuItem();
            this.tabControl = new System.Windows.Forms.TabControl();
            this.tabPageServices = new System.Windows.Forms.TabPage();
            this.panel1 = new System.Windows.Forms.Panel();
            this.labelDisable = new System.Windows.Forms.Label();
            this.labelAutomaticD = new System.Windows.Forms.Label();
            this.labelAutomatic = new System.Windows.Forms.Label();
            this.labelManual = new System.Windows.Forms.Label();
            this.listViewSer = new System.Windows.Forms.ListView();
            this.PageSName = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.PageSStatus = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.PageSDescription = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.PageSStartMode = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.ServicesContextMenu = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.SMenuStart = new System.Windows.Forms.ToolStripMenuItem();
            this.SMenuStop = new System.Windows.Forms.ToolStripMenuItem();
            this.SMenuStartUpMode = new System.Windows.Forms.ToolStripMenuItem();
            this.Automatic = new System.Windows.Forms.ToolStripMenuItem();
            this.Manual = new System.Windows.Forms.ToolStripMenuItem();
            this.Disable = new System.Windows.Forms.ToolStripMenuItem();
            this.tabPageProcess = new System.Windows.Forms.TabPage();
            this.listViewProc = new System.Windows.Forms.ListView();
            this.PagePName = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.PagePLocation = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.PagePProcessID = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.PagePParentProcess = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.PagePTitle = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.ProcessesContextMenu = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.PMenuKillProcess = new System.Windows.Forms.ToolStripMenuItem();
            this.PMenuInfo = new System.Windows.Forms.ToolStripMenuItem();
            this.tabPageTable = new System.Windows.Forms.TabPage();
            this.listViewTable = new System.Windows.Forms.ListView();
            this.PageTProgram = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.PageTDay7 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.PageTDay6 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.PageTDay5 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.PageTDay4 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.PageTDay3 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.PageTDay2 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.PageTDay1 = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.PageTAverage = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.tabPageSTPrograms = new System.Windows.Forms.TabPage();
            this.buttonAddST = new System.Windows.Forms.Button();
            this.labelAddSTProgram = new System.Windows.Forms.Label();
            this.listViewSUP = new System.Windows.Forms.ListView();
            this.PageSTName = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.PageSTCommand = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.PageSTDescription = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.PageSTLocation = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.PageSTUser = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.StartupProgramsContextMenu = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.StartupProgramsDisable = new System.Windows.Forms.ToolStripMenuItem();
            this.MenuStrip = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.MenuStripFileHidden = new System.Windows.Forms.ToolStripMenuItem();
            this.MenuStripFileExit = new System.Windows.Forms.ToolStripMenuItem();
            this.languageToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.MenuStripLanguageEnglish = new System.Windows.Forms.ToolStripMenuItem();
            this.MenuStripLanguageBulgarian = new System.Windows.Forms.ToolStripMenuItem();
            this.helpToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.MenuStripHelpAboutServices = new System.Windows.Forms.ToolStripMenuItem();
            this.MenuStripHelpAboutProcesses = new System.Windows.Forms.ToolStripMenuItem();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.PageSPath = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.NotifyContextMenu.SuspendLayout();
            this.tabControl.SuspendLayout();
            this.tabPageServices.SuspendLayout();
            this.panel1.SuspendLayout();
            this.ServicesContextMenu.SuspendLayout();
            this.tabPageProcess.SuspendLayout();
            this.ProcessesContextMenu.SuspendLayout();
            this.tabPageTable.SuspendLayout();
            this.tabPageSTPrograms.SuspendLayout();
            this.StartupProgramsContextMenu.SuspendLayout();
            this.MenuStrip.SuspendLayout();
            this.SuspendLayout();
            // 
            // notifyIcon1
            // 
            this.notifyIcon1.ContextMenuStrip = this.NotifyContextMenu;
            this.notifyIcon1.Icon = ((System.Drawing.Icon)(resources.GetObject("notifyIcon1.Icon")));
            this.notifyIcon1.Text = "Optimizer";
            this.notifyIcon1.Visible = true;
            this.notifyIcon1.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.notifyIcon1_MouseDoubleClick);
            // 
            // NotifyContextMenu
            // 
            this.NotifyContextMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.NotifyMenuShow,
            this.NotifyMenuClose});
            this.NotifyContextMenu.Name = "contextMenuStrip1";
            this.NotifyContextMenu.Size = new System.Drawing.Size(104, 48);
            // 
            // NotifyMenuShow
            // 
            this.NotifyMenuShow.Name = "NotifyMenuShow";
            this.NotifyMenuShow.Size = new System.Drawing.Size(103, 22);
            this.NotifyMenuShow.Text = "Show";
            this.NotifyMenuShow.Click += new System.EventHandler(this.NotifyMenuShow_Click);
            // 
            // NotifyMenuClose
            // 
            this.NotifyMenuClose.Name = "NotifyMenuClose";
            this.NotifyMenuClose.Size = new System.Drawing.Size(103, 22);
            this.NotifyMenuClose.Text = "Close";
            this.NotifyMenuClose.Click += new System.EventHandler(this.NotifyMenuClose_Click);
            // 
            // tabControl
            // 
            this.tabControl.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.tabControl.Controls.Add(this.tabPageServices);
            this.tabControl.Controls.Add(this.tabPageProcess);
            this.tabControl.Controls.Add(this.tabPageTable);
            this.tabControl.Controls.Add(this.tabPageSTPrograms);
            this.tabControl.Location = new System.Drawing.Point(4, 25);
            this.tabControl.Name = "tabControl";
            this.tabControl.SelectedIndex = 0;
            this.tabControl.Size = new System.Drawing.Size(707, 476);
            this.tabControl.TabIndex = 2;
            // 
            // tabPageServices
            // 
            this.tabPageServices.Controls.Add(this.panel1);
            this.tabPageServices.Controls.Add(this.listViewSer);
            this.tabPageServices.Location = new System.Drawing.Point(4, 22);
            this.tabPageServices.Name = "tabPageServices";
            this.tabPageServices.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageServices.Size = new System.Drawing.Size(699, 450);
            this.tabPageServices.TabIndex = 0;
            this.tabPageServices.Text = "Services";
            this.tabPageServices.UseVisualStyleBackColor = true;
            // 
            // panel1
            // 
            this.panel1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panel1.Controls.Add(this.labelDisable);
            this.panel1.Controls.Add(this.labelAutomaticD);
            this.panel1.Controls.Add(this.labelAutomatic);
            this.panel1.Controls.Add(this.labelManual);
            this.panel1.Location = new System.Drawing.Point(3, 372);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(695, 75);
            this.panel1.TabIndex = 4;
            // 
            // labelDisable
            // 
            this.labelDisable.AutoSize = true;
            this.labelDisable.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.3F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.labelDisable.Location = new System.Drawing.Point(3, 60);
            this.labelDisable.Name = "labelDisable";
            this.labelDisable.Size = new System.Drawing.Size(56, 15);
            this.labelDisable.TabIndex = 3;
            this.labelDisable.Text = "Disabled";
            // 
            // labelAutomaticD
            // 
            this.labelAutomaticD.AutoSize = true;
            this.labelAutomaticD.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.3F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.labelAutomaticD.Location = new System.Drawing.Point(3, 40);
            this.labelAutomaticD.Name = "labelAutomaticD";
            this.labelAutomaticD.Size = new System.Drawing.Size(117, 15);
            this.labelAutomaticD.TabIndex = 2;
            this.labelAutomaticD.Text = "Automatic (Delayed)";
            // 
            // labelAutomatic
            // 
            this.labelAutomatic.AutoSize = true;
            this.labelAutomatic.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.3F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.labelAutomatic.Location = new System.Drawing.Point(3, 20);
            this.labelAutomatic.Name = "labelAutomatic";
            this.labelAutomatic.Size = new System.Drawing.Size(61, 15);
            this.labelAutomatic.TabIndex = 1;
            this.labelAutomatic.Text = "Automatic";
            // 
            // labelManual
            // 
            this.labelManual.AutoSize = true;
            this.labelManual.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.3F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.labelManual.Location = new System.Drawing.Point(3, 0);
            this.labelManual.Name = "labelManual";
            this.labelManual.Size = new System.Drawing.Size(49, 15);
            this.labelManual.TabIndex = 0;
            this.labelManual.Text = "Manual";
            // 
            // listViewSer
            // 
            this.listViewSer.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.listViewSer.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.PageSName,
            this.PageSStatus,
            this.PageSDescription,
            this.PageSStartMode,
            this.PageSPath});
            this.listViewSer.ContextMenuStrip = this.ServicesContextMenu;
            this.listViewSer.FullRowSelect = true;
            this.listViewSer.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.listViewSer.Location = new System.Drawing.Point(3, 3);
            this.listViewSer.Name = "listViewSer";
            this.listViewSer.Size = new System.Drawing.Size(693, 364);
            this.listViewSer.TabIndex = 3;
            this.listViewSer.UseCompatibleStateImageBehavior = false;
            this.listViewSer.View = System.Windows.Forms.View.Details;
            // 
            // PageSName
            // 
            this.PageSName.Text = "Name";
            this.PageSName.Width = 128;
            // 
            // PageSStatus
            // 
            this.PageSStatus.Text = "Status";
            this.PageSStatus.Width = 99;
            // 
            // PageSDescription
            // 
            this.PageSDescription.Text = "Description";
            // 
            // PageSStartMode
            // 
            this.PageSStartMode.Text = "StartMode";
            this.PageSStartMode.Width = 91;
            // 
            // ServicesContextMenu
            // 
            this.ServicesContextMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.SMenuStart,
            this.SMenuStop,
            this.SMenuStartUpMode});
            this.ServicesContextMenu.Name = "contextMenuStrip2";
            this.ServicesContextMenu.Size = new System.Drawing.Size(148, 70);
            this.ServicesContextMenu.Opening += new System.ComponentModel.CancelEventHandler(this.ServicesMenu_Opening);
            // 
            // SMenuStart
            // 
            this.SMenuStart.Name = "SMenuStart";
            this.SMenuStart.Size = new System.Drawing.Size(147, 22);
            this.SMenuStart.Text = "start";
            this.SMenuStart.Click += new System.EventHandler(this.ServicesMenuStart_Click);
            // 
            // SMenuStop
            // 
            this.SMenuStop.Name = "SMenuStop";
            this.SMenuStop.Size = new System.Drawing.Size(147, 22);
            this.SMenuStop.Text = "stop";
            this.SMenuStop.Click += new System.EventHandler(this.ServicesMenuStop_Click);
            // 
            // SMenuStartUpMode
            // 
            this.SMenuStartUpMode.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.Automatic,
            this.Manual,
            this.Disable});
            this.SMenuStartUpMode.Name = "SMenuStartUpMode";
            this.SMenuStartUpMode.Size = new System.Drawing.Size(147, 22);
            this.SMenuStartUpMode.Text = "StartUp Mode";
            // 
            // Automatic
            // 
            this.Automatic.Name = "Automatic";
            this.Automatic.Size = new System.Drawing.Size(130, 22);
            this.Automatic.Text = "Automatic";
            this.Automatic.Click += new System.EventHandler(this.ServicesMenuStartModeAuto_Click);
            // 
            // Manual
            // 
            this.Manual.Name = "Manual";
            this.Manual.Size = new System.Drawing.Size(130, 22);
            this.Manual.Text = "Manual";
            this.Manual.Click += new System.EventHandler(this.ServicesMenuStartModeManual_Click);
            // 
            // Disable
            // 
            this.Disable.Name = "Disable";
            this.Disable.Size = new System.Drawing.Size(130, 22);
            this.Disable.Text = "Disable";
            this.Disable.Click += new System.EventHandler(this.ServicesMenuStartModeDisable_Click);
            // 
            // tabPageProcess
            // 
            this.tabPageProcess.Controls.Add(this.listViewProc);
            this.tabPageProcess.Location = new System.Drawing.Point(4, 22);
            this.tabPageProcess.Name = "tabPageProcess";
            this.tabPageProcess.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageProcess.Size = new System.Drawing.Size(699, 450);
            this.tabPageProcess.TabIndex = 1;
            this.tabPageProcess.Text = "Process";
            this.tabPageProcess.UseVisualStyleBackColor = true;
            // 
            // listViewProc
            // 
            this.listViewProc.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.listViewProc.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.PagePName,
            this.PagePLocation,
            this.PagePProcessID,
            this.PagePParentProcess,
            this.PagePTitle});
            this.listViewProc.ContextMenuStrip = this.ProcessesContextMenu;
            this.listViewProc.FullRowSelect = true;
            this.listViewProc.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.listViewProc.Location = new System.Drawing.Point(3, 3);
            this.listViewProc.Name = "listViewProc";
            this.listViewProc.Size = new System.Drawing.Size(693, 442);
            this.listViewProc.TabIndex = 4;
            this.listViewProc.UseCompatibleStateImageBehavior = false;
            this.listViewProc.View = System.Windows.Forms.View.Details;
            // 
            // PagePName
            // 
            this.PagePName.Text = "Name";
            this.PagePName.Width = 128;
            // 
            // PagePLocation
            // 
            this.PagePLocation.Text = "Location";
            this.PagePLocation.Width = 99;
            // 
            // PagePProcessID
            // 
            this.PagePProcessID.Text = "Process ID";
            this.PagePProcessID.Width = 109;
            // 
            // PagePParentProcess
            // 
            this.PagePParentProcess.Text = "Parent Process";
            this.PagePParentProcess.Width = 103;
            // 
            // PagePTitle
            // 
            this.PagePTitle.Text = "Title";
            // 
            // ProcessesContextMenu
            // 
            this.ProcessesContextMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.PMenuKillProcess,
            this.PMenuInfo});
            this.ProcessesContextMenu.Name = "contextMenuStrip3";
            this.ProcessesContextMenu.Size = new System.Drawing.Size(134, 48);
            this.ProcessesContextMenu.Opening += new System.ComponentModel.CancelEventHandler(this.ProcessesContextMenu_Opening);
            // 
            // PMenuKillProcess
            // 
            this.PMenuKillProcess.Name = "PMenuKillProcess";
            this.PMenuKillProcess.Size = new System.Drawing.Size(133, 22);
            this.PMenuKillProcess.Text = "Kill process";
            this.PMenuKillProcess.Click += new System.EventHandler(this.ProcessesMenuKillProcess_Click);
            // 
            // PMenuInfo
            // 
            this.PMenuInfo.Name = "PMenuInfo";
            this.PMenuInfo.Size = new System.Drawing.Size(133, 22);
            this.PMenuInfo.Text = "Info";
            this.PMenuInfo.Click += new System.EventHandler(this.ProcessesMenuInfo_Click);
            // 
            // tabPageTable
            // 
            this.tabPageTable.Controls.Add(this.listViewTable);
            this.tabPageTable.Location = new System.Drawing.Point(4, 22);
            this.tabPageTable.Name = "tabPageTable";
            this.tabPageTable.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageTable.Size = new System.Drawing.Size(699, 450);
            this.tabPageTable.TabIndex = 2;
            this.tabPageTable.Text = "Table";
            this.tabPageTable.UseVisualStyleBackColor = true;
            // 
            // listViewTable
            // 
            this.listViewTable.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.listViewTable.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.PageTProgram,
            this.PageTDay7,
            this.PageTDay6,
            this.PageTDay5,
            this.PageTDay4,
            this.PageTDay3,
            this.PageTDay2,
            this.PageTDay1,
            this.PageTAverage});
            this.listViewTable.FullRowSelect = true;
            this.listViewTable.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.listViewTable.Location = new System.Drawing.Point(3, 3);
            this.listViewTable.Name = "listViewTable";
            this.listViewTable.Size = new System.Drawing.Size(693, 442);
            this.listViewTable.TabIndex = 4;
            this.listViewTable.UseCompatibleStateImageBehavior = false;
            this.listViewTable.View = System.Windows.Forms.View.Details;
            // 
            // PageTProgram
            // 
            this.PageTProgram.Text = "Program";
            this.PageTProgram.Width = 73;
            // 
            // PageTDay7
            // 
            this.PageTDay7.Text = "day 7";
            this.PageTDay7.Width = 50;
            // 
            // PageTDay6
            // 
            this.PageTDay6.Text = "day 6";
            this.PageTDay6.Width = 50;
            // 
            // PageTDay5
            // 
            this.PageTDay5.Text = "day 5";
            this.PageTDay5.Width = 50;
            // 
            // PageTDay4
            // 
            this.PageTDay4.Text = "day 4";
            this.PageTDay4.Width = 50;
            // 
            // PageTDay3
            // 
            this.PageTDay3.Text = "day 3";
            this.PageTDay3.Width = 50;
            // 
            // PageTDay2
            // 
            this.PageTDay2.Text = "day 2";
            this.PageTDay2.Width = 50;
            // 
            // PageTDay1
            // 
            this.PageTDay1.Text = "day 1";
            this.PageTDay1.Width = 50;
            // 
            // PageTAverage
            // 
            this.PageTAverage.Text = "AVERAGE";
            // 
            // tabPageSTPrograms
            // 
            this.tabPageSTPrograms.Controls.Add(this.buttonAddST);
            this.tabPageSTPrograms.Controls.Add(this.labelAddSTProgram);
            this.tabPageSTPrograms.Controls.Add(this.listViewSUP);
            this.tabPageSTPrograms.Location = new System.Drawing.Point(4, 22);
            this.tabPageSTPrograms.Name = "tabPageSTPrograms";
            this.tabPageSTPrograms.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageSTPrograms.Size = new System.Drawing.Size(699, 450);
            this.tabPageSTPrograms.TabIndex = 3;
            this.tabPageSTPrograms.Text = "StartUp Programs";
            this.tabPageSTPrograms.UseVisualStyleBackColor = true;
            // 
            // buttonAddST
            // 
            this.buttonAddST.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.buttonAddST.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.buttonAddST.Location = new System.Drawing.Point(164, 426);
            this.buttonAddST.Margin = new System.Windows.Forms.Padding(2);
            this.buttonAddST.Name = "buttonAddST";
            this.buttonAddST.Size = new System.Drawing.Size(56, 21);
            this.buttonAddST.TabIndex = 7;
            this.buttonAddST.Text = "Browse";
            this.buttonAddST.UseVisualStyleBackColor = true;
            this.buttonAddST.Click += new System.EventHandler(this.buttonAddST_Click);
            // 
            // labelAddSTProgram
            // 
            this.labelAddSTProgram.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.labelAddSTProgram.AutoSize = true;
            this.labelAddSTProgram.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.labelAddSTProgram.Location = new System.Drawing.Point(5, 426);
            this.labelAddSTProgram.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.labelAddSTProgram.Name = "labelAddSTProgram";
            this.labelAddSTProgram.Size = new System.Drawing.Size(138, 17);
            this.labelAddSTProgram.TabIndex = 6;
            this.labelAddSTProgram.Text = "Add startup program";
            // 
            // listViewSUP
            // 
            this.listViewSUP.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.listViewSUP.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.PageSTName,
            this.PageSTCommand,
            this.PageSTDescription,
            this.PageSTLocation,
            this.PageSTUser});
            this.listViewSUP.ContextMenuStrip = this.StartupProgramsContextMenu;
            this.listViewSUP.FullRowSelect = true;
            this.listViewSUP.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.listViewSUP.Location = new System.Drawing.Point(3, 3);
            this.listViewSUP.Name = "listViewSUP";
            this.listViewSUP.Size = new System.Drawing.Size(693, 420);
            this.listViewSUP.TabIndex = 5;
            this.listViewSUP.UseCompatibleStateImageBehavior = false;
            this.listViewSUP.View = System.Windows.Forms.View.Details;
            // 
            // PageSTName
            // 
            this.PageSTName.Text = "Name";
            // 
            // PageSTCommand
            // 
            this.PageSTCommand.Text = "Command";
            this.PageSTCommand.Width = 126;
            // 
            // PageSTDescription
            // 
            this.PageSTDescription.Text = "Description";
            this.PageSTDescription.Width = 92;
            // 
            // PageSTLocation
            // 
            this.PageSTLocation.Text = "Location";
            this.PageSTLocation.Width = 91;
            // 
            // PageSTUser
            // 
            this.PageSTUser.Text = "User";
            // 
            // StartupProgramsContextMenu
            // 
            this.StartupProgramsContextMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.StartupProgramsDisable});
            this.StartupProgramsContextMenu.Name = "contextMenuStrip4";
            this.StartupProgramsContextMenu.Size = new System.Drawing.Size(113, 26);
            this.StartupProgramsContextMenu.Opening += new System.ComponentModel.CancelEventHandler(this.StartupProgramsContextMenu_Opening);
            // 
            // StartupProgramsDisable
            // 
            this.StartupProgramsDisable.Name = "StartupProgramsDisable";
            this.StartupProgramsDisable.Size = new System.Drawing.Size(112, 22);
            this.StartupProgramsDisable.Text = "Disable";
            this.StartupProgramsDisable.Click += new System.EventHandler(this.StartupProgramsMenuDisable_Click);
            // 
            // MenuStrip
            // 
            this.MenuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.languageToolStripMenuItem,
            this.helpToolStripMenuItem});
            this.MenuStrip.Location = new System.Drawing.Point(0, 0);
            this.MenuStrip.Name = "MenuStrip";
            this.MenuStrip.Size = new System.Drawing.Size(713, 24);
            this.MenuStrip.TabIndex = 3;
            this.MenuStrip.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.MenuStripFileHidden,
            this.MenuStripFileExit});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // MenuStripFileHidden
            // 
            this.MenuStripFileHidden.Name = "MenuStripFileHidden";
            this.MenuStripFileHidden.Size = new System.Drawing.Size(113, 22);
            this.MenuStripFileHidden.Text = "Hidden";
            this.MenuStripFileHidden.Click += new System.EventHandler(this.MenuStripFileHidden_Click);
            // 
            // MenuStripFileExit
            // 
            this.MenuStripFileExit.Name = "MenuStripFileExit";
            this.MenuStripFileExit.Size = new System.Drawing.Size(113, 22);
            this.MenuStripFileExit.Text = "Exit";
            this.MenuStripFileExit.Click += new System.EventHandler(this.MenuStripFileExit_Click);
            // 
            // languageToolStripMenuItem
            // 
            this.languageToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.MenuStripLanguageEnglish,
            this.MenuStripLanguageBulgarian});
            this.languageToolStripMenuItem.Name = "languageToolStripMenuItem";
            this.languageToolStripMenuItem.Size = new System.Drawing.Size(71, 20);
            this.languageToolStripMenuItem.Text = "Language";
            // 
            // MenuStripLanguageEnglish
            // 
            this.MenuStripLanguageEnglish.Name = "MenuStripLanguageEnglish";
            this.MenuStripLanguageEnglish.Size = new System.Drawing.Size(124, 22);
            this.MenuStripLanguageEnglish.Text = "English";
            this.MenuStripLanguageEnglish.Click += new System.EventHandler(this.MenuStripLanguageEnglish_Click);
            // 
            // MenuStripLanguageBulgarian
            // 
            this.MenuStripLanguageBulgarian.Name = "MenuStripLanguageBulgarian";
            this.MenuStripLanguageBulgarian.Size = new System.Drawing.Size(124, 22);
            this.MenuStripLanguageBulgarian.Text = "Bulgarian";
            this.MenuStripLanguageBulgarian.Click += new System.EventHandler(this.MenuStripLanguageBulgarian_Click);
            // 
            // helpToolStripMenuItem
            // 
            this.helpToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.MenuStripHelpAboutServices,
            this.MenuStripHelpAboutProcesses});
            this.helpToolStripMenuItem.Name = "helpToolStripMenuItem";
            this.helpToolStripMenuItem.Size = new System.Drawing.Size(44, 20);
            this.helpToolStripMenuItem.Text = "Help";
            // 
            // MenuStripHelpAboutServices
            // 
            this.MenuStripHelpAboutServices.Name = "MenuStripHelpAboutServices";
            this.MenuStripHelpAboutServices.Size = new System.Drawing.Size(161, 22);
            this.MenuStripHelpAboutServices.Text = "About Services";
            this.MenuStripHelpAboutServices.Click += new System.EventHandler(this.MenuStripHelpAboutServices_Click);
            // 
            // MenuStripHelpAboutProcesses
            // 
            this.MenuStripHelpAboutProcesses.Name = "MenuStripHelpAboutProcesses";
            this.MenuStripHelpAboutProcesses.Size = new System.Drawing.Size(161, 22);
            this.MenuStripHelpAboutProcesses.Text = "About Processes";
            this.MenuStripHelpAboutProcesses.Click += new System.EventHandler(this.MenuStripHelpAboutProcesses_Click);
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Interval = 24000;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // PageSPath
            // 
            this.PageSPath.Text = "Location";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(713, 504);
            this.Controls.Add(this.MenuStrip);
            this.Controls.Add(this.tabControl);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "Form1";
            this.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.Text = "Optimizer";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.NotifyContextMenu.ResumeLayout(false);
            this.tabControl.ResumeLayout(false);
            this.tabPageServices.ResumeLayout(false);
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.ServicesContextMenu.ResumeLayout(false);
            this.tabPageProcess.ResumeLayout(false);
            this.ProcessesContextMenu.ResumeLayout(false);
            this.tabPageTable.ResumeLayout(false);
            this.tabPageSTPrograms.ResumeLayout(false);
            this.tabPageSTPrograms.PerformLayout();
            this.StartupProgramsContextMenu.ResumeLayout(false);
            this.MenuStrip.ResumeLayout(false);
            this.MenuStrip.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.NotifyIcon notifyIcon1;
        private System.Windows.Forms.ContextMenuStrip NotifyContextMenu;
        private System.Windows.Forms.ToolStripMenuItem NotifyMenuShow;
        private System.Windows.Forms.ToolStripMenuItem NotifyMenuClose;
        private System.Windows.Forms.TabPage tabPageServices;
        private System.Windows.Forms.TabPage tabPageProcess;
        private System.Windows.Forms.ListView listViewSer;
        private System.Windows.Forms.ColumnHeader PageSName;
        private System.Windows.Forms.ColumnHeader PageSStatus;
        private System.Windows.Forms.ContextMenuStrip ServicesContextMenu;
        private System.Windows.Forms.ToolStripMenuItem SMenuStart;
        private System.Windows.Forms.ToolStripMenuItem SMenuStop;
        private System.Windows.Forms.ColumnHeader PageSDescription;
        private System.Windows.Forms.TabPage tabPageTable;
        private System.Windows.Forms.ListView listViewTable;
        private System.Windows.Forms.ColumnHeader PageTProgram;
        private System.Windows.Forms.TabPage tabPageSTPrograms;
        private System.Windows.Forms.ColumnHeader PageSStartMode;
        private System.Windows.Forms.ColumnHeader PageTDay7;
        private System.Windows.Forms.ColumnHeader PageTDay6;
        private System.Windows.Forms.ColumnHeader PageTDay5;
        private System.Windows.Forms.ColumnHeader PageTDay4;
        private System.Windows.Forms.ColumnHeader PageTDay3;
        private System.Windows.Forms.ColumnHeader PageTDay2;
        private System.Windows.Forms.ColumnHeader PageTDay1;
        private System.Windows.Forms.ListView listViewProc;
        private System.Windows.Forms.ColumnHeader PagePName;
        private System.Windows.Forms.ColumnHeader PagePLocation;
        public System.Windows.Forms.TabControl tabControl;
        private System.Windows.Forms.ToolStripMenuItem SMenuStartUpMode;
        private System.Windows.Forms.ToolStripMenuItem Automatic;
        private System.Windows.Forms.ToolStripMenuItem Manual;
        private System.Windows.Forms.ToolStripMenuItem Disable;
        private System.Windows.Forms.ContextMenuStrip ProcessesContextMenu;
        private System.Windows.Forms.ToolStripMenuItem PMenuKillProcess;
        private System.Windows.Forms.ListView listViewSUP;
        private System.Windows.Forms.ColumnHeader PageSTName;
        private System.Windows.Forms.ColumnHeader PageSTCommand;
        private System.Windows.Forms.ColumnHeader PageSTDescription;
        private System.Windows.Forms.ColumnHeader PageSTLocation;
        private System.Windows.Forms.ColumnHeader PageSTUser;
        private System.Windows.Forms.MenuStrip MenuStrip;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem MenuStripFileHidden;
        private System.Windows.Forms.ToolStripMenuItem MenuStripFileExit;
        private System.Windows.Forms.ToolStripMenuItem languageToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem MenuStripLanguageEnglish;
        private System.Windows.Forms.ToolStripMenuItem MenuStripLanguageBulgarian;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Label labelManual;
        private System.Windows.Forms.Label labelAutomaticD;
        private System.Windows.Forms.Label labelAutomatic;
        private System.Windows.Forms.Label labelDisable;
        private System.Windows.Forms.ToolStripMenuItem helpToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem MenuStripHelpAboutServices;
        private System.Windows.Forms.ToolStripMenuItem MenuStripHelpAboutProcesses;
        private System.Windows.Forms.ColumnHeader PagePProcessID;
        private System.Windows.Forms.ColumnHeader PagePParentProcess;
        private System.Windows.Forms.ColumnHeader PagePTitle;
        private System.Windows.Forms.ColumnHeader PageTAverage;
        private System.Windows.Forms.ContextMenuStrip StartupProgramsContextMenu;
        private System.Windows.Forms.ToolStripMenuItem StartupProgramsDisable;
        private System.Windows.Forms.Button buttonAddST;
        private System.Windows.Forms.Label labelAddSTProgram;
        private System.Windows.Forms.ToolStripMenuItem PMenuInfo;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.ColumnHeader PageSPath;
    }
}

