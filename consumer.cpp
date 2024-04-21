#include "iostream"
#include "libproc.h"
#include <mach/mach.h>

pid_t find_pid(const char *name)
{
    pid_t pids[2048];
    int bytes = proc_listpids(PROC_ALL_PIDS, 0, pids, sizeof(pids));
    int n_proc = bytes / sizeof(pids[0]);
    for (int i = 0; i < n_proc; i++) {
        struct proc_bsdinfo proc;
        int st = proc_pidinfo(pids[i], PROC_PIDTBSDINFO, 0,
                             &proc, PROC_PIDTBSDINFO_SIZE);
        if (st == PROC_PIDTBSDINFO_SIZE) {
            if (strcmp(name, proc.pbi_name) == 0) {
                /* Process PID */
                return pids[i];                
            }
        }       
    }
    return -1;
}


int main(int argc, char** argv) 
{
    if (argc < 2)
    {
        std::cerr << "usage: " << argv[0] << " <string_argument>" << std::endl;
        return 1;
    }
    kern_return_t kern_return = 0;
    mach_port_t task = 0;
    std::string program_name = argv[1];
    pid_t pid = find_pid(program_name.c_str());
    std::cout << "Process pid: " << pid << std::endl;
    kern_return = task_for_pid(mach_task_self(), pid, &task);
    if (kern_return != KERN_SUCCESS)
    {
        std::cout << "Process failed!" << mach_error_string(kern_return) << std::endl;
        return 0;
    }
    std::cout << task << std::endl;
    return 0;
}