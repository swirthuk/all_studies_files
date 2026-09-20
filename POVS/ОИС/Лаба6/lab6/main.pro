implement main
    open core, console

class predicates
    mathematical_sum : (integer, real, real [out]).
clauses
    mathematical_sum(101, A, A) :- !.
    mathematical_sum(N, A, Sum) :-
        Term = 1.0 / (N * N),
        NewA = A + Term,
        NewN = N + 1,
        mathematical_sum(NewN, NewA, Sum).

    run() :-
        console::init(),
        mathematical_sum(1, 0.0, Sum),
        console::write(Sum),
        nl.

end implement main

goal
    console::runUtf8(main::run).
