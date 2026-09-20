class my

predicates
    complete : (integer X) determ.
    recognition : (string X).
    rule : (integer N [out], string X, string Y [out], integer* [out]) nondeterm.
    discover : (integer*) determ.
    ask : (integer X) determ.

end class

implement my

class facts
    fact : (integer X, string Y).

clauses
    recognition(X) :-
        rule(N, X, Y, Z),
        discover(Z),
        !,
        console::write(X, " - ", Y, " по правилу ", N),
        console::nl,
        recognition(Y).
    recognition("Выбор автомобиля") :-
        console::write("К сожалению, система не смогла определить автомобиль для вас!"),
        !.
    recognition(_).
    discover([]).
    discover([X | Y]) :-
        ask(X),
        discover(Y).
    complete(X) :-
        console::nl,
        Y = console::readLine(),
        assert(fact(X, Y)),
        Y = "1".

clauses
    ask(X) :-
        fact(X, "1"),
        !.
    ask(X) :-
        fact(X, "0"),
        !,
        fail.
    ask(1) :-
        console::write("ДВС?"),
        !,
        complete(1).
    ask(2) :-
        console::write("Бензин?"),
        !,
        complete(2).
    ask(3) :-
        console::write("Гибрид?"),
        !,
        complete(3).
    ask(4) :-
        console::write("Седан?"),
        !,
        complete(4).
    ask(5) :-
        console::write("Хэтчбек?"),
        !,
        complete(5).
    ask(6) :-
        console::write("Внедорожник?"),
        !,
        complete(6).
    ask(7) :-
        console::write("Спорткар?"),
        !,
        complete(7).
    ask(8) :-
        console::write("Пикап?"),
        !,
        complete(8).
    ask(9) :-
        console::write("КПП автомат?"),
        !,
        complete(9).
    ask(10) :-
        console::write("1 электро мотор?"),
        !,
        complete(10).

clauses
    rule(1, "Выбор автомобиля", "седан, бензин, автомат, Ауди rs5", [1, 2, 4, 9]).
    rule(2, "Выбор автомобиля", "седан, бензин, механика, VW Polo", [1, 2, 4]).
    rule(3, "Выбор автомобиля", "хэтчбек, бензин, автомат, Кио Рио", [1, 2, 5, 9]).
    rule(4, "Выбор автомобиля", "хэтчбек, бензин, механика, Honda Civic", [1, 2, 5]).
    rule(5, "Выбор автомобиля", "внедорожник, бензин, автомат, Ленд Крузер 200", [1, 2, 6, 9]).
    rule(6, "Выбор автомобиля", "внедорожник, бензин, механика, УАЗ Хантер", [1, 2, 6]).
    rule(7, "Выбор автомобиля", "спорткар, бензин, Ferrari SPA", [1, 2, 7]).
    rule(8, "Выбор автомобиля", "универсал, бензин, БМВ М3", [1, 2]).

    rule(9, "Выбор автомобиля", "седан, дизель, автомат, Е200d", [1, 4, 9]).
    rule(10, "Выбор автомобиля", "седан, дизель, механика, Ситроен С4", [1, 4]).
    rule(11, "Выбор автомобиля", "хэтчбек, дизель, автомат, Ауди А3", [1, 5, 9]).
    rule(12, "Выбор автомобиля", "хэтчбек, дизель, механика, Toyota Auris", [1, 5]).
    rule(13, "Выбор автомобиля", "внедорожник, дизель, автомат, Nissan X-Trail LE", [1, 6, 9]).
    rule(14, "Выбор автомобиля", "внедорожник, дизель, механика, Renault Duster", [1, 6]).
    rule(15, "Выбор автомобиля", "универсал, дизель, Audi A4 Avant", [1]).

    rule(16, "Выбор автомобиля", "седан, гибрид, 1 электро мотор, Exeed RX", [3, 4, 10]).
    rule(17, "Выбор автомобиля", "седан, гибрид, >1 электро мотора, Exlantix ES", [3, 4]).
    rule(18, "Выбор автомобиля", "хэтчбек, гибрид, 1 электро мотор, Lexus CT200h", [3, 5, 10]).
    rule(19, "Выбор автомобиля", "хэтчбек, гибрид, >1 электро мотора, Honda Fit", [3, 5]).
    rule(20, "Выбор автомобиля", "внедорожник, гибрид, 1 электро мотор, Toyota RAV4 Hybrid", [3, 6, 10]).
    rule(21, "Выбор автомобиля", "внедорожник, гибрид, >1 электро мотора, Chery Tiggo 8 Pro E+", [3, 6]).
    rule(22, "Выбор автомобиля", "универсал, гибрид, , Volvo V60 Recharge", [3]).

    rule(23, "Выбор автомобиля", "седан, электромобиль, 1 электро мотор, Tesla Model 3 Standard Range Plus", [4, 10]).
    rule(24, "Выбор автомобиля", "седан, электромобиль, >1 электро мотора, Tesla Model S Plaid", [4]).
    rule(25, "Выбор автомобиля", "хэтчбек, электромобиль, 1 электро мотор, EVOLUTE i-PRO", [5, 10]).
    rule(26, "Выбор автомобиля", "хэтчбек, электромобиль, >1 электро мотора, Volkswagen ID.4", [5]).
    rule(27, "Выбор автомобиля", "внедорожник, электромобиль, 1 электро мотор, XPeng G6", [6, 10]).
    rule(28, "Выбор автомобиля", "внедорожник, электромобиль, >1 электро мотора, Zeekr 001", [6]).
    rule(29, "Выбор автомобиля", "пикап, электромобиль, Tesla Cybertruck", [8]).
    rule(30, "Выбор автомобиля", "универсал, электромобиль, Tesla Model S Shooting Brake", []).

end implement
goal
    console::init(),
    console::write("Это система помогает выбрать подходящий автомобиль. Отвечайте '1' или '0'."),
    console::nl,
    my::recognition("Выбор автомобиля").