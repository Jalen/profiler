using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace TestCases
{
    class Program
    {
        static int id = DevTools.ProfilerMgd.AcquireWatch("main");

        static void Main(string[] args)
        {
            using (new DevTools.StopWatchMgd(id))
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
