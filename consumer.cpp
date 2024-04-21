#include "iostream"
#include "libproc.h"
#include "stdlib.h"
#include <mach/mach.h>
#include <thread>
#include <chrono>


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
    exit(1);
}


mach_port_t extract_task(pid_t pid)
{
    kern_return_t kern_return = 0;
    mach_port_t task = 0;
    kern_return = task_for_pid(mach_task_self(), pid, &task);
    if (kern_return != KERN_SUCCESS)
    {
        std::cout << "Process failed!" << mach_error_string(kern_return) << std::endl;
        exit(1);
    }
    return task;
}


int read_data(mach_port_t task, vm_address_t data_address)
{
    kern_return_t result;
    vm_size_t size_to_read = (vm_size_t) sizeof(int);
    mach_msg_type_number_t size = sizeof(int);
    void * data;
    while (true)
    {
        result = vm_read(task, data_address, size_to_read, (vm_offset_t *) &data, &size);
        int* char_ptr = (int *) data;
        std::cout << *char_ptr << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    return 0;
}


int main(int argc, char** argv) 
{
    if (argc < 3)
    {
        std::cerr << "usage: " << argv[0] << " <string_argument>" << std::endl;
        std::cerr << "usage: " << argv[0] << " <hex_memory_address>" << std::endl;
        return 1;
    }
    vm_address_t address;
    sscanf(argv[2], "%lX", &address);
    std::string program_name = argv[1];
    pid_t pid = find_pid(program_name.c_str());
    std::cout << "Process pid: " << pid << std::endl;
    mach_port_t task = extract_task(pid);
    std::cout << "Task: " << task << std::endl;
    int data = read_data(task, address);
    std::cout << "Data: " << data << std::endl;
    return 0;
}