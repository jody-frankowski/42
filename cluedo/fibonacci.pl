fib(0, 0).
fib(1, 1).
fib(2, 1).

fib(X, Y) :-
	X1 is X - 1,
	X2 is X - 2,
	fib(X1, X3),
	fib(X2, X4),
	Y is X3 + X4.
