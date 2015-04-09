using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace QPaste
{
    class StringStorage
    {
        public const int NUM_MAX = 100;
        private LinkedList<String> StorageList;
        private int StorageListSize = 0;
        
        public StringStorage()
        {
            StorageList = new LinkedList<String>();
        }

        /// <summary>
        /// Add a string to the StringStorage
        /// </summary>
        /// <param name="s">String to add</param>
        /// <returns>Index of the new string, or -1 if the string cannot be added</returns>
        public int Add(String s)
        {
            if (StorageList.Contains(s))
                return -1;

            StorageList.AddFirst(s);

            if (StorageListSize >= NUM_MAX)
                StorageList.RemoveLast();
            else
                StorageListSize++;

            return 0;
        }

        /// <summary>
        /// Returns the ith string in the StringStorage
        /// </summary>
        /// <param name="i">Index to return</param>
        /// <returns>The ith string, or an empty string if it does not exist</returns>
        public String Get(int i)
        {
            return (0 <= i && i < StorageListSize) ? StorageList.ElementAt(i) : "";
        }
    }
}
