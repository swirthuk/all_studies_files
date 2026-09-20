implement main
    open core, console

class predicates
    list : (string*, string*, string*, string*) nondeterm.
    list2 : (string*, string*, string*, string*).

clauses
    list([], [], [], []).
    list([Head | Tail], T1, T2, _) :-
        list2(Tail, [Head], T1, T2),
        list(Tail, [Head], T1, T2).
    list([Head], T1, T2, _) :-
        list2([], [Head], T1, T2),
        list([], [Head], T1, T2).
    list([], T1, T2, _) :-
        list2([], [], T1, T2),
        list([], [], T1, T2).
    list([], [], T1, _) :-
        list2([], [], [], T1),
        list([], [], [], T1).
    list([], [], [], _) :-
        list2([], [], [], []),
        list([], [], [], []).
    list2(_, A, B, C) :-
        nl,
        write('Задачи ребенка: '),
        write(A),
        nl,
        write('Задачи слуги: '),
        write(B),
        nl,
        write('Задачи взрослого: '),
        write(C),
        nl.
    run() :-
        console::init(),
        list(['Поддерживать огонь', 'Подавать пирожки', 'Наливать чай', 'Читать стихи'], [], [], []),
        !,
        write("")
        or
        write("Конец.").

end implement main

goal
    console::runUtf8(main::run).