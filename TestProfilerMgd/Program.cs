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
            //var stopWatch = new DevTools.StopWatchMgd("main");

            //DevTools.ProfilerMgd.Start("main");
            
            for (int i = 0; i < 1000000; i++)
            {
                int j;
                j = 1000;
            }
       
            //DevTools.ProfilerMgd.Stop("main");

            //DevTools.ProfilerMgd.ReportResult("test", @"c:\test.txt");
        }
    }
}
