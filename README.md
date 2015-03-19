
Profiler is a software component to easier the investigation of the performance issue.
It provides some tools to report the CPU usage and call times of the profiled places.

Currently, it support Android NDK, iOS, C++, C#. And I believe it should be very easier to apply
the same/similar idea to other language and platforms.

# Usage

## iOS

```objc
-foo {
	PROFILER_HERE_OBJC;

	// ...
}
```

You will get a dump simiar as this when the **foo** is called:

```
-[foo:]: 11.704701 Hit Count: 1
-[foo:]: 81.324423 Hit Count: 2
```

## C++

```cpp
void foo()
{
	PROFILER_HERE;

	//....
}
```