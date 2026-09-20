implement main
open core
constants
 className = "family1".
 classVersion = "$JustDate: $$Revision: $".
clauses

domains
 gender = female(); male().
class facts - familyDB
 person : (string Name, gender Gender).
 parent : (string Parent, string Person).

class predicates
 father : (string Person, string Father) nondeterm anyflow.
 clauses
 father(Person, Father) :-
 parent(Father, Person),
 person(Father, male()).

class predicates
 mother : (string Person, string Mother) nondeterm anyflow.
 clauses
 mother(Person, Mother) :-
 parent(Mother, Person),
 person(Mother, female()).

class predicates
 grandFather : (string Person, string GrandFather) nondeterm anyflow.
 clauses
 grandFather(Person, GrandFather) :-
 parent(Parent, Person),
 father(Parent, GrandFather).

class predicates
 grandMother : (string Person, string GrandMother) nondeterm anyflow.
 clauses
 grandMother(Person, GrandMother) :-
 parent(Parent, Person),
 mother(Parent, GrandMother).

class predicates
grandson : (string Person, string GrandSon) nondeterm anyflow.
clauses
grandson(Person, Grandson) :-
(grandFather(Grandson, Person) or grandMother(Grandson, Person)),
person(Grandson, male()).

class predicates
granddaughter : (string Person, string GrandDaughter) nondeterm anyflow.
clauses
granddaughter(Person, GrandDaughter) :-
(grandFather(Granddaughter, Person) or grandMother(Granddaughter, Person)),
person(Granddaughter, female()).

class predicates
 brother : (string Person, string Brother) nondeterm anyflow.
 clauses
 brother(Person, Brother) :-
 parent(Parent, Person),
 parent(Parent, Brother),
 person(Brother, male()),
 Person <> Brother.

class predicates
 sister : (string Person, string Sister) nondeterm anyflow.
 clauses
 sister(Person, Sister) :-
 parent(Parent, Person),
 parent(Parent, Sister),
 person(Sister, female()),
 Person <> Sister.

class predicates
 sibling : (string Person, string Sibling) nondeterm anyflow.
 clauses
 sibling(Person, Sibling) :-
 parent(Parent, Person),
 parent(Parent, Sibling),
 Person <> Sibling.

class predicates
 auntOrUncle : (string Person, string AuntOrUncle) nondeterm anyflow.
 clauses
 auntOrUncle(Person, AuntOrUncle) :-
 parent(Parent, Person),
 sibling(Parent, AuntOrUncle).

class predicates
 nephewOrNiece : (string Person, string NephewOrNiece) nondeterm anyflow.
 clauses
 nephewOrNiece(Person, NephewOrNiece) :-
 parent(Parent, Person),
 sibling(Parent, NephewOrNiece).

class predicates
 uncle : (string Person, string Uncle) nondeterm anyflow.
 clauses
 uncle(Person, Uncle) :-
 parent(Parent, Person),
 sibling(Parent, Uncle),
 person(Uncle, male()),
 Person <> Uncle.

class predicates
 aunt : (string Person, string Aunt) nondeterm anyflow.
 clauses
 aunt(Person, Aunt) :-
 parent(Parent, Person),
 sibling(Parent, Aunt),
 person(Aunt, female()),
 Person <> Aunt.

class predicates
 cousinBrother : (string Person, string CousinBrother) nondeterm anyflow.
 clauses
 cousinBrother(Person, CousinBrother) :-
 parent(Parent, Person),
 sibling(Parent, AuntOrUncle),
 parent(AuntOrUncle, CousinBrother),
 person(CousinBrother, male()).

class predicates
 cousinSister : (string Person, string CousinSister) nondeterm anyflow.
 clauses
 cousinSister(Person, CousinSister) :-
 parent(Parent, Person),
 sibling(Parent, AuntOrUncle),
 parent(AuntOrUncle, CousinSister),
 person(CousinSister, female()).

class predicates
 grandNephew : (string Person, string GrandNephew) nondeterm anyflow.
clauses
 grandNephew(Person, GrandNephew) :-
 sibling(Person, Sibling),
 parent(Sibling, NephewOrNiece),
 parent(NephewOrNiece, GrandNephew),
 person(GrandNephew, female()).
 class predicates
 reconsult : (string FileName).
clauses
 reconsult(FileName) :-
 retractFactDB( familyDB),
 file::consult(FileName, familyDB).
clauses
 run():-
 console::init(),
 reconsult("../fa.txt"),
 stdIO::write("\nfather test\n"),
 father(X, Y),
 stdIO::writef("% is the father of %\n", Y, X),
 fail.
 run():-
 stdIO::write("\nmother test\n"),
 mother(X, Y),
 stdIO::writef("% is the mother of %\n", Y, X),
 fail.
 run():-
 stdIO::write("\ngrandFather test\n"),
 grandFather(X, Y),
 stdIO::writef("% is the grandfather of %\n", Y, X),
 fail.
 run():-
 stdIO::write("\ngrandMother test\n"),
 grandMother(X, Y),
 stdIO::writef("% is the grandmother of %\n", Y, X),
 fail.
 run():-
 stdIO::write("\ngrandson test\n"),
 grandson(X, Y),
 stdIO::writef("% is the grandson of %\n", Y, X),
 fail.
 run():-
 stdIO::write("\ngranddaughter test\n"),
 granddaughter(X, Y),
 stdIO::writef("% is the granddaughter of %\n", Y, X),
 fail.
 run():-
 stdIO::write("\nbrother test\n"),
 brother(X, Y), stdIO::writef("% is the brother of %\n", Y, X),
 fail.
 run():-
 stdIO::write("\nsister test\n"),
 sister(X, Y), stdIO::writef("% is the sister of %\n", Y, X),
 fail.
 run():-
 stdIO::write("\nuncle test\n"),
 uncle(X, Y), stdIO::writef("% is the uncle of %\n", Y, X),
 fail.
 run():-
 stdIO::write("\naunt test\n"),
 aunt(X, Y), stdIO::writef("% is the aunt of %\n", Y, X),
 fail.
 run():-
 stdIO::write("\ncousinBrother test\n"),
 cousinBrother(X, Y), stdIO::writef("% is the cousinBrother of %\n", Y, X),
 fail.
 run():-
 stdIO::write("\ncousinSister test\n"),
 cousinSister(X, Y), stdIO::writef("% is the cousinSister of %\n", Y, X),
 fail.
 run():-
 stdIO::write("\ngrandNephew test\n"),
 grandNephew(X, Y), stdIO::writef("% is the grandNephew of %\n", Y, X),
 fail.
 run():-
 stdIO::write("End of test\n").
end implement main
goal
mainExe::run(main::run).