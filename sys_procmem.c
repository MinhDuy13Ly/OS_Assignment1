#include <linux/linkage.h>
#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/mm.h>
#include <linux/uaccess.h>

struct  proc_segs {
     unsigned long studentID ;
     unsigned long start_code ;
     unsigned long end_code ;
     unsigned long start_data ;
     unsigned long end_data ;
     unsigned long start_heap ;
     unsigned long end_heap ;
     unsigned long start_stack;
};

asmlinkage long  sys_procmem(int pid ,  struct proc_segs * info)
{
       struct task_struct * task ;
       for_each_process(task)
       {
         if(task->pid == pid)
         {
             printk("Finding success pid: %d  \n"  ,  pid )  ;
             if(task->mm != NULL)
             {
              struct proc_segs temp ;
              temp.studentID = 1652113 ;  
              temp.start_code = task->mm->start_code ;
              temp.end_code  = task->mm->end_code ;
              temp.start_data  = task->mm->start_data ;
              temp.end_data = task->mm->end_data ;
              temp.start_heap = task->mm->start_brk;
              temp.end_heap = task->mm->brk ;
              temp.start_stack = task->mm->start_stack ;
              int res = copy_to_user(info , &temp , sizeof(temp));
              if(res == 0) printk("Copy data succesfull\n");  
              printk("Getting data success");
              return 0 ;
             }
         }
         else
           printk("Cannot find the pid ") ;
       }
  return -1 ;
}     
