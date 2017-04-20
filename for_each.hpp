#ifndef FOR_EACH_H
#define FOR_EACH_H
typedef unsigned int uint;

template<template<uint> class Generator, uint start, uint finish>
struct List
{
private:
	List<Generator, start + 1, finish> next;
public:
	template<typename Callback>
	void for_each (Callback callback)
	{
		typename Generator<start>::type dummy;
		callback (dummy, start);
		next.for_each (callback);
	};
};

template<template<uint> class Generator, uint start>
struct List<Generator, start, start>
{
	template<typename Callback>
	void for_each (Callback callback)
	{
		typename Generator<start>::type dummy;
		callback (dummy, start);
	};
};
#endif
