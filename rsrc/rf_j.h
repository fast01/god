
namespace rf
{
	mac max(a,b) r_cond(a>b,a,b)
	mac min(a,b) r_cond(a>b,b,a)
	mac abs(a) r_cond(a<0,neg a,a)

	void* find_func(rstr& s)
	{
		return find_func(s.cstr)
	}

	void* find_func(char* p)
	{
		push p
		calle "find_func"
		mov s_ret,eax
		add esp,4
	}

	void* find_dll(char* p)
	{
		push p
		calle "find_dll"
		mov s_ret,eax
		add esp,4
	}

	void* get_vclass()
	{
		return null
	}

	int GetStdHandle(int a)
	{
		push a
		calle "GetStdHandle"
		mov s_ret,eax
	}

	int SetConsoleCursorInfo(int a,void* b)
	{
		push b
		push a
		calle "SetConsoleCursorInfo"
		mov s_ret,eax
	}

	int SetConsoleTextAttribute(int a,int b)
	{
		push b
		push a
		calle "SetConsoleTextAttribute"
		mov s_ret,eax
	}

	int GetAsyncKeyState(int a)
	{
		push a
		calle "GetAsyncKeyState"
		mov s_ret,eax
	}

	int MessageBoxA(int a,char* b,char* c,int d)
	{
		push d
		push c
		push b
		push a
		calle "MessageBoxA"
		mov s_ret,eax
	}

	int SetConsoleCursorPosition(int a,int b)
	{
		push b
		push a
		calle "SetConsoleCursorPosition"
		mov s_ret,eax
	}
	
	int lstrlenW(wchar* p)
	{
		push p
		calle "lstrlenW"
		mov s_ret,eax
	}
	
	FindClose(int handle)
	{
		push handle
		calle "FindClose"
	}
	
	int FindNextFileW(int handle,void* p)
	{
		push p
		push handle
		calle "FindNextFileW"
		mov s_ret,eax
	}
	
	int FindFirstFileW(wchar* dir,void* p)
	{
		push p
		push dir
		calle "FindFirstFileW"
		mov s_ret,eax
	}
	
	int _beginthreadex(void* _Security,int _StackSize,
		void* start,void* _ArgList,int _InitFlag,void* addr)
	{
		push addr
		push _InitFlag
		push _ArgList
		push start
		push _StackSize
		push _Security
		calle "_beginthreadex"
		add esp,24
		mov s_ret,eax
	}
	
	WaitForSingleObject(int handle,int milliseconds)
	{
		push milliseconds
		push handle
		calle "WaitForSingleObject"
	}

	bool CloseHandle(void* handle)
	{
		push handle
		calle "CloseHandle"
		mov s_ret,eax
	}

	void* create_thr(void* start,void* param=null)
	{
		int ret=_beginthreadex(null,0,start,param,0,null)
		if(ret==0||ret==1)
			return null
		return ret.to<void*>
	}
	
	wait_thr(void* addr)
	{
		WaitForSingleObject(addr.toint,0xFFFFFFFF)
	}
	
	int cmd(rstr s)
	{
		return cmd(s.cstr)
	}

	int cmd(char* p)
	{
		push p
		calle "system"
		add esp,4
		mov s_ret,eax
	}

	srand(int param)
	{
		push param
		calle "srand"
		add esp,4
	}
	
	int8 time(void* p)
	{
		push p
		calle "_time32"
		mov s_ret,eax
		mov [ebp+(s_off s_ret+4)],edx
		add esp,4
	}
	
	srand()
	{
		srand(time(null).toint)
	}
	
	int rand()
	{
		calle "rand"
		mov s_ret,eax
	}
	
	int tick()
	{
		calle "GetTickCount"
		mov s_ret,eax
	}
	
	sleep(int a)
	{
		push a
		calle "Sleep"
	}

	print(char* p)
	{
		push p
		calle "printf"
		add esp,4
	}

	print_l(char* p,int len)
	{
		print(rstr(p,len).cstr)
	}

	int getch()
	{
		calle "_getch"
		mov s_ret,eax
	}
	
	void* getstdin()
	{
		calle "__iob_func"
		mov s_ret,eax
	}

	void* getstdout()
	{
		calle "__iob_func"
		add eax,32
		mov s_ret,eax
	}
	
	int get_argc()
	{
		sub esp,4
		calle "get_argc"
		mov s_ret,eax
		add esp,4
	}
	
	int* get_argv()
	{
		sub esp,4
		calle "get_argv"
		mov s_ret,eax
		add esp,4
	}
	
	void* get_hins()
	{
		sub esp,4
		calle "get_hins"
		mov s_ret,eax
		add esp,4
	}
	
	rbuf<rstr> get_param()
	{
		int argc=get_argc
		int* p=get_argv
		rbuf<rstr> ret
		for i=0;i<argc;i++
			ret.push(rstr((*(p+i)).to<char*>))
		return ret
	}
	
	sprintf(char* dst,char* format,int n)
	{
		push n
		push format
		push dst
		calle "sprintf"
		add esp,12
	}

	sprintf(char* dst,char* format,uint n)
	{
		push n
		push format
		push dst
		calle "sprintf"
		add esp,12
	}
	
	sprintf8(char* dst,char* format,int8 n)
	{
		lea esi,[ebp+s_off n]
		push [esi+4]
		push [esi]
		push format
		push dst
		calle "sprintf"
		add esp,16
	}

	sprintf8(char* dst,char* format,double n)
	{
		lea esi,[ebp+s_off n]
		push [esi+4]
		push [esi]
		push format
		push dst
		calle "sprintf"
		add esp,16
	}

	sscanf(char* src,char* format,void* n)
	{
		push n
		push format
		push src
		calle "sscanf"
		add esp,12
	}

	char* malloc(int size)
	{
		push size
		calle "malloc"
		add esp,4
		mov s_ret,eax
	}

	mfree(char* p)
	{
		push p
		calle "free"
		add esp,4
	}
	
	memset(char* begin,int val,int size)
	{
		push size
		push val
		push begin
		calle "memset"
		add esp,12
	}
	
	memcpy(char* dst,char* src,int size)
	{
		push size
		push src
		push dst
		calle "memcpy"
		add esp,12
	}

	strcpy(char* dst,char* src)
	{
		push src
		push dst
		calle "strcpy"
		add esp,8
	}

	int strcmp(char* a,char* b)
	{
		push b
		push a
		calle "strcmp"
		add esp,8
		mov s_ret,eax
	}

	int strlen(char* p)
	{
		push p
		calle "strlen"
		add esp,4
		mov s_ret,eax
	}

	bool is_number(char ch)
	{
		int t=ch.toint
		return t>=`0&&t<=`9
	}
	
	exit(int a)
	{
		push a
		calle "exit"
		add esp,4
	}
	
	error(char* p="")
	{
		print p
		print "\nerror\n"
		exit(0)
	}

	rstr scanl()
	{
		rstr result
		result.clear();
		char c;
		void* fp=getstdin
		while(1==rff.fread(&c,1,1,fp))
		{
			if(13==c.toint||10==c.toint)
			{
				if(0==result.count())
				{
					continue;
				}
				else
				{
					return result
				}
			}
			result+=c;
		}
		return result;
	}
	
	print(rstr& s)
	{
		print_l s.begin,s.count
	}

	print(uint a)
	{
		print rstr(a).cstr
	}

	print(int a)
	{
		print rstr(a).cstr
	}
	
	print(int8 a)
	{
		print rstr(a).cstr
	}
	
	print(double a)
	{
		print rstr(a).cstr
	}

	printl(rstr& s)
	{
		print_l s.begin,s.count
		print "\n"
	}

	printl(char* p="")
	{
		print p
		print "\n"
	}

	printl(int a)
	{
		print a
		printl
	}

	printl(uint a)
	{
		print a
		printl
	}
	
	printl(int8 a)
	{
		print a
		printl
	}
	
	printl(double a)
	{
		print a
		printl
	}

	enum
	{
		c_call_js,
		c_cp_txt,
		c_find_meta,
		c_find_func,
		c_find_dll,
		c_stdcall_func,
		c_cdecl_func,
		c_get_vclass,

		c_thr_create,
		c_thr_wait,

		c_mu_init,
		c_mu_del,
		c_mu_enter,
		c_mu_leave,

		c_execmd,
		c_srand,
		c_rand,
		c_gettick,
		c_sleep,

		c_puts,
		c_puts_l,
		c_getch,
		c_getstdin,
		c_getstdout,
		c_get_argc,
		c_get_argv,

		c_sprintf,
		c_sprintf8,
		c_sscanf,

		c_malloc,
		c_mfree,
		c_memset,
		c_memcpy,
		
		c_strcpy,
		c_strcmp,
		c_strlen,
		
		c_fopen_w,
		c_fopen,
		c_fclose,
		c_fread,
		c_fwrite,
		c_fseek,
		c_fseek8,
		c_ftell,
		c_ftell8,

		c_s_socket,
		c_s_connect,
		c_s_close,
		c_s_send,
		c_s_recv,
		c_s_bind,
		c_s_listen,
		c_s_accept,
		
		c_gbk_to_utf8,
		c_gbk_to_utf16,
		c_utf8_to_gbk,
		c_utf8_to_utf16,
		c_utf16_to_gbk,
		c_utf16_to_utf8,
		
		c_CloseHandle,
		c_MessageBoxA,
		c_itof8,
	};
}