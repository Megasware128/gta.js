#pragma once
#include <queue>

using namespace std;

namespace Bindings {
	struct fake_ptr
	{
		fake_ptr(void* pointer, int offset, int shift);
		void* pointer;
		int offset;
		int shift;
	};

	class Container
	{
	public:
		Container();
		~Container();

		fake_ptr* create_pointer(void* base, int offset, int shift);
	private:
		queue<fake_ptr*> pointers;
	};

	inline bool __declspec(naked) get(void* aBase, int aOffset, int shift)
	{
		_asm
		{
			enter 0, 0
			mov	eax, dword ptr[aBase]
			mov ecx, dword ptr[aOffset]
			mov	edx, dword ptr[eax + ecx]
			mov ecx, dword ptr[shift]
			shr	edx, cl
			and edx, 1
			mov	eax, edx
			leave
			ret
		}
	}

	inline void __declspec(naked) set(void* aBase, int aOffset, int shift, bool value)
	{
		_asm
		{
			enter 0, 0
			mov eax, dword ptr[value]
			and eax, 1
			mov ecx, dword ptr[shift]
			shl	eax, cl
			push eax
			mov	ecx, dword ptr[aBase]
			mov eax, dword ptr[aOffset]
			mov	edx, dword ptr[ecx + eax]
			and edx, 0FFFFFEFFh
			mov ecx, eax
			pop eax
			or edx, eax
			mov	eax, dword ptr[aBase]
			mov	dword ptr[eax + ecx], edx
			leave
			ret
		}
	}

	void Ped(JsValueRef ped, Container& container);
}