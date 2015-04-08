using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace QPaste
{
    class StringStorage
    {
        public const int NUM_MAX = 1000;
        private LinkedList<String> StorageList;
        private int StorageListSize = 0;
        
        public StringStorage()
        {
            StorageList = new LinkedList<String>();
        }

        public int Add(String s)
        {
            if (StorageList.Contains(s))
                return -1;

            StorageList.AddFirst(s);
            if (StorageListSize >= NUM_MAX)
            {
                StorageList.RemoveLast();
                StorageListSize--;
            }

            return StorageListSize++;
        }
    }
}
