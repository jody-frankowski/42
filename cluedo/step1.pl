femme(anne).
femme(betty).
femme(eve).
femme(julie).
femme(lisa).
femme(sylvie).
femme(valerie).

homme(gerard).
homme(herve).
homme(jacques).
homme(jean).
homme(jules).
homme(leon).
homme(loic).
homme(luc).
homme(marc).
homme(paul).

conjoint(marc, anne).
conjoint(anne, marc).

conjoint(jules, lisa).
conjoint(lisa, jules).

conjoint(loic, eve).
conjoint(eve, loic).

conjoint(luc, betty).
conjoint(betty, luc).

conjoint(leon, sylvie).
conjoint(sylvie, leon).

conjoint(julie, paul).
conjoint(paul, julie).

mari_de(MARI, FEMME) :- homme(MARI), femme(FEMME), conjoint(MARI, FEMME).
femme_de(FEMME, MARI) :- homme(MARI), femme(FEMME), conjoint(MARI, FEMME).

enfant_de(ENFANT, MERE) :- femme(MERE), femme_de(MERE, PERE), enfant_de(ENFANT, PERE).

enfant_de(jean, marc).
enfant_de(jules, marc).
enfant_de(leon, marc).

enfant_de(lisa, luc).
enfant_de(loic, luc).
enfant_de(gerard, luc).

enfant_de(jacques, jules).

enfant_de(herve, leon).
enfant_de(julie, leon).

enfant_de(paul, loic).
enfant_de(valerie, loic).

beaupere_de(BEAUPERE, GENDRE) :- homme(BEAUPERE), enfant_de(CONJOINT, BEAUPERE), conjoint(GENDRE, CONJOINT).
bellemere_de(BELLEMERE, GENDRE) :- femme(BELLEMERE), enfant_de(CONJOINT, BELLEMERE), conjoint(GENDRE, CONJOINT).
ancetre_de(VIEUX, JEUNE) :- enfant_de(JEUNE, VIEUX).
ancetre_de(VIEUX, JEUNE) :- enfant_de(Z, VIEUX), ancetre_de(Z, JEUNE).
