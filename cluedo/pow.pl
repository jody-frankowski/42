power(_,0,1). % 1 est le resutat de n'importe quel nombre exposant 0.

% 	 --- Cas ou l'exposant est positif.
power(X, N, V) :-
    N > 0, X > 0, % Tant que l'exposant est superieur a 0, on appel la fonction.
    N1 is N - 1,  % Decremente l'exposant.
    power(X, N1, V1),
    V is V1 * X.  % On multiplie la valeur du resultat a chaque appel de fonction.

% 	--- Cas ou l'exposant est negatif.
power(X, N, V) :-
    N < 0, X > 0, % Tant que l'exposant n'est pas egal a 0, on appel la fonction.
    N1 is N + 1,  % Incremete l'exposant.
    power(X, N1, V1),
    V is V1 / X.  % On divise la valeur du resultat a chaque appel de fonction.
