
mac$ @ _word ( _mword )
{
	stdcall[#$0,$1]
}

void main_c()
{
	push ebx
	push esi
	push edi
	sub esp,4
	call &main
	add esp,4
	pop edi
	pop esi
	pop ebx
}

char r_char(rstr s)
{
	return s[0]
}

D r_to<D,S>(S a)
{
	mov s_ret,a
}

D r_to_p<D>(void* a)
{
	mov s_ret,a
}

int r_ceil_div(int a,int b)
{
	if(a%b)
	{
		return a/b+1;
		
	}
	return a/b;
}

rstr r_cond(bool cond,rstr a,rstr b)
{
	if(cond)
	{
		return a
	}
	return b
}

uint r_cond(bool cond,uint a,uint b)
{
	if(cond)
	{
		return a
	}
	return b
}

int r_cond(bool cond,int a,int b)
{
	if(cond)
	{
		return a
	}
	return b
}

double r_cond(bool cond,double a,double b)
{
	if(cond)
	{
		return a
	}
	return b
}

//这里如果使用r_cond<int>并不会生成重复的函数
T r_cond<T>(bool cond,T a,T b)
{
	if(cond)
	{
		return a
	}
	return b
}

rt r_cond(bool cond,a,b)
{
	if(cond)
	{
		return a
	}
	return b
}

#ifdef _RVM
int cdecl(int count)
{
	char* name=(*(&count+1)).to<char*>
	pret=&count+count+1
	pfunc=rf.find_dll(name)
	if pfunc==null
		rf.error("cdecl error")
	pstart=&count
	
	sub esp,4
	mov ebx,count
	mov ecx,ebx
	sub ebx,1
	imul ecx,4
	mov esi,pstart
	add esi,ecx
next:
	jebxz end
	push [esi]
	sub ebx,1
	sub esi,4
	jmp next
end:
	mov ebx,count
	sub ebx,1
	push ebx
	push pfunc
	calle rf.c_cdecl_func
	mov edi,pret
	mov [edi],[esp]
	add esp,4

	mov ecx,4
	imul ecx,count
	add ecx,4
	pop ebp
	add esp,sizeof(s_local)
	reti ecx
}

int cdecl_p(int count)
{
	pfunc=(*(&count+1)).to<void*>
	pret=&count+count+1
	pstart=&count
	
	sub esp,4
	mov ebx,count
	mov ecx,ebx
	sub ebx,1
	imul ecx,4
	mov esi,pstart
	add esi,ecx
next:
	jebxz end
	push [esi]
	sub ebx,1
	sub esi,4
	jmp next
end:
	mov ebx,count
	sub ebx,1
	push ebx
	push pfunc
	calle rf.c_cdecl_func
	mov edi,pret
	mov [edi],[esp]
	add esp,4

	mov ecx,4
	imul ecx,count
	add ecx,4
	pop ebp
	add esp,sizeof(s_local)
	reti ecx
}

int stdcall(int count)
{
	char* name=(*(&count+1)).to<char*>
	pret=&count+count+1
	pfunc=rf.find_dll(name)
	if pfunc==null
		rf.error("stdcall error")
	pstart=&count
	
	sub esp,4
	mov ebx,count
	mov ecx,ebx
	sub ebx,1
	imul ecx,4
	mov esi,pstart
	add esi,ecx
next:
	jebxz end
	push [esi]
	sub ebx,1
	sub esi,4
	jmp next
end:
	mov ebx,count
	sub ebx,1
	push ebx
	push pfunc
	calle rf.c_stdcall_func
	mov edi,pret
	mov [edi],[esp]
	add esp,4

	mov ecx,4
	imul ecx,count
	add ecx,4
	pop ebp
	add esp,sizeof(s_local)
	reti ecx
}

int stdcall_p(int count)
{
	pfunc=(*(&count+1)).to<void*>
	pret=&count+count+1
	pstart=&count
	
	sub esp,4
	mov ebx,count
	mov ecx,ebx
	sub ebx,1
	imul ecx,4
	mov esi,pstart
	add esi,ecx
next:
	jebxz end
	push [esi]
	sub ebx,1
	sub esi,4
	jmp next
end:
	mov ebx,count
	sub ebx,1
	push ebx
	push pfunc
	calle rf.c_stdcall_func
	mov edi,pret
	mov [edi],[esp]
	add esp,4

	mov ecx,4
	imul ecx,count
	add ecx,4
	pop ebp
	add esp,sizeof(s_local)
	reti ecx
}
#endif

#ifdef _JIT
int stdcall(int count)
{
	count4=count*4
	char* name=(*(&count+1)).to<char*>
	pret=&count+count+1
	pfunc=rf.find_dll(name)
	if pfunc==null
		putsl(name)
		rf.error("stdcall error")
	pstart=&count
	
	mov ebx,count
	sub ebx,1
	mov ecx,count4
	mov esi,pstart
	add esi,ecx
next:
	jebxz end
	push [esi]
	sub ebx,1
	sub esi,4
	jmp next
end:
	call pfunc
	mov edi,pret
	mov [edi],eax

	mov ecx,4
	imul ecx,count
	add ecx,4
	pop ebp
	add esp,sizeof(s_local)
	mov eax,[esp]
	_reti(eax,ecx)
}
#endif

void* meta(rstr& s)
{
	return meta(s.cstr)
}

void* meta(char* s)
{
	//最好加上friend
	push s
	calle rf.c_cp_txt

	sub esp,4
	calle rf.c_find_meta
	mov s_ret,[esp]
	add esp,4
}

void* self_m(rstr& name,rstr& body)
{
	return meta(name+'{'+body+'}')
}

int _exe_code(void* f,int* p)
{
	sub esp,4
	mov ebx,p
	mov ebx,[ebx]
	mov ecx,ebx
	imul ecx,4

	mov esi,p
	add esi,ecx
next:
	jebxz end
	mov edi,esi
	push [edi]
	sub ebx,1
	sub esi,4
	jmp next
end:
	mov ebx,f
	calle rf.c_eval_txt
	mov s_ret,[esp]
	add esp,4
}

mac utf16c(a) utf16(a).cstrw

rstr utf16(rstr& s)
{
	return rcode.utf8_to_utf16(s)
}

rstr utf16(char* s)
{
	return rcode.utf8_to_utf16(rstr(s))
}

ushort byterev(ushort a)
{
	mov1 [ebp+s_off s_ret],[ebp+(s_off a+1)]
	mov1 [ebp+(s_off s_ret+1)],[ebp+s_off a]
}

rbuf<T> array<T>(int num)
{
	T* p=&num+1
	rbuf<T>* pret=p+num
	pret->rbuf<T>()
	for(i=0;i<num;i++)
	{
		pret->push(*p)
		T& temp
		mov temp,p
		T.~T(temp)
		p++
	}
	mov ecx,sizeof(T)
	imul ecx,num
	add ecx,4
	pop ebp
	add esp,sizeof(s_local)
	mov eax,[esp]
	_reti(eax,ecx)
}

//采用类似的办法可以回溯函数的调用栈，
//即可从被调用函数访问到调用函数的局部变量，
//这样的话可以实现惰性求值
_reti(int addr,int i)
{
	mov ecx,addr
	mov eax,i
	pop ebp
	add esp,16//4+8+4
	add esp,eax
#ifdef _WIN
	rn jmp ecx
#endif
#ifdef _GRUB
	rn jmp ecx
#endif
#ifdef _JIT
	jmp ecx
#endif
#ifdef _RVM
	jmp ecx
#endif
}

//推荐使用函数进行位运算，
//如果一定要使用位运算符请自行DIY位运算符和优先级
int NOT(int a)
{
	bnot a
	mov s_ret,a
}

int AND(int a,int b)
{
	band a,b
	mov s_ret,a
}

int OR(int a,int b)
{
	bor a,b
	mov s_ret,a
}

int XOR(int a,int b)
{
	bxor a,b
	mov s_ret,a
}

int SHL(int a,int b)
{
#ifdef _RVM
	bshl a,b
	mov s_ret,a
#endif
#ifdef _WIN
	mov eax,a
	mov ecx,b
	rn shl eax,cl
	mov s_ret,eax
#endif
#ifdef _GRUB
	mov eax,a
	mov ecx,b
	rn shl eax,cl
	mov s_ret,eax
#endif
#ifdef _JIT
	push b
	push a
	calle "bshl"
	mov s_ret,eax
	add esp,8
#endif
}

int SHR(int a,int b)
{
#ifdef _RVM
	bshr a,b
	mov s_ret,a
#endif
#ifdef _WIN
	mov eax,a
	mov ecx,b
	rn shr eax,cl
	mov s_ret,eax
#endif
#ifdef _GRUB
	mov eax,a
	mov ecx,b
	rn shr eax,cl
	mov s_ret,eax
#endif
#ifdef _JIT
	push b
	push a
	calle "bshr"
	mov s_ret,eax
	add esp,8
#endif
}

int SAR(int a,int b)
{
#ifdef _RVM
	bsar a,b
	mov s_ret,a
#endif
#ifdef _WIN
	mov eax,a
	mov ecx,b
	rn sar eax,cl
	mov s_ret,eax
#endif
#ifdef _GRUB
	mov eax,a
	mov ecx,b
	rn sar eax,cl
	mov s_ret,eax
#endif
#ifdef _JIT
	push b
	push a
	calle "bsar"
	mov s_ret,eax
	add esp,8
#endif
}