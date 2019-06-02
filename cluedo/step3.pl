safe([🐐]).
safe([🌿]).
safe([🐺]).
safe([🌿, 🐺]).
safe([🐺, 🌿]).
safe([]).

move_from_left(Left, Boat, Right, [X|Moves]) :-
	member(X, Left),
	X \= Boat,
	delete(Left, X, Left_Without_X),
	safe(Left_Without_X),
	move_from_right(Left_Without_X, X, [X|Right], Moves).

%% Ending predicate. When Left is empty, and there's no moves left, we're done.
move_from_right([], _, _, []).
move_from_right(Left, Boat, Right, [X|Moves]) :-
	(
		safe(Right) ->
		  X = '¯\\_(ツ)_/¯',
		  move_from_left(Left, '¯\\_(ツ)_/¯', Right, Moves)
		;
		  member(X, Right),
		  X \= Boat,
		  delete(Right, X, Right_Without_X),
		  move_from_left([X|Left], X, Right_Without_X, Moves)
	).

cross() :-
	move_from_left([🐐, 🌿, 🐺], [], [], Moves),
	writeln(Moves).
