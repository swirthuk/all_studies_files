class my

domains
    car = car(names, string BodyType, engine).
    engine = engine(string Model, string Horsepower, string Year).
    names = names(string NameCar, string ModelCar).

predicates
    run : ().
    checkCar : (car*).

end class

implement my
    open core, console

clauses
    checkCar(Cars) :-
        stdio::write("Введите название машины или модель машины или тип кузова или модель двигателя или кол-во лошадиных сил или год мотора для поиска: "),
        SearchQuery = console::readLine(),
        foreach car(names(NameCar, ModelCar), BodyType, engine(Model, Horsepower, Year)) in Cars do
            if NameCar = SearchQuery or ModelCar = SearchQuery or BodyType = SearchQuery or Model = SearchQuery or Horsepower = SearchQuery  or Year = SearchQuery then
                stdio::write("Автомобиль: ", NameCar, ", Модель автомобиля: ", ModelCar, ", Кузов: ", BodyType, ", Модель двигателя: ", Model, ", Лошадиных сил: ", Horsepower, " HP, Год: ", Year, "\n")
            end if
        end foreach.

    run() :-
        console::init(),
        Cars =
            [
                car(names("BMW", "X5"), "SUV", engine("N55", "306", "2018")),
                car(names("Audi", "Q7"), "SUV", engine("3.0 TFSI", "333", "2019")),
                car(names("Mercedes-Benz", "GLC"), "SUV", engine("M274", "245", "2017")),
                car(names("Toyota", "Camry"), "Sedan", engine("2AR-FE", "181", "2016")),
                car(names("Honda", "Accord"), "Sedan", engine("K24W", "185", "2015")),
                car(names("Ford", "Focus"), "Hatchback", engine("EcoBoost", "150", "2017")),
                car(names("Chevrolet", "Cruze"), "Hatchback", engine("LUJ", "140", "2016")),
                car(names("Volkswagen", "Golf"), "Hatchback", engine("TSI", "110", "2015")),
                car(names("Tesla", "Model S"), "Sedan", engine("Electric", "421", "2020")),
                car(names("Nissan", "Leaf"), "Hatchback", engine("Electric", "150", "2019"))
            ],
        checkCar(Cars).

end implement my

goal
    console::runUtf8(my::run).