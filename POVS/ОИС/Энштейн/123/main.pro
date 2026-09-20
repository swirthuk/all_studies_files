class my
predicates
    neighbors:(string, string, string*).
    member:(string, string*).
    nextto:(string, string, string*).
    einstein: ().
end class

implement my

clauses
    neighbors(X, Y, List) :- nextto(X, Y, List).
    neighbors(X, Y, List) :- nextto(Y, X, List).

    member(X, [X | _]).
    member(X, [_ | Rest]) :- member(X, Rest).

    nextto(L, R, [L, R | _]).
    nextto(L, R, [_ | Rest]) :- nextto(L, R, Rest).

    einstein() :-
        Houses = [_, _, _, _, _],

        % 1. Норвежец живёт в первом доме.
        list::nth1(1, Houses, ["norwegian", _, _]),

        % 2. Англичанин живёт в красном доме.
        list::member(["englishman", _, "red"], Houses),

        % 3. Зелёный дом находится слева от белого, рядом с ним.
        nextto([_, _, "green"], [_, _, "white"], Houses),

        % 11. Швед выращивает собак.
        list::member(["swede", "dog", _], Houses),

        % 12. Норвежец живёт рядом с синим домом.
        neighbors(["norwegian", _, _], [_, _, "blue"], Houses),

        % 13. Тот, кто выращивает лошадей, живёт в синем доме.
        list::member([_, "horse", "blue"], Houses),

        % Внимание, вопрос: у кого рыба?
        list::member([Owner, "fish", _], Houses),

        stdIO::write("Владелец рыбы: "), stdIO::write(Owner), stdIO::nl.

end implement my

goal
    my::einstein.
