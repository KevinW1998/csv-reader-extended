#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch.hpp>
#include <CSVReader.h>

TEST_CASE("Main Test", "[csv-reader]") {
    auto reader = CSVReader::MakeStringReader(std::string("This is a test,42,5\nHello,World"));
    auto csv_reader = CSVReader::MakeCSVReaderFromBasicString(&reader, ',');
     
    std::string test_string;
    int answer;
    double five;
    std::string world_string;

    csv_reader
        .ReadDataLine(&test_string, &answer, &five)
        .ReadDataLine(CSVReader::CSVDiscard(), CSVReader::MakeCSVValidator(&world_string, nullptr));
}

TEST_CASE("Test CSVDiscard", "[csv-reader]") {
    auto reader = CSVReader::MakeStringReader(std::string("This is a test,42"));
    auto csv_reader = CSVReader::MakeCSVReaderFromBasicString(&reader, ',');

    int num;
    csv_reader.ReadDataLine(CSVReader::CSVDiscard(), &num);
    REQUIRE(num == 42);
}

TEST_CASE("Test CSVValidator", "[csv-reader]") {
    auto reader = CSVReader::MakeStringReader(std::string("This is a test,42"));
    auto csv_reader = CSVReader::MakeCSVReaderFromBasicString(&reader, ',');

    int num;
    REQUIRE_NOTHROW(csv_reader.ReadDataLine(CSVReader::CSVDiscard(), CSVReader::MakeCSVValidator(&num, [](int* val) {return *val == 42; })));
}

TEST_CASE("Test PostProcessor", "[csv-reader]") {
    auto reader = CSVReader::MakeStringReader(std::string("This is a test,42"));
    auto csv_reader = CSVReader::MakeCSVReaderFromBasicString(&reader, ',');

    int num;
    csv_reader.ReadDataLine(CSVReader::CSVDiscard(), CSVReader::MakeCSVPostProcessor(&num, [](int& val) {val /= 2; }));
    REQUIRE(num == 21);
}

TEST_CASE("Test Optional", "[csv-reader]") {
    auto reader = CSVReader::MakeStringReader(std::string("This is a test"));
    auto csv_reader = CSVReader::MakeCSVReaderFromBasicString(&reader, ',');

    int num;
    csv_reader.ReadDataLine(CSVReader::CSVDiscard(), CSVReader::MakeCSVOptional(&num, 21));
    REQUIRE(num == 21);
}

TEST_CASE("Test Optional and Optional Empty", "[csv-reader]") {
    auto reader = CSVReader::MakeStringReader(std::string("test1|test2||test3\n"
                                                          "test1|test2||test3\n"));
    auto csv_reader = CSVReader::MakeCSVReaderFromBasicString(&reader, '|');

    std::string thirdElement;
    csv_reader.ReadDataLine(
                CSVReader::CSVDiscard(),
                CSVReader::CSVDiscard(),
                CSVReader::MakeCSVOptional(&thirdElement, "Hello")
                );

    REQUIRE(thirdElement == "");

    csv_reader.ReadDataLine(
                CSVReader::CSVDiscard(),
                CSVReader::CSVDiscard(),
                CSVReader::MakeCSVOptionalEmpty(&thirdElement, "Hello")
                );
    REQUIRE(thirdElement == "Hello");
}

TEST_CASE("Sub Reader", "[csv-reader]") {
    auto reader = CSVReader::MakeStringReader(std::string("test1|test2|test3.1,test3.2,test3.3|test4"));
    auto csv_reader = CSVReader::MakeCSVReaderFromBasicString(&reader, '|');

    std::string test32_value;
    csv_reader.ReadDataLine(
                CSVReader::CSVDiscard(),
                CSVReader::CSVDiscard(),
                CSVReader::MakeCSVSubReader(csv_reader, ',',
                                            CSVReader::CSVDiscard(),
                                            &test32_value,
                                            CSVReader::CSVDiscard()
                                            )
                );
    REQUIRE(test32_value == "test3.2");
}

TEST_CASE("Sub Reader Optional", "[csv-reader]") {
    auto reader = CSVReader::MakeStringReader(std::string("test1|test2\n"
                                                          "test1|test2|test3.1,test3.2,test3.3|test4\n"));
    auto csv_reader = CSVReader::MakeCSVReaderFromBasicString(&reader, '|');

    std::string optionalSub = "none";
    std::string optional_test4 = "none";

    auto read_step = [&]{
        csv_reader.ReadDataLine(
                    CSVReader::CSVDiscard(),
                    CSVReader::CSVDiscard(),
                    CSVReader::MakeCSVOptionalSubReader(csv_reader, ',',
                                                        CSVReader::CSVDiscard(),
                                                        &optionalSub,
                                                        CSVReader::CSVDiscard()
                                                        ),
                    CSVReader::MakeCSVOptional(&optional_test4, "none_overwrite")
                    );
    };

    read_step();
    REQUIRE(optionalSub == "none");
    REQUIRE(optional_test4 == "none_overwrite");

    read_step();
    REQUIRE(optionalSub == "test3.2");
    REQUIRE(optional_test4 == "test4");
}

TEST_CASE("Read by iteration", "[csv-reader-iteration]") {
    auto reader = CSVReader::MakeStringReader(std::string("test1|test2|test3\n"));
    auto csv_reader = CSVReader::MakeCSVReaderFromBasicString(&reader, '|');

    int index = 1;
    csv_reader.IterateDataLine([&index](const std::string& next) {
        switch(index) {
            case 1: REQUIRE(next == "test1"); break;
            case 2: REQUIRE(next == "test2"); break;
            case 3: REQUIRE(next == "test3"); break;
        }
        index++;
    });
}



