implement main
    open core, console

domains
    list = integer*.

class predicates
    intersection : (list, list, list [out]).
    member : (integer, list) determ.

clauses
    member(X, [X | _]) :-
        !.
    member(X, [_ | T]) :-
        member(X, T).

    intersection([], _, []).
    intersection([H | T1], L2, [H | T3]) :-
        member(H, L2),
        !,
        intersection(T1, L2, T3).
    intersection([_ | T1], L2, L3) :-
        intersection(T1, L2, L3).

    run() :-
        console::init(),
        List1 = [1,2,3,4,5],
        List2 = [2,3,4,6,7,8],
        intersection(List1, List2, Result),
        !,
        console::write('Список 1: '),
        console::write(List1),
        console::nl,
        console::write('Список 2: '),
        console::write(List2),
        console::nl,
        console::write('Список пересечения: '),
        console::write(Result).

end implement main

goal
    console::runUtf8(main::run).