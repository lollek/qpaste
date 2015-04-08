using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Forms;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace QPaste
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private Boolean HooksAreLoaded = false;
        private StringStorage StringContainer;

        public MainWindow()
        {
            StringContainer = new StringStorage();
            InitializeComponent();
        }

        private void WindowLoaded(object sender, RoutedEventArgs e)
        {
            if (!HooksAreLoaded)
            {
                KeyboardHook.FunPaste = Appear;
                KeyboardHook.Activate();

                ClipboardHook.OnNewData = Add;
                ClipboardHook.Activate(this);
                HooksAreLoaded = true;
            }
        }

        private void WindowUnloaded(object sender, RoutedEventArgs e)
        {
            if (HooksAreLoaded)
            {
                KeyboardHook.Deactivate();
                ClipboardHook.Deactivate();
                HooksAreLoaded = false;      
            }   
        }

        private void Add(String s)
        {
            int i = StringContainer.Add(s);
            if (i != -1)
                listView.Items.Insert(0, new { Id = i, Data = s });
        }

        public void Appear()
        {
            WindowState = WindowState.Normal;
            Activate();
        }

        private void listView_MouseDoubleClick(object sender, MouseButtonEventArgs e)
        {
            if (listView.SelectedIndex == -1)
                return;

            ClipboardHook.SetClipboardData(StringContainer.Get(listView.SelectedIndex));
            WindowState = WindowState.Minimized;
            //Thread.Sleep(1000);
            KeyboardHook.SendPaste();
        }
    }
}
