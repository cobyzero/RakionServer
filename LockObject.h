#pragma once


namespace PerfLib {

	template<typename T>
	class LockObject
	{
	public:
		void LockObject<T>::Lock();
 		void LockObject<T>::Unlock();
		PerfLib::LockObject<T>::LockObject(LPCRITICAL_SECTION lpCriticalSection,char a3);
	};

}
