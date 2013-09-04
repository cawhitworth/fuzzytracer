#FuzzyTracer

Every so often, I get the urge to write yet another raytracer. This is my 2013 effort.

##Why another one?

This is pretty much entirely an intellectual exercise, it's not designed to be a useful image renderer, or a particularly fast/realistic/etc one either.

There's a couple of things I'm experimenting with here:

###C++11

Having been previously a C++ developer for a decade or so, for the last couple of years, I've been writing C#, and C++11 has emerged in that time. I thought it was worth picking it up and finding out what's new, what's good and what's not so good.

(so far: `auto` is great, as is the new `for` syntax for iterating over collections. It's also good to have `shared_ptr` in the standard library, finally.)

###Immutable classes 

One of the things that I've come to love from F# is the immutable-by-default nature of its classes; I thought I'd experiment with this in C++ and see how practical it is.

(short story: you end up violating the Rule of Three as copy-assignment is inherently a mutation; however, making all member variables and functions `const` and have functions always return new (`const`) instances, you can get pretty close. Passing things around has got a bit messy and I'm ending up with a mixture of `const Immutable&` and `std::shared_ptr<const Immutable>` depending on what I'm trying to do. Also, the Matrix class is still mutable, which makes me a little sad).

###Monte-Carlo tracing

Soft shadows, fuzzy reflections and all that other pretty stuff.

###Tests

I initially tried to get a full unit test framework up and running with the [Google C++ testing framework](https://code.google.com/p/googletest/). But I ended up going round in circles chasing compiler errors, so for the moment I'm going with `assert()`s, which makes me unhappy but at least gets me far enough to be able to write tests.