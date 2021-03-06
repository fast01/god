
template<typename T>
class rbuf
{
public:
	T* m_p;
	int m_count;
	int m_cmax;

public:
	~rbuf<T>()
	{
		free();
	}

	rbuf<T>()
	{
		init();
	}

	rbuf<T>(int num)
	{
		init();
		alloc(num);
	}

	rbuf<T>(int num,T& a)
	{
		init();
		alloc(num);
		for(i=0;i<num;i++)
		{
			m_p[i]=a;
		}
	}

	rbuf<T>(rbuf<T>& a)
	{
		init();
		copy(a);
	}

	//如果复制指针一定要处理好等于号，不支持自己复制自己
	void operator=(rbuf<T>& a)
	{
		if(a.m_p==m_p)
		{
			return;
		}
		copy(a);
	}

	friend rbuf<T> operator+(rbuf<T>& a,rbuf<T>& b)
	{
		int total=a.count()+b.count();
		int max=rf::max(a.m_cmax,b.m_cmax);
		rbuf<T> ret;
		if(total>max)
		{
			ret.alloc_not_change(extend_num(total));
		}
		else
		{
			ret.alloc_not_change(max);
		}
		ret+=a;
		ret+=b;
		return ret;
	}

	void operator+=(rbuf<T>& a)
	{
		int total=a.count()+count();
		if(total>m_cmax)
		{
			realloc_not_change(extend_num(total));
		}
		for(int i=count();i<total;i++)
		{
			m_p[i]=a[i-count()];
		}
		m_count=total;
	}

	void operator+=(T& a)
	{
		this.push(a);
	}

	inline T& operator[](int num)
	{
		return m_p[num];
	}

	friend bool operator==(rbuf<T>& a,rbuf<T>& b)
	{
		if(a.count()!=b.count())
		{
			return false;
		}
		for(int i=0;i<a.count();++i)
		{
			if(a[i]!=b[i])
			{
				return false;
			}
		}
		return true;
	}

	friend bool operator!=(rbuf<T>& a,rbuf<T>& b)
	{
		return !(a==b);
	}

	inline void init()
	{
		m_p=null;
		m_count=0;
		m_cmax=0;
	}

	inline friend T* next(T* p)
	{
		return p+1;
	}

	inline friend T* prev(T* p)
	{
		return p-1;
	}

	inline int size()
	{
		return m_count*sizeof(T);
	}

	inline int count()
	{
		return m_count;
	}

	inline T* pos(int num)
	{
		return begin()+num;
	}

	/*inline uint pos(void* p)
	{
		return (T*)p-begin();
	}*/

	inline T* begin()
	{
		return m_p;
	}

	inline T* end()
	{
		return m_p+count();
	}

	inline T* rbegin()
	{
		if(0==m_count)
		{
			return null;
		}
		else
		{
			return m_p+count()-1;
		}
	}

	inline T* rend()
	{
		if(0==m_count)
		{
			return null;
		}
		else
		{
			return m_p-1;
		}
	}

	inline bool empty()
	{
		return 0==m_count;
	}

	inline void clear()
	{
		m_count=0;
	}

	inline friend int extend_num(int num)
	{
		return r_cond(num<16,16,num*2);
	}

	void push(T& a)
	{
		if(m_count>=m_cmax)
		{
			realloc_not_change(extend_num(m_count));
		}
		m_p[count()]=a;
		m_count++;
	}

	void pushm(int num)
	{
		T* p=&num+1
		for(i=0;i<num;i++)
		{
			this.push(*p)
			T& temp
			mov temp,p
			T.~T(temp)
			p++
		}
		mov ecx,sizeof(T)
		imul ecx,num
		add ecx,8
		pop ebp
		add esp,sizeof(s_local)
		mov eax,[esp]
		_reti(eax,ecx)
	}

	T pop()
	{
		/*if(0==m_count)
			exit(0);*/
		m_count--;
		return m_p[count()];
	}

	T pop_front()
	{
		T ret=m_p[0];
		erase(0);
		return ret;
	}

	void push_front(T& a)
	{
		insert(0,a);
	}

	T& top()
	{
		return m_p[count()-1];
	}

	T& bottom()
	{
		return m_p[0];
	}

	T get_top()
	{
		T ret;
		if(count()>0)
		{
			ret=m_p[count()-1];
		}
		return ret;
	}

	T get_bottom()
	{
		T ret;
		if(count()>0)
		{
			ret=m_p[0];
		}
		return ret;
	}

	bool erase(int num)
	{
		if(num<0||num>=count()||count()<=0)
		{
			return false;
		}
		for(int i=num;i<count()-1;++i)
		{
			*(m_p+i)=*(m_p+i+1);
		}
		m_count--;
		return true;
	}

	bool erase(int begin,int end)
	{
		if(begin>=end||end>count()||end<=0)
		{
			return false;
		}
		for(int i=0;i<count()-end;i++)
		{
			m_p[i+begin]=m_p[end+i];
		}
		m_count-=(end-begin);
		return true;
	}

	bool erase_p(T* p)
	{
		return erase(p-m_p);
	}

	bool insert(int pos,T& a)
	{
		if(pos<0||pos>count())
		{
			return false;
		}
		this.push(a);
		for(int i=count()-1;i>pos;--i)
		{
			m_p[i]=m_p[i-1];
		}
		m_p[pos]=a;
		return true;
	}

	bool insert(int pos,T* begin,T* end)
	{
		for(T* p=begin;p<end;++p)
		{
			if(!insert(pos,*p))
			{
				return false;
			}
			pos++;
		}
		return true;
	}

	bool insert(int pos,rbuf<T>& a)
	{
		if(pos<0||pos>count()||0==a.count())
		{
			return false;
		}
		if(m_cmax<m_count+a.count())
		{
			realloc_not_change(a.count()+count());
		}
		for(int i=0;i<count()-pos;i++)
		{
			m_p[a.count()+count()-1-i]=m_p[count()-1-i];
		}
		for(int i=0;i<a.count();i++)
		{
			m_p[pos+i]=a[i];
		}
		m_count+=a.count();
		return true;
	}

	bool insert_p(T* p, T& a)
	{
		return insert(p-m_p,a);
	}

	bool insert_p(T* p,T* begin,T* end)
	{
		return insert(p-m_p,begin,end);
	}

	void alloc(int num)
	{
		if(m_p!=null)
		{
			return;
		}
		if(num<=0)
		{
			init();
			return;
		}
		m_p=r_new<T>num;
		m_cmax=num;
		m_count=m_cmax;
	}

	void alloc_not_change(int num)
	{
		if(m_p!=null)
		{
			return;
		}
		if(num<=0)
		{
			init();
			return;
		}
		m_p=r_new<T>num;
		m_cmax=num;
	}

	void realloc(int num)
	{
		if(null==m_p)
		{
			alloc(num);
			return;
		}
		if(num<=0)
		{
			free();
			return;
		}
		T* p=r_new<T>num;
		int copy_size=rf::min(num,m_count);
		for(int i=0;i<copy_size;i++)
		{
			p[i]=m_p[i];
		}
		r_delete<T>m_p;
		m_p=p;
		m_cmax=num;
		m_count=m_cmax;
	}

	void realloc_not_change(int num)
	{
		if(null==m_p)
		{
			alloc_not_change(num);
			return;
		}
		if(num<=0)
		{
			free();
			return;
		}
		T* p=r_new<T>num;
		int copy_size=rf::min(num,m_count);
		for(int i=0;i<copy_size;i++)
		{
			p[i]=m_p[i];
		}
		r_delete<T>m_p;
		m_p=p;
		m_cmax=num;
	}
	
	//不复制原有的元素
	void realloc_n(int num)
	{
		if(null==m_p)
		{
			alloc(num);
			return;
		}
		if(num<=0)
		{
			free();
			return;
		}
		r_delete<T>m_p;
		m_p=r_new<T>num;
		m_cmax=num;
		m_count=m_cmax;
	}

	void realloc_n_not_change(int num)
	{
		if(null==m_p)
		{
			alloc_not_change(num);
			return;
		}
		if(num<=0)
		{
			free();
			return;
		}
		r_delete<T>m_p;
		m_p=r_new<T>num;
		m_cmax=num;
	}

	void free()
	{
		if(null==m_p)
		{
			return;
		}
		r_delete<T>m_p;
		init();
	}

	void copy(rbuf<T>& a)
	{
		if(m_cmax<a.count())
		{
			realloc_n_not_change(a.m_cmax);
		}
		for(int i=0;i<a.count();i++)
		{
			m_p[i]=a[i];
		}
		m_count=a.count();
	}

	T get(int i)
	{
		T t;
		if(i>=count()||i<0)
		{
			return t;
		}
		else 
		{
			return m_p[i];
		}
	}

	rbuf<T> sub(int begin,int end=count)
	{
		if(end>count())
		{
			end=count();
		}
		if(begin<0)
		{
			begin=0;
		}
		rbuf<T> ret;
		int temp=end-begin;
		ret.alloc(temp);
		for(int i=0;i<temp;i++)
		{
			ret[i]=m_p[begin+i];
		}
		return ret;
	}

	bool exist(T& a)
	{
		for(int i=0;i<count();i++)
		{
			if(a==m_p[i])
			{
				return true;
			}
		}
		return false;
	}

	int find(T& a,int begin=0)
	{
		for(int i=begin;i<count();i++)
		{
			if(a==m_p[i])
			{
				return i;
			}
		}
		return count();
	}
	
	void reverse()
	{
		rbuf<T> t;
		for(int i=count-1;i>=0;i--)
			t.push(m_p[i])
		this=t
	}

	int find_last(T& a)
	{
		for(int i=count-1;i>=0;i--)
		{
			if(m_p[i]==a)
			{
				return i;
			}
		}
		return count();
	}
	
	rstr join(rstr s)
	{
		rstr ret
		for i=0;i<count;i++
			if i!=0
				ret+=s
			ret+=m_p[i].torstr
		return ret
	}
	
	rbuf<T> map(void* f)
	{
		rbuf<T> ret
		for i=0;i<count;i++
			ret.push(T[f,m_p[i]])
		return ret
	}
};
