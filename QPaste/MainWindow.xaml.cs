using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
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
                KeyboardHook.FunPaste = () => Console.WriteLine("Yelow");
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
                listView.Items.Add(new { Id = i, Name = s });
        }
    }
}
