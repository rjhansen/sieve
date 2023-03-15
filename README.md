# The Sieve of Eratosthenes

The Sieve of Eratosthenes is an ancient method for finding prime numbers,
and a recent method for demonstrating the scary capabilities of compilers.
As my friend Doug Keester observed a quarter-century ago, a compiler is an
expert system for the construction of optimized Assembly code… and hardly
anyone living can take on a well-written expert system in its problem
domain.

## What makes it such a good example?

It touches on most of the important things except the network stack.
Although you can certainly run the Sieve entirely in the stack, any
non-trivial invocation requires heap allocations, checking for
out-of-memory conditions, parsing the command-line, sanity-checking
inputs, tapping into the standard math library, and so on.

That makes it a good example.  What will your compiler turn this into?
Can you improve on it?

## Reverse-engineering

For a real challenge, compile this with high optimizations, no debugging
support, strip the executable, and then feed it into your decompiler of 
choice.  You'll be amazed at what a simple two-function program can 
explode into.

## Who wrote it?

I did.  Rob Hansen, `rob@hansen.engineering`.

## What's the license?

Apache 2.0.  Share and Enjoy.