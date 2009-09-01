/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#ifndef HK_DEMOFRAMEWORK_CALLABLE_H
#define HK_DEMOFRAMEWORK_CALLABLE_H

namespace CallbackUtil
{
	struct CallbackStorage
	{
		CallbackStorage(void* o, void* m, int sm) : m_invoker(HK_NULL), m_obj(o)
		{
			setMethod(m,sm);
			for( int i = 0; i < (int) HK_COUNT_OF(m_args); ++i )
			{
				m_args[i] = HK_NULL;
			}
		}

		void setMethod( void* methodPtr, int methodBytes )
		{
			HK_ASSERT(0x6959fcae, methodBytes <= (int) sizeof(m_method)); // increase the size of m_method
			HK_ASSERT(0x6959fcaf, (methodBytes % sizeof(void*)) == 0 );
			int methodCount = methodBytes / sizeof(void*);
			for( int i = 0; i < methodCount; ++i )
			{
				m_method[i] = ((void**)methodPtr)[i];
			}
			for( int i = methodCount; i < (int) HK_COUNT_OF(m_method); ++i )
			{
				m_method[i] = HK_NULL;
			}
		}

		template< typename Method >
		Method getMethod() const
		{
			return *reinterpret_cast<const Method*>(m_method);
		}

		template< typename Arg >
		Arg getArg(int i) const
		{
			return *reinterpret_cast<const Arg*>(&m_args[i]);
		}

		template< typename Arg >
		void setArg( int i, Arg a)
		{
			HK_COMPILE_TIME_ASSERT( sizeof(a) <= sizeof(void*) );
			HK_ASSERT(0x74ab1299, unsigned(i) < unsigned(HK_COUNT_OF(m_args)) );
			union { Arg a; void* v; } u;
			u.a = a;
			m_args[i] = u.v;
		}

		void* m_invoker;
		void* m_obj;
		void* m_args[1];
		void* m_method[3]; // 3 for CW
	};

	template< typename RetType, typename ObjType >
	static RetType ObjectInvoker0( const CallbackStorage& s )
	{
		ObjType* o = static_cast<ObjType*>(s.m_obj);
		typedef RetType (ObjType::*Method)();
		Method m = s.getMethod<Method>();
		return (o->*m)();
	}
	template< typename RetType, typename ObjType, typename Arg0Type >
	static RetType ObjectInvoker0Bound( const CallbackStorage& s )
	{
		ObjType* o = static_cast<ObjType*>(s.m_obj);
		typedef RetType (ObjType::*Method)(Arg0Type);
		Method m = s.getMethod<Method>();
		Arg0Type a0 = s.getArg<Arg0Type>(0);
		return (o->*m)(a0);
	}
	template< typename RetType, typename ObjType, typename Arg0Type >
	static RetType ObjectInvoker1( const CallbackStorage& s, Arg0Type a0 )
	{
		ObjType* o = static_cast<ObjType*>(s.m_obj);
		typedef RetType (ObjType::*Method)(Arg0Type);
		Method m = s.getMethod<Method>();
		return (o->*m)(a0);
	}

	template< typename RetType >
	static RetType FunctionInvoker0( const CallbackStorage& s )
	{
		typedef RetType (*Function)();
		Function f = s.getMethod<Function>();
		return (*f)();
	}
	template< typename RetType, typename Arg0Type >
	static RetType FunctionInvoker0Bound( const CallbackStorage& s )
	{
		typedef RetType (*Function)(Arg0Type);
		Function f = s.getMethod<Function>();
		Arg0Type a0 = s.getArg<Arg0Type>(0);
		return (*f)(a0);
	}
	template< typename RetType, typename Arg0Type >
	static RetType FunctionInvoker1( const CallbackStorage& s, Arg0Type a0 )
	{
		typedef RetType (*Function)(Arg0Type);
		Function f = s.getMethod<Function>();
		return (*f)(a0);
	}
}



template <typename RetType> 
class Callable0
{
	public:

		typedef RetType (*Invoker)(const CallbackUtil::CallbackStorage&);

		Callable0()
			: m_cb(HK_NULL, HK_NULL, 0)
		{
		}

		static Callable0 Function( RetType (*f)() )
		{
			CallbackUtil::CallbackStorage cb(HK_NULL, &f, sizeof(f));
			cb.m_invoker = (void*)(Invoker) &CallbackUtil::FunctionInvoker0<RetType>;
			return cb;
		}

		template< typename Arg0Type >
		static Callable0 BoundFunction( RetType (*f)(Arg0Type), Arg0Type a0 )
		{
			CallbackUtil::CallbackStorage cb(HK_NULL, &f, sizeof(f));
			cb.m_invoker = (void*)(Invoker) &CallbackUtil::FunctionInvoker0Bound<RetType, Arg0Type>;
			cb.setArg(0, a0);
			return cb;
		}

		template< typename ObjType >
		static Callable0 Method( RetType (ObjType::*m)(), ObjType* o )
		{
			CallbackUtil::CallbackStorage cb(o, &m, sizeof(m) );
			cb.m_invoker = (void*)(Invoker) &CallbackUtil::ObjectInvoker0<RetType, ObjType>;
			return cb;
		}

		template< typename ObjType, typename Arg0Type >
		static Callable0 BoundMethod( RetType (ObjType::*m)(Arg0Type), ObjType* o, Arg0Type a0 )
		{
			CallbackUtil::CallbackStorage cb(o, &m, sizeof(m) );
			cb.m_invoker = (void*)(Invoker) &CallbackUtil::ObjectInvoker0Bound<RetType, ObjType, Arg0Type>;
			cb.setArg(0, a0);
			return cb;
		}

		RetType call() const
		{
			Invoker invoker = reinterpret_cast<Invoker>(m_cb.m_invoker);
			return (*invoker)(m_cb);
		}

	private:

		Callable0( const CallbackUtil::CallbackStorage& cb ) : m_cb(cb) {}
		CallbackUtil::CallbackStorage m_cb;
};

template <typename RetType, typename Arg0Type> 
class Callable1
{
	public:

		typedef RetType (*Invoker)(const CallbackUtil::CallbackStorage&, Arg0Type a0);

		Callable1()
			: m_cb(HK_NULL, HK_NULL, 0)
		{
		}

		static Callable1 Function( RetType (*f)(Arg0Type) )
		{
			CallbackUtil::CallbackStorage cb(0, &f, sizeof(f) );
			cb.m_invoker = (void*)(Invoker) &CallbackUtil::FunctionInvoker1<RetType, Arg0Type>;
			return cb;
		}

		template< typename ObjType >
		static Callable1 Method( RetType (ObjType::*m)(Arg0Type), ObjType* o )
		{
			CallbackUtil::CallbackStorage cb(o, &m, sizeof(m));
			cb.m_invoker = (void*)(Invoker) &CallbackUtil::ObjectInvoker1<RetType, ObjType, Arg0Type>;
			return cb;
		}

		RetType call(Arg0Type a0) const
		{
			Invoker invoker = static_cast<Invoker>(m_cb.m_invoker);
			return (*invoker)(m_cb, a0);
		}

	private:

		Callable1( const CallbackUtil::CallbackStorage& cb ) : m_cb(cb) {}
		CallbackUtil::CallbackStorage m_cb;
};

#endif // HK_DEMOFRAMEWORK_CALLABLE_H

/*
* Havok SDK - NO SOURCE PC DOWNLOAD, BUILD(#20090704)
* 
* Confidential Information of Havok.  (C) Copyright 1999-2009
* Telekinesys Research Limited t/a Havok. All Rights Reserved. The Havok
* Logo, and the Havok buzzsaw logo are trademarks of Havok.  Title, ownership
* rights, and intellectual property rights in the Havok software remain in
* Havok and/or its suppliers.
* 
* Use of this software for evaluation purposes is subject to and indicates
* acceptance of the End User licence Agreement for this product. A copy of
* the license is included with this software and is also available at www.havok.com/tryhavok.
* 
*/
