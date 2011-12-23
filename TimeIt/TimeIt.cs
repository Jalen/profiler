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
            //AssemblyDefinition assembiy = AssemblyDefinition.ReadAssembly(args[0]);
            AssemblyDefinition assembiy = AssemblyDefinition.ReadAssembly(@"C:\Users\Jalen\github\Profiler\Debug\TestCases.exe");
            foreach (Mono.Cecil.TypeDefinition item in assembiy.MainModule.Types)
            {
                foreach (MethodDefinition method in item.Methods)
                {
                    if (method.Name.Equals("Main"))
                    {
                        var ins = method.Body.Instructions[0];
                        var worker = method.Body.GetILProcessor();
                        
                        worker.InsertBefore(ins, worker.Create(OpCodes.Ldstr, "Method start…"));
                        worker.InsertBefore(ins, worker.Create(OpCodes.Call,
                            assembiy.MainModule.Import(typeof(Console).GetMethod("WriteLine", new Type[] { typeof(string) }))));

                        ins = method.Body.Instructions[method.Body.Instructions.Count - 1];

                        worker.InsertBefore(ins, worker.Create(OpCodes.Ldstr, "Method finish…"));
                        worker.InsertBefore(ins, worker.Create(OpCodes.Call,
                            assembiy.MainModule.Import(typeof(Console).GetMethod("WriteLine", new Type[] { typeof(string) }))));
                        break;
                    }
                }
            }

            assembiy.Write("IL_" + args[0]);
            Console.Read();
        }
    }
}
