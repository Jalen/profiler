using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace TestCases
{
    class Program
    {
        static void Main(string[] args)
        {
            using (new DevTools.StopWatchMgd("main"))
            {
                for (int i = 0; i < 1000000; i++)
                {
                    int j;
                    j = 1000;
                }
            }

            DevTools.ProfilerMgd.ReportResult("test", @"c:\test.txt");
        }
    }
}
