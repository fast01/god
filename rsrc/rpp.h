import "rset.h"

struct tclass
{
	rstr name;
	rset<tmac> vmac;//宏列表
	rbuf<tdata> vdata;//数据成员列表
	rset<tfunc> vfunc;//函数成员列表
	rset<tfunc> vfunctl;//模板函数列表

	rbuf<tword> vword;
	rbuf<ttl> vtl;
	rbuf<tsent> vfather;//父类表

	int size;
	rbool is_friend;
}

struct tfunc
{
	//rbool is_js;
	rbool is_friend;
	rstr lambda_data;
	tdata retval;
	rstr name;
	rstr name_dec;//增加一个dec变量是为了提高查找效率

	rbuf<ttl> vtl;
	rbuf<tdata> param;//参数列表
	rbuf<tdata> local;//局部变量表
	
	rbuf<tword> vword;//函数内容的词表
	rbuf<tsent> vsent;//语句表
	rbuf<tasm> vasm;

	tpos first_pos;
	tpos last_pos;
	
	int8 count;
	tclass* ptci;//反射到tclass，不用初始化

	uchar* code;//jit代码段
}

//表达式和语句几乎没有区别
struct tsent
{
	tpos pos;
	rstr type;//表达式类型，也可以理解为语句返回值的类型
	rbuf<tword> vword;
}

struct tdata
{
	rstr type;
	rstr name;
	int size;//真实大小
	int count;//数组个数
	int off;//相对偏移
	rbuf<tword> param;//默认参数
}

struct tmac
{
	rstr name;
	rbuf<rstr> param;
	rbuf<rstr> vstr;
	rbool is_super;
};

struct ttl
{
	rstr name;
	rstr val;//默认值
};

struct tword
{
	tpos pos;
	rstr val;
	rbuf<rstr> multi;
	tpos pos_src;
}

struct tasm
{
	tins ins;//tins放在最前面便于把指针转换为tasm*
	rbuf<rstr> vstr;
	tpos pos;
	tfunc* ptfi;//反射到tfunc，不用初始化
	uchar* start;//jit地址
}

struct tpos
{
	void* file;
	int line;
}

struct tins
{
	int type;
	topnd first;
	topnd second;
}

struct topnd
{
	int type;
	int off;
	int val;
}

r_print_asm(tfunc& tfi)
{
	for(i=0;i<tfi.vasm.count;i++)
	{
		tfi.vasm[i].pos.line.print
		puts(' ')
		for(j=0;j<tfi.vasm[i].vstr.count;j++)
		{
			tfi.vasm[i].vstr[j].print
			puts ' '
		}
		putsl
	}
}

//语句间没有输出空格
r_print_sent(tfunc& tfi)
{
	for(i=0;i<tfi.vsent.count;i++)
	{
		tfi.vsent[i].pos.line.print
		puts(' ')
		for(j=0;j<tfi.vsent[i].vword.count;j++)
		{
			tfi.vsent[i].vword[j].val.print
			puts(' ')
		}
		putsl
	}
}

r_print_asm(rstr name)
{
	tasm* p=findf(name)
	if p==null
		return
	r_print_asm(*p->ptfi)
}

r_print_sent(rstr name)
{
	tasm* p=findf(name)
	if p==null
		return
	r_print_sent(*p->ptfi)
}

r_print_vclass()
{
	rset<tclass>* p=rf.get_vclass
	r_print_vclass(*p)
}

r_print_vclass(rset<tclass>& v)
{
	for p=v.begin;p!=v.end;p=v.next(p)
	{
		p->name.printl
	}
}

tclass* r_find_class(rstr name)
{
	rset<tclass>* q=rf.get_vclass
	rset<tclass>& v
	mov v,q
	for p=v.begin;p!=v.end;p=v.next(p)
	{
		//这里是RPP代码和C++直接交互
		//所以不要直接比较，因为RPP使用rstr.==会改变解释器的堆
		tmp=p->name
		if tmp==name
			return p
	}
	return null
}

r_print_class_f(tclass& tci)
{
	//if tci
	for p=tci.vfunc.begin;p!=tci.vfunc.end;p=tci.vfunc.next(p)
	{
		p->name.printl
	}
}