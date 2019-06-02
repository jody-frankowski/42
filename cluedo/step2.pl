:- use_module(library(lists)).

find(FishHouse) :-
	neighborhood(Houses),
	FishHouse = [_, _, _, _, poissons],
	member(FishHouse, Houses).

around_to(HOUSE1, HOUSE2, Houses) :- nextto(HOUSE1, HOUSE2, Houses).
around_to(HOUSE1, HOUSE2, Houses) :- nextto(HOUSE2, HOUSE1, Houses).

neighborhood(Houses) :-
	length(Houses, 5),

	% L'Anglais vit dans la maison rouge
	member([rouge, anglais, _, _, _], Houses),
	% Le Suédois a des chiens.
	member([_, suedois, _, _, chiens], Houses),
	% Le Danois boit du thé.
	member([_, danois, the, _, _], Houses),
	% La maison verte est à gauche de la maison blanche.
	nextto([verte, _, _, _, _], [blanche, _, _, _, _], Houses),
	% Le propriétaire de la maison verte boit du café.
	member([verte, _, cafe, _, _], Houses),
	% La personne qui fume des Pall Mall a des oiseaux.
	member([_, _, _, pall_mall, oiseaux], Houses),
	% Le propriétaire de la maison jaune fume des Dunhill.
	member([jaune, _, _, dunhill, _], Houses),
	% La personne qui vit dans la maison du centre boit du lait.
	Houses = [_, _, [_, _, lait, _, _], _, _],
	% Le Norvégien habite dans la première maison.
	Houses = [[_, norvegien, _, _, _], _, _, _, _],
	% L’homme qui fume des Blend vit à côté de celui qui a des chats.
	around_to([_, _, _, blend, _], [_, _, _, _, chats], Houses),
	% L’homme qui a un cheval est le voisin de celui qui fume des Dunhill.
	around_to([_, _, _, _, cheval], [_, _, _, dunhill, _], Houses),
	% Le propriétaire qui fume des Blue Master boit de la bière.
	member([_, _, biere, blue_master, _], Houses),
	% L’Allemand fume des prince.
	member([_, allemand, _, prince, _], Houses),
	% Le Norvégien vit juste à côté de la maison bleue.
	around_to([_, norvegien, _, _, _], [bleu, _, _, _, _], Houses),
	% L’homme qui fume des Blend a un voisin qui boit de l’eau.
	around_to([_, _, _, blend, _], [_, _, eau, _, _], Houses),
	% Question : Qui a le poisson ?
	member([_, _, _, _, poissons], Houses).
