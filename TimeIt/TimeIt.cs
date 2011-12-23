using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Mono.Cecil;
using Mono.Cecil.Cil; 

namespace TimeIt
{
    class TimeIt
    {
        static void Main(string[] args)
        {
            if (args.Length < 2)
            {
                Console.WriteLine("Usage: TimeIt <DLL> <Filter>");
                return;
            }

            string filter = args[1];

            AssemblyDefinition assembiy = AssemblyDefinition.ReadAssembly(args[0]);

            //assembiy.MainModule.AssemblyReferences.Add(new AssemblyNameReference("ProfilerMgd", new Version(0, 0)));

            foreach (Mono.Cecil.TypeDefinition item in assembiy.MainModule.Types)
            {
                foreach (MethodDefinition method in item.Methods)
                {
                    string fullName = method.DeclaringType + "." + method.Name;
                    if (fullName.IndexOf(filter) != -1)
                    {
                        var ins = method.Body.Instructions[0];
                        var worker = method.Body.GetILProcessor();

                        worker.InsertBefore(ins, worker.Create(OpCodes.Ldstr, fullName));
                        worker.InsertBefore(ins, worker.Create(OpCodes.Call,
                            assembiy.MainModule.Import(typeof(DevTools.ProfilerMgd).GetMethod("Start", new Type[] { typeof(string) }))));
   
                        ins = method.Body.Instructions[method.Body.Instructions.Count - 1];

                        worker.InsertBefore(ins, worker.Create(OpCodes.Ldstr, fullName));
                        worker.InsertBefore(ins, worker.Create(OpCodes.Call,
                            assembiy.MainModule.Import(typeof(DevTools.ProfilerMgd).GetMethod("Stop", new Type[] { typeof(string) }))));

                        break;
                    }
                }
            }

            string filename = "IL_" + args[0];
            assembiy.Write(filename);
            Console.WriteLine("Write to " + filename);
        }
    }
}
