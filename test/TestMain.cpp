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



