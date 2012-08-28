﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using WeifenLuo.WinFormsUI.Docking;
using WorldEditorFramework;

namespace WorldEditor
{
    public partial class FormMain : Form
    {
        private MWorldEditor mWorldEditor;  // 主操作接口

        private SceneForm mSceneForm;       // 主窗口
        private OperateForm mOperateForm;   // 操作窗口

        public FormMain()
        {
            InitializeComponent();

            // 新建窗口对象
            mOperateForm = new OperateForm();
            mSceneForm = new SceneForm();
        }

        // 系统更新回调函数
        public void FormMain_Idle(object sender, EventArgs e)
        {
            if (this.Visible && FormWindowState.Minimized != this.WindowState)
            {
                // 窗口可见,且非最小化
                //
                // 更新操作接口
                if (mWorldEditor != null)
                    mWorldEditor.Update();
            }
        }

        // @{
        //*****************************************************************************************
        // 消息回调函数
        //*****************************************************************************************
        private void FormMain_Load(object sender, EventArgs e)
        {
            // 加载配置界面
            String szConfigFile = Path.Combine(Path.GetDirectoryName(Application.ExecutablePath), "WorldEditor.DockPanel.config");
            if (File.Exists(szConfigFile))
            {
                DeserializeDockContent mDeserializeDockContent = new DeserializeDockContent(GetDockContentFromPersistString);
                this.dockPanelMain.LoadFromXml(szConfigFile, mDeserializeDockContent);
            }
            else
            {
                this.mOperateForm.Show(this.dockPanelMain, DockState.DockRight);
                this.mSceneForm.Show(this.dockPanelMain, DockState.DockLeft);
            }

            // 初始化操作接口
            this.mWorldEditor = new MWorldEditor();
            this.mWorldEditor.Initialize(this.mSceneForm.Handle);

            // 向应用程序注册更新回调函数
            Application.Idle += new EventHandler(this.FormMain_Idle);

            // 向应用程序注册消息过滤器(用于捕捉输入消息)
            Application.AddMessageFilter(new InputMessageFilter(this.mWorldEditor));
        }

        private void FormMain_FormClosing(object sender, FormClosingEventArgs e)
        {
            // 保存配置界面
            String szConfigFile = Path.Combine(Path.GetDirectoryName(Application.ExecutablePath), "WorldEditor.DockPanel.config");
            this.dockPanelMain.SaveAsXml(szConfigFile);
        }
        //*****************************************************************************************
        // @}


        // 用于DockPanel的布局保存
        private IDockContent GetDockContentFromPersistString(string szPersist)
        {
            if (typeof(SceneForm).ToString() == szPersist)
                return mSceneForm;
            else if (typeof(OperateForm).ToString() == szPersist)
                return mOperateForm;
            else
                return null;
        }
    }
}