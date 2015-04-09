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
                KeyboardHook.FunPaste = ShowWindow;
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
                listView.Items.Insert(0, new ListViewItem(i + 1, s));
            listView_ResetIds();
        }

        private void ShowWindow()
        {
            WindowState = WindowState.Normal;
            Activate();
        }

        private void HideWindow()
        {
            WindowState = WindowState.Minimized;
        }

        private void listView_ResetIds()
        {
            for (int i = 0; i < listView.Items.Count; i++)
                ((ListViewItem)listView.Items[i]).Id = i + 1;
            listView.Items.Refresh();
        }

        private void listView_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (listView.SelectedIndex == -1)
                return;

            ClipboardHook.SetClipboardData(StringContainer.Get(listView.SelectedIndex));
            HideWindow();
            KeyboardHook.SendPaste();
        }
    }

    class ListViewItem
    {
        public int Id { get; set; }
        public String Data { get; set; }

        public ListViewItem(int id, String data)
        {
            Id = id;
            Data = data;
        }
    }
}
