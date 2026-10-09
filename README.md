// gui threads(threads which has GUI) have attribute of msg_queue where data bytes from specific hardwares are put
// by windows kernel. non-gui threads must use syscall to open hardware abstraaction provided by driver and then
// driver sends hardware specific bytes to thread through sys call api abstraction provided by kernel.
//
// gui threads are backed-up by regular threads. GUI thread is for fast response to system level messages (i.e keyboard pressing, closing windows, size resolution etc)
//
// kernel tracks currently which gui thread is focused so messages are delivered to active gui thread queue.
//
// 
// SetWindowsHookEx(...) has many usage. it installs hook and where hook  is installed depends on  parameters passed.
// (if talk about keybord_lowlevel type.)driver (raw bytes in mapped memory) ----> windows input system (functions responsible for input data) ---> low-level-hooks ----> threads  msg queue ---> high-level-hooks
// ----> getMessage() ----> ...(optional) ----> process  
//
// windows kernel inside the implementation of SetWindowsHookEx() registers (callback_fn_addr + caller_thread_id) 
// 
// windows input system sends msg to thread which registered low level hook. and for active GUI threads  
//
// puts msg to caller thread's msg queue. inside getMessage() implementation  windows kernel calls regitered callback_fn.(getMessage() calls systemcall to query hook table to find callback function address.)
//
// getMessage() is executted in user mode, therefore calling callback within its implementation is safe for system. 
//
// executing user-defined function by kernel code is not reasonable for system. (for me, i wished such vuln in kernel :))) :D )
//
// kernel maintains hook table which contains entries (thread id ---- callback_fn_addr,type) 
// kernel looks up for current gui thread id  in table and sends msg to thread msg queue (but for low-level hooks, kernel sends msg directly to corresponding thread (find with thread id) inhook table.
// 
//
// thread could have msg queue if  proper syscall is called.
//
// msg queue is mechanism to move data to thread  memory  from  kernel or any other source(mostly for hardwaare data like keyboard,sound,mouse etc) otherwise directy connection to hardware
// abstraction from process.
//
//
