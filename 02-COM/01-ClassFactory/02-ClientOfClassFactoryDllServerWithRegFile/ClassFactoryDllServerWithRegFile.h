#pragma once
class ISum :public IUnknown
{
public:
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0;
};

class ISubstract :public IUnknown
{
public:
	virtual HRESULT __stdcall SubstractionOfTwoIntegers(int, int, int*) = 0;
};

// {738C684F-6B54-465E-9D1A-ED963C531C82}
const CLSID CLSID_SumSubstract = { 0x738c684f, 0x6b54, 0x465e, 0x9d, 0x1a, 0xed, 0x96, 0x3c, 0x53, 0x1c, 0x82 };

// {6FD7F86B-87D9-493F-A6CA-53824EC6A4A8}
const IID IID_ISum = { 0x6fd7f86b, 0x87d9, 0x493f, 0xa6, 0xca, 0x53, 0x82, 0x4e, 0xc6, 0xa4, 0xa8 };

// {3104900D-48BE-4BA8-8FB8-241E83F3295C}
const IID IID_ISubstract = { 0x3104900d, 0x48be, 0x4ba8, 0x8f, 0xb8, 0x24, 0x1e, 0x83, 0xf3, 0x29, 0x5c };
