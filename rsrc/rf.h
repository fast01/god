
namespace rf
{
	mac max(a,b) r_cond(a>b,a,b)
	mac min(a,b) r_cond(a>b,b,a)
	mac abs(a) r_cond(a<0,neg a,a)
	
	//fixme未判断小于0的情况
	int round(double a)
	{
		return (a+0.5).toint
	}

	int GetStdHandle(int a)
	{
		return stdcall["GetStdHandle",a]
	}

	int SetConsoleCursorInfo(int a,void* b)
	{
		return stdcall["SetConsoleCursorInfo",a,b]
	}

	int SetConsoleTextAttribute(int a,int b)
	{
		return stdcall["SetConsoleTextAttribute",a,b]
	}

	int GetAsyncKeyState(int a)
	{
		return stdcall["GetAsyncKeyState",a]
	}

	int MessageBoxA(int a,char* b,char* c,int d)
	{
		return stdcall["MessageBoxA",a,b,c,d]
	}

	int SetConsoleCursorPosition(int a,int b)
	{
		return stdcall["SetConsoleCursorPosition",a,b]
	}
	
	int lstrlenW(wchar* p)
	{
		return cdecl["lstrlenW",p]
	}
	
	FindClose(int handle)
	{
		stdcall["FindClose",handle];
	}
	
	int FindNextFileW(int handle,void* p)
	{
		return stdcall["FindNextFileW",handle,p]
	}
	
	int FindFirstFileW(wchar* dir,void* p)
	{
		return stdcall["FindFirstFileW",dir,p]
	}

	void* find_func(rstr& s)
	{
		return find_func(s.cstr)
	}

	void* find_func(char* p)
	{
		sub esp,4
		push p
		calle c_find_func
		mov s_ret,[esp]
		add esp,4
	}

	void* find_dll(char* p)
	{
		sub esp,4
		push p
		calle c_find_dll
		mov s_ret,[esp]
		add esp,4
	}

	void* get_vclass()
	{
		sub esp,4
		calle c_get_vclass
		mov s_ret,[esp]
		add esp,4
	}

	void* create_thr(void* start,void* param=null)
	{
		sub esp,4
		push param
		push start
		calle c_thr_create,
		mov s_ret,[esp]
		add esp,4
	}
	
	wait_thr(void* addr)
	{
		push addr
		calle c_thr_wait
	}

	bool CloseHandle(void* handle)
	{
		sub esp,4
		push handle
		calle c_CloseHandle
		mov s_ret,[esp]
		add esp,4
	}
	
	int mutex_init()
	{
		sub esp,4
		calle c_mu_init
		mov s_ret,[esp]
		add esp,4
	}
	
	mutex_del(int mutex)
	{
		push mutex
		calle c_mu_del
	}
	
	mutex_enter(int mutex)
	{
		push mutex
		calle c_mu_enter
	}
	
	mutex_leave(int mutex)
	{
		push mutex
		calle c_mu_leave
	}
	
	int cmd(rstr s)
	{
		return cmd(s.cstr)
	}

	int cmd(char* p)
	{
		sub esp,4
		push p
		calle c_execmd,
		mov s_ret,[esp]
		add esp,4
	}

	srand()
	{
		calle c_srand
	}
	
	int rand()
	{
		sub esp,4
		calle c_rand
		mov s_ret,[esp]
		add esp,4
	}
	
	int tick()
	{
		sub esp,4
		calle c_gettick
		mov s_ret,[esp]
		add esp,4
	}
	
	sleep(int a)
	{
		push a
		calle c_sleep
	}

	print(char* p)
	{
		push p
		calle c_puts
	}

	print_l(char* p,int len)
	{
		push len
		push p
		calle c_puts_l
	}

	int getch()
	{
		sub esp,4
		calle c_getch
		mov s_ret,[esp]
		add esp,4
	}
	
	void* getstdin()
	{
		sub esp,4
		calle c_getstdin
		mov s_ret,[esp]
		add esp,4
	}

	void* getstdout()
	{
		sub esp,4
		calle c_getstdout
		mov s_ret,[esp]
		add esp,4
	}
	
	int get_argc()
	{
		sub esp,4
		calle rf.c_get_argc
		mov s_ret,[esp]
		add esp,4
	}
	
	int* get_argv()
	{
		sub esp,4
		calle rf.c_get_argv
		mov s_ret,[esp]
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
		calle c_sprintf
	}

	sprintf(char* dst,char* format,uint n)
	{
		push n
		push format
		push dst
		calle c_sprintf
	}
	
	sprintf8(char* dst,char* format,int8 n)
	{
		lea esi,[ebp+s_off n]
		push [esi+4]
		push [esi]
		push format
		push dst
		calle c_sprintf8
	}

	sprintf8(char* dst,char* format,double n)
	{
		lea esi,[ebp+s_off n]
		push [esi+4]
		push [esi]
		push format
		push dst
		calle c_sprintf8
	}

	sscanf(char* src,char* format,void* n)
	{
		push n
		push format
		push src
		calle c_sscanf
	}

	char* malloc(int size)
	{
		sub esp,4
		push size
		calle c_malloc
		mov s_ret,[esp]
		add esp,4
	}

	mfree(char* p)
	{
		push p
		calle c_mfree
	}
	
	memset(char* begin,int val,int size)
	{
		push size
		push val
		push begin
		calle c_memset
	}
	
	memcpy(char* dst,char* src,int size)
	{
		push size
		push src
		push dst
		calle c_memcpy
	}

	strcpy(char* dst,char* src)
	{
		push src
		push dst
		calle c_strcpy
	}

	int strcmp(char* a,char* b)
	{
		sub esp,4
		push b
		push a
		calle c_strcmp
		mov s_ret,[esp]
		add esp,4
	}

	int strlen(char* p)
	{
		sub esp,4
		push p
		calle c_strlen
		mov s_ret,[esp]
		add esp,4
	}

	bool is_number(char ch)
	{
		int t=ch.toint
		return t>=`0&&t<=`9
	}
	
	error(char* p="")
	{
		print p
		print "\nerror\n"
		halt
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

	print(var& a)
	{
		a.print
	}
	
	printl(var& a)
	{
		a.printl
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
		c_eval_txt,
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